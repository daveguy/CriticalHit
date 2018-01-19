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

std::string Group::GetMachine()
{
	return machineName;
}

void Group::SetMachine(std::string machine)
{
	machineName = machine;
}

void Group::AddPlayer(const Player& player)
{
	players.push_back(player);
}

bool Group::IsFull()
{
	return players.size()==players.capacity();
}

std::ostream & operator<<(std::ostream & out, const Group & group)
{
	out << group.machineName << "\t";
	for (int i = 0; i < group.players.size(); i++)
	{
		out << i + 1 << ": " << group.players[i] << "\t";
	}
	out << std::endl;
	return out;
}
