### Requirements

Install CMAKE   
`pip install cmake`

### Install as a package
##### Coming soon...

### Build and test the development version
To clone the [DPmatchsrvf](https://github.com/pysrvf/dpmatchsrvf.git) repository and build the module, run the following commands.  
```bash
git clone https://github.com/pysrvf/dpmatchsrvf.git
cd DPmatchsrvf
mkdir build
cd build
cmake ..
make
```  
 
This will create three binaries in the `build` directory

1. Standalone executable `build/dpmatchsrvf`    
2. Dynamic linked library `build/libldpmatchsrvf.a`  
3. Importable Python module `build/dpmatchsrvf.cpython-XX.so`

### Tests
Go to the `build` directory and run `python`.   

Then copy and paste the following code  
```python
import numpy as np
from pyDPmatchsrvf import dpmatch
from scipy.io import loadmat
qarray = loadmat('../data/q.mat')
gam = dpmatch().match(np.asarray(qarray['q1'], dtype=np.float32), np.asarray(qarray['q2'], dtype=np.float32))
print(gam)  
```
