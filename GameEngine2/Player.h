// 多重インクルードの防止
#pragma once

// ヘッダファイルのインクルード
#include <DirectXMath.h>
#include <DirectXColors.h>

//#include "..\MyLibrary\3D\Obj3D.h"
//#include "..\MyLibrary\Input\KeyboardUtil.h"
//#include "..\MyLibrary\Collision\CollisionNode.h"

#include "MyLibrary.h"

class Player :
	public MyLibrary::Obj3D
{
public:
	Player();
	~Player();

	// 移動関数
	void Move();

	// 当たり判定の更新関数
	void UpdateCollision();
	// 当たり判定の描画関数
	void DrawCollision();
	//// 当たり判定の取得
	//SphereNode* GetCollision() { return m_collision; }

protected:
	// 当たり判定（カプセル状）
	//SphereNode m_collision;　NOTE:コリジョンノードはコンストラクタのあるクラスなので、まずそれを起動させないとダメ
	//std::unique_ptr<MyLibrary::SphereNode> m_collision;
	MyLibrary::SphereNode* m_collision;
};

