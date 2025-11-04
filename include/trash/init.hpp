#ifndef INIT_HPP
#define INIT_HPP

#include <iostream>
#include <string>
#include <filesystem>
#include "structs/_flags.hpp"
#include "structs/trash/_settings.hpp"
#include "trash/settings.hpp"
#include "trash/file_ops.hpp"

namespace trash{

  #define if_verbose if(parsed_flags.verbose)


    /* PLAN ---------------------------------------------------------------
     * also make sure to check if directory here. idk how im gonna squeeze that in a nice format but
     * curr_setting = get_curr_settings();
     * if(!curr_setting.trash_path.exists()) // check if set doesnt exists
     *    print "path doesnt exist" 
     *    if(default_settings.trash_path.exists()) // try default
     *      return default 
     *    else 
     *      make dir for settings
     * else 
     *    use the curr settings 
     * */  

  inline TrashSettings validate_settings(){
    return get_default_settings();
  }

  // inline void update_settings(TrashSettings){
  //   if(get_current_settings() != settings) {
  //     // set settings
  //   }
  // }

  inline void handle_trash(flags::Flags& parsed_flags){
    auto settings = validate_settings();
    // update_settings(settings); 

    // handle if passed
    // print rel info
    if_verbose std::cout << "Attempting to use trashpath: " << settings.trash_path << "\n";
    

    for(auto& e : parsed_flags.inputs) {
      if_verbose std::cout << "\tAdding: " << e << "\n";

      if(!std::filesystem::exists(e)) {
        std::cout << "PATH [" << e << "] DOES NOT EXIST\n";   
        continue; // goto next path
      }        

      add_to_trash(settings, e, parsed_flags.verbose); 
    }
  }
}

#endif
