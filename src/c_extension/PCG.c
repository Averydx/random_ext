#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "structmember.h"
#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include <stdio.h>
#include "numpy/arrayobject.h"
#include "stdlib.h"
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION


typedef struct {
    PyObject_HEAD
    uint64_t state;
    uint64_t increment; 
    uint64_t multiplier;
} PCG;


/*destructor for PCG*/
void
PCG_dealloc(PCG *self)
{
    Py_TYPE(self)->tp_free((PyObject *) self);
}


/*runs at object creation, sets up the fields before running the constructor*/
PyObject *
PCG_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PCG *self;
    import_array()
    self = (PCG *) type->tp_alloc(type, 0);
    if (self != NULL) {
        self->multiplier = 6364136223846793005u;
        self->increment = 1442695040888963407u;
        self->state = 0; 
    }
    return (PyObject *) self;
}

/*Constructor for the PCG */
int PCG_init(PCG *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"seed",NULL};
    uint64_t seed; 
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|n", kwlist,
                                     &seed))
        return -1;

    self->state = seed + self->increment;

    return 0;
}

/*Helper function for next int not accessible outside this file*/
static inline uint32_t rotr32(uint32_t x, unsigned r)
{
	return x >> r | x << (-r & 31);
}

static uint32_t next_int_C(PCG* self)
{
    uint64_t x = self->state;
	unsigned count = (unsigned)(x >> 59);		

    self->state = x * self->multiplier + self->increment;
	x ^= x >> 18;			
    return rotr32((uint32_t)(x >> 27), count);
}

/*Generates an unsigned random int */
PyObject* next_int(PCG *self, PyObject *Py_UNUSED(ignored))
{				
	return PyLong_FromUnsignedLong(next_int_C(self));	  
}

double static inline standard_uniform_C(PCG* self)
{
    return (double)next_int_C(self)/(double)UINT32_MAX;
}

PyObject* standard_uniform(PCG *self,PyObject *Py_UNUSED(ignored))
{
    return PyFloat_FromDouble(standard_uniform_C(self));
}

PyObject* standard_normal(PCG *self,PyObject *args)
{
    size_t size;
    
    if(!PyArg_ParseTuple(args,"n",&size))
        return NULL;


    double* arr = malloc(size*sizeof(double));
    Py_BEGIN_ALLOW_THREADS 
    for(size_t i = 0;i < size;i+=2)
    {
        double u,v,s;
        do
        {
        u = standard_uniform_C(self) * 2 -1;
        v = standard_uniform_C(self) * 2 -1; 
        s = u*u + v*v;
        }while(s == 0 || s>=1.f);

        double d = sqrt(-2.f*log(s)/s);
        double z0 = u * d;
        double z1 = v * d;
        
        if(i == size-1)
        {
            arr[i] = z1;
        }
        else{
        arr[i] = z0;
        arr[i+1] = z1;
        }
    }
    Py_END_ALLOW_THREADS

    npy_intp dims[] = {(int)size};
    PyArrayObject* result = PyArray_SimpleNewFromData(1,dims,NPY_DOUBLE,(void*)arr);
    if(result == NULL)
    {
        free(arr);
        return NULL;
    }
    PyArray_ENABLEFLAGS((PyArrayObject*) result, NPY_ARRAY_OWNDATA);
    return (PyObject*)result;
}

