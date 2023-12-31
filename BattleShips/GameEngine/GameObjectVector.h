#pragma once
#include <vector>
#include <set>
#include "GameObject.h"


// Provides PushBack and Erase operations that workin O(log n) time, where n is the size of the vector
template<class T>
class Vector
{
public:
	Vector() = default;
	Vector(uint32_t max_size)
	{
		MAX_SIZE = max_size;
		game_objects.reserve(max_size);
		empty_indexes.reserve(max_size);
		for (int i = 0; i < max_size; i++)
		{
			empty_indexes.push_back(i);
		}
	}

	T& const PushBack(const T& object)
	{
		int it_first_empty_index = empty_indexes.begin();
		if (it_first_empty_index != empty_indexes.end())
		{
			objects[*it_first_empty_index] = object;
			empty_indexes.erase(it_first_empty_index);
			return objects[*it_first_empty_index];
		}

		std::cerr << "WARNING: The limit of the Vector is exceeded. The new object will not be added.\n";
		return nullptr;
	}

	void Erase(int index)
	{
		empty_indexes.insert(index);
	}

	T& operator[](uint32_t index) const noexcept
	{
		return objects[index];
	}


private:
	uint32_t MAX_SIZE;
	std::vector<T> objects;
	std::set<int> empty_indexes;
};