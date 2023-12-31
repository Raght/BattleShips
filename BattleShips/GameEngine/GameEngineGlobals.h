#pragma once
#include <random>


inline std::random_device global_random_device;
inline std::default_random_engine global_rng(global_random_device());