class MulLayer:
    def __init__(self):
        self.x = None;
        self.y = None;
        
    def forward(self,x,y):
        self.x = x
        self.y = y
        out = x*y
        
        return out
    def backward(self,dout):
        dx = dout * self.y
        dy = dout * self.x
        
        return dx,dy
# 사과 살때 개수와 세금포함 
apple = 100
apple_num = 2
tax = 1.1
    
# mul_apple_layer = MulLayer()
# mul_tax_layer = MulLayer()

# buy apple
# apple_price = mul_apple_layer.forward(apple,apple_num);
# price = mul_tax_layer.forward(apple_price,tax)
# print(price)

# dprice = 1
# dapple_price,dtax = mul_tax_layer.backward(dprice)
# dapple,dapple_num = mul_apple_layer.backward(dapple_price)
# print(dapple, dapple_num,dtax)

class AddLayer:
    def __init__(self):
        pass
    
    def forward(self,x,y):
        out = x+y
        return out
    
    def backward(self,dout):
        dx = dout*1
        dy = dout*1
        return dx,dy
#buy apples and oranges
apple = 100
apple_num = 2
orange = 150
orange_num = 3
tax = 1.1

mul_apple_layer = MulLayer()
mul_orange_layer = MulLayer()
add_apple_orange_layer = AddLayer()
mul_tax_layer = MulLayer()

apple_price = mul_apple_layer.forward(apple,apple_num)
orange_price = mul_orange_layer.forward(orange,orange_num)
sum_price = add_apple_orange_layer.forward(apple_price,orange_price)
price = mul_tax_layer.forward(sum_price,tax)
print(price)

dprice = 1
dsum_price,dtax = mul_tax_layer.backward(dprice)
dapple_price,dorange_price = add_apple_orange_layer.backward(dsum_price)
dapple,dapple_num = mul_apple_layer.backward(dapple_price)
dorange,dorange_num = mul_orange_layer.backward(dorange_price)

print(dapple_num,dapple,dorange,dorange_num,dtax)
