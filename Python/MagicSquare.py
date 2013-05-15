'''Ryan Paulsen
May 30, 2012
Magic Square
I did this in java and thought it was fun
so I am going to give it a try here.'''

class Magic_Square():
    '''a magic square is an n*n (where n is odd) grid of numbers
    where the sum of each row and column is equal'''
    def __init__(self, size):
        'initialize the square'
        self.size = size
        self.square = []
        for row in range(size):
            self.square.append([])
            for col in range(size):
                self.square[row].append(0)

    def make_square(self):
        'build the square'
        row = self.size - 1
        col = self.size // 2
        pos = 1
        while (pos <= self.size * self.size):
            self.square[row][col] = pos
            row += 1
            col +=1
            if (row == self.size): row = 0
            if (col == self.size): col = 0
            if (self.square[row][col] > 0):
                row -= 2
                if (row < 0): row += self.size
                col -= 1
                if (col < 0): col += self.size
            pos += 1

    def print_square(self):
        'display the square'
        for row in range(self.size):
            for col in range(self.size):
                print(self.square[row][col], end=' ')
            print()


def test():
    a = Magic_Square(5)
    a.make_square()
    a.print_square()
