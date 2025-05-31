
#ifndef GLOBALS_H
#define GLOBALS_H
#include "road_status.h"

#include <domain/Usuario.h>
class Globals {
public:
    static inline Usuario usuario_actual;
  static inline std::vector<StatusEntry> status;
};

#endif //GLOBALS_H
