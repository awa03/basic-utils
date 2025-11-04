#include <iostream>
#include "flags.hpp"
#include "install/install.hpp"

int main(int argc, char** argv){
  install::check_installed_help();
  auto parsed_flags = flags::parse_flags(argc, argv);
  flags::handle_flags(parsed_flags);
}
