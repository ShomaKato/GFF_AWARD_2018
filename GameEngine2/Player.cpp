///-------------------------------------------------------------------
//*
//*	@作成日		2017/11/16
//*
//*	@名前		Player.cpp
//*
//*	@著者		加藤 彰馬
//*
//* @役割		Obj3Dクラスを継承し、移動機能を追記した自機クラスのソース
//*
///----------------------------------------------------------------

// ヘッダファイルのインクルード
#include "Player.h"

// 名前空間の定義
using namespace MyLibrary;
using namespace DirectX;
using namespace DirectX::SimpleMath;


////////////////////////
//* メンバ変数の定義 *//
////////////////////////

////----------------------------------------------------------------------
////! @関数名：Player
////!
////! @役割：プレイヤクラスのコンストラクタ
////!
////! @引数：なし(void)
////!
////! @戻り値：存在しない
////----------------------------------------------------------------------
Player::Player(bool isPlayer)
	:m_isOver(false)
{
	// 当たり判定の設定
	//m_collision = std::make_unique<SphereNode>();
	m_collision.Initialize();
	m_collision.SetDebugVisible(false);
	//m_collision.SetLength(0.1f);
	m_collision.SetTrans(GetTrans());
	//m_collision.SetRot(Vector3(0, 0, 0));

	// 引数によって、プレイヤモデルか障害物モデルか切り替える
	if (isPlayer)
	{
		// プレイヤモデルの読み込み
		LoadModel(L"ball2");
		m_collision.SetLocalRadius(0.9f);
	}
	else
	{
		// 障害物モデルの読み込み
		LoadModel(L"ball3");
		m_collision.SetLocalRadius(1.45f);
	}
}


////----------------------------------------------------------------------
////! @関数名：~Player
////!
////! @役割：プレイヤクラスのデストラクタ
////!
////! @引数：存在しない
////!
////! @戻り値：存在しない
////----------------------------------------------------------------------
Player::~Player()
{

}


////----------------------------------------------------------------------
////! @関数名：Move
////!
////! @役割：キーボードで左右上下移動を可能にする関数
////!
////! @引数：なし(void)
////!
////! @戻り値：なし(void)
////----------------------------------------------------------------------
void Player::Move()
{
	//* 今いる場所に、現在座標を更新
	m_Trans = GetTrans();

	//* 常に前に向かって進み続ける
	m_Trans.z = m_Trans.z - 0.2f;

	//* Aキーが押されたら
	if (KeyboardUtil::GetInstance()->IsPressed(Keyboard::Keys::A))
	{
		m_Trans.x = m_Trans.x - 0.2f;
	}
	//* Dキーが押されたら
	if (KeyboardUtil::GetInstance()->IsPressed(Keyboard::Keys::D))
	{
		m_Trans.x = m_Trans.x + 0.2f;
	}
	//* Wキーが押されたら
	if (KeyboardUtil::GetInstance()->IsPressed(Keyboard::Keys::W))
	{
		m_Trans.y = m_Trans.y + 0.2f;
	}
	//* Sキーが押されたら
	if (KeyboardUtil::GetInstance()->IsPressed(Keyboard::Keys::S))
	{
		m_Trans.y = m_Trans.y - 0.2f;
	}

	//* 移動後の座標を現在座標に設定
	SetTrans(m_Trans);
}


////----------------------------------------------------------------------
////! @関数名：UpdateCollision
////!
////! @役割：当たり判定を更新する関数
////!
////! @引数：なし(void)
////!
////! @戻り値：なし(void)
////----------------------------------------------------------------------
void Player::UpdateCollision()
{
	// スペースキーが押されたら可視化フラグのオンオフ
	if (KeyboardUtil::GetInstance()->IsTriggered(Keyboard::Keys::Space))
	{
		m_collision.SetDebugVisible(!m_collision.GetDebugVisible());
	}
	// 当たり判定の更新
	m_collision.SetTrans(GetTrans());
	m_collision.Update();

}


////----------------------------------------------------------------------
////! @関数名：DrawCollision
////!
////! @役割：当たり判定を描画する関数
////!
////! @引数：なし(void)
////!
////! @戻り値：なし(void)
////----------------------------------------------------------------------
void Player::DrawCollision()
{
	// 可視化フラグがオンなら当たり判定を表示する
	if (m_collision.GetDebugVisible())
	{
		// 当たり判定の描画
		m_collision.Draw();
	}
}


////----------------------------------------------------------------------
////! @関数名：Finalization
////!
////! @役割：プレイヤクラスのインスタンスを消去する関数
////!
////! @引数：なし(void)
////!
////! @戻り値：なし(void)
////----------------------------------------------------------------------
bool Player::isEnded()
{
	if (m_isOver)
	{
		return true;
	}
	return false;
}


////----------------------------------------------------------------------
////! @関数名：Finalization
////!
////! @役割：プレイヤクラスのインスタンスを消去する関数
////!
////! @引数：なし(void)
////!
////! @戻り値：なし(void)
////----------------------------------------------------------------------
void Player::Finalization()
{
	m_isOver = 1;
}
