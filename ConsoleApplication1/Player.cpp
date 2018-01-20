#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	name = "test";
}

Player::Player(std::string name) : name(name), strikes(0), eliminated(false), inGroup(false)
{
}

std::string Player::GetName()
{
	return std::string();
}

void Player::SetName(std::string inName)
{
	name = inName;
}

void Player::AddStrike()
{
	strikes++;
	if (strikes == 2) { eliminated = true; }
}

std::ostream & operator<<(std::ostream & out, const Player & player)
{
	out << player.name << " ";
	for (int i = 0; i < player.strikes; i++)
	{
		out << "X";
	}
	return out;
}

bool operator==(const Player & player1, const Player & player2)
{
	return player1.name == player2.name;
}


