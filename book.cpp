#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <set>
#include "book.h"
#include "util.h"
#include "product.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string author, const std::string isbn)
 : Product(category, name, price, qty) {
   authorName = author;
   ISBN = isbn;
}

Book::~Book() {

}

std::set<std::string> Book::keywords() const{
  set<string> ans = parseStringToWords(name_);
  ans.insert(ISBN);
  set<string> author = parseStringToWords(authorName);
  ans = setUnion(ans, author);
  return ans;
}

bool Book::isMatch(std::vector<std::string>& searchTerms) const {
  set<string> keys = keywords();
  for (size_t i = 0; i < searchTerms.size(); i++) {
    if (keys.find(searchTerms[i]) != keys.end()) {
      return true;
    }
  }
  return false;
}

std::string Book::displayString() const{
  stringstream ans;
  ans << name_ << "\nAuthor: " << authorName << " ISBN: " << ISBN << "\n" << price_ << " " << qty_ << " left." << endl;
  return ans.str();
}

void Book::dump(std::ostream& os) const {
  Product::dump(os);
  os << ISBN << "\n" << authorName << endl;
}

//Accessors
std::string Book::getAuthor() const {
  return authorName;
}

std::string Book::getISBN() const {
  return ISBN;
}
