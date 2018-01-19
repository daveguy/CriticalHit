#include "stdafx.h"
#include "IOHelper.h"

void IOHelper::PrintGames(const std::vector<std::string>& gamesList)
{
	for (std::string s : gamesList)
	{
		std::cout << s << std::endl;
	}
}

void IOHelper::PrintPlayers(const std::vector<Player>& playerList)
{
	for (Player p : playerList)
	{
		std::cout << p;
	}
}

void IOHelper::PrintGame(GroupManager &groupManager)
{
	for (int i = 0; i < groupManager.getNumGroups(); i++)
	{
		std::cout << i + 1 << ": " << groupManager.GetGroup(i) << std::endl;
	}
}
