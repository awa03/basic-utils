#ifndef _FLAGS_HPP
#define _FLAGS_HPP

#include <string>
#include <vector>

namespace flags {

struct Flags {
  bool help = false;
  bool help_two = false;
  bool verbose = false;
  bool join = false;
  bool add_trash = false;
  bool del_trash = false;
  bool see_trash = false;
  bool install = false;
  std::string output;
  std::vector<std::string> inputs;
};

}

#endif
