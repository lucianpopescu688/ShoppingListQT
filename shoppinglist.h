#ifndef SHOPPINGLIST_H
#define SHOPPINGLIST_H
#include <string>

using namespace std;

class shoppinglist
{
public:
    shoppinglist(string category, string name, string quantity);
    string _category;
    string _name;
    string _quantity;
};

#endif // SHOPPINGLIST_H
