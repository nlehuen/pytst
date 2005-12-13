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

#include <iostream>
#include <string>
#include "textindex.h"

template <class S, class T> class python_textindex : public textindex<S,T> {
    public:
        list find_list(std::basic_string<S> word) {
            list result;
            p_entries entries = find(word);
            p_entries::element_type::iterator s,e;
            
            for(s=entries->begin(),e=entries->end();s != e;s++) {
                result.append(make_tuple(s->first,s->second));
            }
            
            return result;
        }
};

BOOST_PYTHON_MODULE(textindex)
{
    scope().attr("TST_VERSION") = std::string(TST_VERSION)+"-Boost.Python";

    class_< python_textindex<char,object> >("textindex")
        .def("put",&python_textindex<char,object>::put)
        .def("find",&python_textindex<char,object>::find_list)
    ;
}