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
	int getNumGroups() const;
	const Group& GetGroup(int index) const;

private:
	std::vector<Group> groupList;
	int numPlayers;//number of non-eliminated players
	int CalculateNumGroups() const;
	void InitializeWithRandomRange(std::vector<int> &outVec, int size);
};
