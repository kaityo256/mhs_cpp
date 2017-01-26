//------------------------------------------------------------------------
#include <emmintrin.h>
#include <iostream>
#include <stdint.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
//------------------------------------------------------------------------
typedef int32_t mybit;
int max_size = 0;
typedef std::vector<mybit> mybits;
//------------------------------------------------------------------------
int popcnt(mybit v) {
  return __builtin_popcount(v);
}
//------------------------------------------------------------------------
std::string
b2s(mybit v) {
  std::stringstream ss;
  for (int i = max_size - 1; i >= 0; --i) {
    if (v & (1 << i)) {
      ss << "1";
    } else {
      ss << "0";
    }
  }
  return ss.str();
}
//------------------------------------------------------------------------
mybit
a2b(std::string str) {
  std::istringstream is(str);
  std::string token;
  mybit t = 0;
  while (getline(is, token, ' ')) {
    if (token != "") {
      int v = atoi(token.c_str());
      if (v > max_size) max_size = v;
      t |= (1 << (v - 1));
    }
  }
  return t;
}
//------------------------------------------------------------------------
std::string
b2a(mybit t) {
  std::stringstream ss;
  for (int i = max_size - 1; i >= 0; --i) {
    if (t & (1 << i)) {
      ss << (i + 1) << " ";
    }
  }
  std::string s = ss.str();
  s.erase(--s.end());
  return s;
}
//------------------------------------------------------------------------
mybit
s2b(std::string str) {
  mybit t = 0;
  for (int i = 0; i < str.length(); i++) {
    t |= ((str[i] - '0') << (str.length() - i - 1));
  }
  return t;
}
//------------------------------------------------------------------------
mybits
load_datfile(std::string filename) {
  mybits v;
  std::ifstream ifs(filename.c_str());
  std::string line;
  while (getline(ifs, line)) {
    v.push_back(a2b(line));
  }
  return v;
}
//------------------------------------------------------------------------
mybits
load_bitsfile(std::string filename) {
  mybits v;
  std::ifstream ifs(filename.c_str());
  std::string line;
  while (getline(ifs, line)) {
    v.push_back(s2b(line));
  }
  return v;
}
//------------------------------------------------------------------------
bool
check_file_is_bits(std::string filename) {
  std::ifstream ifs(filename.c_str());
  if (ifs.fail()) {
    std::cerr << "Could not open file " << filename << std::endl;
    exit(1);
  }
  std::string line;
  getline(ifs, line);
  if (line.length() == 1) return false;
  for (int i = 0; i < line.length(); i++) {
    if (line[i] != '0' && line[i] != '1') return false;
  }
  max_size = line.length();
  return true;
}
//------------------------------------------------------------------------
void
show(mybits &v) {
  for (int i = 0; i < v.size(); i++) {
    std::cout << b2a(v[i]) << std::endl;
  }
}
//------------------------------------------------------------------------
void
show_bits(mybits &v) {
  for (int i = 0; i < v.size(); i++) {
    std::cout << b2s(v[i]) << std::endl;
  }
}
//------------------------------------------------------------------------
bool
check_minimal(mybit t, int k, mybits &e) {
  mybit v = t;
  while (v) {
    mybit t2 = v & -v;
    mybit t3 = t ^ t2;
    bool flag = true;
    for (int i = 0; i < k; i++) {
      flag &= ((e[i] & t3) != 0);
    }
    if (flag)return false;
    v = v ^ t2;
  }
  return true;
}
//------------------------------------------------------------------------
bool
check_minimal2(mybit t, int k, mybits &e) {
  mybit t2 = 0;
  for (int i = 0; i < k; i++) {
    if (popcnt(t & e[i]) == 1) {
      t2 = t2 | (t & e[i]);
    }
  }
  return (t2 == t);
}
//------------------------------------------------------------------------
void
search(int k, mybit t, mybits &e, mybits &r) {
  if (!check_minimal2(t, k, e))return;
  if (k == e.size()) {
    r.push_back(t);
    return;
  }
  if (t & e[k]) {
    search(k + 1, t, e, r);
  } else {
    mybit v = e[k];
    while (v) {
      mybit t2 = v & -v;
      search(k + 1, t | t2, e, r);
      v = v ^ t2;
    }
  }
}
//------------------------------------------------------------------------
int
main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "usage: ./a.out inputfile" << std::endl;
    return 0;
  }
  std::string filename = argv[1];
  mybits e;
  bool bits = check_file_is_bits(filename);
  if (bits) {
    e = load_bitsfile(filename);
  } else {
    e = load_datfile(filename);
  }
  mybits r;
  search(0, 0, e, r);
  //show(r);
  if (bits) {
    show_bits(r);
  } else {
    show(r);
  }
}
//------------------------------------------------------------------------
