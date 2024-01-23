#include "GamerMap.h"
#include <iostream>

GamerMap::GamerMap()
{
	;
}

bool GamerMap::addGamer(KeyType name)
{
	return map.insert(name, 0);
}

ValueType GamerMap::hoursSpent(KeyType name) const
{
	ValueType v;
	if (map.get(name, v))
		return v;
	else
		return -1;
}

bool GamerMap::play(KeyType name, ValueType hours)
{
	if (hours < 0)
		return false;

	ValueType v;
	if (!map.get(name, v))
		return false;

	return map.update(name, v+hours);
}

int GamerMap::numGamers() const
{
	return map.size();
}

void GamerMap::print() const
{
	KeyType k;
	ValueType v;
	for (int i = 0; i < map.size(); i++) {
		map.get(i, k, v);
		std::cout << k << " " << v << std::endl;
	}
}
