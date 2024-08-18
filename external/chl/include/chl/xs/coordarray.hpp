/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef CHL_XS_ARRAY_HPP_
#define CHL_XS_ARRAY_HPP_

#include <initializer_list>
#include <tuple>
#include <vector>

#include "coordinate.hpp"

namespace chl {
namespace xs {

class CoordArray {
 public:
  CoordArray(std::initializer_list<Coordinate> c_list);

  std::tuple<std::vector<double>, std::vector<double>> coordinates();
  size_t size();
  void push_back(Coordinate c);
  void push_back(double station, double elevation);

 private:
  std::vector<Coordinate> coords;
};
}  // namespace xs
}  // namespace chl

#endif
