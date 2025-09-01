#pragma once
#include <memory>
#include <array>

template<typename T, int size>
struct Matrix2{
	std::array<std::array<T, size>, size> matrix = {};
};
