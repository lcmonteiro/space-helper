import numpy as np

def sliding_window(data, strides, shape):
    from numpy.lib.stride_tricks import as_strided
    # utils
    dsd = np.array(data.strides)
    dsh = np.array(data.shape)    
    # normalize
    isd = np.concatenate((strides, np.ones(len(dsd) - len(strides)))) 
    ish = np.concatenate((shape  , dsh[len(shape):]                )) 
    # compute strides & shape
    sd = np.concatenate((((dsd      ) * isd)    , dsd)).astype(np.int)
    sh = np.concatenate((((dsh - ish) / isd) + 1, ish)).astype(np.int)
    # apply strides & shape
    return as_strided(data, strides=sd, shape=sh, writeable=False)

idata = np.arange(0, 9).reshape(3, 3)
print("idata:\n", idata)
odata = sliding_window(idata, (1, 2), (2, 1))
print("odata:\n", odata)
