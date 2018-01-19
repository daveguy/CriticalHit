#pragma once
#include <string>

class Player
{
public:
	Player();
	Player(std::string name);
	
	bool eliminated;
	bool inGroup;

	std::string GetName();
	void SetName(std::string inName);
	friend std::ostream& operator<<(std::ostream &out, const Player &player);
	friend bool operator==(const Player &player1, const Player &player2);

private:
	std::string name;
	int strikes;
};
