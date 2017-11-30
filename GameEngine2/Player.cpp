// ヘッダファイルのインクルード
#include "Player.h"

using namespace MyLibrary;
using namespace DirectX;
using namespace DirectX::SimpleMath;

Player::Player()
{
	// モデルの読み込み
	LoadModel(L"ball2");

	// 当たり判定の設定
	//m_collision = std::make_unique<SphereNode>();
	m_collision = new SphereNode;
	m_collision->Initialize();
	m_collision->SetDebugVisible(true);
	//m_collision->SetLocalRadius(1.2f);
	//m_collision->SetLength(0.1f);
	m_collision->SetTrans(GetTrans());
	//m_collision->SetRot(Vector3(0, 0, 0));

}


Player::~Player()
{
	delete m_collision;
}

void Player::UpdateCollision()
{
	// 当たり判定の更新
	m_collision->SetTrans(GetTrans());
	m_collision->Update();

	//* スペースキーが押されたら可視化フラグのオンオフ
	if (KeyboardUtil::GetInstance()->IsTriggered(Keyboard::Keys::Space))
	{
		m_collision->SetDebugVisible(!m_collision->GetDebugVisible());
	}
}

void Player::DrawCollision()
{
	// 可視化フラグがオンなら当たり判定を表示する
	if (m_collision->GetDebugVisible())
	{
		// 当たり判定の描画
		m_collision->Draw();
	}
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
