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
#include <Python.h>
#include "udis86_module.h"
#include "pyudis86.h"

PyTypeObject py_udis86_t = {
    PyObject_HEAD_INIT(&PyType_Type)
    0, /* ob_size */
    "Udis86", /* tp_name */
    sizeof(py_udis86), /* tp_basicsize */
    0, /* tp_itemsize */
    (destructor)py_udis86_dealloc, /* tp_dealloc */
    0, /* tp_print */
    (getattrfunc)py_udis86_getattr, /* tp_getattr */
    0, /* tp_setattr */
    0, /* tp_compare */
    0, /* tp_repr */
    0, /* tp_as_number */
    0, /* tp_as_sequence */
    0, /* tp_as_mapping */
    0, /* tp_hash */
    0, /* tp_call */
    0, /* tp_str */
    0, /* tp_getattro */
    0, /* tp_setattro */
    0, /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT, /* tp_flags */
    "Udis86 object", /* tp_doc */
};

PyObject *
py_udis86_new(PyObject *self, PyObject *args) {
	ud_t *udobject = NULL;
	py_udis86 *ud = NULL;

	ud = PyObject_New(py_udis86, &py_udis86_t);
	
	udobject = malloc(sizeof(ud_t));
	ud->udobject = udobject;

	ud_init(ud->udobject);

	return (PyObject *)ud;
}

static void
py_udis86_dealloc(PyObject *self, PyObject *args) {

	PyObject_Del(self);
}

static PyObject *
py_udis86_disassemble(PyObject *self, PyObject *args) {
	int rc;

	rc=ud_disassemble(UDIS86_OBJ(self));

	return Py_BuildValue("i", rc);
}

static PyObject *
py_udis86_insn_asm(PyObject *self, PyObject *args) {
	return Py_BuildValue("s", ud_insn_asm(UDIS86_OBJ(self)));
}

static PyObject *
py_udis86_insn_hex(PyObject *self, PyObject *args) {
	return Py_BuildValue("s", ud_insn_hex(UDIS86_OBJ(self)));
}

static PyObject *
py_udis86_insn_off(PyObject *self, PyObject *args) {
	return Py_BuildValue("l", ud_insn_off(UDIS86_OBJ(self)));
}

static PyObject *
py_udis86_insn_len(PyObject *self, PyObject *args) {
	return Py_BuildValue("i", ud_insn_len(UDIS86_OBJ(self)));
}

static PyObject *
py_udis86_insn_ptr(PyObject *self, PyObject *args) {
	return Py_BuildValue("i", ud_insn_ptr(UDIS86_OBJ(self)));
}

static PyObject *
py_udis86_set_input_buffer(PyObject *self, PyObject *args) {
	char *buffer;
	int size;

	if (!PyArg_ParseTuple(args, "s#", &buffer, &size)) {
		PyErr_SetString(PyExc_TypeError, "invalid buffer argument");
		return NULL;
	}

	ud_set_input_buffer(UDIS86_OBJ(self), (unsigned char *)buffer, (size_t)size);

	return Py_BuildValue("i", 0);
}

static PyObject *
py_udis86_set_input_file(PyObject *self, PyObject *args) {
	PyObject *file;

	if (!PyArg_ParseTuple(args, "O", &file)) {
		PyErr_SetString(PyExc_TypeError, "invalid file argument");
		return NULL;
	}

	ud_set_input_file(UDIS86_OBJ(self), (FILE *)PyCObject_AsVoidPtr(file));

	return Py_BuildValue("i", 0);
}

static PyObject *
py_udis86_set_mode(PyObject *self, PyObject *args) {
	int mode = MOD_32;

	if (!PyArg_ParseTuple(args, "i", &mode) || mode < 0) {
		PyErr_SetString(PyExc_TypeError, "invalid mode argument");
		return NULL;
	}

	ud_set_mode(PY_UDIS86(self)->udobject, (uint8_t)mode);

	return Py_BuildValue("i", mode);
}

static PyObject *
py_udis86_set_pc(PyObject *self, PyObject *args) {
	int origin;

	if (!PyArg_ParseTuple(args, "i", &origin) || origin < 0) {
		PyErr_SetString(PyExc_TypeError, "invalid origin argument");
		return NULL;
	}

	ud_set_pc(UDIS86_OBJ(self), (uint64_t)origin);

	return Py_BuildValue("i", origin);
}

static PyObject *
py_udis86_set_syntax(PyObject *self, PyObject *args) {
	int syntax = UD_MODULE_SYN_ATT;

	if (!PyArg_ParseTuple(args, "i", &syntax)) {
		PyErr_SetString(PyExc_TypeError, "invalid syntax argument");
		return NULL;
	}

	if (syntax == UD_MODULE_SYN_INTEL)
		ud_set_syntax(UDIS86_OBJ(self), UD_SYN_INTEL);
	else if (syntax == UD_MODULE_SYN_ATT)
		ud_set_syntax(UDIS86_OBJ(self), UD_SYN_ATT);
	else {
		PyErr_SetString(PyExc_TypeError, "unknown syntax");
		return NULL;
	}
	
	return Py_BuildValue("i", syntax);
}

static PyObject *
py_udis86_set_vendor(PyObject *self, PyObject *args) {
	int vendor = UD_VENDOR_AMD;

	if (!PyArg_ParseTuple(args, "i", &vendor)) {
		PyErr_SetString(PyExc_TypeError, "invalid vendor argument");
	}

	(void)ud_set_vendor(PY_UDIS86(self)->udobject, (unsigned)vendor);

	return Py_BuildValue("i", vendor);
}

static PyMethodDef udis86_methods[] = {
	{"disassemble", py_udis86_disassemble, METH_NOARGS, ""},
	{"insn_asm", py_udis86_insn_asm, METH_NOARGS, ""},
	{"insn_hex", py_udis86_insn_hex, METH_NOARGS, ""},
	{"insn_len", py_udis86_insn_len, METH_NOARGS, ""},
	{"insn_off", py_udis86_insn_off, METH_NOARGS, ""},
	{"insn_ptr", py_udis86_insn_ptr, METH_NOARGS, ""},
	{"set_input_bufer", py_udis86_set_input_buffer, METH_VARARGS, ""},
	{"set_input_file", py_udis86_set_input_file, METH_VARARGS, ""},
	{"set_mode", py_udis86_set_mode, METH_VARARGS, ""},
	{"set_pc", py_udis86_set_pc, METH_VARARGS, ""},
	{"set_syntax", py_udis86_set_syntax, METH_VARARGS, ""},
	{"set_vendor", py_udis86_set_vendor, METH_VARARGS, ""},
	{ NULL, 0, 0, NULL }
};

static PyObject *
py_udis86_getattr(PyObject *self, char *name) {
	return Py_FindMethod(udis86_methods, self, name);
}
