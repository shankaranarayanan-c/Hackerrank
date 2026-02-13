#include <iostream>
using namespace std;

template <bool... args>
struct BinaryValue;

template <>
struct BinaryValue<> {
  static int get() { return 0; }
};

template <bool first, bool... rest>
struct BinaryValue<first, rest...> {
  static int get() {
    int placeValue = 5 - sizeof...(rest);
    return (1 << placeValue) * first + BinaryValue<rest...>::get();
  }
};

template <bool... args>
int reversed_binary_value() {
  return BinaryValue<args...>::get();
}

template <int n, bool... digits>
struct CheckValues {
  static void check(int x, int y) {
    CheckValues<n - 1, 0, digits...>::check(x, y);
    CheckValues<n - 1, 1, digits...>::check(x, y);
  }
};

template <bool... digits>
struct CheckValues<0, digits...> {
  static void check(int x, int y) {
    int z = reversed_binary_value<digits...>();
    std::cout << (z + 64 * y == x);
  }
};

int main() {
  //   int t;
  //   std::cin >> t;

  //   for (int i = 0; i != t; ++i) {
  //     int x, y;
  //     cin >> x >> y;
  CheckValues<6>::check(65, 1);
  //     cout << "\n";
  //   }
}
