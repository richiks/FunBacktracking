/**
 * File: queens-display.h
 * ----------------------
 * Defines the QueensDisplay class that can be used
 * to animate the search for a solution to the N-Queens
 * problem.
 */
#pragma once

#include <string>
#include "gwindow.h"
#include "grid.h"

/**
 * Class: QueensDi
 * splay
 * --------------------
 * Introduces the QueensDisplay class and the set of methods
 * needed to animate the search for a solution to the N-Queens
 * problem.
 */
class QueensDisplay: private GWindow {
public:
    /**
     * Method: setDimension
     * --------------------
     * Redraws the screen and populates it with an square, empty
     * board of the provided dimension.
     */
    void setDimension(int dimension);

    /**
     * Method: considerQueen
     * ---------------------
     * Places a queen at the specified location, noting that it's
     * only being considered while the program determines whether or
     * not the (row, col) cell is safe from attack from the left.
     */
    void considerQueen(int row, int col);

    /**
     * Method: provisionallyPlaceQueen
     * -------------------------------
     * Notes that the location is safe from attack, even though
     * we've yet to learn whether placement causes problems with
     * other columns yet to be considered.
     */
    void provisionallyPlaceQueen(int row, int col);

    /**
     * Method: permanentlyPlaceQueen
     * -----------------------------
     * Visually updates the screen to be clear that the queen
     * belongs where it's been placed.
     */
    void permanentlyPlaceQueen(int row, int col);

    /**
     * Method: removeQueen
     * -------------------
     * Clears the specified location.
     */
    void removeQueen(int row, int col);

private:
    Grid<GLabel *> labels; // need to add and remove these, and that requires state
    int dimension;
    double windowDimension;
    void drawBoard();
    void drawSquare(int row, int col);
    void drawQueen(int row, int col);
    void updateQueen(int row, int col, const std::string& color);
    double getCenterX(int col);
    double getCenterY(int row);
};
