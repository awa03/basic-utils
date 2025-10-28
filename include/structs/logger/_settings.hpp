#ifndef _SETTINGS_HPP
#define _SETTINGS_HPP

#include <string>
namespace logger {

typedef struct {
  std::string log_path;  // trashcan path 
  std::string settings_path;  // settings path 
} LogSettings;

}

#endif
