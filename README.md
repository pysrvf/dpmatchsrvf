### Requirements

Install CMAKE   
`pip install cmake`

### Install as a package

```bash
git clone https://github.com/pysrvf/dpmatchsrvf.git
cd dpmatchsrvf
pip install . 
```

### Testing to see if the module can be loaded and executed

In the `python` terminal copy and paste the following code  
```python
from dpmatchsrvf import dpmatch
import numpy as np

q1 = np.array([[ 0.00169204,  0.17140255,  0.37388457,  0.40324848,  0.40343557,
                 0.39931306,  0.3291022 ,  0.14283323,  0.03878632,  0.06112178,
                 0.15182835,  0.32823288,  0.24597359,  0.12237112,  0.12082556],
               [-0.40890987, -0.34235618, -0.11528322, -0.00266175, -0.00552813,
                -0.04960033, -0.21496045, -0.36961304, -0.40563656, -0.40312208,
                -0.36960482, -0.08352837,  0.29167956,  0.38069163,  0.38153135]])

q2 = np.array([[ 0.00552389,  0.15402398,  0.35514829,  0.40165261,  0.40273699,
                 0.40255453,  0.40253769,  0.40258229,  0.40253601,  0.40270615,
                 0.40333676,  0.37552986,  0.25658819,  0.15670754,  0.12006318],
               [-0.40721385, -0.35557242, -0.16439049, -0.02555373, -0.00244349,
                0.00529482,  0.00559469,  0.00458355,  0.00590347, -0.00049341,
                -0.00937906, -0.11410367, -0.29597692, -0.37419586, -0.38819515]])


gam=dpmatch().match(q1, q2)
gam
```

### Build and test the C++ library development version (optional)
Install `naonobind` as a submodule first.
```
git submodule add https://github.com/wjakob/nanobind ext/nanobind
git submodule update --init --recursive
```
To clone the [dpmatchsrvf](https://github.com/pysrvf/dpmatchsrvf.git) repository and build the module, run the following commands.  
```bash
git clone https://github.com/pysrvf/dpmatchsrvf.git
cd dpmatchsrvf
mkdir build
cd build
cmake ..
make
```  

This will create three binaries in the `build` directory

1. Standalone executable `build/dpmatchsrvf`    
2. Dynamic linked library `build/libldpmatchsrvf.a`  
3. Importable Python module `build/dpmatchsrvf.cpython-XX.so`
