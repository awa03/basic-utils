#include <iostream>
#include "flags.hpp"

int main(int argc, char** argv){
  auto parsed_flags = flags::parse_flags(argc, argv);
  flags::handle_flags(parsed_flags);
}
