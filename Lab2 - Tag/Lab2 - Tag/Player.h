#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>
using namespace std;

class Player{
private:
	int m_posX, m_posY;
	int m_velX, m_velY;
	
	//bVec2 (m_posX, m_posY)

public:
	Player();
	Player(int,int);
	~Player();
	void update(float);

	//Getters and Setters
	bVec2 getPosition();
}
#endif