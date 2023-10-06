#pragma once

#include <cstdint>

using IdT = uint64_t;

static IdT typeid_counter = 0;

template<typename T>
class TypeId {
public:
	static IdT Get() {
		if (inited_) {
			return id_;
		}
		inited_ = true;
		return (id_ = typeid_counter++);
	}
private:
	static bool inited_;
	static IdT id_;

};

template<typename T>
bool TypeId<T>::inited_ = false;

template<typename T>
IdT TypeId<T>::id_ = 0;