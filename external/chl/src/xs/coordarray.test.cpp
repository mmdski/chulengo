#include <gtest/gtest.h>

#include <chl/xs/coordarray.hpp>

namespace {
TEST(CoordArray, InitializerListConstructor) {
  chl::xs::CoordArray ca = {{210, 90}, {220, 82}, {260, 80}, {265, 70},
                            {270, 71}, {275, 81}, {300, 83}, {310, 91}};
}
};  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
