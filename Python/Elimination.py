# Ryan Paulsen

import random

#Global Constants
PEG_HOLE = 10

#Functions

def instructions():
    print("Elimination!")
    print("""To play, the computer rolls 2 dice and you place pegs in the
holes that either equal or add up to the total of the roll.""")
    print("You can exit at any time by typing 'exit'.\n")

def roll_die():
    #This function will simulate rolling two six sided dice
    d1 = random.randint(1,6)
    d2 = random.randint(1,6)
    total = d1 + d2
    print("You rolled a", total)
    return total

def create_peg_holes():
    #This function creates the initial hole list, consisting of 10 numbers
    pegholes = []
    for hole in range(1,PEG_HOLE+1):
        pegholes.append(hole)
    return pegholes

def valid_moves(pegholes):
    #This function will return a list of numbers, which are empty (don't
    #have pegs in them)
    validMoves = []
    for hole in range(1,PEG_HOLE+1):
        if pegholes[hole-1] != "X":
            validMoves.append(hole)
    return validMoves

def print_peghole(pegholes):
    # Print out the pegholes list
    print("-" * 40)
    for i in (pegholes):
        print("(", i, ")", sep="", end="")
    print()
    print("-" * 40)

def enter_peg(pegholes, roll):
    valid = valid_moves(pegholes)
    while True:
        # ask for move
        move = input("Which hole would you like to peg (1-10)? ")
        if move.lower() == "exit":
            move = move.lower()
            return pegholes, move
        move = int(move)# convert to int
        if move not in range(1, PEG_HOLE+1): #check if in range
            print("Number is out of range.")
        elif move not in valid:  #check if valid
            print("That hole is already pegged")
        elif move > roll:  #check if greater than roll
            print("Invalid. The sum of the pegs is greater than the roll.")
        else:    
            pegholes[move-1] = "X"
            roll -= move
            return pegholes, roll

def winner(pegholes):
    if valid_moves(pegholes):
        return False
    else:
        return True


# Main program
def main():
    #instructions
    instructions()
    #Create the empty peg board
    pegholes = create_peg_holes()
    #Print the peg board
    print_peghole(pegholes)

    while True:
        roll = roll_die()
        while roll > 0:
            pegholes, roll = enter_peg(pegholes, roll)
            if roll == "exit":
                print("Thanks for playing.")
                return
            print_peghole(pegholes)
            if winner(pegholes):
                print("You Win!")
                return

main()

