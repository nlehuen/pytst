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
import distutils
from distutils.core import setup, Extension

# patch distutils if it can't cope with the "classifiers" or
# "download_url" keywords
import sys
if sys.version < '2.2.3':
    from distutils.dist import DistributionMetadata
    DistributionMetadata.classifiers = None
    DistributionMetadata.download_url = None

if sys.platform=="win32":
	extra_compile_args = '/Zp1 /Og /Ob2 /Oi /Ot /GS'.split()
else:
	extra_compile_args = []

setup(
    name = "pytst",
    version = "0.70",
    author = "Nicolas Lehuen",
    author_email = "nicolas@lehuen.com",
    url = "http://nicolas.lehuen.com/",
    description = "An implementation of a Ternary Search Tree (TST) in C++ with Python bindings",
    py_modules = ["tst"],
    ext_modules = [
        Extension(
            "_tst",
            ["tst_wrap.cxx"],
            include_dirs=['..','include'],
            extra_compile_args = extra_compile_args,
        ),
    ],
    download_url = "http://nicolas.lehuen.com/download/",
    classifiers = [
        'Development Status :: 4 - Beta',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: GNU Library or Lesser General Public License (LGPL)',
        'Programming Language :: C++',
        'Programming Language :: Python',
        'Topic :: Software Development :: Libraries :: Python Modules',
        'Topic :: Scientific/Engineering :: Information Analysis',
    ]
)
