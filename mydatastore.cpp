#include <string>
#include <set>
#include <vector>
#include <iostream>
#include <queue>

#include "datastore.h"
#include "util.h"
#include "user.h"
#include "product.h"
#include "product_parser.h"
#include "mydatastore.h"

using namespace std;

MyDataStore::MyDataStore() {

}

MyDataStore::~MyDataStore() {
  pMap.clear();
  cartMap.clear();
  set<Product*>::iterator it;
  for (it = products.begin(); it != products.end(); ++it) {
    delete(*it);
  }
  products.clear();

  set<User*>::iterator userit;
  for (userit = users.begin(); userit != users.end(); ++userit) {
    delete(*userit);
  }
  users.clear();
}

void MyDataStore::addProduct(Product* p) {
  products.insert(p);
  set<string> words = p->keywords();
  set<string>::iterator it;
  for (it = words.begin(); it != words.end(); ++it) {
    if (pMap.find(*it) == pMap.end()) {
      set<Product*> toAdd;
      toAdd.insert(p);
      pMap.insert(std::pair<string, set<Product*>>(*it, toAdd));
    }
    else {
      (pMap.find(*it)->second).insert(p);
    }
  }
}

void MyDataStore::addUser(User* u) {
  users.insert(u);
  queue<Product*> cart;
  cartMap.insert(std::pair<string, queue<Product*>>(convToLower(u->getName()), cart));
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
  std::vector<Product*> ans;

  set<Product*> temp;
  //And search
  if (type == 0) {
    for (size_t i = 0; i < terms.size(); i++) {
      if (pMap.find(terms[i]) != pMap.end()) {
        if (temp.size() == 0) {
          temp = pMap.find(terms[i])->second;
        }
        else {
          temp = setIntersection(temp, pMap.find(terms[i])->second);
        }
      }
    }
  }
  //Or search
  else if (type == 1) {
    for (size_t i = 0; i < terms.size(); i++) {
      if (pMap.find(terms[i]) != pMap.end()) {
        temp = setUnion(temp, pMap.find(terms[i])->second);
      }
    }
  }

  set<Product*>::iterator it;
  for (it = temp.begin(); it != temp.end(); ++it) {
    ans.push_back(*it);
  }

  return ans;
}

void MyDataStore::dump(std::ostream& ofile) {
  //first output all of the products
  ofile << "<products>" << endl;
  set<Product*>::iterator it;
  for (it = products.begin(); it != products.end(); ++it) {
    (*it)->dump(ofile);
  }
  ofile << "</products>" << endl;

  //output all of the users
  ofile << "<users>" << endl;
  set<User*>::iterator userit;
  for (userit = users.begin(); userit != users.end(); ++userit) {
    (*userit)->dump(ofile);
  }
  ofile << "</users>" << endl;
}

void MyDataStore::addToCart(std::string username, Product* p) {
  string u = convToLower(username);
  if (cartMap.find(u) == cartMap.end()) {
    cout << "Invalid request" << endl;
  }
  else {
    cartMap.find(u)->second.push(p);
  }
}

void MyDataStore::printCart(std::string username) {
  string u = convToLower(username);
  if (cartMap.find(u) == cartMap.end()) {
    cout << "Invalid username" << endl;
  }
  else {
    queue<Product*> copy = cartMap.find(u)->second;
    int index = 1;
    while (!copy.empty()) {
      Product* p = copy.front();
      cout << "Item " << index << endl;
      cout << p->displayString() << endl;
      index++;
      copy.pop();
    }
  }
}

void MyDataStore::buyCart(std::string username) {
  string lowercaseName = convToLower(username);
 if (cartMap.find(lowercaseName) == cartMap.end()) {
   cout << "Invalid username" << endl;
 }
 else {
   //finds the user associated with that username
   set<User*>::iterator it;
   User* u = nullptr;
   for (it = users.begin(); it != users.end(); ++it) {
     if (((*it)->getName().compare(lowercaseName) == 0)) {
       u = (*it);
       break;
     }
   }

   //goes through the cart and continues buying as long as it is valid
   //checks if the cart is not empty and if item is in stock
   //and if the user has enough money
    Product* currProd = nullptr;   //buffer for the products

    while ((!cartMap.find(lowercaseName)->second.empty())) {
      currProd = cartMap.find(lowercaseName)->second.front();
      if (currProd->getQty() > 0 && (u->getBalance() - currProd->getPrice() > 0)) {
        currProd->subtractQty(1);
        u->deductAmount(currProd->getPrice());
        cartMap.find(lowercaseName)->second.pop();
      }
      else {
        return;
      }
   }
 }
}