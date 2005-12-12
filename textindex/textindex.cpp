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
#include "textindex.h"

BOOST_PYTHON_MODULE(textindex)
{
    scope().attr("TST_VERSION") = std::string(TST_VERSION)+"-Boost.Python";

    class_< textindex<char,object> >("textindex")
    ;
}