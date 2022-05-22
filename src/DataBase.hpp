#pragma once

#include <vector>

#include "Conductor.hpp"
#include "Medium.hpp"
#include "Window.hpp"

class DataBase;

class DataBase {
 public:
  // constructor
  DataBase(): _window(nullptr) { }
  ~DataBase();

  // getter
  auto get_task() { return _task; }
  auto get_window() { return _window; }

  // setter
  void set_task(std::string task) { _task = task; }
  void set_window(Window* w);

  // function
  void insertMediun(Medium* m);
  void insertConductor(Conductor* cdt);
  void format(std::string opath);

 private:
  // members
  std::vector<Medium*> _medium_list;
  std::vector<Conductor*> _conductor_list;
  std::string _task;
  Window* _window; 
};

///////////// inline ///////////////

inline void DataBase::insertMediun(Medium* m) {
  if (m) {
    _medium_list.push_back(m);
  }
}

inline void DataBase::insertConductor(Conductor* cdt) {
  if (cdt) {
    _conductor_list.push_back(cdt);
  }
}

inline void DataBase::set_window(Window* w) {
  if (w) _window = w;
}