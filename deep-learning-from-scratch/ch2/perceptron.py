import numpy as np
def AND(x1,x2):
    x = np.array([x1,x2])
    w = np.array([0.5,0.5]) 
    b = -0.7
    tmp = np.sum(w*x)+b
    if tmp <= 0:
        return 0
    else:
        return 1

def OR(x1,x2):
    x = np.array([x1,x2])
    w = np.array([0.5,0.5]) 
    b = -0.2
    tmp = np.sum(w*x)+b
    if tmp <= 0:
        return 0
    else:
        return 1

def NAND(x1,x2):
    x = np.array([x1,x2])
    w = np.array([-0.5,-0.5]) 
    b = 0.7
    tmp = np.sum(w*x)+b
    if tmp <= 0:
        return 0
    else:
        return 1
    
def XOR(x1,x2): 
    s1 = NAND(x1,x2)
    s2 = OR(x1,x2)
    y = AND(s1,s2)
    
    return y


# 퍼셉트론의 아름다움은 층을 쌓아 다층 퍼셉트론을 만들 수 있다는 점!
# 게이트의 Truth Table을 통해 알아내면 편하다