#include<iostream>
#include<vector>
#include<iterator>
#include<string>
#include<sstream>
#include<fstream>
#include<utility>
#include<algorithm>

using namespace std;

int main(int argc, char const *argv[]) {
  vector<char> dict={'E','T','A','O','I','N','S',
  'H','R','D','L','C','U','M','W','F','G',
  'Y','P','B','V','K','J','X','Q','Z'};
  vector<pair<int,char>> c={{3,'A'},{24,'B'},
  {14,'C'},{0,'D'},
  {59,'E'},{8,'F'},{8,'G'},
  {17,'H'},{45,'I'},{83,'J'},
  {20,'K'},{20,'L'},{66,'M'},
  {43,'N'},{48,'O'},{21,'P'},
  {3,'Q'},{8,'R'},{43,'S'},
  {1,'T'},{21,'U'},{53,'V'},
  {47,'W'},{12,'X'},{1,'Y'},{42,'Z'}};
  sort(c.begin(), c.end());
  for (int i=25; i >=0; --i) {
    cout << c.at(i).first << "  " << c.at(i).second
    << "  " << dict[25-i] << endl;
  }
  char cc[]= "efghjklnoqrsuvwxyzimpactbd";
  ifstream ctext{"CO_cipher.txt"};
  ofstream ptext{"CO_plain.txt"};
  char ch;
  while (ctext.get(ch)) {
    if (ch <= 'Z' and ch >= 'A'){
      for(int i=0; i < 26; ++i) {
        if ((ch+32) == cc[i]) {
          ptext << char(i+'a');
        }
      }
      /*if (c.at(i).second==ch) {
      ptext << char(dict.at(25-i)+32);
      break;
      */
    }
  }
  ptext << endl;
  ctext.close();
  ptext.close();
  return 0;
}
