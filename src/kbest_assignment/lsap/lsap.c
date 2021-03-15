
#include <math.h>
#include "numpy/arrayobject.h"
#include "numpy/ndarraytypes.h"
#include "rectangular_lsap/rectangular_lsap.h"

static PyObject*
calculate_assignment(PyObject* self, PyObject* args)
{
    PyObject* a = NULL;
    PyObject* b = NULL;
    PyObject* u = NULL;
    PyObject* v = NULL;
    PyObject* result = NULL;
    PyObject* obj_cost = NULL;
    if (!PyArg_ParseTuple(args, "O", &obj_cost))
        return NULL;

    PyArrayObject* obj_cont =
      (PyArrayObject*)PyArray_ContiguousFromAny(obj_cost, NPY_DOUBLE, 2, 2);
    if (!obj_cont) {
        PyErr_SetString(PyExc_TypeError, "invalid cost matrix object");
        return NULL;
    }

    double* cost_matrix = (double*)PyArray_DATA(obj_cont);
    if (cost_matrix == NULL) {
        PyErr_SetString(PyExc_TypeError, "invalid cost matrix object");
        goto cleanup;
    }

    npy_intp num_rows = PyArray_DIM(obj_cont, 0);
    npy_intp num_cols = PyArray_DIM(obj_cont, 1);

    // test for NaN and -inf entries
    for (npy_intp i = 0; i < num_rows*num_cols; i++) {
        if (cost_matrix[i] != cost_matrix[i] || cost_matrix[i] == -INFINITY) {
            PyErr_SetString(PyExc_ValueError,
                            "matrix contains invalid numeric entries");
            goto cleanup;
        }
    }

    npy_intp dim_r[1] = { num_rows };
    npy_intp dim_c[1] = { num_cols };
    a = PyArray_SimpleNew(1, dim_r, NPY_INT64);
    if (!a)
        goto cleanup;

    b = PyArray_SimpleNew(1, dim_r, NPY_INT64);
    if (!b)
        goto cleanup;

    u = PyArray_SimpleNew(1, dim_c, NPY_FLOAT64);
    if (!u)
        goto cleanup;

    v = PyArray_SimpleNew(1, dim_c, NPY_FLOAT64);
    if (!v)
        goto cleanup;

    int64_t* adata = PyArray_DATA((PyArrayObject*)a);
    for (npy_intp i = 0; i < num_rows; i++)
        adata[i] = i;

    int ret = solve_rectangular_linear_sum_assignment(
      num_rows, num_cols, cost_matrix, PyArray_DATA((PyArrayObject*)u), PyArray_DATA((PyArrayObject*)v), PyArray_DATA((PyArrayObject*)b));
    if (ret != 0) {
        PyErr_SetString(PyExc_ValueError, "cost matrix is infeasible");
        goto cleanup;
    }

    result = Py_BuildValue("OOOO", a, b, u, v);

cleanup:
    Py_XDECREF((PyObject*)obj_cont);
    Py_XDECREF(a);
    Py_XDECREF(b);
    Py_XDECREF(u);
    Py_XDECREF(v);
    return result;
}

static PyMethodDef lsap_module_methods[] = {
    { "calculate_assignment", calculate_assignment, METH_VARARGS,
      "Solves the rectangular linear sum assignment problem." },
    { NULL, NULL, 0, NULL }
};

static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "lsap",
    "Solves the rectangular linear sum assignment.",
    -1,
    lsap_module_methods,
    NULL,
    NULL,
    NULL,
    NULL,
};

PyObject*
PyInit_lsap(void)
{
    PyObject* m;
    m = PyModule_Create(&moduledef);
    import_array();
    return m;
}
