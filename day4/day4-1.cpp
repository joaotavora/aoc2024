#include <cctype>
#include <iostream>
#include <print>
#include <ranges>
#include <string>
#include <vector>

using mat_t = std::vector<std::string>;

enum directions_t { lines, columns, positive_diagonals, negative_diagonals };

namespace rv = std::ranges::views;

template <directions_t dir> auto subsequences(const mat_t &m);

template <> auto subsequences<columns>(const mat_t &m) {
  auto cols = m.size();
  return rv::iota(0u, cols) | rv::transform([&](size_t coli) {
           return m | rv::transform(
                          [coli](const std::string &row) { return row[coli]; });
         });
}

template <> auto subsequences<lines>(const mat_t &m) { return m; }

template <> auto subsequences<positive_diagonals>(const mat_t &m) {

  auto n = m.size();

  return rv::iota(0u, 2 * n - 1) | rv::transform([&m, n](size_t diagi) {
           return rv::iota(0u, n) | rv::filter([&m, diagi, n](size_t rowi) {
                    size_t col = diagi - rowi;
                    return rowi < n && col < n;
                  }) |
                  rv::transform([&m, diagi](size_t relevant_rowi) {
                    return m[relevant_rowi][diagi - relevant_rowi];
                  });
         });
}

template <> auto subsequences<negative_diagonals>(const mat_t &m) {
  auto n = m.size();

  return rv::iota(-(n - 1), n) | rv::transform([&m, n](int diag) {
           return rv::iota(0u, n) | rv::filter([&m, n, diag](size_t row) {
                    int col = static_cast<int>(row) - diag;
                    return row < n && col >= 0 && col < n;
                  }) |
                  rv::transform([&m, diag](size_t relevant_rowi) {
                    return m[relevant_rowi][relevant_rowi - diag];
                  });
         });
}

template <directions_t dir> size_t search(const mat_t &m) {
  size_t res{}, lineidx{};
  auto seqs = subsequences<dir>(m);

  using namespace std::string_view_literals;

  for (auto &&x : seqs) {
    lineidx++;
    size_t xmas_idx{};
    size_t samx_idx{};
    for (char c : x) {
      if (c == "XMAS"sv.at(xmas_idx))
        xmas_idx++;
      else
        xmas_idx = c == 'X' ? 1 : 0;
      if (c == "SAMX"sv.at(samx_idx))
        samx_idx++;
      else
        samx_idx = c == 'S' ? 1 : 0;

      if (xmas_idx > 3) {
        xmas_idx = 0;
        res++;
      }
      if (samx_idx > 3) {
        samx_idx = 0;
        res++;
      }
    }
  }
  return res;
}

int main() {
  std::string s;
  mat_t m;
  while (std::getline(std::cin, s))
    m.push_back(s);

  size_t count = 0;

  count += search<lines>(m);
  count += search<columns>(m);
  count += search<positive_diagonals>(m);
  count += search<negative_diagonals>(m);

  std::println("{}", count);
}
