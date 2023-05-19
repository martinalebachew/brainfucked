// memory_tape.hpp
// (C) Martin Alebachew, 2023

#pragma once
#include <vector>
#include <iostream>

constexpr int tapeInitialSize = 5;

typedef unsigned char byte;

class DoubleSidedTape {
private:
  byte *positiveMemoryTape;
  byte *negativeMemoryTape; // Includes zero index
  int positiveMemorySize; // Element count
  int negativeMemorySize; // Element count
  void showTapeImpl(int from, int to) const;

public:
  int currentCell; // Zero-based index

  DoubleSidedTape();
  ~DoubleSidedTape();

  const byte getCurrentValue() const;
  void setCurrentValue(byte value);
  void showTape() const;
};