#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <iostream>
#include <map>
#include <queue>
#include "product.h"
#include "util.h"
#include "user.h"

class MyDataStore : public DataStore {
  public:

    MyDataStore();

    ~MyDataStore();

    void addProduct(Product* p);

    void addUser(User* u);

    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    void dump(std::ostream& ofile);

    void addToCart(std::string username, Product* p);

    void printCart(std::string username);

    void buyCart(std::string username);

  private:
    std::set<User*> users;
    std::set<Product*> products;
    std::map<std::string, std::set<Product*>> pMap;  //maps keyword to set of products that match
    std::map<std::string, std::queue<Product*>>  cartMap;  //maps username to cartMap
};

#endif