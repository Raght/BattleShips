#pragma once
#include <vector>
#include "olcPixelGameEngine.h"


struct Team
{
	int32_t id = -1;
	olc::Pixel color;

	bool operator==(const Team& other);
	bool operator!=(const Team& other);
};

inline const Team TEAM_GREEN =  { 0, olc::GREEN  };
inline const Team TEAM_RED =    { 1, olc::RED    };
inline const Team TEAM_BLUE =   { 2, olc::BLUE   };
inline const Team TEAM_YELLOW = { 3, olc::YELLOW };

inline const std::vector<Team> TEAMS = { TEAM_GREEN, TEAM_RED, TEAM_BLUE, TEAM_YELLOW };