/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <chl/xs/coordarray.hpp>

namespace chl {
namespace xs {

CoordArray::CoordArray(std::initializer_list<Coordinate> il) : coords{} {
  for (auto beg = il.begin(); beg != il.end(); ++beg) {
    this->push_back(*beg);
  }
}

CoordArray::CoordArray(std::initializer_list<Coordinate> il) : coords{} {
  for (auto beg = il.begin(); beg != il.end(); ++beg) {
    this->push_back(*beg);
  }
}
std::tuple<std::vector<double>, std::vector<double>> CoordArray::coordinates() {
  std::vector<double> station;
  std::vector<double> elevation;
  for (const Coordinate& c : this->coords) {
    station.push_back(c.station);
    elevation.push_back(c.elevation);
  }
  return {station, elevation};
}

void CoordArray::push_back(Coordinate c) {
  if (!this->coords.empty()) {
    if (c.station < this->coords.back().station)
      throw std::invalid_argument{
          "Station values of coordinates must be in ascending order"};
  }
  this->coords.push_back(c);
}

void CoordArray::push_back(double station, double elevation) {
  this->push_back({station, elevation});
}

size_t CoordArray::size() { return this->coords.size(); }

}  // namespace xs
}  // namespace chl
