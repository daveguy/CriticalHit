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

std::vector<std::string> gamesList;
std::vector<Player> playerList;
GroupManager groupManager;

void EnterGames()
{
	bool finished = false;
	std::string game;
	while (!finished)
	{
		std::cout << std::flush;
		system("CLS");
		std::cout << "Current games:" << std::endl;
		IOHelper::PrintGames(gamesList);
		std::cout << "Enter the next game or 'q' to finish" << std::endl;
		std::cin >> game;
		if (game == "q") { return; }
		gamesList.push_back(game);
	}
}

void EnterPlayers()
{
	bool finished = false;
	std::string player;
	while (!finished)
	{
		std::cout << std::flush;
		system("CLS");
		std::cout << "Current players:" << std::endl;
		IOHelper::PrintPlayers(playerList, true);
		std::cout << "Enter the next player or 'q' to finish" << std::endl;
		std::cin >> player;
		if (player == "q") { return; }
		playerList.push_back(Player(player));
	}
}

void ResetInGroup()
{
	for (Player& p : playerList)
	{
		p.inGroup = false;
	}
}

//returns the number of players that are non-eliminated and not already in a group
int GetNumPlayers() {
	int numPlayers = 0;
	for (Player& p : playerList)
	{
		if (!p.eliminated && !p.inGroup)
		{
			numPlayers++;
		}
	}
	return numPlayers;
}

void AddPlayerToGroup()
{
	int group;
	int playerIndex;
	std::cout << "Add player to which group?" << std::endl;
	std::cin >> group;
	std::cout << "Add which player?" << std::endl;
	IOHelper::PrintPlayers(playerList, true);
	std::cin >> playerIndex;
	groupManager.AddPlayerToGroup(group - 1, playerList[playerIndex - 1]);
	playerList[playerIndex - 1].inGroup = true;
}

void AddPlayerToGroup(int group, int playerIndex)
{
	groupManager.AddPlayerToGroup(group - 1, playerList[playerIndex - 1]);
	playerList[playerIndex - 1].inGroup = true;
}

int RemovePlayerFromGroup()
{
	int playerIndex;
	std::cout << "remove which player?" << std::endl;
	IOHelper::PrintPlayers(playerList, true);
	std::cin >> playerIndex;
	groupManager.RemovePlayer(playerList[playerIndex - 1]);
	return playerIndex;
}

void ChangePlayersGroup()
{
	int playerIndex = RemovePlayerFromGroup();
	int group;
	std::cout << "Add player to which group?" << std::endl;
	std::cin >> group;
	AddPlayerToGroup(group, playerIndex);
}

void SwapPlayers()
{
	int playerIndex1;
	int playerIndex2;
	std::cout << "Swap which players?" << std::endl;
	IOHelper::PrintPlayers(playerList, true);
	std::cin >> playerIndex1;
	std::cin >> playerIndex2;
	int group1 = groupManager.RemovePlayer(playerList[playerIndex1 - 1]);
	int group2 = groupManager.RemovePlayer(playerList[playerIndex2 - 1]);
	AddPlayerToGroup(group2 + 1, playerIndex1);
	AddPlayerToGroup(group1 + 1, playerIndex2);
}

void PauseForCardPlay(std::string header)
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
		IOHelper::PrintGame(groupManager);
		std::cin >> choice;
		if (choice == "a")
		{
			AddPlayerToGroup();
		}
		else if (choice == "c")
		{
			ChangePlayersGroup();
		}
		else if(choice == "s")
		{
			SwapPlayers();
		}
		else if (choice == "q")
		{
			finished = true;
		}
	}
}

void PauseForResults()
{
	bool finished = false;
	while (!finished)
	{
		int playerIndex;
		std::cout << std::flush;
		system("CLS");
		std::cout << "Who got dem strikes?" << std::endl;
		std::cout << "Enter '-1' to finish" << std::endl;
		IOHelper::PrintPlayers(playerList, true);
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

bool Finished()
{
	int numLeft = 0;
	for (Player& p : playerList)
	{
		if (!p.eliminated) { numLeft++; }
	}
	return numLeft == 1;
}

Player& GetWinner()
{
	for (Player& p : playerList)
	{
		if (!p.eliminated) { return p; }
	}
	return Player("Error");
}

void PlayGame()
{
	bool finished = false;
	while (!finished)
	{
		ResetInGroup();
		groupManager.CreateGroups(GetNumPlayers());
		//Pause for 'Before group selection' cards
		PauseForCardPlay("Play 'Before Group selection' cards now");

		//Assign remaining players to groups
		groupManager.AssignGroups(playerList);
		std::cout << std::flush;
		system("CLS");
		IOHelper::PrintGame(groupManager);
		//pause for 'before round begins' cards
		PauseForCardPlay("Play 'Before round begins' cards now");

		//results
		PauseForResults();
		//repeat until finished
		if (Finished())
		{
			finished = true;
		}
	}
	std::cout << "The winner is: " << GetWinner() << std::endl;
}

int main()
{
	std::srand(unsigned(std::time(0)));//set srand for shuffling
	gamesList.reserve(100);
	playerList.reserve(100);
	groupManager = GroupManager();
	EnterGames();
	EnterPlayers();
	PlayGame();

    return 0;
}

