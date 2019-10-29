/**
 * File: queens.cpp
 * ----------------
 * This program demonstrates how recursive backtracking can be
 * used to solve the N-Queens problem.
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "queens-display.h"
#include "queens-constants.h"
#include "grid.h"
#include "queens-constants.h"
using namespace std;

/**
 * Function: getIntegerInRange
 * ---------------------------
 * Operates much like getInteger, except that it requires the user
 * enter an integer between low and high, inclusive.  This version
 * also allows the user to enter 0.
 */
static int getIntegerInRange(int low, int high) {
    string prompt = "Please enter an integer between " + integerToString(low) + " and " + integerToString(high) + " [or 0 to quit]";
    while (true) {
        int response = getInteger(prompt);
        if (response == 0 || (response >= low) /* && response <= high) */) return response;
        cout << "Response out of range." << endl;
    }
}

/**
 * Function: isDirectionSafe
 * -------------------------
 * Returns true if and only if the (row, col)-th cell on the board is
 * safe from attack in the (drow, dcol) direction.
 */
static bool isDirectionSafe(const Grid<bool>& board, int row, int col, int drow, int dcol) {
    if (drow == 0 && dcol == 0) return true;
    
    row += drow;
	col += dcol;
	while (board.inBounds(row, col) && !board[row][col]) {
		row += drow;
		col += dcol;
	}
	return !board.inBounds(row, col);
}

/**
 * Function: isSafe
 * ----------------
 * Returns true if and only if the (row, col)-th cell on the
 * provided board is safe from attack from all eight directions.
 */
static bool isSafe(const Grid<bool>& board, int row, int col) {
	for (int drow  = -1; drow  <= 1; drow++) {
        if (!isDirectionSafe(board, row, col, drow, -1))
            return false;
	}
	return true;
}

/**
 * Function: solve
 * ---------------
 * Uses recursive backtracking to decide whether or not queens
 * can be placed in column col and beyond to silve the N-Queens
 * problem.
 */
static bool solve(QueensDisplay& display, Grid<bool>& board, int col) {
    if (col == board.numCols()) return true;
    for (int rowToTry = 0; rowToTry < board.numRows(); rowToTry++) {
        display.considerQueen(rowToTry, col);
        if (isSafe(board, rowToTry, col)) {
            board[rowToTry][col] = true;
            display.provisionallyPlaceQueen(rowToTry, col);
            if (solve(display, board, col + 1)) {
                display.permanentlyPlaceQueen(rowToTry, col);
                return true;
            }
            board[rowToTry][col] = false;
        }
        display.removeQueen(rowToTry, col);
    }
    
    return false;
}

/**
 * Function: solve
 * ---------------
 * Updates the board (and the companion display of the board) with a
 * solution to the N-Queens problem.  This version of solve animates
 * the discovery of the solution using the second form of solve implemented
 * above.
 */
static void solve(QueensDisplay& display, Grid<bool>& board) {
    solve(display, board, 0);
}

/**
 * Function: main
 * --------------
 * Defines the entry point of the entire program, which allows the
 * user to discover solutions to the N-Queens problem.
 */
int main() {
    QueensDisplay display;
    while (true) {
        int dimension = getIntegerInRange(kMinBoardDimension, kMaxBoardDimension);
        if (dimension == 0) break;
        Grid<bool> board(dimension, dimension);
        display.setDimension(dimension);
        solve(display, board);
    }
    return 0;
}
