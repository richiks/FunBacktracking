/**
 * File: sudoku-display.h
 * ----------------------
 * Presents the SuDoKuDisplay class, which can be used to animate
 * the search for a solution to a SuDoKu puzzle.
 */
#pragma once

#include <string>
#include "gwindow.h"
#include "grid.h"
class GLabel; // forward declare just the type's existence

/**
 * Type: SuDoKuDisplay
 * -------------------
 * Defines the SuDoKuDisplay class, which allows us to visualize the search for
 * a solution to a SuDoKu puzzle.
 */
class SuDoKuDisplay: private GWindow {
public:

    /**
     * Constructor: SuDoKuDisplay
     * --------------------------
     * Constructs an instance to display a classic SuDoKu board where all
     * locations are unoccupied.
     */
    SuDoKuDisplay();

    /**
     * Function: placeFixedNumber
     * --------------------------
     * Plants the provided number down in the view using a color that
     * makes it clear the number contributes to the original puzzle.
     */
    void placeFixedNumber(int row, int col, int number);

    /**
     * Function: provisionallyPlaceNumber
     * ----------------------------------
     * Places the provided number at the specified location within the view
     * so that it's clear the number might be able to be placed there in a
     * full solution to the puzzle, but that more work needs to be done to confirm
     * that its placement doesn't prevent the rest of the puzzle from being solved.
     */
    void provisionallyPlaceNumber(int row, int col, int number);

    /**
     * Function: permanentlyPlaceNumber
     * --------------------------------
     * Transitions the provisionally placed number at the provided
     * location to actually be permanent, making it clear that the
     * number placed at (row, col) contributed to a solution.
     */
    void permanentlyPlaceNumber(int row, int col);

    /**
     * Function: liftNumber
     * --------------------
     * Removes the provisionally placed number for the provided (row, col) location.
     */
    void liftNumber(int row, int col);

private:
    void drawBoard();
    void drawSquare(int row, int col, int inset = 0);
    void drawSeparators();
    void introduceNumber(int number, int row, int col, const std::string& color);
    int getCenterX(int col);
    int getCenterY(int row);
    int getSeparatorX(int col);
    int getSeparatorY(int row);
    Grid<class GLabel *> numberLabels;
};
