#include "dpmatch.h"
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>

#include<iostream>
using namespace std;
namespace nb = nanobind;
using nparray = nb::ndarray<nb::numpy, float, nb::ndim<2>>;


float data[] = { 1, 2, 3, 4, 5, 6, 7, 8 };


auto match(const nparray &q1, const nparray &q2)
{

    dpmatch dpmatchobj;
    size_t shape[2] = {q1.shape(0), q1.shape(1)};
    int n = q1.shape(0);
    int T = q1.shape(1);
 
    const float *q1ptr = static_cast<const float *>(q1.data());
    const float *q2ptr = static_cast<const float *>(q2.data());

    float *gamma = nullptr;
    gamma = dpmatchobj.match(n, T, q1ptr, q2ptr);
    return (nb::ndarray<nb::numpy, float>(gamma, {(unsigned long) T}));
}

NB_MODULE(dpmatchsrvf, m)
{
    m.doc() = "nanobind dpmatchsrvf plugin";
    m.def("match", &match, nb::rv_policy::take_ownership);
}


