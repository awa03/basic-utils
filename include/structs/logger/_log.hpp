#ifndef _LOG_HPP
#define _LOG_HPP

#include <string>
#include <unordered_map>
#include <ctime>
#include "structs/logger/_settings.hpp"
#include "json.hpp"

using json = nlohmann::json;

namespace logger {

// TODO
inline std::unordered_map<int, std::string> get_cls_tbl() {
  // load tbl
  return {};
};

class ErrCls{
public:
  ErrCls(){}
  ErrCls(int e) : err_code(e) {};
  int get_err(){
    return err_code;
  } 
  void set_err(int e){
    err_code = e;
  }
  std::string to_string(){
    return get_cls_tbl()[err_code];
  } 

private:
  int err_code;
};


class LogEntry {
public:
  LogEntry() {
    // settings = get_current_settings();
  }
  
  ErrCls get_err(){
    return classification.get_err();
  }

  LogSettings& get_current_settings(){
    // Read Settings
    // If Null or invalid path
    //    Get Default settings
    // Else
    //    settings = user_settings
    return settings;
  }

  json serialize(){

  }

  void deserialize(json serialized){

  }

private:
  LogSettings settings;  
  std::string name;
  std::string desc;
  ErrCls classification;
  // time_t time;
};

}

#endif
