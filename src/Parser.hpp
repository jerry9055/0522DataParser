#pragma once

#include <regex>
#include <map>

#include "DataBase.hpp"

class Parser;
enum Token {
  none,

  qbem_beg,
  medium_beg,
  block_beg,
  conductor_beg,
  task_beg,
  cap_beg,
  comment_beg,
  window_beg,

  name,
  basepoint,
  v1,
  v2,
  hvector,
  diel,

  qbem_end,
  medium_end,
  block_end,
  conductor_end,
  task_end,
  cap_end,
  comment_end,
  window_end,
};

struct PatternInf {
  std::regex pattern;
  Token token;
};

class Parser {
 public:
  Parser(std::string fpath, DataBase* db);
  ~Parser() = default;

 private:
  // function
  void InitPtInfList();
  
  // members
  std::map<Token, std::regex> _token_map;
};