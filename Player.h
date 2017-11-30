// 多重インクルードの防止
#pragma once

#include <DirectXMath.h>
#include <DirectXColors.h>

//#include "MyLibrary.h"
#include "..\MyLibrary\Input\KeyboardUtil.h"
#include "..\MyLibrary\3D\Obj3D.h"

class Player : public Obj3D
{
public:
	Player();
	~Player();

private:
	void Move();

};

