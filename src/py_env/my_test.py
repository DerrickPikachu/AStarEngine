
class MyTest:
    def __init__(self):
        self.test_str = "pikachu: hello world"
    
    def say_hello(self):
        print(self.test_str)
    
    def say_something(self, something):
        print(f'pikachu: {something}')

    def add_one(self, something, value):
        print(f'pikachu: {something} {value + 1}')