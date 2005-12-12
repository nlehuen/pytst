/* 
 # $Id: tst.h 1488 2005-12-07 14:06:02Z nlehuen $
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
            if(!r || (r[1] > remaining_distance) ) {
                result_dict[s] = make_tuple(data,remaining_distance);
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

BOOST_PYTHON_MODULE(tst)
{
    filter<char,object> *test = new NullFilter<char,object>;
    action<char,object> *test2 = new NullAction<char,object>;

    scope().attr("TST_VERSION") = std::string(TST_VERSION)+"-Boost.Python";

    class_< memory_tst<char,object> >("TST")
        .def("put",&memory_tst<char,object>::put)
        .def("__setitem__",&memory_tst<char,object>::put)
        
        .def("get",&memory_tst<char,object>::get)
        .def("__getitem__",&memory_tst<char,object>::get)
        
        .def("get_or_build",&memory_tst<char,object>::get_or_build)
        
        .def("remove",&memory_tst<char,object>::remove)

        .def("write",&memory_tst<char,object>::write)
        .def("read",&memory_tst<char,object>::read)

        .def("walk",&memory_tst<char,object>::walk1)
        .def("walk",&memory_tst<char,object>::walk2)

        .def("close_match",&memory_tst<char,object>::close_match)
        .def("prefix_match",&memory_tst<char,object>::prefix_match)

        .def("pack",&memory_tst<char,object>::pack)
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