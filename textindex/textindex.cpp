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

#include <boost/python.hpp>
using namespace boost::python;

#define __PYTHON__BUILD__
#include "textindex.h"

template <class S, class T> class python_textindex : public textindex<S,T> {
    public:
        list find_word(std::basic_string<S> word) {
            return to_list(textindex<S,T>::find_word(word));
        }

        list find_text(std::basic_string<S> word,bool intersection) {
            return to_list(textindex<S,T>::find_text(word,intersection));
        }

protected:
        list to_list(p_entries entries) {
            list result;
            for(p_entries::element_type::iterator s(entries->begin()),e(entries->end());s != e;s++) {
                result.append(make_tuple(s->first,s->second));
            }
            return result;
        }
};

BOOST_PYTHON_MODULE(textindex)
{
    scope().attr("TST_VERSION") = std::string(TST_VERSION)+"-Boost.Python";

    class_< python_textindex<char,object> >("textindex")
        .def("put_word",&python_textindex<char,object>::put_word)
        .def("put_text",&python_textindex<char,object>::put_text)
        .def("find_word",&python_textindex<char,object>::find_word)
        .def("find_text",&python_textindex<char,object>::find_text)
        .def("pack",&python_textindex<char,object>::pack)
    ;
}