#include "newMap.h"

Map::Map()
{
	map_size = 0;
	map_cap = DEFAULT_MAX_ITEMS;
	map = new Pair[map_cap];
}

Map::Map(int items)
{
	map_size = 0;
	map_cap = items;
	map = new Pair[map_cap];
}

Map::~Map()
{
	delete [] map;
}

Map::Map(const Map& other)
{
	map_size = other.map_size;
	map_cap = other.map_cap;
	map = new Pair[map_cap];

	for (int i = 0; i < map_size; i++)
		map[i] = other.map[i];
}

Map& Map::operator=(const Map& other)
{
	map_size = other.map_size;
	map_cap = other.map_cap;
	delete [] map;
	map = new Pair[map_cap];

	for (int i = 0; i < map_size; i++)
		map[i] = other.map[i];

	return *this;
}

bool Map::empty() const
{
	return map_size == 0;
}

int Map::size() const
{
	return map_size;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
	if (map_size >= map_cap)
		return false;
	if (contains(key))
		return false;

	// find location to insert
	int i;
	for (i = 0; i < map_size; i++) {
		if (key < map[i].key)
			break;
	}

	// shift values forward
	for (int j = map_size; j > i; j--)
		map[j] = map[j-1];
	map_size++;

	Pair tmp;
	tmp.key = key;
	tmp.value = value;
	map[i] = tmp;
	return true;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
	int i = getIndex(key);
	if (i < 0) // key not found
		return false;

	map[i].value = value;
	return true;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	if (!update(key, value)) { // key not found
		if (!insert(key, value)) { // full
			return false;
		}
	}
	return true;
}

bool Map::erase(const KeyType& key)
{
	int i = getIndex(key);
	if (i < 0) // key not found
		return false;

	while (i < map_size-1) {
		map[i] = map[i+1];
		i++;
	}
	map_size--;

	return true;
}

bool Map::contains(const KeyType& key) const
{
	return getIndex(key) >= 0;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
	int i = getIndex(key);
	if (i < 0) // key not found
		return false;

	value = map[i].value;
	return true;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
	if (!(0 <= i && i < map_size))
		return false;

	key = map[i].key;
	value = map[i].value;
	return true;
}

void Map::swap(Map& other)
{
	Pair* ptr;
	ptr = other.map;
	other.map = map;
	map = ptr;

	int tmp;
	tmp = other.map_size;
	other.map_size = map_size;
	map_size = tmp;

	tmp = other.map_cap;
	other.map_cap = map_cap;
	map_cap = tmp;
}

int Map::getIndex(const KeyType& key) const
{
	for (int i = 0; i < map_size; i++) {
		if (map[i].key == key)
			return i;
	}
	return -1;
}
