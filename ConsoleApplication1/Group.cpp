#include "stdafx.h"
#include "Group.h"

Group::Group(int size)
{
	players.reserve(size);
}

Group::Group(std::string machine)
{
	machineName = machine;
	players.reserve(4);
}

std::string Group::GetMachine() const
{
	return machineName;
}

void Group::SetMachine(std::string machine)
{
	machineName = machine;
}

void Group::AddPlayer(const Player &player)
{
	players.push_back(player);
}

bool Group::IsFull() const
{
	return players.size()==players.capacity();
}

bool Group::Contains(const Player &player) const
{

	for (const Player& p : players)
	{
		if (p == player) { return true; }
	}
	return false;
}

void Group::RemovePlayer(const Player& player)
{
	players.erase(players.begin() + GetPlayerIndex(player));
}

int Group::GetPlayerIndex(const Player& player) const
{
	for (int i = 0; i < players.size(); i++)
	{
		if (players[i] == player) { return i; }
	}
	return -1;
}

std::ostream & operator<<(std::ostream& out, const Group& group)
{
	out << group.machineName << "\t";
	for (int i = 0; i < group.players.size(); i++)
	{
		out << i + 1 << ": " << group.players[i] << "\t";
	}
	out << std::endl;
	return out;
}
