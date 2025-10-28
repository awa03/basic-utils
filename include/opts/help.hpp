#define HELP_HPP
#ifdef HELP_HPP
#include <iostream>

namespace opts {

  inline void render_help_menu(){
    std::cout << "Trash -----------------------------------------------------\n";
    std::cout << "\t--add_trash\t| Add Trash Contents\n"; 
    std::cout << "\t--del_trash\t| Delete Trash Contents\n"; 
    std::cout << "\t--see_trash\t| See Trashcan contents\n"; 

    std::cout << "\n\n";
    std::cout << "Install ---------------------------------------------------\n";
    std::cout << "\t--install\t| Install shortcuts into your shell\n"; 
    std::cout << "\n\n";

    std::cout << "Opts ------------------------------------------------------\n";
    std::cout << "\t-h, --help\t| See This Menu\n"; 
    std::cout << "\t-v, --verbose\t| See This Menu\n"; 
    std::cout << "\n\n";

    std::cout << "Inputs ----------------------------------------------------\n";
    std::cout << "\t-j, --join\t| Join Files Together\n"; 
    std::cout << "\t-o, --output\t| Specify Output File\n"; 
    std::cout << "\t-i, --input\t| Add Input Strings\n"; 

    std::cout << "Important -------------------------------------------------\n";
    std::cout << "Note that individual programs will only evaluate relevant\nflags. See help2 (h2) to view more information\n"; 
  }


  inline void input_help_menu(){
      std::cout << "Input Files not specified...\n";
      std::cout << "\t-i, --input | Specify Input Files\n";
  }

  inline void output_help_menu(){
    std::cout << "Output Files not specified...\n";
    std::cout << "\t-o, --output | Specify Output Files\n";
  }
}
#endif
