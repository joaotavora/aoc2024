#include <cctype>
#include <iostream>
#include <print>
#include <ranges>
#include <string>
#include <vector>

using mat_t = std::vector<std::string>;
namespace rv = std::ranges::views;

auto threebythrees(const mat_t &m) {
  auto n = m.size();
  return rv::iota(0u, n * (n - 2)) |
         rv::filter([n](auto i) { return i % n < n - 2; }) |
         rv::transform([&m, n](size_t i) {
           auto rowi = i / n;
           auto coli = i % n;
           return m | rv::drop(rowi) | rv::take(3) |
                  rv::transform([coli](auto &&row) {
                    return row | rv::drop(coli) | rv::take(3);
                  });
         });
}

int main() {
  std::string s;
  mat_t m;
  while (std::getline(std::cin, s))
    m.push_back(s);

  size_t count = 0;

  for (auto &&x : threebythrees(m)) {
    if (x[1][1] == 'A') {
      if ((x[0][0] == 'M' && x[0][2] == 'M' && x[2][0] == 'S' &&
           x[2][2] == 'S') ||
          (x[0][0] == 'S' && x[0][2] == 'M' && x[2][0] == 'S' &&
           x[2][2] == 'M') ||
          (x[0][0] == 'S' && x[0][2] == 'S' && x[2][0] == 'M' &&
           x[2][2] == 'M') ||
          (x[0][0] == 'M' && x[0][2] == 'S' && x[2][0] == 'M' &&
           x[2][2] == 'S')) {
        count++;
      }
    }
  }

  std::println("{}", count);
}
