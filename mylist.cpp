#include "mylist.h"

mylist::iterator::iterator(const iterator&)
{

}
~iterator();
iterator& operator=(const iterator&);
iterator& operator++(); //prefix increment
item operator*() const;