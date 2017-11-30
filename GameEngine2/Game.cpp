//
// Game.cpp
//

#include "Game.h"
#include "ParticleTest.h"

extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;
using namespace MyLibrary;

Game::Game(HINSTANCE hInstance, int nCmdShow)
	: Framework(hInstance, nCmdShow)
{
}

void Game::Initialize()
{
	DeviceResources* deviceResources = DeviceResources::GetInstance();

	// マウスライブラリにウィンドウハンドルを渡す
	MouseUtil::GetInstance()->SetWindow(DeviceResources::GetInstance()->GetWindow());
	
	// ウィンドウ矩形取得
	RECT windowRect = deviceResources->GetOutputSize();

	//// デバッグカメラ作成
	m_debugCamera = std::make_unique<DebugCamera>(windowRect.right- windowRect.left, windowRect.bottom - windowRect.top);

	//* カメラの初期化-----------------------------------------------------------
	//m_camera = std::make_unique<Camera>(windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);
	//* -------------------------------------------------------------------------

	{ // Obj3D初期化
		// 設定
		Obj3D::CommonDef def;
		def.pCamera = m_debugCamera.get();
		//def.pCamera = m_camera.get();
		def.pDevice = deviceResources->GetD3DDevice();
		def.pDeviceContext = deviceResources->GetD3DDeviceContext();
		// 設定を元に初期化
		Obj3D::InitializeCommon(def);
	}

	// 天球読み込み
	m_ObjSkydome = std::make_unique<Obj3D>();
	m_ObjSkydome->LoadModel(L"skydome");

	//m_ObjTest = std::make_unique<Obj3D>();
	//m_ObjTest->LoadModel(L"SphereNode");
	//m_ObjSkydome->AddChild(m_ObjTest.get());


	//* プレイヤの初期化 ---------------------------------------------------

	//* ボール読み込み
	m_player = std::make_unique<Player>();

	//* --------------------------------------------------------------------

	//* 仮障害物の初期化 ---------------------------------------------------

	//* ボックス読み込み
	m_obstacle = std::make_unique<Obstacle>();
	m_obstacle->SetTrans(Vector3(0, 0, -5));
	m_obstacle->SetRot(Vector3(0, XMConvertToRadians(90), 0));

	//* --------------------------------------------------------------------


	ADX2Le::GetInstance()->Initialize(L"ADX2_samples.acf");
	ADX2Le::GetInstance()->ADX2Le::LoadAcb(L"Basic.acb", L"Basic.awb");
}

void Game::Finalize()
{
	ADX2Le::GetInstance()->Finalize();
}

#pragma region Frame Update
/// <summary>
/// 毎フレーム更新
/// </summary>
/// <param name="timer">時間情報</param>
void Game::Update(StepTimer const& timer)
{
	MouseUtil::GetInstance()->Update();
	ADX2Le::GetInstance()->Update();


	//* キーボード情報を毎フレーム更新する
	KeyboardUtil::GetInstance()->Update();

	//* プレイヤの移動関数
	m_player->Move();
	m_player->Update();
	m_player->UpdateCollision();






	m_debugCamera->Update();

	//* カメラの更新-----------------------------------------------------------
	//m_camera->Update();
	//* -----------------------------------------------------------------------





	//if (MouseUtil::GetInstance()->IsTriggered(MyLibrary::MouseUtil::Button::Left))
	//{
	//	ADX2Le::GetInstance()->Play(5);
	//}
}
#pragma endregion

#pragma region Frame Render
/// <summary>
/// 毎フレーム描画
/// </summary>
void Game::Render()
{
	m_ObjSkydome->Draw();

	//* ボールの描画
	m_player->Draw();
	m_player->DrawCollision();

	//* ボックスの描画
	m_obstacle->Draw();
}



//
//
////* テスト用プレイヤ関数-------------------------------------------------
//void Game::Move()
//{
//	//* 今いる場所に、現在座標を更新
//	m_pos = m_ball->GetTrans();
//
//	//* 常に前に向かって進み続ける
//	m_pos.z = m_pos.z - 0.1f;
//
//	//* Aキーが押されたら
//	if (KeyboardUtil::GetInstance()->IsPressed(Keyboard::Keys::A))
//	{
//		m_pos.x = m_pos.x - 0.3f;
//	}
//	//* Dキーが押されたら
//	if (KeyboardUtil::GetInstance()->IsPressed(Keyboard::Keys::D))
//	{
//		m_pos.x = m_pos.x + 0.3f;
//	}
//	//* Wキーが押されたら
//	if (KeyboardUtil::GetInstance()->IsPressed(Keyboard::Keys::W))
//	{
//		m_pos.y = m_pos.y + 0.3f;
//	}
//	//* Sキーが押されたら
//	if (KeyboardUtil::GetInstance()->IsPressed(Keyboard::Keys::S))
//	{
//		m_pos.y = m_pos.y - 0.3f;
//	}
//
//	//* 移動後の座標を現在座標に設定
//	m_ball->SetTrans(m_pos);
//}
////* ---------------------------------------------------------------------
