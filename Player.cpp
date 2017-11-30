// ヘッダファイルのインクルード
#include "player.h"

using namespace MyLibrary;
//using namespace MyLibrary::Obj3D;
using namespace DirectX;
using namespace DirectX::SimpleMath;

Player::Player()
{
	LoadModel(L"ball2");
}


Player::~Player()
{
}

void Player::Move()
{
	//* 今いる場所に、現在座標を更新
	m_Trans = GetTrans();

	//* 常に前に向かって進み続ける
	m_Trans.z = m_Trans.z - 0.1f;

	//* Aキーが押されたら
	if (KeyboardUtil::GetInstance()->IsPressed(Keyboard::Keys::A))
	{
		m_Trans.x = m_Trans.x - 0.3f;
	}
	//* Dキーが押されたら
	if (KeyboardUtil::GetInstance()->IsPressed(Keyboard::Keys::D))
	{
		m_Trans.x = m_Trans.x + 0.3f;
	}
	//* Wキーが押されたら
	if (KeyboardUtil::GetInstance()->IsPressed(Keyboard::Keys::W))
	{
		m_Trans.y = m_Trans.y + 0.3f;
	}
	//* Sキーが押されたら
	if (KeyboardUtil::GetInstance()->IsPressed(Keyboard::Keys::S))
	{
		m_Trans.y = m_Trans.y - 0.3f;
	}

	//* 移動後の座標を現在座標に設定
	SetTrans(m_Trans);
}
