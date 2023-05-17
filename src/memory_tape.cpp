// memory_tape.cpp
// (C) Martin Alebachew, 2023

#include "memory_tape.hpp"

DoubleSidedTape::DoubleSidedTape() : currentCell(0), positiveMemorySize(tapeInitialSize), negativeMemorySize(tapeInitialSize) {
  positiveMemoryTape = (byte*)calloc(tapeInitialSize, sizeof(byte));
  negativeMemoryTape = (byte*)calloc(tapeInitialSize, sizeof(byte));
}

DoubleSidedTape::~DoubleSidedTape() {
  free(positiveMemoryTape);
  free(negativeMemoryTape);
}

const byte DoubleSidedTape::getCurrentValue() const {
  if (currentCell > 0) { // Positive tape
    if (currentCell > positiveMemorySize) return 0; // If tape is too small, return zero
    return positiveMemoryTape[currentCell - 1]; // Else return current cell value

  } else { // Negative tape / zero index
    if ((currentCell * -1) >= negativeMemorySize) return 0; // If tape is too small, return zero
    return negativeMemoryTape[currentCell * -1]; // Else return current cell value
  }
}

void DoubleSidedTape::setCurrentValue(byte value) {
  if (currentCell > 0) { // Positive tape
    if (currentCell > positiveMemorySize) {
      // If tape is too small, expand it
      int newMemorySize = currentCell * 1.5;
      positiveMemoryTape = (byte*)realloc(positiveMemoryTape, newMemorySize);

      // Zero only new cells, except for the first new one
      memset(positiveMemoryTape + positiveMemorySize + 1, 0, newMemorySize - positiveMemorySize - 1);
      positiveMemorySize = newMemorySize; // Update tape size
    }
    positiveMemoryTape[currentCell - 1] = value; // Set current cell value

  } else { // Negative tape / zero index
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

std::string operator *(std::string rep, unsigned int n) {
    std::string output = "";
    while (n--) {
        output += rep;
    }

    return output;
}

void DoubleSidedTape::showTape() const {
  constexpr int minPadding = 2;
  constexpr int cellLength = 3 + minPadding; // Modify the padding above, not this value!

  int tapeLength = negativeMemorySize + positiveMemorySize;
  std::string seperators = " " + std::string("-") * (cellLength);
  seperators = seperators * tapeLength;

  std::string values, indexes = " ";
  for (int i = negativeMemorySize - 1; i >= 0 ; i--) {
    std::string valueString = std::to_string(negativeMemoryTape[i]);
    int valueLength = valueString.length();
    int paddingBefore = (cellLength - valueLength) / 2;
    int paddingAfter = cellLength - valueLength - paddingBefore;
    values += "|" + ((std::string)" " * paddingBefore) + valueString + ((std::string)" " * paddingAfter);

    std::string indexString = std::to_string(i * -1);
    int indexLength = indexString.length();
    paddingBefore = (cellLength - indexLength) / 2;
    paddingAfter = cellLength - indexLength - paddingBefore + 1;
    indexes += ((std::string)" " * paddingBefore) + indexString + ((std::string)" " * paddingAfter);
  }

  for (int i = 0; i < positiveMemorySize; i++) {
    std::string valueString = std::to_string(positiveMemoryTape[i]);
    int valueLength = valueString.length();
    int paddingBefore = (cellLength - valueLength) / 2;
    int paddingAfter = cellLength - valueLength - paddingBefore;
    values += "|" + ((std::string)" " * paddingBefore) + valueString + ((std::string)" " * paddingAfter);

    std::string indexString = std::to_string(i + 1);
    int indexLength = indexString.length();
    paddingBefore = (cellLength - indexLength) / 2;
    paddingAfter = cellLength - indexLength - paddingBefore + 1;
    indexes += ((std::string)" " * paddingBefore) + indexString + ((std::string)" " * paddingAfter);
  }

  values += "|";

  std::string pointerArrow;
  if (currentCell > positiveMemorySize) {
    // If cell is positively out of bounds
    int totalTapeSize = negativeMemorySize + positiveMemorySize;
    int arrowLocation = totalTapeSize * (cellLength + 1);
    pointerArrow = (std::string)" " * arrowLocation + "(" + std::to_string(currentCell) + ") -->";
  } else if ((currentCell * -1) >= negativeMemorySize) {
    // If cell is negatively out of bounds
    pointerArrow = "<-- (" + std::to_string(currentCell) + ")";
  } else {
    // If cell is in bounds
    int passedCells = currentCell + negativeMemorySize - 1;
    int arrowLocation = 1 + passedCells * (cellLength + 1) + cellLength * 0.5;
    pointerArrow = std::string(" ") * arrowLocation + "^";
  };

  std::cout << seperators << std::endl;
  std::cout << values << std::endl;
  std::cout << seperators << std::endl;
  std::cout << indexes << std::endl;
  std::cout << pointerArrow << std::endl << std::endl;
}