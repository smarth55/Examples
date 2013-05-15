# Ryan Paulsen

import random

# set global dictionary for snakes and ladders
SNL = {0:32, 18:74, 68:84, 44:14, 81:47, 97:77}

## functions
def instructions():
    print("SNAKES AND LADDERS!")
    print("Roll the dice and move up the board.")
    print("Land on the bottom of a ladder and move up.")
    print("Land on the top of a snake and slide down.")
    print("\nEnter 'r' to roll the dice and 'e' to exit the game.")
    print("You can restart the game by entering any other key.")

def make_board():
    # make the list of numbers for the board
    board = []
    for num in range(1, 100+1):
        board.append(num)
    return board

def snakes_ladders(board):
    # specify the snakes and ladders for the board
    board[0], board[32] = "L1","L1"
    board[18], board[74] = "L2","L2"
    board[68], board[84] = "L3","L3"
    board[44], board[14] = "S1","S1"
    board[81], board[47] = "S2","S2"
    board[97], board[77] = "S3","S3"
    return board

def print_board(board):
    # print the formatted board
    print("-"*50)
    for index in range(len(board)-1,-1,-1):
        print(board[index], "|", end=" ")
        if ((index%10) == 0):
            print()
            print("-"*50)

def roll_dice():
    # roll 1 dice
    roll = random.randint(1,6)
    print("You rolled a", roll)
    return roll

def move(board, current_pos, score):
    board = snakes_ladders(make_board())
    if current_pos == 0 or current_pos == 18 or current_pos == 68:  
        score -= 10  # subtract 10 if player lands on a ladder
    else:
        score+= 1  # add 1 to the score
    current_pos = SNL.get(current_pos, current_pos)  # check if on an active snake or ladder
    board[current_pos] = "X"  # mark current position
    return board, current_pos, score

def winner(board):
    if board[99] == "X":  # if player is on final position
        return True
    else:
        return False


def save_scores(score):
    scores = open("scores.txt", "a")  # open scores to append
    scores.write(str(score) + "\n")  # save scores to file
    scores.close()
    scores = open("scores.txt", "r")  # open scores for reading
    score_list = scores.readlines()
    for item in range(len(score_list)):
        score_list[item] = int(score_list[item].strip())
    scores.close()
    score_list.sort()  # arrange scores by order
    new_list = []
    for item in range(5):
        try:
            new_list.append(str(score_list[item]) + "\n")  # append score to new list lowest to highest
        except IndexError:
            break
    scores = open("scores.txt", "w")
    scores.writelines(new_list)  # write new score file with new score list
    scores.close()

def last_scores():
    try:
        scores = open("scores.txt", "r")
    except:
        print("Could not find 'scores' file.")
        return
    score_list = scores.readlines()
    print("Here are your five lowest scores:")
    for item in range(len(score_list)):
        print(score_list[item], end="")
    scores.close()


def main():
    instructions()
    last_scores()  # show previous scores to the player
    board = snakes_ladders(make_board())  # make the board with the snakes and ladders marked
    print_board(board)  # print the initial board
    # initialize variables
    roll = 0
    current_pos = -1
    score = 0
    while True:
        response = input("Enter 'r' to roll. Enter 'e' to exit. ")  # get input
        if response == "r":  # if 'r', roll and move
            roll = roll_dice()
            # player can't go over 100, so player stays, but score increases by 1
            if (current_pos + roll) >= 100: 
                score += 1
                print_board(board)
                continue
            current_pos += roll  # add the roll to the current position
            board, current_pos, score = move(board, current_pos, score)  # move the player piece
        elif response == "e":  # if 'e', then exit the game
            print("Thanks for playing.")
            return "e"
        else:
            ## restart the game ##
            return
        last_scores()
        print_board(board)  # print the new board with new position
        if winner(board):  # check if new board is winning board
            print("You Win!")
            print("Your score was", score)
            save_scores(score)  # save the score
            return "e"

while True:
    game = main()
    if game == "e":
        break
