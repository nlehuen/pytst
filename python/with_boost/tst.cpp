#include <boost/python.hpp>
using namespace boost::python;

#include "tst.h"

typedef memory_storage<char,int> M;
typedef ReaderWriter<int> RW;

class TST : public tst<char,int,M,RW> {
    public:
        TST() : tst<char,int,M,RW>(
            new M(16),
            0
        ) {
        }
};

class Floob {
    public:
        void set(int value) {
            foo = value;
        }
        
        int get() {
            return foo;
        }

    private:
        int foo;    
};

BOOST_PYTHON_MODULE(tst)
{
    class_<TST>("TST")
        .def("put",&TST::put)
        .def("get",&TST::get)
    ;
    class_<Floob>("Floob")
        .def("set",&Floob::set)
        .def("get",&Floob::get)
    ;
}