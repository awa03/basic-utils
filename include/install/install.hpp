#ifndef INSTALL_HPP
#define INSTALL_HPP
#include <iostream>
#include <cstdlib> // for env variables
#include <filesystem>
#include <fstream>
#include <string>
#include "structs/_flags.hpp"
#include "logger/log_ops.hpp"
#include <unistd.h>  // for readlink()
//
// Use local bin directory (no root required)
#define INSTALL_DIR "/usr/local/bin"
#define EXECUTABLE_NAME "basic-utils"
#define DETECT_FILE_NAME ".basic_utils_installed"

namespace install {

inline void make_installed_file(){
  const std::filesystem::path home = std::getenv("HOME");
  std::filesystem::path installed_path = home / DETECT_FILE_NAME;
  std::ofstream installed_file(installed_path);
  if(!installed_file.is_open()){
    std::cerr << "File could not be created at " << installed_path << "\n";
  }
}

inline bool check_installed(){
  const std::filesystem::path home = std::getenv("HOME");
  std::cout << "Added to " << home.string() << "\n"; 
  const std::filesystem::path path_to_detection = home / DETECT_FILE_NAME;
  // /.config/basic_utils/.installed
  
  // check home
  if(!std::filesystem::exists(path_to_detection)){
    return false;
  }
  return true;
}

inline std::filesystem::path get_executable_path() {
  char buf[4096];
  ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
  if (len == -1) {
    throw std::runtime_error("Failed to read /proc/self/exe");
  }
  buf[len] = '\0';
  return std::filesystem::path(buf);
}

inline void install(flags::Flags& parsed_flags){
  const std::string shell_path = std::getenv("SHELL");
  const std::string home = std::getenv("HOME");
  if(shell_path.empty()){
    std::cout << "Error getting shell environment\n";   
    return;
  }
  // usr/bin/bash ----> /home/aiden/.bashrc
  const std::filesystem::path shell_path_obj(shell_path); 
  const std::filesystem::path pred_path = home;
  const std::filesystem::path shellrc_path = pred_path / ("." + shell_path_obj.filename().string() + "rc");
  
  if(std::filesystem::exists(shellrc_path)){
    try {
      auto this_path = get_executable_path();
      std::filesystem::path destination = std::filesystem::path(INSTALL_DIR) / EXECUTABLE_NAME;
      
      // Create install directory if it doesn't exist
      std::filesystem::create_directories(INSTALL_DIR);
      
      // Copy executable with proper permissions
      std::filesystem::copy(this_path, destination, 
                           std::filesystem::copy_options::overwrite_existing);
      
      // Set executable permissions
      std::filesystem::permissions(destination,
                                  std::filesystem::perms::owner_all |
                                  std::filesystem::perms::group_read | std::filesystem::perms::group_exec |
                                  std::filesystem::perms::others_read | std::filesystem::perms::others_exec);
      
      std::ofstream out_file(shellrc_path, std::ios::app);
      if(!out_file.is_open()){
        std::cout << "Error output file " << shellrc_path.string() << " did not open correctly...";
        return;
      }
      
      out_file << "\n# Added by installer\n";
      out_file << "export PATH=\"" << INSTALL_DIR << ":$PATH\"\n";
      out_file << "# End installer\n";
      
      make_installed_file();
      
      std::cout << "Installed Basic Utils!\n";
      std::cout << "\tExecutable installed to: " << destination << "\n";
      std::cout << "\tAliases installed to: " << shellrc_path.string() << "\n";
      std::cout << "\tDetection installed to: " << home << "/" << DETECT_FILE_NAME << "\n";
      std::cout << "\nPlease run: source " << shellrc_path.string() << "\n";
      std::cout << "Or restart your terminal.\n";
      
    } catch(const std::exception& e) {
      std::cerr << "Installation failed: " << e.what() << "\n";
      std::cerr << "Note: Installing to " << INSTALL_DIR << " may require sudo.\n";
    }
  }
  else {
    std::cout << "Error " << shellrc_path.string() << " does not exist...\n"; 
  }
}

inline void check_installed_help(){
  if(check_installed()){
    
  }
  else {
    std::cout << "Basic-Utils is NOT Installed..!\n";
    std::cout << "Please Run:\n";
    std::cout << "\tbasic-utils --install\n";
    std::cout << "Or with sudo if permission denied:\n";
    std::cout << "\tsudo basic-utils --install\n";
  }
}

// TODO
inline void uninstall(flags::Flags& parsed_flags){
}

}

#endif
