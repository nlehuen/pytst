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
        
        int get_or_build(std::basic_string<S> string,filter<S,T>* factory) {
            return tst<S,T,M,RW>::get_or_build(const_cast<S*>(string.data()),string.size(),factory);
        }


        void remove(std::basic_string<S> string) {
            tst<S,T,M,RW>::remove(const_cast<S*>(string.data()),string.size());
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

template <class S, class T> class string_action_wrapper : public action<S,T>, public wrapper< action<S,T> > {
    public:
        void perform(S* string,int string_length,int remaining_distance,T data) {
            return call<void,std::basic_string<S>,int,T>(
                this->get_override("perform").ptr(),
                std::basic_string<S>(string,string_length),
                remaining_distance,
                data
            );
        }
        
        T result() {
            return call<int>(this->get_override("result").ptr());
        }
        
};

template <class S, class T> class string_filter_wrapper : public filter<S,T>, public wrapper< filter<S,T> > {
    public:
        T perform(S* string,int string_length,int remaining_distance,T data) {
            return call<T,std::basic_string<S>,int,T>(
                this->get_override("perform").ptr(),
                std::basic_string<S>(string,string_length),
                remaining_distance,
                data
            );
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
        .def("__setitem__",&TST::put)
        
        .def("get",&TST::get)
        .def("__getitem__",&TST::get)
        
        .def("get_or_build",&TST::get_or_build)
        
        .def("remove",&TST::remove)

        .def("write",&TST::write)
        .def("read",&TST::read)

        .def("walk",&TST::walk)

        .def("close_match",&TST::close_match)
        .def("prefix_match",&TST::prefix_match)

        .def("pack",&TST::pack)
    ;
    
    string_action_wrapper<char,int> foobar;
    
    class_< string_action_wrapper<char,int>, boost::noncopyable >("Action")
        .def("perform", pure_virtual(&action<char,int>::perform))
        .def("result", pure_virtual(&action<char,int>::result))
    ;

    class_< string_filter_wrapper<char,int>, boost::noncopyable >("Filter")
        .def("perform", pure_virtual(&filter<char,int>::perform))
    ;
}