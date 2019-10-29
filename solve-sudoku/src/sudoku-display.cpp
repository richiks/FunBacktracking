/**
 * File: sudoku-display.cpp
 * ------------------------
 * Presents the implementation of the SuDoKuDisplay
 * class.  The vast majority of the implementation below
 * is just code to realize geometry and simple animation.
 */
#include <string>
#include "sudoku-constants.h"
#include "sudoku-display.h"
#include "gwindow.h"
#include "gobjects.h"
#include "grid.h"
using namespace std;

static const double kSquareSize = 48;
static const double kWindowDimension = (kBoardDimension + 1) * kSquareSize;

static const string kWindowTitle = "Solve SuDoKu";
SuDoKuDisplay::SuDoKuDisplay() : GWindow(kWindowDimension, kWindowDimension), numberLabels(kBoardDimension, kBoardDimension) {
    setTitle(kWindowTitle);
    drawBoard();
    drawSeparators();
}

static const string kFixedNumberColor = "#000000";
void SuDoKuDisplay::placeFixedNumber(int row, int col, int digit) {
    introduceNumber(digit, row, col, kFixedNumberColor);
}

static const string kProvisionalColor = "#0000ff";
static const int kDelay = 1;
void SuDoKuDisplay::provisionallyPlaceNumber(int row, int col, int digit) {
    introduceNumber(digit, row, col, kProvisionalColor);
    pause(kDelay);
}

static const string kPermanantColor = "#229922";
void SuDoKuDisplay::permanentlyPlaceNumber(int row, int col) {
    numberLabels[row][col]->setColor(kPermanantColor);
    pause(kDelay);
}

void SuDoKuDisplay::liftNumber(int row, int col) {
    remove(numberLabels[row][col]);
    delete numberLabels[row][col];
    numberLabels[row][col] = NULL;
    pause(kDelay);
}

static const double kInset = 2;
void SuDoKuDisplay::drawBoard() {
    for (int row = 0; row < kBoardDimension; row++) {
        for (int col = 0; col < kBoardDimension; col++) {
            drawSquare(row, col, kInset);
        }
    }
}

static const string kFillColor = "#fafafa";
static const string kBorderColor = "#777777";
void SuDoKuDisplay::drawSquare(int row, int col, int inset) {
    int ulx = getCenterX(col) - kSquareSize/2;
    int uly = getCenterY(row) - kSquareSize/2;
    GRect *square = new GRect(ulx + inset, uly + inset, kSquareSize - 2 * inset, kSquareSize - 2 * inset);
    square->setFilled(true);
    square->setFillColor(kFillColor);
    square->setColor(kBorderColor);
    add(square);
}

int SuDoKuDisplay::getCenterX(int col) {
    return (kWindowDimension - kBoardDimension * kSquareSize)/2 + (2 * col + 1) * kSquareSize/2;
}

int SuDoKuDisplay::getCenterY(int row) {
    return (kWindowDimension - kBoardDimension * kSquareSize)/2 + (2 * row + 1) * kSquareSize/2;
}

static const double kWindowInset = 10;
void SuDoKuDisplay::drawSeparators() {
    GLine *separators[] = {
        new GLine(getSeparatorX(3), kWindowInset,
                  getSeparatorX(3), getWidth() - kWindowInset),
        new GLine(getSeparatorX(6), kWindowInset,
                  getSeparatorX(6), getWidth() - kWindowInset),
        new GLine(kWindowInset, getSeparatorY(3),
                  getHeight() - kWindowInset, getSeparatorY(3)),
        new GLine(kWindowInset, getSeparatorY(6),
                  getHeight() - kWindowInset, getSeparatorY(6))
    };

    for (GLine *separator: separators) add(separator);
}

int SuDoKuDisplay::getSeparatorX(int col) {
    return (getWidth() - kBoardDimension * kSquareSize)/2 + col * kSquareSize;
}

int SuDoKuDisplay::getSeparatorY(int row) {
    return (getHeight() - kBoardDimension * kSquareSize)/2 + row * kSquareSize;
}

static const string kFont = "Times-Bold-" + integerToString(0.7 * kSquareSize);
void SuDoKuDisplay::introduceNumber(int number, int row, int col, const string& color) {
    GLabel *label = numberLabels[row][col] = new GLabel(integerToString(number));
    label->setFont(kFont);
    label->setColor(color);
    add(label, getCenterX(col) - label->getWidth()/2, getCenterY(row) + label->getFontAscent()/2);
}

