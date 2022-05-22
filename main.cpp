#include "src/DataBase.hpp"
#include "src/Parser.hpp"

int main() {
  DataBase* db = new DataBase();
  Parser p = Parser("/home/liangyuyao/CppStudy/0522Format/input.txt", db);
  db->format("../result.txt");
  return 0;
}