#include "Team.h"


bool Team::operator==(const Team& other) { return id == other.id; }
bool Team::operator!=(const Team& other) { return id != other.id; }