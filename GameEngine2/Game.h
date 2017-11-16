//
// Game.h
//

#pragma once

#include <DirectXMath.h>
#include <DirectXColors.h>

#include "MyLibrary.h"
#include "ParticleTest.h"

class Game : public MyLibrary::Framework
{
public:
	Game(HINSTANCE hInstance, int nCmdShow);

    void Initialize() override;

	void Finalize() override;

private:

    void Update(MyLibrary::StepTimer const& timer);
    void Render();


	// デバッグカメラ
	std::unique_ptr<MyLibrary::DebugCamera> m_debugCamera;
	// 天球
	std::unique_ptr<MyLibrary::Obj3D> m_ObjSkydome;
	std::unique_ptr<MyLibrary::Obj3D> m_ObjTest;



	//* テスト用プレイヤ-------------------------------------------------
	std::unique_ptr<MyLibrary::Obj3D> m_ball;
	//* 座標
	DirectX::SimpleMath::Vector3 m_pos;

	//* 移動関数
	void Move();
	//* -----------------------------------------------------------------

	//* カメラ-----------------------------------------------------------
	std::unique_ptr<MyLibrary::Camera> m_camera;
	// カメラ座標
	DirectX::SimpleMath::Vector3 m_eyepos;
	// ターゲット座標
	DirectX::SimpleMath::Vector3 m_refpos;
	// 上方向ベクトル
	DirectX::SimpleMath::Vector3 m_upvec;

	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;
	// プロジェクション行列
	DirectX::SimpleMath::Matrix m_proj;
	// 縦方向視野角
	float m_fovY;
	// アスペクト比
	float m_aspect;
	// ニアクリップ
	float m_nearClip;
	// ファークリップ
	float m_farClip;
};