// double_sided_buffer.hpp
// (C) Martin Alebachew, 2023

#pragma once
#include <vector>
#include <iostream>

constexpr int tapeInitialSize = 5;

typedef unsigned char byte;

class DoubleSidedBuffer {
private:
  byte *positiveMemoryTape;
  byte *negativeMemoryTape; // Includes zero index
  int positiveMemorySize; // Element count
  int negativeMemorySize; // Element count

public:
  int currentCell; // Zero-based index

  DoubleSidedBuffer();
  ~DoubleSidedBuffer();

  const byte getCurrentValue() const;
  void setCurrentValue(byte value);
  void showTape() const;
};