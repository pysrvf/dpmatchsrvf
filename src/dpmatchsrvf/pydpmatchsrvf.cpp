#include "dpmatch.h"
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/vector.h>


namespace nb = nanobind;
using namespace nb::literals;
using floatvect = std::vector<float>;
using IntVector = std::vector<int>;
using nparray = nb::ndarray<float, nb::ndim<2>>;
using nparray_ret = nb::ndarray<nb::numpy, float, size_t, nb::any>;

void inspect(nparray);

IntVector double_it(const IntVector &in) {
    IntVector out(in.size());
    for (size_t i = 0; i < in.size(); ++i)
        out[i] = in[i] * 2;
    return out;
}
// const float data[] = { 1, 2, 3, 4, 5, 6, 7, 8 };

void inspect(nb::ndarray<> a)
{
    printf("Array data pointer : %p\n", a.data());
    printf("Array dimension : %d\n", a.ndim());
    for (size_t i = 0; i < a.ndim(); ++i) {
        printf("Array dimension [%d] : %d\n", i, a.shape(i));
        printf("Array stride    [%d] : %d\n", i, a.stride(i));
    }
    printf("Device ID = %u (cpu=%i, cuda=%i)\n", a.device_id(),
        int(a.device_type() == nb::device::cpu::value),
        int(a.device_type() == nb::device::cuda::value)
    );
    printf("Array dtype: int16=%i, uint32=%i, float32=%i\n",
        a.dtype() == nb::dtype<int16_t>(),
        a.dtype() == nb::dtype<uint32_t>(),
        a.dtype() == nb::dtype<float>()
    );
}


nparray testnanovect(nparray &data)
{
    printf("the size is (%d, %d)", (int) data.shape(0), (int) data.shape(1));
    size_t shape_arr[2]; 
    shape_arr[0] = data.shape(0);
    shape_arr[1] = data.shape(1);
    size_t shape_arr2[2] = { 2, 4 };
    return(data);
        // return nparray_ret(data, 2, shape_arr);
    // return nb::ndarray<nb::numpy, float, nb::ndim<2>>(
        //  data, shape_arr2);

    // gh = data;
    // return nparray_ret(data, 2, shape_arr);
    // return nb::ndarray<nb::numpy, float, nb::ndim<2>>(
        //  data, shape_arr2);
    // return nb::ndarray(data, /* ndim = */ 2, shape_arr2);

    // return nparray(data, 2, shape_arr);
}

nparray testmatch(nparray &q1, nparray &q2)
{
    float *q1ptr = static_cast<float *>(q1);
    printf("\nthe size of q1 is (%d, %d)\n", (int) q1.shape(0), (int) q1.shape(1));
    printf("\nthe size of q2 is (%d, %d)\n", (int) q2.shape(0), (int) q2.shape(1));
    auto a = q2.view(); /// <-- new!

    a(0, 0) = 9999;

    printf("\n v(0, 0)  = %f", v(0, 0));
    printf("\n v(1, 4)  = %f", v(1, 4));
    // inspect(q2);
    printf("\n");
    // inspect(v);
    // inspect(np.array([[1,2,3], [3,4,5]], dtype=np.float32))

    // IntVector out = double_it([1, 2, 3]);

    



    // return(out);
    return(q2);
}

NB_MODULE(dpmatchsrvf, m)
{
    m.doc() = "nanobind dpmatchsrvf plugin";
    // bindings to dpmatch class
    
    m.def("testnano", &testnano);
    m.def("testnanovect", &testnanovect);
    m.def("testmatch", &testmatch, nb::rv_policy::move);
    m.def("double_it", &double_it);

}

// NB_MODULE(dpmatchsrvf, m) {
//     m.def("ret_numpy", []() {
//         size_t shape[2] = { 2, 4 };

//         // return nb::ndarray<nb::numpy, const float, size_t>(
//             // data, /* ndim = */ 2, shape);
//             return(nb::ndarray<nb::numpy, const float[]> (data))
//     });
//  }


// NB_MODULE(dpmatchsrvf, m) {
//     m.def("ret_numpy", []() {
//         size_t shape[2] = { 2, 4 };
//         return nb::ndarray<nb::numpy, const float, nb::shape<2, nb::any>>(
//             data, /* ndim = */ 2, shape);
//     });
//  }
