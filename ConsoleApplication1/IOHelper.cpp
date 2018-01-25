#include "stdafx.h"
#include "IOHelper.h"

void IOHelper::PrintGames(const std::vector<std::string>& gamesList)
{
	for (int i = 0; i < gamesList.size(); i++)
	{
		std::cout << i + 1 << ": " << gamesList[i]<<std::endl;
	}
}


void IOHelper::PrintPlayers(const std::vector<Player>& playerList, bool aliveOnly)
{
	for (int i = 0; i < playerList.size(); i++)
	{
		if (aliveOnly)
		{
			playerList[i].eliminated ? std::cout : std::cout << i + 1 << ": " << playerList[i] << std::endl;
		}
		else
		{
			std::cout << i + 1 << ": " << playerList[i] << std::endl;
		}
	}
}

void IOHelper::PrintGame(const GroupManager &groupManager)
{
	for (int i = 0; i < groupManager.getNumGroups(); i++)
	{
		std::cout << i + 1 << ": " << groupManager.GetGroup(i) << std::endl;
	}
}
