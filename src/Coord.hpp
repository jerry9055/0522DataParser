#pragma once

#include <ostream>

class Coord;

class Coord {
 public:
  // constructor
  Coord() = default;
  ~Coord() = default;

  // getter 
  auto get_x() { return _x; }
  auto get_y() { return _y; }
  auto get_z() { return _z; }

  // setter
  void set_x(double x) { _x = x; }
  void set_y(double y) { _y = y; }
  void set_z(double z) { _z = z; }
  void set_xyz(double x, double y, double z) { _x = x; _y = y; _z = z; }

  Coord& operator=(const Coord& other);
  Coord operator+(const Coord& other);

  // function
  void reset() { _x = 0; _y = 0; _z = 0; }
  void print(std::ostream& stream);

 private:
  // members
  double _x;
  double _y;
  double _z;
};

///////////// inline //////////

inline Coord& Coord::operator=(const Coord& other) {
  _x = other._x;
  _y = other._y;
  _z = other._z;
  return *this;
}

inline Coord Coord::operator+(const Coord& other) {
  Coord tmp;
  tmp._x = _x + other._x;
  tmp._y = _y + other._y;
  tmp._z = _z + other._z;
  return tmp;
}

inline void Coord::print(std::ostream& stream) {
  stream << _x << " " << _y << " " << _z;
  stream.flush(); 
}