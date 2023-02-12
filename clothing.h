#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include <cstdlib>
#include <string>
#include "product.h"

class Clothing : public Product {
  public:
    Clothing(const std::string category, const std::string name, double price, int qty, const std::string size_, const std::string brand_);

    ~Clothing();

    std::set<std::string> keywords() const;

    bool isMatch(std::vector<std::string>& searchTerms) const;

    std::string displayString() const;

    void dump(std::ostream& os) const;

    //Accessors
    std::string getSize() const;
    std::string getBrand() const;

  private:
    std::string size;
    std::string brand;

};
#endif