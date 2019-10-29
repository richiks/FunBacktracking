/**
 * File: sudoku-constants.h
 * ------------------------
 * Defines a collection of constants that need to be shared between
 * the model and the view of the SuDoKu solver.
 */

#pragma once

/* Constants */
static const int kNumDigits = 9;
static const int kBoardDimension = kNumDigits;
static const int kBlockWidth = kNumDigits / 3;
static const int kEmpty = 0; // sentinel in place to mean no number has been placed


