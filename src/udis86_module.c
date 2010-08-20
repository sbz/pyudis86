/*-
 * Copyright (c) 2010, Sofian Brabez <sbz@6dev.net>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the author nor the names of any co-contributors
 *       may be used to endorse or promote products derived from this software 
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <udis86.h>
#include "udis86_module.h"

static PyMethodDef udis86_module_methods[] = {
	{"init", py_udis86_new, METH_NOARGS, ""},
	{NULL, 0, 0, NULL}
};

#define PY_CONST(x, y) PyDict_SetItemString(dict, #x, PyInt_FromLong(y))

PyMODINIT_FUNC
initudis86(void) {
	PyObject *module, *dict;

	module = Py_InitModule(PYUDIS86_MODULE_NAME, udis86_module_methods);
	dict = PyModule_GetDict(module);

	PyDict_SetItemString(dict, "__version__", 
			PyString_FromString(PYUDIS86_VERSION));

	PY_CONST(UD_SYN_INTEL, UD_MODULE_SYN_INTEL);
	PY_CONST(UD_SYN_ATT, UD_MODULE_SYN_ATT);

	PY_CONST(MOD_16, MOD_16);
	PY_CONST(MOD_32, MOD_32);
	PY_CONST(MOD_64, MOD_64);

	PY_CONST(UD_VENDOR_INTEL, UD_VENDOR_INTEL);
	PY_CONST(UD_VENDOR_AMD, UD_VENDOR_AMD);

	if (PyErr_Occurred())
		PyErr_SetString(PyExc_ImportError, "udis86: init failed");
}
