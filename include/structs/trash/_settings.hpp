#ifndef _SETTINGS_HPP
#define _SETTINGS_HPP

#include <iostream>

#define DIR 0
#define FILE 1
#define NAP 2 // not a path

namespace trash {
typedef struct {
  std::string trash_path;  // trashcan path 
  std::string settings_path;  // settings path 
  bool confirmation; // if user needs to confirm 
} TrashSettings;

}

#endif
