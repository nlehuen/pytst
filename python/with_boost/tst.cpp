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
#include "tst.h"

/********************* PYTHON SPECIFIC CODE ***********************************/

template <class S, class T> class NullAction : public action<S,T>, public wrapper< action<S,T> > {
    public:
        void perform(S* string,int string_length,int remaining_distance,T data) {
        }
        
        T result() {
            return T();
        }
        
};

template <class S,class T> class DictAction : public action<S,T>, public wrapper< action<S,T> > {
    public:
        void perform(S* string,int string_length,int remaining_distance,T data) {
            std::basic_string<S> s(string,string_length);
            object r = result_dict.get(s);
            if(!r || (r[0] > remaining_distance) ) {
                result_dict[s] = make_tuple(remaining_distance,data);
            }
        }        
        
        T result() {
            return result_dict;
        }
    
    private:
        dict result_dict;
};

template <class S,class T> class TupleListAction : public action<S,T>, public wrapper< action<S,T> > {
    public:
        void perform(S* string,int string_length,int remaining_distance,T data) {
            std::basic_string<S> s(string,string_length);
            result_list.append(make_tuple(s,remaining_distance,data));
        }        
        
        T result() {
            return result_list;
        }
    
    private:
        list result_list;
};

template <class S,class T> class ListAction : public action<S,T>, public wrapper< action<S,T> > {
    public:
        void perform(S* string,int string_length,int remaining_distance,T data) {
            std::basic_string<S> s(string,string_length);
            result_list.append(data);
        }        
        
        T result() {
            return result_list;
        }
    
    private:
        list result_list;
};

template <class S,class T> class CallableAction : public action<S,T>, public wrapper< action<S,T> > {
    public:
        CallableAction<S,T>(object perform, object result) :
            _perform(perform),
            _result(result) {
        }
    
        void perform(S* string,int string_length,int remaining_distance,T data) {
            std::basic_string<S> s(string,string_length);
            call<void,std::basic_string<S>,int,T>(
                _perform.ptr(),
                s,
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

template <class S, class T> class NullFilter : public filter<S,T>, public wrapper< filter<S,T> > {
    public:
        T perform(S* string,int string_length,int remaining_distance,T data) {
            return data;
        }
};

template <class S,class T> class CallableFilter : public filter<S,T>, public wrapper< filter<S,T> > {
    public:
        CallableFilter<S,T>(object perform) :
            _perform(perform) {
        }
    
        T perform(S* string,int string_length,int remaining_distance,T data) {
            std::basic_string<S> s(string,string_length);
            return call<T,std::basic_string<S>,int,T>(
                _perform.ptr(),
                s,
                remaining_distance,
                data
            );
        }        
    
    private:
        object _perform;
};

class ObjectSerializer {
    public:
        ObjectSerializer();
        
        void write(FILE* file,object data);
        object ObjectSerializer::read(FILE* file);
    
        void write_to_file(object file,object data);
        object ObjectSerializer::read_from_file(object file);
    
    private:
        object dumps,loads;
};

ObjectSerializer::ObjectSerializer() {
    object cPickle(handle<>(PyImport_Import(str("cPickle").ptr())));
    dumps = cPickle.attr("dumps");
    loads = cPickle.attr("loads");
}

void ObjectSerializer::write(FILE* file,object data) {
    str result = (str)dumps(data,2);
    char *string;
    int length;
    PyString_AsStringAndSize(result.ptr(),&string,&length);
    fwrite(&length,sizeof(int),1,file);
    fwrite(string,sizeof(char),length,file);
}

void ObjectSerializer::write_to_file(object file,object data) {
    return write(PyFile_AsFile(file.ptr()),data);
}

object ObjectSerializer::read(FILE* file) {
    int length;
    fread(&length,sizeof(int),1,file);
    char* string=(char*)tst_malloc(length);
    fread(string,sizeof(char),length,file);
    
    str dumped(string,length);
    object result = loads(dumped);
    tst_free(string);
    return result;
}

object ObjectSerializer::read_from_file(object file) {
    return read(PyFile_AsFile(file.ptr()));
}

class TST : public string_tst<char,object,memory_storage<char,object>,ObjectSerializer> {
    public:
        TST() : string_tst<char,object,memory_storage<char,object>,ObjectSerializer>(new memory_storage<char,object>(16),object()) {
        }
    
        void write_to_file(object file) {
            this->write(PyFile_AsFile(file.ptr()));
        }
    
        void read_from_file(object file) {
            this->read(PyFile_AsFile(file.ptr()));
        }
};

BOOST_PYTHON_MODULE(tst)
{
    filter<char,object> *test = new NullFilter<char,object>;
    action<char,object> *test2 = new NullAction<char,object>;

    scope().attr("TST_VERSION") = std::string(TST_VERSION)+"-Boost.Python";

    class_< TST >("TST")
        .def("put",&TST::put)
        .def("__setitem__",&TST::put)
        
        .def("get",&TST::get)
        .def("__getitem__",&TST::get)
        
        .def("__delitem__",&TST::remove)
        
        .def("contains",&TST::contains)
        .def("__contains__",&TST::contains)

        .def("get_or_build",&TST::get_or_build)
        
        .def("get_maximum_key_length",&TST::get_maximum_key_length)
        
        .def("remove",&TST::remove)

        .def("scan",&TST::scan)
        .def("scan_with_stop_chars",&TST::scan_with_stop_chars)

        .def("write_to_file",&TST::write_to_file)
        .def("read_from_file",&TST::read_from_file)

        .def("walk",&TST::walk1)
        .def("walk",&TST::walk2)

        .def("close_match",&TST::close_match)
        .def("prefix_match",&TST::prefix_match)

        .def("pack",&TST::pack)
    ;
    
    class_< NullAction<char,object>, boost::noncopyable >("NullAction")
    ;

    class_< DictAction<char,object>, boost::noncopyable >("DictAction")
        .def("result", &DictAction<char,object>::result)
    ;

    class_< TupleListAction<char,object>, boost::noncopyable >("TupleListAction")
        .def("result", &TupleListAction<char,object>::result)
    ;

    class_< ListAction<char,object>, boost::noncopyable >("ListAction")
        .def("result", &ListAction<char,object>::result)
    ;

    class_< CallableAction<char,object>, boost::noncopyable >("CallableAction",init<object,object>())
        .def("result", &CallableAction<char,object>::result)
    ;

    class_< NullFilter<char,object>, boost::noncopyable >("NullFilter")
    ;

    class_< CallableFilter<char,object>, boost::noncopyable >("CallableFilter",init<object>())
    ;
}
