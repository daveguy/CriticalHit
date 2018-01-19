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
		IOHelper::PrintPlayers(playerList);
		std::cout << "Enter the next player or 'q' to finish" << std::endl;
		std::cin >> player;
		if (player == "q") { return; }
		playerList.push_back(Player(player));
	}
}

//returns the number of players that are non-eliminated and not already in a group
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

//int CalculateNumGroups()
//{
//	int numPlayers = GetNumPlayers();
//	return numPlayers % 4 == 0 ? numPlayers /4 : numPlayers /4 +1;
//}

//void CreateGroups()
//{
//	int numGroups = CalculateNumGroups();
//	int numGroupsOf4 = numGroups - (4 - GetNumPlayers() % 4);
//	groupList.clear();
//	for (int i = 0; i < numGroups; i++)
//	{
//		if(i < numGroupsOf4)
//		{
//			groupList.push_back(Group(4));
//		}
//		else {
//			groupList.push_back(Group(3));
//		}
//	}
//}

//void AssignPlayers()
//{
//	std::random_shuffle(playerList.begin(), playerList.end());
//	int group = 0;
//	for (Player player : playerList) {
//		if (player.eliminated || player.inGroup) { continue; }
//		if (groupList[group].IsFull())
//		{
//			group++;
//		}
//		groupList[group].AddPlayer(player);
//	}
//}

void AddPlayerToGroup()
{
	int group;
	int playerIndex;
	std::cout << "There are " << groupManager.getNumGroups() << " Groups" << std::endl;
	std::cout << "Add player to which group?" << std::endl;
	std::cin >> group;
	std::cout << "Add which player?" << std::endl;
	std::cin >> playerIndex;
	groupManager.AddPlayerToGroup(group - 1, playerList[playerIndex - 1]);
	playerList[playerIndex - 1].inGroup = true;
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
		IOHelper::PrintGame(groupManager);
		std::cin >> choice;
		if (choice == "a")
		{
			AddPlayerToGroup();
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
	groupManager.CreateGroups(GetNumPlayers());
	//Pause for 'Before group selection' cards
	PauseForCardPlay("Play 'Before Group selection' cards now");
	//TODO assign players to group based on card
	//AssignGames();
	//PrintGame();

	//Assign remaining players to groups
	groupManager.AssignGroups(playerList);
	std::cout << std::flush;
	system("CLS");
	IOHelper::PrintGame(groupManager);
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
	groupManager = GroupManager();
	EnterGames();
	EnterPlayers();
	PlayGame();


    return 0;
}

