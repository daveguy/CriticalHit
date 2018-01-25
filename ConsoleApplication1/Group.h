#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Player.h"

class Group
{
public:
	Group(int size);
	Group(std::string machine);

	std::string GetMachine() const;
	void SetMachine(std::string machine);
	void AddPlayer(const Player& player);
	bool IsFull() const;
	bool Contains(const Player &player) const;
	void RemovePlayer(const Player &player);

	friend void SwapPlayers(int playerFromThisGroup, int playerFromOther, Group otherGroup);
	friend std::ostream& operator<<(std::ostream &out, const Group &group);

private:
	std::string machineName;
	std::vector<Player> players;
	int GetPlayerIndex(const Player &player) const;
};