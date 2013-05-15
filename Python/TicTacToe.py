def build_board():
    board = []
    for i in range(9):
        board.append(" ")
    return board

def print_board(board):
    print(board[0], "|", board[1], "|", board[2])
    print("-"*10)
    print(board[3], "|", board[4], "|", board[5])
    print("-"*10)
    print(board[6], "|", board[7], "|", board[8])

def move(board):
    spot = int(input("choose a position on the board (0-8): "))
    while (board[spot] != " "):
        print("Not a valid position.")
        spot = int(input("choose a position on the board (0-8): "))
    return spot

def winning(board):
    ways_to_win = ((0,1,2),
                   (3,4,5),
                   (6,7,8),
                   (0,3,6),
                   (1,4,7),
                   (2,5,8),
                   (0,4,8),
                   (2,4,6))
    for row in ways_to_win:
        if board[row[0]] == board[row[1]] == board[row[2]] != " ":
            winner = board[row[0]]
            return winner

    if " " not in board:
        return "Tie"

    return None

def main():
    #get a board
    board = build_board()
    #start the game
    turn = "X"
    while (not winning(board)):
        #format board for printing
        print_board(board)
        spot = move(board)
        board[spot] = turn
        if (turn == "X"):
            turn = "0"
        else:
            turn = "X"
        #or turn = "0" if (turn == "X") else "X"
    winner = winning(board)
    if (winner == "Tie"):
        print("The game ends in a tie.")
    else:
        print(winner, "wins the game.")
    print("Thanks for playing.")
main()
