import numpy as np
import matplotlib.pyplot as plt

x= np.arange(0,6,0.1) #데이터준비
y= np.sin(x)
z= np.cos(x)


plt.plot(x,y,label ="sin")
plt.plot(x,z, linestyle="--",label ="cos") #cos함수는 점선으로 그리기
plt.xlabel("x")
plt.ylabel("y")
plt.title("SaC")
plt.legend(loc='upper right') #데이터 종류표시
plt.show()
