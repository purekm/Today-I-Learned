import numpy as np

y= [0.1,0.05,0.6,0.0,0.05,0.1,0.0,0.1,0.0,0.0]
t= [0,0,1,0,0,0,0,0,0,0]

def sum_squares_error(y,t):
    return 0.5*np.sum((y-t)**2)

print(sum_squares_error(np.array(y),np.array(t)));
#오차 제곱합

def cross_entropy_error(y,t):
    delta = 1e-7
    return -np.sum(t*np.log(y+delta))

# print(cross_entropy_error(np.array(y),np.array(t))); 
#교차 엔트로피


#둘다 손실함수를 구하는 함수 