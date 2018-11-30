// basic file operations
#include "../include/LinkedList.h"
#include "../include/Vector.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

#define SMALL_TEST 1000
#define BIG_TEST 100000
#define TEST_SCALE 10
#define MILI_TO_NANO 1000000

std::ofstream myfile;


void testAppend(aisdi::Vector<int> vec, aisdi::LinkedList<int> list, int testType)
{
    myfile << "Append result in nano sec for " << testType << std::endl;
    const clock_t Vbegin_time = clock();
    
    vec.append(0);
    myfile << "Vector : " << float( clock () - Vbegin_time ) * MILI_TO_NANO /  CLOCKS_PER_SEC << std::endl;

    const clock_t Lbegin_time = clock();
    
    list.append(0);
    myfile << "List : " << float( clock () - Lbegin_time ) * MILI_TO_NANO /  CLOCKS_PER_SEC << std::endl << std::endl;
}
void testPrepend(aisdi::Vector<int> vec, aisdi::LinkedList<int> list, int testType)
{
    myfile << "Prepend result in nano sec for " << testType << std::endl;
    const clock_t Vbegin_time = clock();
    
    vec.prepend(0);
    myfile << "Vector : " << float( clock () - Vbegin_time ) * MILI_TO_NANO /  CLOCKS_PER_SEC << std::endl;

    const clock_t Lbegin_time = clock();
    
    list.prepend(0);
    myfile << "List : " << float( clock () - Lbegin_time ) * MILI_TO_NANO /  CLOCKS_PER_SEC << std::endl << std::endl;
}
void testInsertMiddle(aisdi::Vector<int> vec, aisdi::LinkedList<int> list, int testType)
{
    myfile << "Insert (middle) result in nano sec for " << testType << std::endl;
    
    auto itVec = vec.begin();
    for(int i = 0; i < testType/2; i++) 
    {
        itVec++;
    }

    const clock_t Vbegin_time = clock();
    vec.insert(itVec, 0);
    myfile << "Vector : " << float( clock () - Vbegin_time ) * MILI_TO_NANO /  CLOCKS_PER_SEC << std::endl;

    auto itList = list.begin();
    for(int i = 0; i < testType/2; i++) 
    {
        itList++;
    }
    const clock_t Lbegin_time = clock();
    
    list.insert(itList,0);
    myfile << "List : " << float( clock () - Lbegin_time ) * MILI_TO_NANO /  CLOCKS_PER_SEC << std::endl << std::endl;
}
void testPopLast(aisdi::Vector<int> vec, aisdi::LinkedList<int> list, int testType)
{
    myfile << "PopLast result in nano sec for " << testType << std::endl;
    const clock_t Vbegin_time = clock();
    
    vec.popLast();
    myfile << "Vector : " << float( clock () - Vbegin_time ) * MILI_TO_NANO /  CLOCKS_PER_SEC << std::endl;

    const clock_t Lbegin_time = clock();
    
    list.popLast();
    myfile << "List : " << float( clock () - Lbegin_time ) * MILI_TO_NANO /  CLOCKS_PER_SEC << std::endl << std::endl;
}
void testPopFirst(aisdi::Vector<int> vec, aisdi::LinkedList<int> list, int testType)
{
    myfile << "PopFirst result in nano sec for " << testType << std::endl;
    const clock_t Vbegin_time = clock();
    
    vec.popFirst();
    myfile << "Vector : " << float( clock () - Vbegin_time ) * MILI_TO_NANO /  CLOCKS_PER_SEC << std::endl;

    const clock_t Lbegin_time = clock();
    
    list.popFirst();
    myfile << "List : " << float( clock () - Lbegin_time ) * MILI_TO_NANO /  CLOCKS_PER_SEC << std::endl << std::endl;
}
void testEraseMiddle(aisdi::Vector<int> vec, aisdi::LinkedList<int> list, int testType)
{   
    myfile << "Erase (middle) result in nano sec for " << testType << std::endl;
    auto itVec = vec.begin();
    for(int i = 0; i < testType/2; i++) 
    {
        itVec++;
    }

    const clock_t Vbegin_time = clock();
    vec.erase(itVec);
    myfile << "Vector : " << float( clock () - Vbegin_time ) * MILI_TO_NANO /  CLOCKS_PER_SEC << std::endl;

    auto itList = list.begin();
    for(int i = 0; i < testType/2; i++) 
    {
        itList++;
    }
    const clock_t Lbegin_time = clock();
    
    list.erase(itList);
    myfile << "List : " << float( clock () - Lbegin_time ) * MILI_TO_NANO /  CLOCKS_PER_SEC << std::endl << std::endl;
}
void testFindMiddle(aisdi::Vector<int> vec, aisdi::LinkedList<int> list, int testType)
{   
    int middle = testType / 2;
    myfile << "Find (middle) result in nano sec for " << testType << std::endl;
    
    const clock_t Vbegin_time = clock();
    // dostep jednakowy dla kazdego elementu
    auto itVec = vec.begin();
    *(itVec+testType/2);
    myfile << "Vector : " << float( clock () - Vbegin_time ) * MILI_TO_NANO /  CLOCKS_PER_SEC << std::endl;

    
    const clock_t Lbegin_time = clock();
    auto itList = list.begin();
    while(middle--) {
        itList ++;
    }

    myfile << "List : " << float( clock () - Lbegin_time ) * MILI_TO_NANO /  CLOCKS_PER_SEC << std::endl << std::endl;
}
void test(int testType)
{
    
    aisdi::Vector<int> vec;
    aisdi::LinkedList<int> list;

    for (int i = 0; i <testType; i++)
    {
        vec.append(i);
        list.append(i);
    }
    std::cout << testType << std::endl;

    testAppend(vec, list, testType);
    testPrepend(vec, list, testType);
    testInsertMiddle(vec, list, testType);
    testPopLast(vec, list, testType);
    testPopFirst(vec, list, testType);
    testEraseMiddle(vec, list, testType);
    testFindMiddle(vec, list, testType);
    
}
int main ()
{
  
  myfile.open ("example.txt");

  for(int testType = SMALL_TEST; testType <= BIG_TEST; testType *= TEST_SCALE )
  { 
    test(testType);
  }
  
  myfile.close();
  
  return 0;
}