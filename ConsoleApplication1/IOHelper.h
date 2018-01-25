//Eventually going to be depricated when GUI is implemented
#pragma once

#include <vector>
#include "Player.h"
#include "Group.h"
#include "GroupManager.h"
#include <iostream>

class IOHelper
{
public:
	void PrintGames(const std::vector<std::string> &gamesList);
	void PrintPlayers(const std::vector<Player> &playerList, bool aliveOnly);
	void PrintGame(const GroupManager &groupManager);
};