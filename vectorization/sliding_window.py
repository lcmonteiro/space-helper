import numpy as np

def sliding_window(data, axis, step, shape):
    from numpy.lib.stride_tricks import as_strided
    # cast strides & shapes & steps
    dsd = np.array(data.strides)
    dsh = np.array(data.shape)
    isp = np.array(step)
    ish = np.array(shape)    
    # take stride & shape 
    psd = np.take(dsd, axis)
    psh = np.take(dsh, axis)
    # update base shape
    np.put(dsh, axis, shape)
    # compute strides & shape
    osd = np.concatenate((((psd      ) * isp)    , dsd)).astype(int)
    osh = np.concatenate((((psh - ish) / isp) + 1, dsh)).astype(int)
    # apply strides & shape
    return as_strided(data, strides=osd, shape=osh, writeable=False)

# test case
if __name__ == '__main__':
  print("idata:")
  idata = np.arange(0, 12).reshape(3, 4)
  print(idata)

  print("odata:")
  odata = sliding(idata, axis=(-2,-1), step=(1,2), shape=(2,2))
  print(odata, odata.shape)

  print("mean:")
  mean = np.mean(odata, axis=(-2,-1), keepdims=True)
  print(mean, mean.shape)

  print("subtract:")
  sub = np.subtract(odata, mean)
  print(sub, sub.shape)
