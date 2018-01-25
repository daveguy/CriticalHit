// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Player.h"
#include "Group.h"
#include "GroupManager.h"
#include "IOHelper.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <stdlib.h>
#include <array>

void EnterGames(IOHelper &ioHelper, std::vector<std::string> &gamesList)
{
	bool finished = false;
	std::string game;
	while (!finished)
	{
		std::cout << std::flush;
		system("CLS");
		std::cout << "Current games:" << std::endl;
		ioHelper.PrintGames(gamesList);
		std::cout << "Enter the next game or 'q' to finish" << std::endl;
		std::cin >> game;
		if (game == "q") { return; }
		gamesList.push_back(game);
	}
}

void EnterPlayers(IOHelper &ioHelper, std::vector<Player> &playerList)
{
	bool finished = false;
	std::string player;
	while (!finished)
	{
		std::cout << std::flush;
		system("CLS");
		std::cout << "Current players:" << std::endl;
		ioHelper.PrintPlayers(playerList, true);
		std::cout << "Enter the next player or 'q' to finish" << std::endl;
		std::cin >> player;
		if (player == "q") { return; }
		playerList.push_back(Player(player));
	}
}

void ResetInGroup(std::vector<Player> &playerList)
{
	for (Player& p : playerList)
	{
		p.inGroup = false;
	}
}

//returns the number of players that are non-eliminated and not already in a group
int GetNumPlayers(const std::vector<Player> &playerList) {
	int numPlayers = 0;
	for (const Player& p : playerList)
	{
		if (!p.eliminated && !p.inGroup)
		{
			numPlayers++;
		}
	}
	return numPlayers;
}

void AddPlayerToGroup(IOHelper &ioHelper, std::vector<Player> &playerList, GroupManager &groupManager)
{
	int group;
	int playerIndex;
	std::cout << "Add player to which group?" << std::endl;
	std::cin >> group;
	std::cout << "Add which player?" << std::endl;
	ioHelper.PrintPlayers(playerList, true);
	std::cin >> playerIndex;
	groupManager.AddPlayerToGroup(group - 1, playerList[playerIndex - 1]);
	playerList[playerIndex - 1].inGroup = true;
}

//TODO should just take a group and player
void AddPlayerToGroup(int group, int playerIndex, GroupManager &groupManager, std::vector<Player> &playerList)
{
	groupManager.AddPlayerToGroup(group - 1, playerList[playerIndex - 1]);
	playerList[playerIndex - 1].inGroup = true;
}

int RemovePlayerFromGroup(IOHelper &ioHelper, GroupManager &groupManager, std::vector<Player> &playerList)
{
	int playerIndex;
	std::cout << "remove which player?" << std::endl;
	ioHelper.PrintPlayers(playerList, true);
	std::cin >> playerIndex;
	groupManager.RemovePlayer(playerList[playerIndex - 1]);
	return playerIndex;
}

void ChangePlayersGroup(IOHelper &ioHelper, GroupManager &groupManager, std::vector<Player> &playerList)
{
	int playerIndex = RemovePlayerFromGroup(ioHelper, groupManager, playerList);
	int group;
	std::cout << "Add player to which group?" << std::endl;
	std::cin >> group;
	AddPlayerToGroup(group, playerIndex, groupManager, playerList);
}

void SwapPlayers(IOHelper &ioHelper, GroupManager &groupManager, std::vector<Player> &playerList)
{
	int playerIndex1;
	int playerIndex2;
	std::cout << "Swap which players?" << std::endl;
	ioHelper.PrintPlayers(playerList, true);
	std::cin >> playerIndex1;
	std::cin >> playerIndex2;
	int group1 = groupManager.RemovePlayer(playerList[playerIndex1 - 1]);
	int group2 = groupManager.RemovePlayer(playerList[playerIndex2 - 1]);
	AddPlayerToGroup(group2 + 1, playerIndex1, groupManager, playerList);
	AddPlayerToGroup(group1 + 1, playerIndex2, groupManager, playerList);
}

void PauseForCardPlay(IOHelper &ioHelper, std::string &header, GroupManager &groupManager, std::vector<Player> &playerList)
{
	bool finished = false;
	std::string choice;
	while (!finished)
	{
		std::cout << std::flush;
		system("CLS");
		std::cout << header << std::endl;
		std::cout << "Press 'a' to add a player to a group" << std::endl;
		std::cout << "Press 'c' to change a players group" << std::endl;
		std::cout << "Press 's' to swap two players" << std::endl;
		std::cout << "Press 'q' to finish" << std::endl;
		ioHelper.PrintGame(groupManager);
		std::cin >> choice;
		if (choice == "a")
		{
			AddPlayerToGroup(ioHelper, playerList, groupManager);
		}
		else if (choice == "c")
		{
			ChangePlayersGroup(ioHelper, groupManager, playerList);
		}
		else if(choice == "s")
		{
			SwapPlayers(ioHelper, groupManager, playerList);
		}
		else if (choice == "q")
		{
			finished = true;
		}
	}
}

void PauseForResults(IOHelper &ioHelper, std::vector<Player> &playerList)
{
	bool finished = false;
	while (!finished)
	{
		int playerIndex;
		std::cout << std::flush;
		system("CLS");
		std::cout << "Who got dem strikes?" << std::endl;
		std::cout << "Enter '-1' to finish" << std::endl;
		ioHelper.PrintPlayers(playerList, true);
		std::cin >> playerIndex;
		if (playerIndex == -1)
		{
			return;
		}
		else
		{
			playerList[playerIndex - 1].AddStrike();
		}
	}
}

bool Finished(const std::vector<Player> &playerList)
{
	int numLeft = 0;
	for (const Player& p : playerList)
	{
		if (!p.eliminated) { numLeft++; }
	}
	return numLeft == 1;
}

const Player& GetWinner(const std::vector<Player> &playerList)
{
	for (const Player& p : playerList)
	{
		if (!p.eliminated) { return p; }
	}
	return Player("Error");
}

void PlayGame(IOHelper ioHelper, std::vector<Player> playerList, GroupManager groupManager)
{
	bool finished = false;
	while (!finished)
	{
		ResetInGroup(playerList);
		groupManager.CreateGroups(GetNumPlayers(playerList));
		//Pause for 'Before group selection' cards
		PauseForCardPlay(ioHelper, std::string("Play 'Before Group selection' cards now"), groupManager, playerList);

		//Assign remaining players to groups
		groupManager.AssignGroups(playerList);
		std::cout << std::flush;
		system("CLS");
		ioHelper.PrintGame(groupManager);
		//pause for 'before round begins' cards
		PauseForCardPlay(ioHelper, std::string("Play 'Before round begins' cards now"), groupManager, playerList);

		//results
		PauseForResults(ioHelper, playerList);
		//repeat until finished
		if (Finished(playerList))
		{
			finished = true;
		}
	}
	std::cout << "The winner is: " << GetWinner(playerList) << std::endl;
}

int main()
{
	std::vector<std::string> gamesList;
	std::vector<Player> playerList;
	GroupManager groupManager;
	IOHelper ioHelper;

	std::srand(unsigned(std::time(0)));//set srand for shuffling
	gamesList.reserve(100);
	playerList.reserve(100);
	groupManager = GroupManager();
	EnterGames(ioHelper, gamesList);
	EnterPlayers(ioHelper,playerList);
	PlayGame(ioHelper, playerList, groupManager);

    return 0;
}

