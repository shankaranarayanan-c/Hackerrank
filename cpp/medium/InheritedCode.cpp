#include <exception>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

/* Define the exception here */
class BadLengthException : public std::exception {
public:
  BadLengthException(int n) {
    std::stringstream strStream;
    strStream << n;
    size = strStream.str();
  }

  const char *what() const noexcept override { return size.c_str(); }

private:
  std::string size;
};

bool checkUsername(string username) {
  bool isValid = true;
  int n = username.length();
  if (n < 5) {
    throw BadLengthException(n);
  }
  for (int i = 0; i < n - 1; i++) {
    if (username[i] == 'w' && username[i + 1] == 'w') {
      isValid = false;
    }
  }
  return isValid;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    string username;
    cin >> username;
    try {
      bool isValid = checkUsername(username);
      if (isValid) {
        cout << "Valid" << '\n';
      } else {
        cout << "Invalid" << '\n';
      }
    } catch (BadLengthException e) {
      cout << "Too short: " << e.what() << '\n';
    }
  }
  return 0;
}
