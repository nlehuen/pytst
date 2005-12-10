#include <boost/python.hpp>
using namespace boost::python;

#include <string>
#include "tst.h"

template <class S, class T, class M, class RW> class string_tst : public tst<S,T,M,RW> {
    public:
        string_tst<S,T,M,RW>(M* storage,T default_value) : tst<S,T,M,RW>(storage,default_value)
        {
        }
        
        T put(std::basic_string<S> string, T value) {
            return tst<S,T,M,RW>::put(const_cast<S*>(string.data()),string.size(),value);
        }

        T get(std::basic_string<S> string) {
            return tst<S,T,M,RW>::get(const_cast<S*>(string.data()),string.size());
        }
        
        T get_or_build(std::basic_string<S> string,filter<S,T>* factory) {
            return tst<S,T,M,RW>::get_or_build(const_cast<S*>(string.data()),string.size(),factory);
        }

        void remove(std::basic_string<S> string) {
            tst<S,T,M,RW>::remove(const_cast<S*>(string.data()),string.size());
        }

        T walk1(filter<S,T> *filter,action<S,T> *to_perform) {
            return tst<S,T,M,RW>::walk(filter,to_perform);
        }

        T walk2(filter<S,T> *filter,action<S,T> *to_perform,std::basic_string<S> string) {
            return tst<S,T,M,RW>::walk(filter,to_perform,const_cast<S*>(string.data()),string.size());
        }
        
        T close_match(std::basic_string<S> string,int maximum_distance,filter<S,T> *filter,action<S,T> *to_perform) {
            return tst<S,T,M,RW>::close_match(const_cast<S*>(string.data()),string.size(),maximum_distance,filter,to_perform);
        }
        
        T prefix_match(std::basic_string<S> string,filter<S,T> *filter,action<S,T> *to_perform) {
            return tst<S,T,M,RW>::prefix_match(const_cast<S*>(string.data()),string.size(),filter,to_perform);
        }
};

template <class S, class T> class memory_tst : public string_tst< char,T,memory_storage<S,T>,null_reader_writer<T> > {
    public:
        memory_tst<S,T>() : string_tst< S,T,memory_storage<S,T>,null_reader_writer<T> >(
            new memory_storage<S,T>(16),
            T()
        ) {
        }
};

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
            // TODO : try to use dict.get() instead of has_key / []
            std::basic_string<S> s(string,string_length);
            extract<tuple&> r(result_dict.get(s));
            if((!r.check()) || ((tuple&)r)[1] > remaining_distance) {
                result_dict[s] = make_tuple(data,remaining_distance);
            }
        }        
        
        T result() {
            return result_dict;
        }
    
    private:
        dict result_dict;
};

template <class S, class T> class NullFilter : public filter<S,T>, public wrapper< filter<S,T> > {
    public:
        T perform(S* string,int string_length,int remaining_distance,T data) {
            return data;
        }
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

    class_< NullFilter<char,object>, boost::noncopyable >("NullFilter")
    ;
}