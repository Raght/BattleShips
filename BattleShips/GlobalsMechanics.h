#pragma once
#include <random>


inline std::random_device device;
inline std::default_random_engine rng(device());