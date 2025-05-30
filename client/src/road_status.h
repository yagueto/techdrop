#ifndef ROAD_STATUS_H
#define ROAD_STATUS_H
#include <string>
#include <vector>

struct StatusEntry {
  std::string titulo;
  std::string descripcion;
};
std::string query_api();
std::vector<StatusEntry> get_road_status();
#endif // ROAD_STATUS_H
