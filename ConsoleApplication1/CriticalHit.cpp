// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Player.h"
#include "Group.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <stdlib.h>

std::vector<std::string> gamesList;
std::vector<Player> playerList;
std::vector<Group> groupList;

void PrintGames()
{
	for (std::string s : gamesList)
	{
		std::cout << s << std::endl;
	}
}

void PrintPlayers()
{
	for (Player p : playerList)
	{
		std::cout << p;
	}
}

void EnterGames()
{
	bool finished = false;
	std::string game;
	while (!finished)
	{
		std::cout << std::flush;
		system("CLS");
		std::cout << "Current games:" << std::endl;
		PrintGames();
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
		PrintPlayers();
		std::cout << "Enter the next player or 'q' to finish" << std::endl;
		std::cin >> player;
		if (player == "q") { return; }
		playerList.push_back(Player(player));
	}
}

int GetNumPlayers() {
	int numPlayers = 0;
	for (Player p : playerList)
	{
		if (!p.eliminated && !p.inGroup)
		{
			numPlayers++;
		}
	}
	return numPlayers;
}

int GetNumGroups()
{
	int numPlayers = GetNumPlayers();
	return numPlayers % 4 == 0 ? numPlayers /4 : numPlayers /4 +1;
}

void CreateGroups()
{
	int numGroups = GetNumGroups();
	int numGroupsOf4 = numGroups - (4 - GetNumPlayers() % 4);
	groupList.clear();
	for (int i = 0; i < numGroups; i++)
	{
		if(i < numGroupsOf4)
		{
			groupList.push_back(Group(4));
		}
		else {
			groupList.push_back(Group(3));
		}
	}
}

void AssignGames()
{
	int numGroups = GetNumGroups();
	groupList.clear();
	std::random_shuffle(gamesList.begin(), gamesList.end());
	for (int i = 0; i < numGroups; i++)
	{
		if (i == gamesList.size())
		{
			std::random_shuffle(gamesList.begin(), gamesList.end());
		}
		groupList.push_back(Group(gamesList[i%gamesList.size()]));
	}
}

void PrintGame()
{
	for (int i = 0; i < groupList.size(); i++)
	{
		std::cout << i + 1 << ": " << groupList[i] << std::endl;
	}
}

void AssignPlayersOld()
{
	std::random_shuffle(playerList.begin(), playerList.end());
	int numPlayers = GetNumPlayers();
	int numGroups = GetNumGroups();
	int numGroupsOf4 = numGroups - (4 - numPlayers % 4);
	for (int i(0),j(0); i < numGroups; i++)
	{
		if (playerList[j].eliminated || playerList[j].inGroup)
		{
			continue;
		}
		if (i < numGroupsOf4)
		{
			for (int k = 0; k < 4; k++,j++)
			{
				groupList[i].AddPlayer(playerList[j]);
			}
		}
		else
		{
			for (int k = 0; k < 3; k++, j++)
			{
				groupList[i].AddPlayer(playerList[j]);
			}
		}
	}
}

void AssignPlayers()
{
	std::random_shuffle(playerList.begin(), playerList.end());
	int group = 0;
	for (Player player : playerList) {
		if (player.eliminated || player.inGroup) { continue; }
		if (groupList[group].IsFull())
		{
			group++;
		}
		groupList[group].AddPlayer(player);
	}
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
		std::cout << "Press c to change a players group" << std::endl;
		std::cout << "Press 'q' to finish" << std::endl;
		PrintGame();
		std::cin >> choice;
		if (choice == "a")
		{

		}
		else if (choice == "c")
		{

		}
		else if (choice == "q")
		{
			finished = true;
		}
	}
}

void PlayGame()
{
	CreateGroups();
	//Pause for 'Before group selection' cards
	PauseForCardPlay("Play 'Before Group selection' cards now");
	//TODO assign players to group based on card
	//AssignGames();
	//PrintGame();

	//Assign remaining players to groups
	AssignPlayers();
	std::cout << std::flush;
	system("CLS");
	PrintGame();
	//pause for 'before round begins' cards
	//TODO add shuffling of players &/or games

	//results
	//repeat until finished

	
}

int main()
{
	std::srand(unsigned(std::time(0)));//set srand for shuffling
	gamesList.reserve(100);
	playerList.reserve(100);
	EnterGames();
	EnterPlayers();
	PlayGame();


    return 0;
}

