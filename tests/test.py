### Tests

import numpy as np
from dpmatchsrvf import dpmatch
from scipy.io import loadmat
qarray = loadmat('../data/q.mat')
gam=dpmatch().match(np.asarray(qarray['q1'], dtype=np.float32), np.asarray(qarray['q2'], dtype=np.float32))
gam

dpmatch().print_int(1)
dpmatch().print_vector(np.arange(2, 10, dtype=float))
dpmatch().print_array(np.ndarray(shape=(5,6), dtype=np.float32))

