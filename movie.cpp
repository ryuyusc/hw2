#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <set>
#include "movie.h"
#include "util.h"
#include "product.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre_, const std::string rating_)
 : Product(category, name, price, qty) {
   rating = rating_;
   genre = genre_;
}

Movie::~Movie() {

}

std::set<std::string> Movie::keywords() const{
  set<string> ans = parseStringToWords(name_);
  ans.insert(convToLower(genre));
  return ans;
}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const {
  set<string> keys = keywords();
  for (size_t i = 0; i < searchTerms.size(); i++) {
    if (keys.find(convToLower(searchTerms[i])) != keys.end()) {
      return true;
    }
  }
  return false;
}

std::string Movie::displayString() const{
  stringstream ans;
  ans << name_ << "\nGenre: " << genre << " Rating: " << rating << "\n" << price_ << " " << qty_ << " left." << endl;
  return ans.str();
}

void Movie::dump(std::ostream& os) const {
  Product::dump(os);
  os << genre << "\n" << rating << endl;
}

//Accessors
std::string Movie::getRating() const {
  return rating;
}

std::string Movie::getGenre() const {
  return genre;
}
