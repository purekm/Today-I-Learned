import sys,os
sys.path.append(os.path.dirname(os.path.abspath(os.path.dirname(__file__))))
import numpy as np
from dataset.mnist import load_mnist

y= [0.1,0.05,0.6,0.0,0.05,0.1,0.0,0.1,0.0,0.0]
t= [0,0,1,0,0,0,0,0,0,0]
(x_train,t_train),(x_test,t_test) = \
    load_mnist(normalize=True,one_hot_label=True)
    
print(x_train.shape)
print(t_train.shape)

# train_size = x_train.shape[0]
# batch_size = 10
# batch_mask = np.random.choice(train_size,batch_size)
# x_batch = x_train[batch_mask]
# t_batch = t_train[batch_mask] 방식으로 random index 뽑기

def cross_entropy_error(y,t):
    if y.ndim == 1:
        t = t.reshape(1,t.size)
        y = y.reshape(1,y.size)
    batch_size = y.shape[0]
    return -np.sum(t*np.log(y+1e-7)) / batch_size 
#교차 엔트로피 오차 구현 원-핫 인코딩 방식이므로 t가 0일때는 무시!


def cross_entropy_error2(y,t):
    if y.ndim == 1:
        t = t.reshape(1,t.size)
        y = y.reshape(1,y.size)
    batch_size = y.shape[0]
    return -np.sum(np.log(y[np.arrange(batch_size),t]+1e-7)) / batch_size 
#정답레이블이 숫자 레이블로 주어졌을 떄

print(cross_entropy_error(np.array(y),np.array(t)))