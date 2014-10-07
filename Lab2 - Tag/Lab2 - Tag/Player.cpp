#include "Player.h"

Player::Player(){
}

Player::Player(int x, int y){
	m_posX = x;
	m_posY = y;
}

void Player::update(float gameTime){

	m_posX = m_velX;
	m_posY = m_velY;

	/*
	if (Key.isPressed())
	{
		if (key. == W)
		{
			vel.y = 5;
		}
		else if (key = s)
		{
			vel.y = -5
		}
		else {
		m_velY = 0;
		}
		key a and d left and rught
	}
	*/
}

/*bVec2 Player::getPosition(){
	return bVec2 position;
}*/