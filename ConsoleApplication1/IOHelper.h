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
	static void PrintGames(const std::vector<std::string> &gamesList);
	static void PrintPlayers(const std::vector<Player> &playerList);
	static void PrintGame(GroupManager &groupManager);
};