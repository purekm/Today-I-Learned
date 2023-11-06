import numpy as np
def function_2(x):
    return x[0]**2+x[1]**2
def numerical_diff(f,x):
    h = 1e-50
    return (f(x+h)-f(x))/h
#수치 미분 기본
def numerical_approximate_diff(f,x):
    h = 1e-4
    return (f(x+h)-f(x-h))/(2*h)
#중심차분 근사 도함수를 구하지 못할때 근사값

def numerical_gradient(f,x):
    h = 1e-4
    grad = np.zeros_like(x)
    it = np.nditer(x, flags=['multi_index'],op_flags=['readwrite'])
    while not it.finished:
        idx = it.multi_index
        tmp_val = x[idx]
        x[idx] = tmp_val + h
        fxh1 = f(x)
        
        x[idx] = tmp_val - h
        fxh2 = f(x)
        
        grad[idx] = (fxh1-fxh2) /(2*h)
        x[idx] = tmp_val
        it.iternext()
        
    return grad

# print(numerical_gradient(function_2,np.array([3.0,4.0]))) # 