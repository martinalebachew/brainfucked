// processor.cpp
// (C) Martin Alebachew, 2023

#include "processor.hpp"

Processor::Processor(std::string instructionBuffer) {
  this->instructionBuffer = instructionBuffer; 
}

void Processor::execute() {
  int instructionPointer = 0;
  std::cout << "Executing command:\n" << instructionBuffer << std::endl;

  while (instructionPointer < instructionBuffer.length()) {
    switch (instructionBuffer[instructionPointer]) {
      case '>':
        memory.currentCell++;
        break;

      case '<':
        memory.currentCell--;
        break;

      case '+':
        memory.setCurrentValue(memory.getCurrentValue() + 1);
        break;

      case '-':
        memory.setCurrentValue(memory.getCurrentValue() - 1);
        break;

      case '.':
        std::cout << (char)memory.getCurrentValue();
        break;

      case ',':
        // TODO: Implement input command
        break;

      case '[':
        // Unsafe! Assumes ']' exists
        if (memory.getCurrentValue() == 0) {
          do {
            instructionPointer++;
          } while (instructionBuffer[instructionPointer] != ']'); // Account for incrementation at the end of this loop
        }
        break;

      case ']':
        // Unsafe! Assumes '[' exists
        if (memory.getCurrentValue() != 0) {
          do {
            instructionPointer--;
          } while (instructionBuffer[instructionPointer] != '['); // Account for incrementation at the end of this loop          
        }
        break;

      default:
        throw std::runtime_error("Unknown command: " + instructionBuffer[instructionPointer]);
    }

    instructionPointer++;
  }
}

void Processor::showTape() const {
  memory.showTape();
}