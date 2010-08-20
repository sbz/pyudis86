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
#ifndef _PY_UDIS86_H_
#define _PY_UDIS86_H_

#include <Python.h>
#include <udis86.h>

typedef struct {
	PyObject_HEAD
	void *udobject;
	int dealloc;
} py_udis86; /* udis86 */


#define PY_UDIS86(x) ((py_udis86 *)x)
#define UDIS86_OBJ(x) (PY_UDIS86(x)->udobject)

extern PyTypeObject py_udis86_t;

static void py_udis86_dealloc(PyObject *self, PyObject *args);

static PyObject * py_udis86_set_input_buffer(PyObject *self, PyObject *args);
static PyObject * py_udis86_set_input_file(PyObject *self, PyObject *args);
static PyObject * py_udis86_set_mode(PyObject *self, PyObject *args);
static PyObject * py_udis86_set_syntax(PyObject *self, PyObject *args);
static PyObject * py_udis86_set_vendor(PyObject *self, PyObject *args);
static PyObject * py_udis86_insn_asm(PyObject *self, PyObject *args);
static PyObject * py_udis86_getattr(PyObject *self, char *name);

#endif /* _PY_UDIS86_H_ */
