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

#include <boost/python.hpp>
using namespace boost::python;

#define SCANNER

#include <string>
#include <iostream>
#include <fstream>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include "tst.h"

/********************* ACTION & FILTER ***********************************/

template <class S, class T, class string_type>
class NullAction : public tst_action<S,T,string_type>, public wrapper< tst_action<S,T,string_type> > {
    public:
        void perform(const typename string_type & string,int remaining_distance,T data) {
        }
        
        T result() {
            return T();
        }
        
};

template <class S,class T, class string_type>
class DictAction : public tst_action<S,T,string_type>, public wrapper< tst_action<S,T,string_type> > {
    public:
        void perform(const typename string_type & string,int remaining_distance,T data) {
            object r = result_dict.get(string);
            if(!r || (r[0] > remaining_distance) ) {
                result_dict[string] = make_tuple(remaining_distance,data);
            }
        }        
        
        T result() {
            return result_dict;
        }
    
    private:
        dict result_dict;
};

template <class S,class T, class string_type>
class TupleListAction : public tst_action<S,T,string_type>, public wrapper< tst_action<S,T,string_type> > {
    public:
        void perform(const typename string_type & string,int remaining_distance,T data) {
            result_list.append(make_tuple(string,remaining_distance,data));
        }        
        
        T result() {
            return result_list;
        }
    
    private:
        list result_list;
};

template <class S,class T, class string_type>
class ListAction : public tst_action<S,T,string_type>, public wrapper< tst_action<S,T,string_type> > {
    public:
        void perform(const typename string_type & string,int remaining_distance,T data) {
            result_list.append(data);
        }        
        
        T result() {
            return result_list;
        }
    
    private:
        list result_list;
};

template <class S,class T, class string_type>
class CallableAction : public tst_action<S,T,string_type>, public wrapper< tst_action<S,T,string_type> > {
    public:
        CallableAction(object perform, object result) :
            _perform(perform),
            _result(result) {
        }
    
        void perform(const typename string_type & string,int remaining_distance,T data) {
            _perform(
                string,
                remaining_distance,
                data
            );
        }        
        
        T result() {
            return call<T>(
                _result.ptr()
            );
        }
    
    private:
        object _perform;
        object _result;
};

template <class S, class T, class string_type>
class NullFilter : public filter<S,T,string_type>, public wrapper< filter<S,T,string_type> > {
    public:
        T perform(const typename string_type & string,int remaining_distance,T data) {
            return data;
        }
};

template <class S,class T, class string_type>
class CallableFilter : public filter<S,T,string_type>, public wrapper< filter<S,T,string_type> > {
    public:
        CallableFilter(object perform) :
            _perform(perform) {
        }
    
        T perform(const typename string_type & string,int remaining_distance,T data) {
        	return _perform(string,remaining_distance,data);
        }        
    
    private:
        object _perform;
};

/********************* SERIALIZER ***********************************/

class ObjectSerializer {
    public:
        ObjectSerializer();
        
        void write(std::ostream& file,object data);
        object ObjectSerializer::read(std::istream& file);
    
    private:
        object dumps,loads;
};

ObjectSerializer::ObjectSerializer() {
    object cPickle(handle<>(PyImport_ImportModule("cPickle")));
    dumps = cPickle.attr("dumps");
    loads = cPickle.attr("loads");
}

void ObjectSerializer::write(std::ostream& file,object data) {
    str result = (str)dumps(data,2);
    char *string;
    int length;
    PyString_AsStringAndSize(result.ptr(),&string,&length);
    file.write((char*)(&length),sizeof(int));
    file.write(string,length);
}

object ObjectSerializer::read(std::istream& file) {
    int length;
    file.read((char*)(&length),sizeof(int));
    char* string=(char*)tst_malloc(length);
    file.read(string,length);
    
    str dumped(string,length);
    object result = loads(dumped);
    tst_free(string);
    return result;
}

/********************* ITERATOR ***********************************/

class TST;

template <typename iterator_type>
class TSTIterator {
    private:
        friend class TST;
        
    public:
        TSTIterator copy() {
            return *this;
        }
    
        tuple next() {
            iterator_type::value_type v = iterator.next();
            if(v.second) {
                return make_tuple(v.first,*(v.second));
            } else {
                object exception(handle<>(
                    PyImport_ImportModule("exceptions"))
                );
                exception = exception.attr("StopIteration");
                PyErr_SetNone(exception.ptr());
                throw_error_already_set();
                
                // ( this is never called, it's just to remove the warning )
                return make_tuple();
            }
        }
    
    private:
        TSTIterator(iterator_type i) : iterator(i) {
        }
        
        iterator_type iterator;
};

typedef lexical_iterator<char,object,memory_storage<char,object>,ObjectSerializer,std::basic_string<char> > lexical_iterator_type;
typedef match_iterator<char,object,memory_storage<char,object>,ObjectSerializer,std::basic_string<char> > close_match_iterator_type;
typedef TSTIterator<lexical_iterator_type> TSTLexicalIterator;
typedef TSTIterator<close_match_iterator_type> TSTCloseMatchIterator;

/********************* TST ***********************************/

class TST : public tst<char,object,memory_storage<char,object>,ObjectSerializer,std::basic_string<char> > {
    public:
        TST() : tst<char,object,memory_storage<char,object>,ObjectSerializer,std::basic_string<char> >() {
        }
    
        void write_to_file(str file) const {
            std::ofstream out(PyString_AsString(file.ptr()),std::ofstream::binary|std::ofstream::out|std::ofstream::trunc);
            out.exceptions(std::ofstream::eofbit | std::ofstream::failbit | std::ofstream::badbit);
            boost::iostreams::filtering_ostream fout;
            fout.push(boost::iostreams::zlib_compressor());
            fout.push(out);
            this->write(fout);
            fout.strict_sync();
            // out.close();
        }
    
        void read_from_file(str file) {
            std::ifstream in(PyString_AsString(file.ptr()),std::ifstream::binary|std::ifstream::in);
            in.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);
            boost::iostreams::filtering_istream fin;
            fin.push(boost::iostreams::zlib_decompressor());
            fin.push(in);
            this->read(fin);
            // in.close();
        }

        object walk1(filter<char,object,std::basic_string<char> >* filter,tst_action<char,object,std::basic_string<char> >* to_perform) const {
            return walk(filter,to_perform);
        }
        
        object walk2(filter<char,object,std::basic_string<char> >* filter,tst_action<char,object,std::basic_string<char> >* to_perform,const std::basic_string<char>& string) const {
            return walk(filter,to_perform,string);
        }


        TSTLexicalIterator iterator1() {
            return TSTLexicalIterator(tst<char,object,memory_storage<char,object>,ObjectSerializer,std::basic_string<char> >::iterator());
        }
        
        TSTLexicalIterator iterator2(std::basic_string<char> s) {
            return TSTLexicalIterator(tst<char,object,memory_storage<char,object>,ObjectSerializer,std::basic_string<char> >::iterator(s));
        }
        
        TSTCloseMatchIterator close_match_iterator(std::basic_string<char> s, int distance) {
            return TSTCloseMatchIterator(tst<char,object,memory_storage<char,object>,ObjectSerializer,std::basic_string<char> >::close_match_iterator(s,distance));
        }
};

BOOST_PYTHON_MODULE(tst)
{
    scope().attr("TST_VERSION") = std::string(TST_VERSION)+"-Boost.Python";

    class_< TSTLexicalIterator >("TSTLexicalIterator",no_init)
        .def("__iter__",&TSTLexicalIterator::copy)
        .def("copy",&TSTLexicalIterator::copy)
        .def("next",&TSTLexicalIterator::next)
    ;

    class_< TSTCloseMatchIterator >("TSTCloseMatchIterator",no_init)
        .def("__iter__",&TSTCloseMatchIterator::copy)
        .def("copy",&TSTCloseMatchIterator::copy)
        .def("next",&TSTCloseMatchIterator::next)
    ;

    class_< TST >("TST")
        .def("put",&TST::put)
        .def("__setitem__",&TST::put)
        
        .def("get",&TST::get)
        .def("__getitem__",&TST::get)
        
        .def("__delitem__",&TST::remove)
        
        .def("contains",&TST::contains)
        .def("__contains__",&TST::contains)

        .def("get_or_build",&TST::get_or_build)
        
        .def("get_number_of_nodes",&TST::get_number_of_nodes)

        .def("remove",&TST::remove)

        .def("scan",&TST::scan)
        .def("scan_with_stop_chars",&TST::scan_with_stop_chars)

        .def("write_to_file",&TST::write_to_file)
        .def("read_from_file",&TST::read_from_file)

        .def("walk",&TST::walk1)
        .def("walk",&TST::walk2)

        .def("close_match",&TST::close_match)
        .def("prefix_match",&TST::prefix_match)
        .def("match",&TST::match)

        .def("pack",&TST::pack)

        .def("__iter__",&TST::iterator1)
        .def("iterator",&TST::iterator1)
        .def("iterator",&TST::iterator2)
        .def("close_match_iterator",&TST::close_match_iterator)
    ;
    
    class_< Nulltst_action<char,object,std::basic_string<char> >, boost::noncopyable >("NullAction")
    ;

    class_< Dicttst_action<char,object,std::basic_string<char> >, boost::noncopyable >("DictAction")
        .def("result", &Dicttst_action<char,object,std::basic_string<char> >::result)
    ;

    class_< TupleListtst_action<char,object,std::basic_string<char> >, boost::noncopyable >("TupleListAction")
        .def("result", &TupleListtst_action<char,object,std::basic_string<char> >::result)
    ;

    class_< Listtst_action<char,object,std::basic_string<char> >, boost::noncopyable >("ListAction")
        .def("result", &Listtst_action<char,object,std::basic_string<char> >::result)
    ;

    class_< Callabletst_action<char,object,std::basic_string<char> >, boost::noncopyable >("CallableAction",init<object,object>())
        .def("result", &Callabletst_action<char,object,std::basic_string<char> >::result)
    ;

    class_< NullFilter<char,object,std::basic_string<char> >, boost::noncopyable >("NullFilter")
    ;

    class_< CallableFilter<char,object,std::basic_string<char> >, boost::noncopyable >("CallableFilter",init<object>())
    ;
}
