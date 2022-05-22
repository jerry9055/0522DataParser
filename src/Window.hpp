#pragma once

#include "Coord.hpp"

class Window;

class Window {
 public:
  // constructor
  Window() = default;
  ~Window() = default;

  // getter
  auto get_v1() { return _v1; }
  auto get_v2() { return _v2; }

  // setter
  void set_v1(const Coord& c) { _v1 = c; }
  void set_v2(const Coord& c) { _v2 = c; }  

 private:
  // members
  Coord _v1;
  Coord _v2;
};