#include <numeric>
#include <string>
#include <iostream>
#include <string_view>
#include <vector>
#include <map>
#include <print>

auto main() -> int {

  using map_t = std::vector<std::string>;
  using point_t = std::pair<size_t, size_t>;
  enum direction_e {north, east, south, west};

  size_t n{0};
  map_t map{};
  direction_e direction{north};
  point_t pos{0, 0};

  std::string buf;
  std::string_view starter{"^>v<"};
  while (std::getline(std::cin, buf)) {
    for (auto j = 0u; j < buf.size(); ++j) {
      if (auto p = starter.find(buf[j]); p != starter.npos) {
        direction = static_cast<direction_e>(p);
        pos = {j, map.size()};
      }
    }
    map.push_back(std::move(buf));
  }

  while (true) {
    switch (direction) {
    case south: {
      
      break;
    }
    case west: {
      break;
    }
    case north: {
      break;
    }
    case west: {
      break;
    }
  }


  std::println("{}", std::accumulate(bitmap.begin(), bitmap.end(), 0));

}
