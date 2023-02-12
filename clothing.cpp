#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <set>
#include "clothing.h"
#include "util.h"
#include "product.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size_, const std::string brand_)
 : Product(category, name, price, qty) {
   size = size_;
   brand = brand_;
}

Clothing::~Clothing() {

}

std::set<std::string> Clothing::keywords() const{
  set<string> ans = parseStringToWords(name_);
  set<string> brnd = parseStringToWords(brand);
  ans = setUnion(ans, brnd);
  return ans;
}

bool Clothing::isMatch(std::vector<std::string>& searchTerms) const {
  set<string> keys = keywords();
  for (size_t i = 0; i < searchTerms.size(); i++) {
    if (keys.find(searchTerms[i]) != keys.end()) {
      return true;
    }
  }
  return false;
}

std::string Clothing::displayString() const{
  stringstream ans;
  ans << name_ << "\nSize: " << size << " Brand: " << brand << "\n" << price_ << " " << qty_ << " left." << endl;
  return ans.str();
}

void Clothing::dump(std::ostream& os) const {
  Product::dump(os);
  os << size << "\n" << brand << endl;
}

//Accessors
std::string Clothing::getSize() const {
  return size;
}

std::string Clothing::getBrand() const {
  return brand;
}
