#include "../include/LinkedList.h"
#include "../include/Vector.h"

#include <stdio.h>
#include <iostream>
#include <vector>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <iostream>

#define SMALL_TEST  1000
#define MID_TEST    10000
#define BIG_TEST    100000
#define VBIG_TEST   1000000

int main() {

// small test
  aisdi::Vector<int> vec;
  aisdi::LinkedList<int> list;
  for(int i = 0; i < SMALL_TEST; i++) {
      
    vec.append(i);
    list.append(i);
  }
  
  std::cout<< "Size of vec " << int(vec.getSize()) << '\n';
  std::vector<int> foo (3,0);
  std::vector<int> bar (5,0);

  bar = foo;
  foo = std::vector<int>();

  std::cout << "Size of foo: " << int(foo.size()) << '\n';
  std::cout << "Size of bar: " << int(bar.size()) << '\n';

    
}