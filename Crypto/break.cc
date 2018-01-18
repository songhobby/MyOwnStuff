#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <utility>
using namespace std;

int const KEY_LENGTH_MAX = 1;

int main(int argc, char const *argv[]) {
  ifstream ctext("ctext.txt");
  char ch;
  vector<unsigned char> c;
  map<char,int> m;
  while (ctext.get(ch)) {
    stringstream ss;
    ss << ch;
    int ch1;
    ss >> hex >> ch1;
    c.emplace_back(static_cast<unsigned char>(ch1));
  }
  for (int i = 0; i < KEY_LENGTH_MAX; ++i) {
    for (auto x : c)
    cout << static_cast<int>(x);
  }
  cout << endl;
  ctext.close();
  return 0;
}
