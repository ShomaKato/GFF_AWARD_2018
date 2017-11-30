#include "Obstacle.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Obstacle::Obstacle()
{
	LoadModel(L"box2");
}


Obstacle::~Obstacle()
{
}
