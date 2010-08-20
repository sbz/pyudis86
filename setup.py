#
# Copyright (c) 2010, Sofian Brabez <sbz@6dev.net>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of the author nor the names of any co-contributors
#       may be used to endorse or promote products derived from this software 
#       without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
"""
    Installation script for udis86 python binding
"""
from distutils.core import setup, Extension
import os, sys, glob

url = 'http://github.com/sbz/pyudis86/'
version = open('VERSION').read().strip()
major, minor, patch = version.split(".")

udis86_src = glob.glob('src/*.c')
udis86_dep = glob.glob('src/*.h')
udis86_lib = ['udis86']
udis86_libdir = ['/usr/lib/']
udis86_incdir = ['/usr/include/', '/usr/include/libudis86']
if 'bsd' in sys.platform[-1] or 'bsd' in os.uname()[0].lower():
    udis86_incdir = ['/usr/include/', '/usr/include/libudis86']
    udis86_libdir = ['/usr/local/lib/']
udis86_compile_args = ['-ggdb']

udis86 = Extension(
    'udis86',
    define_macros = [
        ('MAJOR_VERSION', major),
        ('MINOR_VERSION', minor),
        ('PATCH_VERSION', patch)
    ],
    sources = udis86_src,
    depends = udis86_dep,
    include_dirs = udis86_incdir,
    library_dirs = udis86_libdir,
    libraries = udis86_lib,
    extra_compile_args = udis86_compile_args
)

setup(
    name = 'pyudis86',
    version = version,
    description = "udis86 python binding",
    author = "Sofian Brabez",
    author_email = "sbz@6dev.net",
    url = url,
    download_url = '%s/download/pyudis86-%s.tar.gz' % (url, version),
    license = 'BSD',
    platforms = ['Linux', 'BSD'],
    classifiers = [],
    ext_modules = [udis86]
)
