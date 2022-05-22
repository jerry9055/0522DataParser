#pragma once

#include "Block.hpp"
#include "NameObj.hpp"

class Conductor;
 
class Conductor : public NameObj {
 public:
  // constructor
  Conductor() = default;
  ~Conductor() = default;

  // getter
  auto get_block() { return _block; }

  // setter
  void set_block(Block* block) { _block = *block; }

 private:
  // members
  Block _block;

};