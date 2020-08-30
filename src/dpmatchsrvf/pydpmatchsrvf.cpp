#include "dpmatch.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

// pybind11 wrapper for dpmatch.match() function
py::array_t<float> match(dpmatch& self,
                         const py::array_t<float, py::array::c_style | py::array::forcecast>& q1,
                         const py::array_t<float, py::array::c_style | py::array::forcecast>& q2){
    py::buffer_info q1buff = q1.request();
    py::buffer_info q2buff = q2.request();
    float *q1ptr = static_cast<float *>(q1buff.ptr);
    float *q2ptr = static_cast<float *>(q2buff.ptr);
    int n = q1.shape(0);
    int T = q1.shape(1);

    float *gamma = self.match(n, T, q1ptr, q2ptr); //match will allocate memory
    std::vector<float> gamma_vect {gamma, gamma + T};
    delete gamma; //delete gamma
    return py::cast(gamma_vect);
}

PYBIND11_MODULE(dpmatchsrvf, m)
{
    m.doc() = "pybind11 dpmatchsrvf plugin";
    // bindings to dpmatch class
    py::class_<dpmatch>(m, "dpmatch")
            .def(py::init())
            .def("print_int", &dpmatch::print_int)
            .def("copy", &dpmatch::copy)
            .def("print_vector", [](dpmatch& self, std::vector<float> vect){
                self.print_vector(vect.data(), vect.size());
            })
            .def("print_array", [](dpmatch& self, const py::array_t<float, py::array::c_style>& array){
                py::buffer_info array_buff = array.request();
                float *ptr = static_cast<float *>(array_buff.ptr);
                self.print_array(ptr, (int) array.shape(0), (int) array.shape(1));
            })
            .def("match", &match, pybind11::return_value_policy::move);
}
