#ifndef FILE_OPS_HPP
#define FILE_OPS_HPP

#include <iostream>
#include <filesystem>
#include "structs/trash/_settings.hpp"

namespace trash {

inline void add_file_to_trash(TrashSettings settings, std::string path, bool verbose){
  if(settings.confirmation){
    char input = ' ';
    while(input != 'y' || input != 'n') {
      std::cout << "Would you like to delete " << path << "? (y/n)\n";
      std::cin >> input;
    }
    if(input == 'n'){
      return;
    }
  } 

  // get file name
  std::filesystem::path full_path = path; 
  std::filesystem::path trash_path = settings.trash_path; 
  std::filesystem::path file_name = full_path.filename();

  // join paths -- ps i hate this overload
  std::filesystem::path new_path =  trash_path / file_name; // "trash/path/{file_name}" 

  try {
    std::filesystem::rename(full_path, new_path);
    if(verbose) std::cout << "File moved to [" << new_path.c_str() << "]\n";
    std::cout << "File Moved [" << file_name.c_str() << "]\n";
  }
  catch(const std::filesystem::filesystem_error& e){
    std::cout << "Error moving [" << file_name.c_str() << "] to trash\n";
  }

}

}

#endif
