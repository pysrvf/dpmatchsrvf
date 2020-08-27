### Tests

import numpy as np
from pyDPmatchsrvf import DPmatch
from scipy.io import loadmat
qarray = loadmat('../data/q.mat')
gam=DPmatch().match(np.asarray(qarray['q1'], dtype=np.float32), np.asarray(qarray['q2'], dtype=np.float32))
gam

DPmatch().print_int(1)
DPmatch().print_vector(np.arange(2, 10, dtype=float))
DPmatch().print_array(np.ndarray(shape=(5,6), dtype=np.float32))

