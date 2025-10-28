#ifndef JOIN_FILES_HPP
#define JOIN_FILES_HPP
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "structs/_flags.hpp"

namespace join {

inline std::string get_all_file_contents(flags::Flags& parsed_flags){
  std::string contents = "";  
  for (auto& file : parsed_flags.inputs){
    std::ifstream open_file(file);
    if(!open_file.is_open()) {
      std::cerr << "Error Opening " + file + "\n";
      continue;
    }

    std::stringstream buff;
    buff << open_file.rdbuf();

    open_file.close();

    contents += buff.str();

    if(parsed_flags.verbose){
      std::cout << "Added: " << file << "\n";
      std::cout << "\nContents: " << buff.str() << "\n";
    }
  }
  return contents;
}

inline bool add_contents_to_file(flags::Flags& parsed_flags, std::string contents) {
  std::string& file = parsed_flags.output;
  std::ofstream out_file;
  out_file.open(file);

  if(!out_file.is_open()){
    std::cerr << "Error Opening " + file + "\n";
    return 1;
  }

  out_file << contents;
  out_file.close();

  // no err
  return 0;
}

inline void join_files(flags::Flags& parsed_flags) {
  std::string contents = get_all_file_contents(parsed_flags);
  add_contents_to_file(parsed_flags, contents);
}

}

#endif
