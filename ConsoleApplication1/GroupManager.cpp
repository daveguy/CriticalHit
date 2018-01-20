#include "stdafx.h"
#include "GroupManager.h"
#include <algorithm>
#include <ctime>

GroupManager::GroupManager()
{
	std::srand(unsigned(std::time(0)));//set srand for shuffling
}


void GroupManager::CreateGroups(int numPlayers)
{
	this->numPlayers = numPlayers;
	int numGroups = CalculateNumGroups();
	int numGroupsOf4 = numGroups - (4 - numPlayers % 4);
	groupList.clear();
	for (int i = 0; i < numGroups; i++)
	{
		if (i < numGroupsOf4)
		{
			groupList.push_back(Group(4));
		}
		else {
			groupList.push_back(Group(3));
		}
	}
}

//TODO some error checking somewhere to make sure this is groovy
void GroupManager::AddPlayerToGroup(int group, const Player & player)
{
	groupList[group].AddPlayer(player);
}

//Returns the index of the containing group
int GroupManager::RemovePlayer(const Player & player)
{
	int i = 0;
	for (; i < groupList.size(); i++)
	{
		bool contains = groupList[i].Contains(player);
		if (contains)
		{
			groupList[i].RemovePlayer(player);
			return i;
		}
	}
	return -1;
}

//Randomly assigns remaining players
void GroupManager::AssignGroups(const std::vector<Player>& playerList)
{
	std::vector<int> playerIndex;
	InitializeWithRandomRange(playerIndex, playerList.size());
	int group = 0;
	for (int i : playerIndex) {
		if (playerList[i].eliminated || playerList[i].inGroup) { continue; }
		if (groupList[group].IsFull())
		{
			group++;
		}
		groupList[group].AddPlayer(playerList[i]);
	}
}

int GroupManager::getNumGroups()
{
	return groupList.size();
}

const Group& GroupManager::GetGroup(int index)
{
	return groupList[index];
}

int GroupManager::CalculateNumGroups()
{
	return numPlayers % 4 == 0 ? numPlayers / 4 : numPlayers / 4 + 1;
}

void GroupManager::InitializeWithRandomRange(std::vector<int> &outVec, int size)
{
	for (int i = 0; i < size; i++)
	{
		outVec.push_back(i);
	}
	std::random_shuffle(outVec.begin(), outVec.end());
}
