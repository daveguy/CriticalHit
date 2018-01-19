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
	out << player.name << std::endl;
	return out;
}
