/**
 * File: queens-display.cpp
 * ------------------------
 * Presents the implementation of all QueensDisplay methods.
 * All of the method implementations, while tedious to follow,
 * are straightforward geometry.
 */

#include "queens-display.h"
#include "queens-constants.h"
#include "gobjects.h"
using namespace std;

static const double kSquareSize = 48;
static const double kMenuHeight = 24;
void QueensDisplay::setDimension(int dimension) {
    clear();
    this->dimension = dimension;
    setTitle("Solve " + integerToString(dimension) + " Queens");
    labels.resize(dimension, dimension);
    windowDimension = (dimension + 1) * kSquareSize;
    setSize(windowDimension + 2, windowDimension + kMenuHeight + 2);
    drawBoard();
}

static const string kBorderColor = "Blue";
void QueensDisplay::drawSquare(int row, int col) {
    int ulx = getCenterX(col) - kSquareSize/2;
    int uly = getCenterY(row) - kSquareSize/2;
    GRect *square = new GRect(ulx, uly, kSquareSize, kSquareSize);
    square->setColor(kBorderColor);
    add(square);
}

static const string kQueenLabel = "Q";
void QueensDisplay::drawQueen(int row, int col) {
    int cx = getCenterX(col);
    int cy = getCenterY(row);
    labels[row][col] = new GLabel(kQueenLabel);
    labels[row][col]->setFont("Courier-Bold-" + integerToString(kSquareSize));
    labels[row][col]->setVisible(false);
    add(labels[row][col], cx - labels[row][col]->getWidth()/2, cy + labels[row][col]->getFontDescent());
}

void QueensDisplay::drawBoard() {
    for (int row = 0; row < dimension; row++) {
        for (int col = 0; col < dimension; col++) {
            drawSquare(row, col);
            drawQueen(row, col);
        }
    }
}

static const string kPossibilityColor = "#aaaaaa";
void QueensDisplay::considerQueen(int row, int col) {
    updateQueen(row, col, kPossibilityColor);
}

static const string kProvisionalColor = "#0000ff";
void QueensDisplay::provisionallyPlaceQueen(int row, int col) {
    updateQueen(row, col, kProvisionalColor);
}

static const string kPermanantColor = "#55aa55";
void QueensDisplay::permanentlyPlaceQueen(int row, int col) {
    updateQueen(row, col, kPermanantColor);
}

static const string kNotPossibleColor = "#dd0000";
void QueensDisplay::removeQueen(int row, int col) {
    updateQueen(row, col, kNotPossibleColor);
    labels[row][col]->setVisible(false);
}

static const double kMillisecondDelay = 10;
void QueensDisplay::updateQueen(int row, int col, const string& color) {
    labels[row][col]->setColor(color);
    labels[row][col]->setVisible(true);
    pause(kMillisecondDelay);
}

double QueensDisplay::getCenterX(int col) {
    return (windowDimension - dimension * kSquareSize)/2 + col * kSquareSize + kSquareSize/2;
}

double QueensDisplay::getCenterY(int row) {
    return (windowDimension - dimension * kSquareSize)/2 + (dimension - row - 1) * kSquareSize + kSquareSize/2;
}
