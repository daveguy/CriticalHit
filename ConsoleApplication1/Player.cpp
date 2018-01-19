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

std::ostream & operator<<(std::ostream & out, const Player & player)
{
	out << player.name;
	return out;
}

bool operator==(const Player & player1, const Player & player2)
{
	return player1.name == player2.name;
}


