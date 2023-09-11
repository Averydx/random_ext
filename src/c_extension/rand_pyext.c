#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "structmember.h"
#include <stdint.h>
#include "PCG.h"
#include "numpy/arrayobject.h"

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

static PyModuleDef Rand = {
    PyModuleDef_HEAD_INIT,
    .m_name = "Rand",
    .m_doc = "Defines a series a random number generating functions.",
    .m_size = -1,
};

/*Structs for definition of PCG*/

//method definitions
static PyMethodDef PCG_methods[] = {
    {"next_int", (PyCFunction) next_int, METH_NOARGS,
     "returns an random unsigned int between 0 and max(uint32_t)"
    },
    {"standard_uniform",(PyCFunction)standard_uniform,METH_NOARGS,
    "returns a float in the standard uniform distribution [0,1]"},
    {"standard_normal",(PyCFunction)standard_normal,METH_VARARGS,
    "returns the standard normal variate"},
    {NULL,NULL,0,NULL}  /* Sentinel */
};

//type definition
static PyTypeObject PCG_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "Rand.PCG",
    .tp_doc = PyDoc_STR("Custom objects"),
    .tp_basicsize = sizeof(PCG),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = PCG_new,
    .tp_dealloc = (destructor) PCG_dealloc,
    .tp_init = (initproc) PCG_init,
    .tp_methods = PCG_methods
};


PyMODINIT_FUNC
PyInit_Rand(void)
{
    if (PyType_Ready(&PCG_type) < 0)
        return NULL;

    PyObject* m = PyModule_Create(&Rand);
    
    if (m == NULL)
        return NULL;

    Py_INCREF(&PCG_type);
    if (PyModule_AddObject(m, "PCG", (PyObject *) &PCG_type) < 0) {
        Py_DECREF(&PCG_type);
        Py_DECREF(m);
        return NULL;
    }
    if(PyArray_API == NULL)
    {
    import_array(); 
    }

    
    return m;
}
