#include "DataBase.hpp"

#include <assert.h>
#include <fstream>
#include <iostream>

DataBase::~DataBase() {
  for (auto m : _medium_list) {
    delete m;
  }
  _medium_list.clear();

  if (_window) delete _window;
}

void DataBase::format(std::string opath) {

  std::fstream output;
  std::cout << "output file path:" << opath << std::endl;
  output.open(opath, std::ios::out);
  assert(output.is_open());

  output << "begin_geo\n";
  
  for (auto m : _medium_list) {
    output << "boundary " << m->get_diel() << " ";
    m->get_block().cal_c1().print(output);
    output << " ";
    m->get_block().cal_c7().print(output);
    output << std::endl;
  }
  
  int num = 0;
  int main_index = -1;
  for (size_t index = 0; index < _conductor_list.size(); ++index) {
    Conductor* cdt = _conductor_list[index];

    output << "conductor " << ++num << " ";
    cdt->get_block().cal_c1().print(output);
    output << " ";
    cdt->get_block().cal_c7().print(output);
    output << std::endl;

    if (cdt->get_name().compare(_task) == 0) {
      main_index = index;
    }
  }

  if (main_index > 0) {
    output << "main_conductor " << main_index << std::endl;
  }
  output << "end_geo\n";
  output.flush();

  output.close();
}