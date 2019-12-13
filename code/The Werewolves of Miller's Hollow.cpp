#include "judge.hpp"
#include "player.hpp"
#include <iostream>

  Judge::Judge(){};
  Judge::~Judge(){};

using std::endl;
using std::cout;
using std::string;

void Judge::on(const Player* player){
	static int flag = 0;
    if(flag == 0)
    {
        m_players_count = 0;
    }
	m_players[m_players_count] = player;
	m_players_count++;
	flag++;
}

void Judge::call(Player::Role role){
	int i;
	string ro[6] = { "Uninitialized", "Villager", "Werewolf", "Seer", "Witch", "Hunter" };
	cout << "Calling: " << ro[role] << endl;
	if(role == Player::Role::Villager)
	{
		for(i = 0; i < m_players_count; i++)
		{
			m_players[i]->pretend();
		}
	}
	else
	{
	    for(i = 0; i < m_players_count; i++)
	    {

		    if(m_players[i]->role() == role)
		    {
			    m_players[i]->answer();
		    }
	    }
    }
}

#include "player.hpp"
#include "judge.hpp"
#include <iostream>

using std::endl;
using std::cout;
using std::string;

  Player::Player(){};
  Player::~Player(){};

void Player::init(std::string name, Role role){
	m_name = name;
	m_role = role;
}

Player::Role Player::role() const{
    return m_role;
}

void Player::answer() const{
    string ro[6] = { "Uninitialized", "Villager", "Werewolf", "Seer", "Witch", "Hunter" };
    cout << m_name << ": Shh... I am a " << ro[role()] << "." << endl;
}

void Player::pretend() const{
    cout << m_name << ": I am the villager!!" << endl;
}W
