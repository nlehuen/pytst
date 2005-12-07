#include <boost/python.hpp>
using namespace boost::python;

#include <string>
#include "tst.h"

template <class S, class T, class M, class RW> class string_tst : public tst<S,T,M,RW> {
    public:
        string_tst<S,T,M,RW>(M* storage,T default_value) : tst<S,T,M,RW>(storage,default_value)
        {
        }
        
        int put(std::basic_string<S> string, T value) {
            return tst<S,T,M,RW>::put(const_cast<S*>(string.data()),string.size(),value);
        }

        int get(std::basic_string<S> string) {
            return tst<S,T,M,RW>::get(const_cast<S*>(string.data()),string.size());
        }
        
        T walk(filter<S,T>* filter,action<S,T>* to_perform,std::basic_string<S> string) {
            return tst<S,T,M,RW>::walk(filter,to_perform,const_cast<S*>(string.data()),string.size());
        }
        
        T close_match(std::basic_string<S> string,int maximum_distance,filter<S,T>* filter,action<S,T>* to_perform) {
            return tst<S,T,M,RW>::close_match(const_cast<S*>(string.data()),string.size(),maximum_distance,filter,to_perform);
        }
        
        T prefix_match(std::basic_string<S> string,filter<S,T>* filter,action<S,T>* to_perform) {
            return tst<S,T,M,RW>::prefix_match(const_cast<S*>(string.data()),string.size(),filter,to_perform);
        }

};

template <class S, class T> class Action : public action<S,T>, wrapper< action<S,T> > {
    public:
        void perform(S* string,int string_length,int remaining_distance,T data) {
            return call<void>(this->get_override("perform").ptr());
        }
        
        T result() {
            return call<T>(this->get_override("result").ptr());
        }
};

class TST : public string_tst< char,int,memory_storage<char,int>,reader_writer<int> > {
    public:
        TST() : string_tst< char,int,memory_storage<char,int>,reader_writer<int> >(
            new memory_storage<char,int>(16),
            0
        ) {
        }
}; 

BOOST_PYTHON_MODULE(tst)
{
    class_< TST >("TST")
        .def("put",&TST::put)
        .def("get",&TST::get)
        .def("__setitem__",&TST::put)
        .def("__getitem__",&TST::get)
        .def("walk",&TST::walk)
        .def("close_match",&TST::close_match)
        .def("prefix_match",&TST::prefix_match)
    ;
    
    /*class_< Action<char,int>, boost::noncopyable >("Action")
        .def("perform", pure_virtual(&action<char,int>::perform))
        .def("result", pure_virtual(&action<char,int>::result))
    ;*/
}