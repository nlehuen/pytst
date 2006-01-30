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

template <class character_type, class document_type> class python_textindex : public textindex<character_type,document_type> {
    public:
        list find_word(std::basic_string<character_type> word) {
            return to_list(textindex<character_type,document_type>::find_word(word));
        }

        list find_text(std::basic_string<character_type> word,bool intersection) {
            return to_list(textindex<character_type,document_type>::find_text(word,intersection));
        }

        list __getitem__1(std::basic_string<character_type> word) {
            return to_list(textindex<character_type,document_type>::find_text(word,true));
        }

        list __getitem__2(tuple item) {
            return to_list(textindex<character_type,document_type>::find_text(extract<std::basic_string<character_type> >(item[0]),item[1]));
        }

protected:
        list to_list(documents_score_pointer entries) {
            list result;
            for(documents_score_pointer::element_type::iterator s(entries->begin()),e(entries->end());s != e;s++) {
                result.append(make_tuple(s->first,s->second));
            }
            return result;
        }
};

BOOST_PYTHON_MODULE(textindex)
{
    scope().attr("TST_VERSION") = std::string(TST_VERSION)+"-Boost.Python";

    class_< python_textindex<wchar_t,object> >("textindex")
        .def("put_word",&python_textindex<wchar_t,object>::put_word)
        .def("put_text",&python_textindex<wchar_t,object>::put_text)
        .def("__setitem__",&python_textindex<wchar_t,object>::put_text)
        .def("find_word",&python_textindex<wchar_t,object>::find_word)
        .def("find_text",&python_textindex<wchar_t,object>::find_text)
        .def("__getitem__",&python_textindex<wchar_t,object>::__getitem__1)
        .def("__getitem__",&python_textindex<wchar_t,object>::__getitem__2)
        .def("pack",&python_textindex<wchar_t,object>::pack)
    ;
}
