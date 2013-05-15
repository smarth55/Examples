'''Ryan Paulsen
May 22, 2012'''

import random

def manhattan(h, w):
    '''simulate a walk around a grid'''
    #create the grid
    grid = []
    for i in range(h):
        row = []
        for i in range(w):
            row.append(0)
        grid.append(row)

    #starting position
    pos_row = h//2
    pos_col = w//2
    grid[pos_row][pos_col] = 1
    
    while True:
        move = random.randint(1,4)
        if move == 1: #move west
            pos_col -= 1
        elif move == 2: #move north
            pos_row -= 1
        elif move == 3: #move east
            pos_col += 1
        else: #move south
            pos_row += 1

        #check if outside the grid
        if (pos_row > h-1 or pos_row < 0 or pos_col > w-1 or pos_row < 0):
            break

        #update value of position on grid
        grid[pos_row][pos_col] += 1

    #print the grid
    for row in grid:
        print(row)
