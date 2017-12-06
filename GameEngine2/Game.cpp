//
// Game.cpp
//

#include "Game.h"
#include "ParticleTest.h"
#include<time.h>

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

	//* 乱数のランダム化
	srand((unsigned int)time(NULL));

	//* カメラの初期化-----------------------------------------------------------
	m_camera = std::make_unique<Camera>(windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);
	//* -------------------------------------------------------------------------

	{ // Obj3D初期化
		// 設定
		Obj3D::CommonDef def;
		def.pCamera = m_camera.get();
		def.pDevice = deviceResources->GetD3DDevice();
		def.pDeviceContext = deviceResources->GetD3DDeviceContext();
		// 設定を元に初期化
		Obj3D::InitializeCommon(def);
	}

	// 天球読み込み
	m_ObjSkydome = std::make_unique<Obj3D>();
	m_ObjSkydome->LoadModel(L"skydome");

	//* プレイヤの初期化 ---------------------------------------------------
	m_player = std::make_unique<Player>(1);
	//* --------------------------------------------------------------------

	//* 壁の初期化 ---------------------------------------------------

	//* 最初は0の壁が手前
	m_whichWall = 0;
	//* どれくらい進んだら次の壁が作られるか
	m_wallInterval = -100.0f;

	//* 左の壁の読み込み
	m_leftWall[0] = std::make_unique<Obstacle>();
	m_leftWall[0]->SetTrans(Vector3(-7.5f, -10.0f, 0.0f));
	m_leftWall[0]->SetScale(Vector3(1.0f, 20.0f, 20.0f));
	m_leftWall[1] = std::make_unique<Obstacle>();
	m_leftWall[1]->SetTrans(Vector3(-7.5f, -10.0f, -100.0f));
	m_leftWall[1]->SetScale(Vector3(1.0f, 20.0f, 20.0f));

	//* 右の壁の読み込み
	m_rightWall[0] = std::make_unique<Obstacle>();
	m_rightWall[0]->SetTrans(Vector3(7.5f, -10.0f, 0.0f));
	m_rightWall[0]->SetScale(Vector3(1.0f, 20.0f, 20.0f));
	m_rightWall[1] = std::make_unique<Obstacle>();
	m_rightWall[1]->SetTrans(Vector3(7.5f, -10.0f, -100.0f));
	m_rightWall[1]->SetScale(Vector3(1.0f, 20.0f, 20.0f));
	//* 天井の読み込み
	m_roofWall[0] = std::make_unique<Obstacle>();
	m_roofWall[0]->SetTrans(Vector3(0.0f, 4.4f, 0));
	m_roofWall[0]->SetScale(Vector3(20.0f, 1.0f, 20.0f));
	m_roofWall[1] = std::make_unique<Obstacle>();
	m_roofWall[1]->SetTrans(Vector3(0.0f, 4.4f, -100));
	m_roofWall[1]->SetScale(Vector3(20.0f, 1.0f, 20.0f));
	//* 床の読み込み
	m_floorWall[0] = std::make_unique<Obstacle>();
	m_floorWall[0]->SetTrans(Vector3(0.0f, -5.4f, 0.0f));
	m_floorWall[0]->SetScale(Vector3(20.0f, 1.0f, 20.0f));
	m_floorWall[1] = std::make_unique<Obstacle>();
	m_floorWall[1]->SetTrans(Vector3(0.0f, -5.4f, -100.0f));
	m_floorWall[1]->SetScale(Vector3(20.0f, 1.0f, 20.0f));

	//* --------------------------------------------------------------------

	//* 障害物の初期化 ---------------------------------------------------

	//* 最初は0が最初で、奥に進むに連れて1,2,3となっていく
	m_whichObstacle = 0;
	//* どれくらい進んだら次の障害物が作られるか
	m_obstacleInterval = -20.0f;

	//* 障害物読み込み
	for (int i = 0; i < 8; i++)
	{
		m_obstacle[i] = std::make_unique<Player>(0);
		m_obstacle[i]->SetScale(Vector3(1.5f, 1.5f, 1.5f));
		m_obstacle[i]->SetTrans(Vector3(rand() % 8-4, rand() % 4-2, -15 + (m_obstacleInterval * i)));
	}


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
	//MouseUtil::GetInstance()->Update();
	//ADX2Le::GetInstance()->Update();

	//* キーボード情報を毎フレーム更新する
	KeyboardUtil::GetInstance()->Update();

	//* カメラの更新処理 -----------------------------------------------------------
	m_camera->Update();
	//* ----------------------------------------------------------------------------


	//* プレイヤの更新処理 ---------------------------------------------------------

	//* 進んだ記録を左上に表示
	int distance = m_player->GetTrans().z;
	m_DebugText->AddText(Vector2(0, 0), L"Record:%dm", -distance);

	//* ゲームオーバーでないなら前進し続ける
	if (!m_player->isEnded())
	{
		m_player->Move();
	}

	//* 壁のコリジョン判定を考える時間がなさそうなので、領域で判定
	//* 領域の外に出たらゲームオーバー
	if (m_player->GetTrans().x < 6.0f && 
		m_player->GetTrans().x > -6.0f &&
		m_player->GetTrans().y < 3.5f &&
		m_player->GetTrans().y > -3.5f)
	{//* 領域の外に出ていないならば
		//* プレイヤの更新処理
		m_player->Update();
		m_player->UpdateCollision();
		//* 障害物の更新処理
		for (int i = 0; i < 8; i++)
		{
			m_obstacle[i]->Update();
			m_obstacle[i]->UpdateCollision();
		}
	}
	else
	{
		// ゲームオーバーになったら記録とタイトルへ促す文章を表示
		m_player->Finalization();
		m_DebugText->AddText(Vector2(0, 50), L"Your record is %d m!", -distance);
	}


	// プレイヤと障害物の、当たり判定の球を受け取る
	const Sphere& playerSphere = m_player->GetCollision();
	for (int i = 0; i < 8; i++)
	{
		const Sphere& obstacleSphere = m_obstacle[i]->GetCollision();

		//* 障害物に触れてもゲームオーバー
		if (CheckSphere2Sphere(obstacleSphere, playerSphere))
		{
			m_player->Finalization();
			m_DebugText->AddText(Vector2(0, 50), L"Your record is %d m!", -distance);
		}
	}
	//* ----------------------------------------------------------------------------


	//* 壁の更新 -------------------------------------------------------------------
	//* プレイヤが一定距離進んだら、手前の壁が奥に移動して次の壁になる
	if (distance <= m_wallInterval)
	{
		m_wallInterval -= 100.0f;
		m_leftWall[m_whichWall]->SetTrans(Vector3(-7.5f, -10.0f, m_wallInterval));
		m_rightWall[m_whichWall]->SetTrans(Vector3(7.5f, -10.0f, m_wallInterval));
		m_roofWall[m_whichWall]->SetTrans(Vector3(0.0f, 4.4f, m_wallInterval));
		m_floorWall[m_whichWall]->SetTrans(Vector3(0.0f, -5.4f, m_wallInterval));
		m_whichWall = !m_whichWall;
	}
	//* ----------------------------------------------------------------------------

	//* 障害物の更新 ---------------------------------------------------------------
	//* プレイヤが一定距離進んだら、一番手前の障害物が奥に移動して次の障害物になる
	if (distance <= m_obstacleInterval)
	{
		m_obstacleInterval -= 20.f;
		m_obstacle[m_whichObstacle]->SetTrans(Vector3(rand() % 8-4, rand() % 4-2, -135 + m_obstacleInterval));
		m_whichObstacle++;

		if (m_whichObstacle == 8)
		{
			m_whichObstacle = 0;
		}
	}
	//* ----------------------------------------------------------------------------
}
#pragma endregion

#pragma region Frame Render
/// <summary>
/// 毎フレーム描画
/// </summary>
void Game::Render()
{
	//m_ObjSkydome->Draw();

	//* プレイヤの描画
	m_player->Draw();
	m_player->DrawCollision();

	//* 障害物の描画
	for (int i = 0; i < 8; i++)
	{
		m_obstacle[i]->Draw();
		m_obstacle[i]->DrawCollision();
	}

	//* 壁の描画
	m_leftWall[0]->Draw();
	m_leftWall[1]->Draw();
	m_rightWall[0]->Draw();
	m_rightWall[1]->Draw();
	m_roofWall[0]->Draw();
	m_roofWall[1]->Draw();
	m_floorWall[0]->Draw();
	m_floorWall[1]->Draw();
}


bool Game::StopGame()
{
	return false;
}
