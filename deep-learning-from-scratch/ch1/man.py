class Man:
    def __init__(self, name):
        self.name = name
        print("Instalized")
        
    def hello(self):
        print("Hello "+self.name)
m = Man("Kyeongmin")
m.hello()