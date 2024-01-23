#include "newMap.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Map m;  // maps strings to doubles
    assert(m.empty());
    ValueType v = -1234.5;
    assert( !m.get("abc", v)  &&  v == -1234.5); // v unchanged by get failure
    m.insert("xyz", 9876.5);
    assert(m.size() == 1);
    KeyType k = "hello";
    assert(m.get(0, k, v)  &&  k == "xyz"  &&  v == 9876.5);

    Map mm;
    mm.insert("Little Ricky", 3.206);
    mm.insert("Ethel", 3.538);
    mm.insert("Ricky", 3.350);
    mm.insert("Lucy", 2.956);
    mm.insert("Ethel", 3.538);
    mm.insert("Fred", 2.956);
    mm.insert("Lucy", 2.956);
    assert(mm.size() == 5);  // duplicate "Ethel" and "Lucy" were not added
    KeyType x;
    ValueType y;
    mm.get(0, x, y);
    assert(x == "Ethel");  // "Ethel" is greater than exactly 0 items in mm
    mm.get(4, x, y);
    assert(x == "Ricky");  // "Ricky" is greater than exactly 4 items in mm
    mm.get(2, x, y);
    assert(x == "Little Ricky");  // "Little Ricky" is greater than exactly 2 items in mm
    assert(y == 3.206);  // the value corresponding to the key "Little Ricky"

    Map m1;
    m1.insert("Fred", 2.956);
    Map m2;
    m2.insert("Ethel", 3.538);
    m2.insert("Lucy", 2.956);
    m1.swap(m2);
    assert(m1.size() == 2  &&  m1.contains("Ethel")  &&  m1.contains("Lucy")  &&
           m2.size() == 1  &&  m2.contains("Fred"));

    Map gpas;
    gpas.insert("Fred", 2.956);
    assert(!gpas.contains(""));
    gpas.insert("Ethel", 3.538);
    gpas.insert("", 4.000);
    gpas.insert("Lucy", 2.956);
    assert(gpas.contains(""));
    gpas.erase("Fred");
    assert(gpas.size() == 3  &&  gpas.contains("Lucy")  &&  gpas.contains("Ethel")  &&
                gpas.contains(""));
    assert(gpas.get(2, k, v)  &&  k == "Lucy" && v == 2.956);
    assert(gpas.get(1, k, v)  &&  k == "Ethel");
    assert(gpas.get(0, k, v)  &&  k == "");

    Map m3;
    m3.insertOrUpdate("A", 1);
    m3.insert("B", 2);
    m3.insert("C", 3);
    assert(m3.size() == 3 && m3.contains("A") && m3.contains("B")
                         && m3.contains("C"));
    m3.insertOrUpdate("D", 4);
    m3.insertOrUpdate("A", 0);
    assert(m3.size() == 4 && m3.contains("A") && m3.contains("B")
                          && m3.contains("C") && m3.contains("D"));
    k = "AAA";
    v = 12121;
    assert(m3.get(0, k, v) && k == "A" && v == 0);
    assert(m3.get(3, k, v) && k == "D" && v == 4);
    assert(m3.get("A", v) && v == 0);
    assert(m3.get("D", v) && v == 4);
    assert(!m3.erase("E") && m3.erase("B") && m3.size() == 3 && !m3.contains("B"));

    Map a(1000);   // a can hold at most 1000 key/value pairs
    Map b(5);      // b can hold at most 5 key/value pairs
    Map c;         // c can hold at most DEFAULT_MAX_ITEMS key/value pairs
    KeyType k1[6] = {"A", "B", "C", "D", "E", "F"};
    ValueType v1  = 21;

      // No failures inserting pairs with 5 distinct keys into b
    for (int n = 0; n < 5; n++)
        assert(b.insert(k1[n], v1));

      // Failure if we try to insert a pair with a sixth distinct key into b
    assert(!b.insert(k1[5], v1));

      // When two Maps' contents are swapped, their capacities are swapped
      // as well:
    a.swap(b);
    assert(!a.insert(k1[5], v1)  &&  b.insert(k1[5], v1));
    assert(a.get("A", v) && v == 21);
    assert(!a.contains("F"));
    assert(b.size() == 1);

    b = a;
    assert(b.size() == 5 && b.contains("A"));

    Map d(b);
    assert(d.size() == 5 && d.contains("B"));

    cout << "Passed all tests" << endl;
}

//int main()
//{
//    Map m;  // maps ints to strings
//    assert(m.empty());
//    ValueType v = "Ouch";
//    assert( !m.get(42, v)  &&  v == "Ouch"); // v unchanged by get failure
//    m.insert(123456789, "Wow!");
//    assert(m.size() == 1);
//    KeyType k = 9876543;
//    assert(m.get(0, k, v)  &&  k == 123456789  &&  v == "Wow!");
//    cout << "Passed all tests w/ reversed map" << endl;
//}
