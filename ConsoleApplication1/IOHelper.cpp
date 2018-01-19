#include "stdafx.h"
#include "IOHelper.h"

void IOHelper::PrintGames(const std::vector<std::string>& gamesList)
{
	for (int i = 0; i < gamesList.size(); i++)
	{
		std::cout << i + 1 << ": " << gamesList[i];
	}
}

void IOHelper::PrintPlayers(const std::vector<Player>& playerList)
{
	for (int i = 0; i < playerList.size(); i++)
	{
		std::cout << i + 1 << ": " << playerList[i];
	}
}

void IOHelper::PrintGame(GroupManager &groupManager)
{
	for (int i = 0; i < groupManager.getNumGroups(); i++)
	{
		std::cout << i + 1 << ": " << groupManager.GetGroup(i) << std::endl;
	}
}
