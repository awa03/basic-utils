#ifndef FLAGS_HPP
#define FLAGS_HPP

#include <iostream>
#include <string>
#include <vector>
#include "cxxopts.hpp"
#include "opts/help.hpp"
#include "join/join_files.hpp"
#include "structs/_flags.hpp"
#include "trash/init.hpp"
#include "trash/file_ops.hpp"
#include "install/install.hpp"

namespace flags {

inline Flags parse_flags(int argc, char** argv) {
  cxxopts::Options options("basic-utils", "Provides basic utilities");
  
  options.add_options()
    ("h,help", "Show help")
    ("v,verbose", "Enable verbose output")
    ("j,join", "Join files or perform join operation")
    ("add_trash", "Add item(s) to trash")
    ("del_trash", "Delete item(s) from trash")
    ("see_trash", "View items in trash")
    ("install", "Run installation process")
    ("o,output", "Output filename", cxxopts::value<std::string>())  
    ("i,input", "Input filenames", cxxopts::value<std::vector<std::string>>());
  
  options.parse_positional({"input"});
  options.positional_help("[files...]");
  
  auto result = options.parse(argc, argv);
  
  // construct flag object
  Flags parsed_flags;
  parsed_flags.help = result.count("help") > 0;
  parsed_flags.verbose = result.count("verbose") > 0;
  parsed_flags.join = result.count("join") > 0;
  parsed_flags.add_trash = result.count("add_trash") > 0;
  parsed_flags.del_trash = result.count("del_trash") > 0;
  parsed_flags.see_trash = result.count("see_trash") > 0;
  parsed_flags.install = result.count("install") > 0;

  // handle input and output files
  if (result.count("output"))
    parsed_flags.output = result["output"].as<std::string>();
  
  if (result.count("input"))
    parsed_flags.inputs = result["input"].as<std::vector<std::string>>();
  
  if (result.count("input"))
    parsed_flags.inputs = result["input"].as<std::vector<std::string>>();
  
  return parsed_flags;
}

inline void handle_flags(Flags& parsed_flags) {
  // Refactor if more pages needed
  if (parsed_flags.help) {
    opts::render_help_menu();
  } 

  if (parsed_flags.join){

    // handle no files specified
    if(parsed_flags.inputs.size() == 0) {
      opts::input_help_menu();
      return; 
    }
    else if(parsed_flags.output.empty()) {
      opts::output_help_menu();
      return;
    }

    // run operation
    join::join_files(parsed_flags); 
  }
  
  if(parsed_flags.add_trash){

    if(parsed_flags.inputs.size() == 0) {
      opts::input_help_menu();   
      return;
    }

    trash::handle_trash(parsed_flags);
  }

  if(parsed_flags.see_trash){
    // refactor
    trash::see_trash(trash::get_default_settings()); 
  }

  if(parsed_flags.del_trash){
    trash::del_trash(trash::get_default_settings());
  }

  if(parsed_flags.install){
    install::install(parsed_flags);  
  }

}

} // namespace flags

#endif // FLAGS_HPP
