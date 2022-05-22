#pragma once

#include "Coord.hpp"
#include "NameObj.hpp"

class Block;

class Block: public NameObj {
 public:
  // constructor
  Block() = default;
  ~Block() = default;
 
  // getter
  auto get_base() { return _base; }
  auto get_v1() { return _v1; }
  auto get_v2() { return _v2; }

  // setter
  void set_base(double x, double y, double z) { _base.set_xyz(x, y, z); }
  void set_v1(double x, double y, double z) { _v1.set_xyz(x, y, z); }
  void set_v2(double x, double y, double z) { _v2.set_xyz(x, y, z); }  
  void set_h(double x, double y, double z) { _h.set_xyz(x, y, z); }  

  // operator
  Block& operator=(const Block& other);

  // function
  void reset();
  Coord cal_c1();
  Coord cal_c7();

 private:
  // members
  Coord _base;  // basepoint
  Coord _v1;
  Coord _v2;
  Coord _h;
};

///////// inline ////////////

inline Block& Block::operator=(const Block& other) {
  _name = other._name;
  _base = other._base;
  _v1 = other._v1;
  _v2 = other._v2;
  _h = other._h;
  return *this;
}