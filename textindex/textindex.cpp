/* 
 # $Id$
 # Copyright (C) 2004-2005 Nicolas Lehuen <nicolas@lehuen.com>
 #
 # This library is free software; you can redistribute it and/or
 # modify it under the terms of the GNU Lesser General Public
 # License as published by the Free Software Foundation; either
 # version 2.1 of the License, or (at your option) any later version.
 #
 # This library is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 # Lesser General Public License for more details.
 #
 # You should have received a copy of the GNU Lesser General Public
 # License along with this library; if not, write to the Free Software
 # Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <string>
#include <iostream>
#include <fstream>
#include <boost/python.hpp>
using namespace boost::python;

#define COMPRESS_INDEX_FILE
#ifdef COMPRESS_INDEX_FILE
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#endif

#define __PYTHON__BUILD__
#include "textindex.h"


class object_serializer {
    public:
        object_serializer();
        
        void write(std::ostream& file,object data);
        object object_serializer::read(std::istream& file);
    
    private:
        object dumps,loads;
};

object_serializer::object_serializer() {
    object cPickle(handle<>(PyImport_ImportModule("cPickle")));
    dumps = cPickle.attr("dumps");
    loads = cPickle.attr("loads");
}

void object_serializer::write(std::ostream& file,object data) {
    str result = (str)dumps(data,2);
    char *string;
    int length;
    PyString_AsStringAndSize(result.ptr(),&string,&length);
    file.write((char*)(&length),sizeof(int));
    file.write(string,length);
}

object object_serializer::read(std::istream& file) {
    int length;
    file.read((char*)(&length),sizeof(int));
    char* string=(char*)tst_malloc(length);
    file.read(string,length);
    
    str dumped(string,length);
    object result = loads(dumped);
    tst_free(string);
    return result;
}

template <typename character_type> class python_textindex : public textindex<character_type,object,object_serializer> {
    public:
        list find_word(std::basic_string<character_type> word) {
            return to_list(textindex<character_type,object,object_serializer>::find_word(word));
        }

        list find_text(std::basic_string<character_type> word,bool intersection) {
            return to_list(textindex<character_type,object,object_serializer>::find_text(word,intersection));
        }

        list __getitem__1(std::basic_string<character_type> word) {
            return to_list(textindex<character_type,object,object_serializer>::find_text(word,true));
        }

        list __getitem__2(tuple item) {
            return to_list(textindex<character_type,object,object_serializer>::find_text(extract<std::basic_string<character_type> >(item[0]),item[1]));
        }
        
        void write_to_file(str file) {
            std::ofstream out(PyString_AsString(file.ptr()),std::ofstream::binary|std::ofstream::out|std::ofstream::trunc);
            out.exceptions(std::ofstream::eofbit | std::ofstream::failbit | std::ofstream::badbit);
            #ifdef COMPRESS_INDEX_FILE
                boost::iostreams::filtering_ostream fout;
                fout.push(boost::iostreams::zlib_compressor());
                fout.push(out);
                write(fout);
                fout.strict_sync();
            #else
                write(out);
            #endif
        }
        
        void read_from_file(object file) {
            std::ifstream in(PyString_AsString(file.ptr()),std::ifstream::binary|std::ifstream::in);
            in.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);
            #ifdef COMPRESS_INDEX_FILE
                boost::iostreams::filtering_istream fin;
                fin.push(boost::iostreams::zlib_decompressor());
                fin.push(in);
                read(fin);
            #else
                read(in);
            #endif
        }

    protected:
        list to_list(result_pointer entries) {
            list result;
            for(result_pointer::element_type::iterator item(entries->begin()),end(entries->end());item!=end;++item) {
                result.append(make_tuple(item->first,item->second));
            }
            return result;
        }
};

BOOST_PYTHON_MODULE(textindex)
{
    scope().attr("TST_VERSION") = std::string(TST_VERSION)+"-Boost.Python";

    class_< python_textindex<wchar_t> >("textindex")
        .def("put_word",&python_textindex<wchar_t>::put_word)
        .def("put_text",&python_textindex<wchar_t>::put_text)
        .def("remove_document",&python_textindex<wchar_t>::remove_document)
        .def("__setitem__",&python_textindex<wchar_t>::put_text)
        .def("find_word",&python_textindex<wchar_t>::find_word)
        .def("find_text",&python_textindex<wchar_t>::find_text)
        .def("__getitem__",&python_textindex<wchar_t>::__getitem__1)
        .def("__getitem__",&python_textindex<wchar_t>::__getitem__2)
        .def("pack",&python_textindex<wchar_t>::pack)
        .def("write",&python_textindex<wchar_t>::write_to_file)
        .def("read",&python_textindex<wchar_t>::read_from_file)
    ;

    /*class_< documents_scores<std::basic_string<wchar_t> > >("documents_scores")
        .def("add_document",&documents_scores<std::basic_string<wchar_t> >::add_document)

        .def("merge_with",&documents_scores<std::basic_string<wchar_t> >::merge_with)
        .def("intersect_with",&documents_scores<std::basic_string<wchar_t> >::intersect_with)

        .def("size",&documents_scores<std::basic_string<wchar_t> >::size)
        .def("get_document",&documents_scores<std::basic_string<wchar_t> >::get_document)
        .def("get_score",&documents_scores<std::basic_string<wchar_t> >::get_score)
    ;*/
}
