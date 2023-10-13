import random

def initialize_board(n):
    # Initialize the Tic Tac Toe board as an n x n grid with empty cells
    return [[' ' for _ in range(n)] for _ in range(n)]

def display_board(board):
    for row in board:
        print(' | '.join(row))
        print('-' * (4 * len(row) - 1))

def check_win(player, board):
    n = len(board)
    
    # Check rows
    for row in board:
        if all(cell == player for cell in row):
            return True

    # Check columns
    for col in range(n):
        if all(board[row][col] == player for row in range(n)):
            return True

    # Check diagonals
    if all(board[i][i] == player for i in range(n)) or all(board[i][n - i - 1] == player for i in range(n)):
        return True

    return False

def is_board_full(board):
    return all(board[row][col] != ' ' for row in range(len(board)) for col in range(len(board[0])))

def check_Os(count, blocked_count, n):
    return count == n and blocked_count == 0

def check_n_O(player, board, n):
    def check_rows():
        for i in range(len(board)):
            for j in range(len(board) - n + 1):
                row_count = sum(1 for k in range(n) if board[i][j + k] == player)
                blocked_count = sum(1 for k in range(n) if board[i][j + k] == 'X')
                if check_Os(row_count, blocked_count, n):
                    return True
        return False

    def check_columns():
        for i in range(len(board)):
            for j in range(len(board) - n + 1):
                col_count = sum(1 for k in range(n) if board[j + k][i] == player)
                blocked_count = sum(1 for k in range(n) if board[j + k][i] == 'X')
                if check_Os(col_count, blocked_count, n):
                    return True
        return False

    def check_diagonals():
        for i in range(len(board) - n + 1):
            for j in range(len(board) - n + 1):
                main_diag_count = sum(1 for k in range(n) if board[i + k][j + k] == player)
                blocked_count = sum(1 for k in range(n) if board[i + k][j + k] == 'X')
                if check_Os(main_diag_count, blocked_count, n):
                    return True

                anti_diag_count = sum(1 for k in range(n) if board[i + k][j + n - k - 1] == player)
                blocked_count = sum(1 for k in range(n) if board[i + k][j + n - k - 1] == 'X')
                if check_Os(anti_diag_count, blocked_count, n):
                    return True
        return False

    return check_rows() or check_columns() or check_diagonals()

def ai_move(board, n):
    for row in range(len(board)):
        for col in range(len(board[0])):
            if board[row][col] == ' ':
                # Check if AI can win in the next move
                board[row][col] = 'O'
                if check_win('O', board):
                    return
                board[row][col] = ' '  # Reset the cell

    # Check if AI needs to block the user from winning
    for row in range(len(board)):
        for col in range(len(board[0])):
            if board[row][col] == ' ':
                board[row][col] = 'X'
                if check_win('X', board):
                    board[row][col] = 'O'  # Reset the cell
                    return
                board[row][col] = ' '  # Reset the cell

    # If no winning or blocking move, choose a move that creates 'n' 'O's in a row, column, or diagonal
    for row in range(len(board)):
        for col in range(len(board[0])):
            if board[row][col] == ' ':
                board[row][col] = 'O'
                if check_n_O('O', board, n):
                    return
                board[row][col] = ' '  # Reset the cell

    # If no winning, blocking, or 'n' 'O's move, choose a random available cell
    available_cells = [(row, col) for row in range(len(board)) for col in range(len(board[0])) if board[row][col] == ' ']
    if available_cells:
        row, col = random.choice(available_cells)
        board[row][col] = 'O'

def main():
    n = -1 # dimension of the board
    
    # Board size should be at least 3*3
    while n < 3:
        n = int(input("Enter the board size (n): "))
    
    board = initialize_board(n)
    
    display_board(board)

    while True:
        # Player's move
        while True:
            row, col = map(int, input(f"Enter row and column (0-{n - 1}) separated by space: ").split())
            if board[row][col] == ' ':
                board[row][col] = 'X'
                break
            else:
                print("Invalid move! Cell is already occupied. Try again")
                

        display_board(board)

        # Check if the player wins
        if check_win('X', board):
            print("Congratulations! You win!")
            break

        # Check if the board is full
        if is_board_full(board):
            print("It's a draw!")
            break

        # AI's move
        ai_move(board, n)
        print("AI's move:")
        display_board(board)

        # Check if the AI wins
        if check_win('O', board):
            print("AI wins!")
            break

        # Check if the board is full
        if is_board_full(board):
            print("It's a draw!")
            break

if __name__ == "__main__":
    main()
