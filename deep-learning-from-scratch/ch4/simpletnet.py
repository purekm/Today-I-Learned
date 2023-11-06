import sys,os
sys.path.append(os.path.dirname(os.path.abspath(os.path.dirname(__file__))))
import numpy as np
from ch3.neuralnet import softmax
from minibatch import cross_entropy_error
from numerical import numerical_gradient

class simplenet:
    def __init__(self):
        self.W = np.random.randn(2,3)
    
    def predict(self,x):
        return np.dot(x,self.W)
    
    def loss(self,x,t):
        z = self.predict(x)
        y = softmax(z)
        loss = cross_entropy_error(y,t)
        
        return loss
net = simplenet()
print(net.W)
x = np.array([0.6,0.9])
p = net.predict(x)
print(p)
# a = np.argmax(p)
# print(a)
t = np.array([0,0,1])
b = net.loss(x,t)
print(b)

f = lambda w: net.loss(x,t)
dW = numerical_gradient(f,net.W)
print(dW)