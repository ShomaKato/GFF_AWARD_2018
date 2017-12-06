///-------------------------------------------------------------------
//*
//*	@作成日		2017/11/16
//*
//*	@名前		Player.h
//*
//*	@著者		加藤 彰馬
//*
//* @役割		Obj3Dクラスを継承し、移動機能を追記した自機クラスのヘッダー
//*
///----------------------------------------------------------------

// 多重インクルードの防止
#pragma once

// ヘッダファイルのインクルード
//#include <DirectXMath.h>
//#include <DirectXColors.h>

//#include "..\MyLibrary\3D\Obj3D.h"
//#include "..\MyLibrary\Input\KeyboardUtil.h"
//#include "..\MyLibrary\Collision\CollisionNode.h"

#include "MyLibrary.h"


//////////////////////
//* プレイヤクラス *//
//////////////////////
class Player :
	public MyLibrary::Obj3D
{
public:
	Player(bool isPlayer);
	~Player();

	// 移動関数
	void Move();

	// 当たり判定の更新関数
	void UpdateCollision();
	// 当たり判定の描画関数
	void DrawCollision();
	// 終了関数
	void Finalization();
	// 終了かどうかの判定関数
	bool isEnded();
	// 当たり判定の取得
	const MyLibrary::SphereNode& GetCollision() { return m_collision; }

private:
	// 当たり判定（球状）
	//SphereNode m_collision;　NOTE:コリジョンノードはコンストラクタのあるクラスなので、まずそれを起動させないとダメ
	//std::unique_ptr<MyLibrary::SphereNode> m_collision;
	MyLibrary::SphereNode m_collision;

	//* ゲームオーバー判定
	bool m_isOver;
};

