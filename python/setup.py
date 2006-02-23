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
import ez_setup
ez_setup.use_setuptools()

from setuptools import setup, find_packages, Extension
import sys

extra_compile_args = []
if sys.platform == "win32" and sys.version >= '2.4':
	extra_compile_args = '/Zp1 /Og /Ob2 /Oi /Ot /GS'.split()

setup(
    name = "pytst",
    version = "1.07",
    author = "Nicolas Lehuen",
    author_email = "nicolas@lehuen.com",
    url = "http://nicolas.lehuen.com/",
    description = "An implementation of a Ternary Search Tree (TST) in C++ with Python bindings",
    py_modules = ["tst"],
    ext_modules = [
        Extension(
            "_tst",
            ["tst_wrap.cxx"],
            include_dirs=['include'],
            extra_compile_args = extra_compile_args,
            define_macros=[('SCANNER', None),],
        )
    ],
    download_url = "http://nicolas.lehuen.com/download/",
    classifiers = [
        'Development Status :: 5 - Production/Stable',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: GNU Library or Lesser General Public License (LGPL)',
        'Programming Language :: C++',
        'Programming Language :: Python',
        'Topic :: Software Development :: Libraries :: Python Modules',
        'Topic :: Scientific/Engineering :: Information Analysis',
    ]
)
