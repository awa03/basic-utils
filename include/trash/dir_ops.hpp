#ifndef DIR_OPS_HPP
#define DIR_OPS_HPP

#include <filesystem>
#include "structs/_flags.hpp"
#include "structs/trash/_settings.hpp"

namespace trash {

  inline int is_dir(std::string path){
    if(std::filesystem::exists(path)){
      return (std::filesystem::is_directory(path))
        ? DIR  
        : FILE;
    }
    else {
      return NAP; // 2
    }
  }

  inline void add_dir_to_trash(flags::Flags& parsed_flags, std::string path){
    
  }
}

#endif
