#include <iostream>
#include <numeric>
#include <print>
#include <string>
#include <string_view>
#include <vector>

auto main() -> int {

  std::vector<std::string>          map{};
  enum { north, east, south, west } direction{north};
  struct { int x; int y; }          pos{0, 0};

  std::string buf;
  constexpr std::string_view starter{"^>v<"};
  while (std::getline(std::cin, buf)) {
    for (auto j = 0; j < buf.size(); ++j) {
      if (auto p = starter.find(buf[j]); p != starter.npos) {
        direction = static_cast<decltype(direction)>(p);
        pos = {j, static_cast<int>(map.size())};
        buf[j] = 'X';
      }
    }
    map.push_back(std::move(buf));
  }
  size_t n{map.size()};

  auto step = [&]() -> bool {
    auto ret = pos;
    switch (direction) {
    case west:  ret.x--; break;
    case east:  ret.x++; break;
    case north: ret.y--; break;
    case south: ret.y++; break;
    }
    if (ret.x < 0 || ret.x >= n || ret.y < 0 || ret.y >= n)
      return false;
    if (map[ret.y][ret.x] == '#') {
      direction = static_cast<decltype(direction)>((direction + 1) % 4);
    } else {
      map[ret.y][ret.x] = 'X';
      pos = ret;
    }
    return true;
  };

  while (step());

  std::println(
      "{}", std::accumulate(map.begin(), map.end(), 0, [](int acc, auto &&row) {
        return acc + std::accumulate(
            row.begin(), row.end(), 0,
            [](int acc, auto &&c) { return acc + ((c == 'X') ? 1 : 0); });
      }));
}
