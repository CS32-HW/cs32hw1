#include "GamerMap.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	GamerMap m;
	assert(m.addGamer("Casey"));
	assert(m.hoursSpent("Casey") == 0);
	m.play("Casey", 1000);
	assert(m.hoursSpent("Casey") == 1000);
	m.play("Casey", 1000);
	assert(m.hoursSpent("Casey") == 2000);
	assert(m.numGamers() == 1);
	m.addGamer("Bob");
	m.play("Bob", 500.5);
	m.play("Bob", 500.5);
	assert(m.hoursSpent("Bob") == 1001);
	m.addGamer("Jonny");
	m.addGamer("Zach");
	assert(m.numGamers() == 4);
	m.print();

	cout << "Passed all tests" << endl;
}
