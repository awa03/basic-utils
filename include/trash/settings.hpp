#include "structs/trash/_settings.hpp"
#include <cstdlib> 
namespace trash {

  inline TrashSettings get_default_settings(){
    const std::string HOME_DIR = getenv("HOME");
    return (TrashSettings() = {
      .trash_path = (HOME_DIR + "/TrashCan"),
      .settings_path = (HOME_DIR + ".config/TrashCan/trash_settings.json"),
      .confirmation = false 
    }); 
  }

  /* 
   * Plan: 
   *  Serialize and deserialize json to get settings
   *  Also add flags for:
     *  use default, 
     *  update trash path, 
     *  use confirm, 
     *  update settings path
   * */
  inline TrashSettings /*refactor*/ get_current_settings(){
    return *(new TrashSettings());
  }

}
