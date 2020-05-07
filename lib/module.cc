#include <pybind11/pybind11.h>
#include "tetobj.h"

namespace py = pybind11;

#ifndef PYTHON_MODULE_NAME
#define PYTHON_MODULE_NAME py11igl
#endif


PYBIND11_MODULE(PYTHON_MODULE_NAME, m) {
	m.doc() = "LibIGL with pybind11";
	tet::define_module(m);
}
