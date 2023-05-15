// double_sided_buffer.cpp
// (C) Martin Alebachew, 2023

#include "double_sided_buffer.hpp"

DoubleSidedBuffer::DoubleSidedBuffer() : currentCell(0), positiveMemorySize(tapeInitialSize), negativeMemorySize(tapeInitialSize) {
  positiveMemoryTape = (byte*)calloc(tapeInitialSize, sizeof(byte));
  positiveMemoryTape = (byte*)calloc(tapeInitialSize, sizeof(byte));
}

DoubleSidedBuffer::~DoubleSidedBuffer() {
  free(positiveMemoryTape);
  free(negativeMemoryTape);
}

byte DoubleSidedBuffer::getCurrentValue() {
  if (currentCell) { // Positive tape
    if (currentCell >= positiveMemorySize) return 0; // If tape is too small, return zero
    return positiveMemoryTape[currentCell]; // Else return current cell value

  } else { // Negative tape
    if ((currentCell * -1) >= negativeMemorySize) return 0; // If tape is too small, return zero
    return negativeMemoryTape[currentCell * -1]; // Else return current cell value
  }
}

void DoubleSidedBuffer::setCurrentValue(byte value) {
  if (currentCell) { // Positive tape
    if (currentCell >= positiveMemorySize) {
      // If tape is too small, expand it
      int newMemorySize = (currentCell + 1) * 1.5;
      positiveMemoryTape = (byte*)realloc(positiveMemoryTape, newMemorySize);

      // Zero only new cells, except for the first new one
      memset(positiveMemoryTape + positiveMemorySize + 1, 0, newMemorySize - positiveMemorySize - 1);
      positiveMemorySize = newMemorySize; // Update tape size
    }
    positiveMemoryTape[currentCell] = value; // Set current cell value

  } else { // Negative tape
    if ((currentCell * -1) >= negativeMemorySize) {
      // If tape is too small, expand it
      int newMemorySize = ((currentCell * -1) + 1) * 1.5;
      negativeMemoryTape = (byte*)realloc(negativeMemoryTape, newMemorySize);

      // Zero only new cells, except for the first new one
      memset(negativeMemoryTape + negativeMemorySize + 1, 0, newMemorySize - negativeMemorySize - 1);
      negativeMemorySize = newMemorySize; // Update tape size
    }
    negativeMemoryTape[currentCell * -1] = value; // Set current cell value
  }
}