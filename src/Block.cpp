#include "Block.hpp"

void Block::reset() {
  _name = "";
  _base.reset();
  _v1.reset();
  _v2.reset();
  _h.reset();
}

Coord Block::cal_c1() {
  Coord a = _base + _v1;
  Coord b = _base + _v2 + _h;
  Coord c1;
  c1.set_x(std::min(a.get_x(), b.get_x()));
  c1.set_y(std::min(a.get_y(), b.get_y()));
  c1.set_z(std::min(a.get_z(), b.get_z()));
  return c1;
}

Coord Block::cal_c7() {
  Coord a = _base + _v1;
  Coord b = _base + _v2 + _h;
  Coord c7;
  c7.set_x(std::max(a.get_x(), b.get_x()));
  c7.set_y(std::max(a.get_y(), b.get_y()));
  c7.set_z(std::max(a.get_z(), b.get_z()));
  return c7;
}