#include "Parser.hpp"

#include <iostream>
#include <fstream>
#include <string>

#include "Debug.h"
#include "Medium.hpp"
#include "Conductor.hpp"

Parser::Parser(std::string fpath, DataBase* db) {
  InitPtInfList();

  std::fstream input;
  input.open(fpath, std::ios::in);
  assert(input.is_open());
  std::cout << "input file path:" << fpath << std::endl;

  Medium* medium = nullptr;
  std::pair<const Token, std::regex>* match_pattern = nullptr;
  NameObj* name_obj = nullptr;
  Conductor* cdt = nullptr;
  Window* window = nullptr;
  std::vector<Token> stack;
  std::vector<NameObj*> name_obj_list;
  Block block;
  std::smatch sm;

  std::string line;
  while(std::getline(input, line)) {

    for (auto& pt_inf_kv : _token_map) {
      if (std::regex_search(line, sm, pt_inf_kv.second)) {
        // std::cout << line << ",tag = " << pt_inf_kv.first << "\n";
        match_pattern = &pt_inf_kv;
        break;
      }
    }

    ASSERT(match_pattern, "Can not parse data = %s", line.c_str());
    Token tk = match_pattern->first;

    switch (tk) {
      case Token::qbem_beg: {
        stack.push_back(tk);
      } break;
      case Token::medium_beg: {
        stack.push_back(tk);

        medium = new Medium();
        name_obj_list.push_back(medium);
      } break;
      case Token::block_beg: {
        stack.push_back(tk);

        block.reset();
        name_obj_list.push_back(&block);
      } break;
      case Token::conductor_beg: {
        stack.push_back(tk);
        
        cdt = new Conductor();
        name_obj_list.push_back(cdt);
      } break;
      case Token::task_beg: {
        stack.push_back(tk);
      } break; 
      case Token::cap_beg: {
        stack.push_back(tk);

        std::getline(input, line);
        ASSERT(std::regex_search(line, sm, std::regex("[\\w_]+")), "Data missing");
        db->set_task(sm[0]);
      } break;
      case Token::comment_beg: {
        stack.push_back(tk);
      } break;
      case Token::window_beg: {
        stack.push_back(tk);

        window = new Window();
        block.reset();
      } break;
      case Token::name: {
        ASSERT(name_obj_list.size(), "No Name_object created");
        name_obj = name_obj_list.back();
        
        ASSERT(sm.size() >= 2, "Data missing");
        name_obj->set_name(sm[1]);
      } break;
      case Token::basepoint: {
        ASSERT(sm.size() >= 4, "Data missing");
        block.set_base(stof(sm[1].str()), stof(sm[2].str()), stof(sm[3].str()));
      } break;
      case Token::v1: {
        ASSERT(sm.size() >= 4, "Data missing");
        block.set_v1(stof(sm[1].str()), stof(sm[2].str()), stof(sm[3].str()));
      } break;
      case Token::v2: {
        ASSERT(sm.size() >= 4, "Data missing");
        block.set_v2(stof(sm[1].str()), stof(sm[2].str()), stof(sm[3].str()));
      } break;
      case Token::hvector: {
        ASSERT(sm.size() >= 4, "Data missing");
        block.set_h(stof(sm[1].str()), stof(sm[2].str()), stof(sm[3].str()));
      } break;
      case Token::diel: {
        ASSERT(stack.back() == Token::medium_beg, "Error construction");
        ASSERT(sm.size() >= 2, "Data missing");
        medium->set_diel(stof(sm[1]));
      } break;
      case Token::block_end: {
        name_obj_list.pop_back();

        ASSERT(stack.back() == Token::block_beg, "Error construction");
        stack.pop_back();
        switch (stack.back()) {
          case Token::medium_beg:     medium->set_block(&block);  break;
          case Token::conductor_beg:  cdt->set_block(&block);     break;
          default: PANIC("Unhandled block when stack.back() = %d", (int)stack.back());
        }
      } break;
      case Token::medium_end: {
        name_obj_list.pop_back();

        ASSERT(stack.back() == Token::medium_beg, "Error construction");
        stack.pop_back();
        db->insertMediun(medium);
        medium = nullptr;
      } break;
      case Token::conductor_end: {
        name_obj_list.pop_back();

        ASSERT(stack.back() == Token::conductor_beg, "Error construction");
        stack.pop_back();
        db->insertConductor(cdt);
        cdt = nullptr;
      } break;
      case Token::comment_end: {  
        ASSERT(stack.back() == Token::comment_beg, "Error construction");
        stack.pop_back();
      } break;
      case Token::cap_end: {
        ASSERT(stack.back() == Token::cap_beg, "Error construction");
        stack.pop_back();
      } break;
      case Token::task_end: {
        ASSERT(stack.back() == Token::task_beg, "Error construction");
        stack.pop_back();
      } break;
      case Token::window_end: {
        ASSERT(stack.back() == Token::window_beg, "Error construction");
        stack.pop_back();

        window->set_v1(block.get_v1());
        window->set_v2(block.get_v2());
        db->set_window(window);

        window = nullptr;
      } break;
      case Token::qbem_end: {
        ASSERT(stack.back() == Token::qbem_beg, "Error construction");
        stack.pop_back();
      } break;

      default: {
        PANIC("Unhandled data, tag = %d", (int)tk);
      }
    }

    match_pattern = nullptr;
  }

  input.close();
}

void Parser::InitPtInfList() {
  struct PatternInit {
    std::string str;
    Token token;
  };
  PatternInit pattern_init_list[] = {
    {.str = "\\s*<qbem>", .token = Token::qbem_beg},
    {.str = "\\s*<medium>", .token = Token::medium_beg},
    {.str = "\\s*<block>", .token = Token::block_beg},
    {.str = "\\s*name\\s*(\\w+)", .token = Token::name},
    {.str = "\\s*<conductor>", .token = Token::conductor_beg},
    {.str = "\\s*<task>", .token = Token::task_beg},
    {.str = "\\s*<capacitance>", .token = Token::cap_beg},
    {.str = "\\s*\\/\\*", .token =Token::comment_beg},
    {.str = "\\s*<window>", .token =Token::window_beg},
    {.str = "\\s*basepoint\\((-*\\d+\\.*\\d*),\\s*(-*\\d+\\.*\\d*),\\s*(-*\\d+\\.*\\d*)\\)", .token = Token::basepoint},
    {.str = "\\s*v1\\((-*\\d+\\.*\\d*),\\s*(-*\\d+\\.*\\d*),\\s*(-*\\d+\\.*\\d*)\\)", .token = Token::v1},
    {.str = "\\s*v2\\((-*\\d+\\.*\\d*),\\s*(-*\\d+\\.*\\d*),\\s*(-*\\d+\\.*\\d*)\\)", .token = Token::v2},
    {.str = "\\s*hvector\\((-*\\d+\\.*\\d*),\\s*(-*\\d+\\.*\\d*),\\s*(-*\\d+\\.*\\d*)\\)", .token = Token::hvector},
    {.str = "\\s*diel (-*\\d+\\.*\\d*)", .token = Token::diel},
    {.str = "\\s*\\[/qbem\\]", .token = Token::qbem_end},
    {.str = "\\s*\\[/medium\\]", .token = Token::medium_end},
    {.str = "\\s*\\[/block\\]", .token = Token::block_end},
    {.str = "\\s*\\[/conductor\\]", .token = Token::conductor_end},
    {.str = "\\s*\\[/task\\]", .token = Token::task_end},
    {.str = "\\s*\\[/capacitance\\]", .token = Token::cap_end},
    {.str = "\\s*\\*\\/", .token =Token::comment_end},
    {.str = "\\s*\\[/window\\]", .token = Token::window_end},
  };

  for (auto pattern_init : pattern_init_list) {
    std::regex pattern(pattern_init.str);
    _token_map[pattern_init.token] = pattern;
  };
}