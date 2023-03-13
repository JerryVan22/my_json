#ifndef _MY_JSON_H_
#define _MY_JSON_H_
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <map>
#include <variant>
#include <vector>

namespace my_json {
struct Node;
using Null = std::monostate;
using Int = int64_t;
using Decimal = double;
using Bool = bool;
using String = std::string;
using Array= std::vector<Node>;
using Object = std::map<std::string, Node>;
using Value = std::variant<Null, Int, Decimal, Bool, String, Object>;

enum class TYPE { Null, Int, Decimal, Bool, String, Object, Value };
enum class PARSE_STATUS { OK, EXPECT_VALUE, INVALID_VALUE, ROOT_NOT_SING };

struct Node {
  Value value;
};

PARSE_STATUS parse(const char *json,my_json::TYPE & type);



}  // namespace my_json

#endif