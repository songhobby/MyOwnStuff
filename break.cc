#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <utility>
using namespace std;

#define KEY_LENGTH_MAX 1

int main(int argc, char const *argv[]) {
  ifstream ctext("ctext.txt");
  stringstream ss;
  unsigned char ch;
  vector<int> c;
  ss << hex << "f";
  ss >> ch;
  cout << static_cast<int>(ch) << endl;
  c.emplace_back(ch);
  map<char,int> m;
  for (int i = 0; i < KEY_LENGTH_MAX; ++i) {
    for (auto& x : c)
    cout << x;
  }
  cout << endl;
  ctext.close();
  return 0;
}
