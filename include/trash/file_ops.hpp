#ifndef FILE_OPS_HPP
#define FILE_OPS_HPP

#include <iostream>
#include <filesystem>
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

inline void add_to_trash(TrashSettings settings, std::string path, bool verbose){
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

inline void print_tree(const std::filesystem::path& path, int depth = 0) {
    std::string indent(depth * 4, '-'); 

    if (std::filesystem::is_directory(path)) {
        std::cout << indent << "DIR:  " << path.filename().string() << "\n";
        for (auto& entry : std::filesystem::directory_iterator(path)) {
            print_tree(entry.path(), depth + 1);
        }
    } else {
        std::cout << indent << "FILE: " << path.filename().string() << "\n";
    }
}

inline void see_trash(TrashSettings settings) {
    std::filesystem::path root_path(settings.trash_path);
    if (std::filesystem::exists(root_path)) {
        print_tree(root_path);
    } else {
        std::cerr << "Error: Path does not exist: " << root_path << "\n";
    }
}

inline void del_trash(TrashSettings settings){
  std::filesystem::remove_all(settings.trash_path);
  std::filesystem::path dir_path = settings.trash_path;
  std::filesystem::create_directory(dir_path);
}

}

#endif
