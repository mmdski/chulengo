/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <chl/xs/coordinate.hpp>

namespace chl {
namespace xs {

Coordinate Coordinate::interp_elevation(Coordinate& other, double station) {
  // determine left and right coordinates
  Coordinate& left_coord = this->station < other.station ? *this : other;
  Coordinate& right_coord = this->station > other.station ? *this : other;

  if (station < left_coord.station || right_coord.station < station)
    throw std::domain_error{
        "station value must be between coordinate stations"};

  // if all stations are equal, return the coordinate with the station and
  // higher of the two coordinate elevations
  if (this->station == other.station && this->station == station) {
    double h_elevation =
        this->elevation > other.elevation ? this->elevation : other.elevation;
    return {station, h_elevation};
  }

  double elev = (right_coord.elevation - left_coord.elevation) /
                    (right_coord.station - left_coord.station) *
                    (station - left_coord.station) +
                left_coord.elevation;

  return {station, elev};
}

Coordinate Coordinate::interp_station(Coordinate& other, double elevation) {
  // determine left and right coordinates
  Coordinate& left_coord = this->station < other.station ? *this : other;
  Coordinate& right_coord = this->station > other.station ? *this : other;

  // determine high and low coordinates
  double high_elevation =
      this->elevation > other.elevation ? this->elevation : other.elevation;
  double low_elevation =
      this->elevation < other.elevation ? this->elevation : other.elevation;

  if (elevation < low_elevation || high_elevation < elevation)
    throw std::domain_error{
        "elevation value must be between coordinate elevations"};

  double station = (right_coord.station - left_coord.station) /
                       (right_coord.elevation - left_coord.elevation) *
                       (elevation - left_coord.elevation) +
                   left_coord.station;

  return {station, elevation};
}
}  // namespace xs
}  // namespace chl
