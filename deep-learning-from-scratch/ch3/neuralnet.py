import numpy as np
from ch3.sigmoid import sigmoid
x = np.array([1.0,0.5])
W1 = np.array([[0.1,0.3,0.5],[0.2,0.4,0.6]])
B1 = np.array([0.1,0.2,0.3])

# print(W1.shape)
# print(x.shape)
# print(B1.shape)

A1 = np.dot(x,W1)+B1;
Z1 = sigmoid(A1)

# print(A1)
# print(Z1)

W2 = np.array([[0.1,0.4],[0.2,0.5],[0.3,0.6]])
B2 = np.array([0.1,0.2])

# print(Z1.shape)
# print(W2.shape)
# print(B2.shape)

A2 = np.dot(Z1,W2)+B2
Z2 = sigmoid(A2)

def identity_function(x):
    return x

W3 = np.array([[0.1,0.3],[0.2,0.4]])
B3 = np.array([0.1,0.2])

A3 = np.dot(Z2,W3)+B3
Y = identity_function(A3)

def softmax(a):
    c = np.max(a)
    exp_a = np.exp(a-c)
    sum_exp_a = np.sum(exp_a)
    y = exp_a / sum_exp_a
    
    return y;
    