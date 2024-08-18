/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef CHL_XS_COORDINATE_HPP_
#define CHL_XS_COORDINATE_HPP_

namespace chl {
namespace xs {

struct Coordinate {
  double station;
  double elevation;
  Coordinate interp_elevation(Coordinate& other, double sta);
  Coordinate interp_station(Coordinate& other, double ele);
};

}  // namespace xs
}  // namespace chl
#endif
