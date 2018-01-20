#pragma once

#include "Player.h"
#include "Group.h"

class GroupManager
{
public:
	GroupManager();
	void CreateGroups(int numPlayers);
	void AddPlayerToGroup(int group, const Player& player);
	int RemovePlayer(const Player& player);
	void AssignGroups(const std::vector<Player> &playerList);
	int getNumGroups();
	const Group& GetGroup(int index);

private:
	std::vector<Group> groupList;
	int numPlayers;//number of non-eliminated players
	int CalculateNumGroups();
	void InitializeWithRandomRange(std::vector<int> &outVec, int size);
};
