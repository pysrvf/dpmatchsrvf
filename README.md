### Requirements

Install CMAKE `pip install cmake`

### Install as a package
##### Coming soon...

### Build and test the development version
To clone the [DPmatchsrvf](https://github.com/pysrvf/DPmatchsrvf.git) repository and build the module, run the following commands.  
```bash
git clone https://github.com/pysrvf/DPmatchsrvf.git
cd build
cmake ..
make
```  
 
This will create three binaries in the `build` directory

1. Standalone executable `build/DPmatchsrvf`    
2. Dynamic linked library `build/libDPmatchsrvf.a`  
3. Importable Python module `build/pyDPmatchsrvf.cpython-XX.so`

### Tests
Go to the `build` directory and run `python`.   

Then copy and paste the following code  
```python
import numpy as np
from pyDPmatchsrvf import DPmatch
from scipy.io import loadmat
qarray = loadmat('../data/q.mat')
gam = DPmatch().match(np.asarray(qarray['q1'], dtype=np.float32), np.asarray(qarray['q2'], dtype=np.float32))
print(gam)  
```
