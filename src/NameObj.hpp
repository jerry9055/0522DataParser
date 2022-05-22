#pragma once 

#include <string>

class NameObj;

class NameObj {
 public:
  // constructor
  NameObj() = default;
  ~NameObj() = default;
  
  // getter
  auto get_name() { return _name; }

  // setter
  void set_name(std::string name) { _name = name; }

 protected:
  // members
  std::string _name;
};