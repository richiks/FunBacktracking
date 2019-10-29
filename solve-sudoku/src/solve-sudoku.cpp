/**
 * File: solve-sudoku.cpp
 * ----------------------
 * Presents a program that animates the search for a solution
 * to a SuDoKu puzzle.
 */

#include <string>
#include "gevents.h"
#include "grid.h"
#include "sudoku-constants.h"
#include "sudoku-display.h"
using namespace std;

/* Constants */
static const std::string kBoard[] = {
    "000030200",
    "020040350",
    "007100008",
    "800001062",
    "060000070",
    "270600003",
    "700008900",
    "056090040",
    "008010000"
};

/**
 * Function: configureBoard
 * ------------------------
 * Updates the board and the view to store and display the
 * board defined by kBoard above.
 */
static void configureBoard(SuDoKuDisplay& display, Grid<int>& board) {
	for (int row = 0; row < kBoardDimension; row++) {
		for (int col = 0; col < kBoardDimension; col++) {
			board[row][col] = kBoard[row][col] - '0';
            if (board[row][col] > kEmpty)
                display.placeFixedNumber(row, col, board[row][col]);
		}
	}
}

/**
 * Function: isLegal
 * -----------------
 * Brute force check that confirms whether it's okay to place the
 * specific digit in the (row, col) location of the board without
 * violating the rules.
 */
static bool isLegal(const Grid<int>& board, int row, int col, int digit) {
    for (int c = 0; c < kBoardDimension; c++) {
        if (board[row][c] == digit) return false;
    }

    for (int r = 0; r < kBoardDimension; r++) {
        if (board[r][col] == digit) return false;
    }

    int rowblock = row / kBlockWidth;
    int colblock = col / kBlockWidth;
    for (int drow = 0; drow < kBlockWidth; drow++) {
        for (int dcol = 0; dcol < kBlockWidth; dcol++) {
            if (board[kBlockWidth * rowblock + drow][kBlockWidth * colblock + dcol] == digit) {
                return false;
            }
        }
    }

    return true;
}

/**
 * Function: countNumOptions
 * -------------------------
 * Returns the number of digits that could be placed in the (row, col) position
 * without violating the rules.  The return value can be as low of 0 (because no
 * number works there), as high as 9 (because there are no constraint), or any
 * integer in between.
 */
static int countNumOptions(const Grid<int>& board, int row, int col) {
    int numOptions = 0;
    for (int digit = 1; digit <= kNumDigits; digit++) {
        if (isLegal(board, row, col, digit))
            numOptions++;
    }

    return numOptions;
}

/**
 * Function: findBestEmptyLocation
 * -------------------------------
 * Searches all of the locations and surfaces the unoccuplied (row, col) location
 * that is the most constrained.  The most constrained one can be argued to the
 * the best location to address earlier rather than later.  Note that true is
 * returned if a best location is eventually discovered, and false is returned
 * if there are no unoccupied locations.
 */
static bool findBestEmptyLocation(const Grid<int>& board, int& row, int& col) {
    int smallestNumOptions = kNumDigits + 1;
    for (int r = 0; r < kBoardDimension; r++) {
        for (int c = 0; c < kBoardDimension; c++) {
            if (board[r][c] == kEmpty) {
                int numOptions = countNumOptions(board, r, c);
                if (numOptions < smallestNumOptions) {
                    row = r;
                    col = c;
                    smallestNumOptions = numOptions;
                }
            }
        }
    }

    return smallestNumOptions <= kNumDigits;
}

/**
 * Function: findFirstEmptyLocation
 * --------------------------------
 * Surfaces the first unoccupied position on the board, returning true once
 * row and col have been selected.  If there are no unoccupied locations, then
 * false is returned to express failure.
 */
static bool findFirstEmptyLocation(const Grid<int>& board, int& row, int& col) {
    for (row = 0; row < kBoardDimension; row++) {
        for (col = 0; col < kBoardDimension; col++) {
            if (board[row][col] == kEmpty) {
                return true;
            }
        }
    }
    return false;
}

/**
 * Function: findLocation
 * ----------------------
 * Returns a location that should be considered next.  Note that
 * kUseOptimizedLocationSearch can be set to true or false and everything
 * will still work.
 */
static const bool kUseOptimizedLocationSearch = false;
static bool findLocation(const Grid<int>& board, int& row, int& col) {
    if (kUseOptimizedLocationSearch)
        return findBestEmptyLocation(board, row, col);
    else
        return findFirstEmptyLocation(board, row, col);
}

/**
 * Function: solve
 * ---------------
 * Returns true if and only if the board represents a partial solution
 * to some SuDoKu puzzle that can actually be solved.  If true is returned,
 * the full solution is left within the board and presented in the view.
 * Otherwise, false is returned and the board and display are left as they
 * were when solve was called.
 */
static bool solve(SuDoKuDisplay& display, Grid<int>& board) {
    int row, col;
    if (!findLocation(board, row, col)) return true;
    
    for (int digit = 1; digit <= 9; digit++) {
        if (isLegal(board, row, col, digit)) {
            board[row][col] = digit;
            display.provisionallyPlaceNumber(row, col, digit);
            if (solve(display, board)) {
                display.permanentlyPlaceNumber(row, col);
                return true;
            }
            board[row][col] = kEmpty;
            display.liftNumber(row, col);
        }
    }
    
    return false;
}

/**
 * Function: main
 * --------------
 * Defines the entry point for the entire program, which
 * animates the discovery of a solution to the SuDoKu puzzle
 * specified by kBoard.
 */
int main() {
    SuDoKuDisplay display;
	Grid<int> board(kBoardDimension, kBoardDimension);
    configureBoard(display, board);
    waitForClick();
    solve(display, board);
    return 0;
}
