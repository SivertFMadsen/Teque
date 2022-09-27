import array, io, os

"""
Dette programmet beskriver en teque, som er en beholder hvor man kan legge til nye elementer først, 
sist, og i midten av køen.

"""

class teque:
    def __init__(self, size) -> None:

        # Initializes full teque at startup:
        self._teque = array.array("I", [0] * (size * 3))

        # Index for front of teque:
        self._front = size
        # Index for back of teque:
        self._back = size * 2

        self._weight_front = 0
        self._weight_back = 0

        self._buffer_out = io.StringIO()

    def push_front(self, x):

        self._teque[self._front] = x
        # Updates weight of front part of teque:
        self._weight_front += 1
        # Updates front index:
        self._front -= 1

        self.check_balance()

    def push_back(self, x):

        if self._weight_front == 0:
            self.push_front(x)

        else:
            self._teque[self._back] = x
            # Updates weight of back part of teque:
            self._weight_back += 1
            # Updates back index:
            self._back += 1

            self.check_balance()

    def push_middle(self, x):

        if self._weight_front == 0:
            self.push_front(x)
        elif self._weight_back == 0:
            self.push_back(x)

        elif self._weight_front == self._weight_back:
            # Inserts the element at the back of the front part of the teque:
            self._teque[self._front + self._weight_front + 1] = x
            # Updates weight of front part of teque:
            self._weight_front += 1

        else:
            # Inserts the element at the front of the back part of the teque:
            self._teque[self._back - (self._weight_back + 1)] = x
            # Updates weight of back part of teque:
            self._weight_back += 1
        
        self.check_balance()

    def get(self, i):
        output = ""

        if i < self._weight_front:
            output = self._teque[self._front + i + 1]
        else:
            output = self._teque[self._back - (self._weight_back) + (i - self._weight_front)]
        
        assert output != None, "Error when fetching item."

        self._buffer_out.write(str(output) + "\n")

    def check_balance(self):
        if self._weight_front > self._weight_back + 1:
            # Teque is front-heavy
            self._teque[self._back - (self._weight_back + 1)] = self._teque[self._front + self._weight_front]
            # Updates weight of back part of teque:
            self._weight_back += 1
            # Updates weight of front part of teque:
            self._weight_front -= 1
        
        elif self._weight_back > self._weight_front:
            # Teque is back-heavy
            self._teque[self._front + self._weight_front + 1] = self._teque[self._back - self._weight_back]
            # Updates weight of back part of teque:
            self._weight_back -= 1
            # Updates weight of front part of teque:
            self._weight_front += 1
        
    def get_buffer(self):
        return self._buffer_out.getvalue()


def main():

    input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
    # From https://www.geeksforgeeks.org/fast-i-o-for-competitive-programming-in-python/

    size = int(input().decode())

    teq = teque(size)
    
    counter = 0

    while (counter < size):
        cmd = input().decode().split()

        eval(f'teq.{cmd[0]}({cmd[1]})')
        counter += 1
    
    print(teq.get_buffer().strip())

main()