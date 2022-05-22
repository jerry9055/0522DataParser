#pragma once 

#include "Block.hpp"
#include "NameObj.hpp"

class Medium;

class Medium : public NameObj {
 public:
  // constructor
  Medium() = default;
  ~Medium() = default;

  // getter
  auto get_block() { return _block; }
  auto get_diel() { return _diel; }

  // setter
  void set_block(Block* block) { _block = *block; }
  void set_diel(double diel) { _diel = diel; }

 private:
  // members
  Block _block;
  double _diel;
};