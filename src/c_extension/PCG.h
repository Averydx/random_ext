#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "structmember.h"
#include <stdint.h>
#include "numpy/arrayobject.h"

typedef struct {
    PyObject_HEAD
    uint64_t state;
    uint64_t increment; 
    uint64_t multiplier;
} PCG;

void
PCG_dealloc(PCG *self);

PyObject *
PCG_new(PyTypeObject *type, PyObject *args, PyObject *kwds);

int PCG_init(PCG *self, PyObject *args, PyObject *kwds);

PyObject* next_int(PCG *self, PyObject *Py_UNUSED(ignored));

PyObject* standard_uniform(PCG *self,PyObject *Py_UNUSED(ignored));

PyObject* standard_normal(PCG *self,PyObject *args);
