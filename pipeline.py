import pickle 
import os
import numpy as np

f = './RandomForest_cls_0.pkl'
sf = './Scaler_per_cls_0.pkl'
d = './features.npy'

print("Loading Data")
data = np.load(d)
scaler = pickle.load(open(sf,'rb'))
lm = pickle.load(open(f,'rb'))

print("Scaled Data")
scaled_data = scaler.transform(data)
# print(lm.predict(scaled_data))
print(data.dtype)
print(scaled_data.dtype)
pass