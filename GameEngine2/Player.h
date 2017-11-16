#pragma once

#include <DirectXMath.h>
#include <DirectXColors.h>

#include "MyLibrary.h"

class Player
{
public:
	Player();
	~Player();

	void Move();

private:
	std::unique_ptr<MyLibrary::Obj3D> m_ball;
	//* ç¿ïW
	DirectX::SimpleMath::Vector3 m_pos;

};

