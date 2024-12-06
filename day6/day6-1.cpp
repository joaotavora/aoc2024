#include <string>
#include <iostream>
#include <string_view>
#include <vector>
#include <map>
#include <print>

auto main() -> int {

  using obstacle_map_t = std::map<size_t, std::vector<size_t>>;
  using point_t = std::pair<size_t, size_t>;

  obstacle_map_t obstacles_by_row;
  obstacle_map_t obstacles_by_col;

  enum direction_e {north, east, south, west} direction = north;
  point_t pos;

  std::string buf;
  std::string_view starter{"^>v<"};
  size_t i{};
  while (std::getline(std::cin, buf)) {
    for (auto j = 0u; j < buf.size(); ++j) {
      if (buf[j] == '#') {
        obstacles_by_row[i].push_back(j);
        obstacles_by_col[j].push_back(i);
      } else if (auto p = starter.find(buf[j]); p != starter.npos) {
        direction = static_cast<direction_e>(p);
        pos = {j, i};
      }
    }
    ++i;
  }

  std::println("Starting position is ({},{})", pos.first, pos.second);
  std::println("Starting direction is {}", static_cast<int>(direction));

  for (auto&& row : obstacles_by_row) {
    std::print("Obstacles on row {}: ", row.first);
    auto sep = "";
    for (auto&& o : row.second) {
      std::print("{}{}", sep, o);
      sep = ",";
    }
    std::println();
  }

  for (auto&& col : obstacles_by_col) {
    std::print("Obstacles on col {}: ", col.first);
    auto sep = "";
    for (auto&& o : col.second) {
      std::print("{}{}", sep, o);
      sep = ",";
    }
    std::println();
  }

}
