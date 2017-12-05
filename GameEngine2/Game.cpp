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


	//* カメラの初期化-----------------------------------------------------------	
	// デバッグカメラ作成
	//m_debugCamera = std::make_unique<DebugCamera>(windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);

	m_camera = std::make_unique<Camera>(windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);
	//* -------------------------------------------------------------------------

	{ // Obj3D初期化
		// 設定
		Obj3D::CommonDef def;
		//def.pCamera = m_debugCamera.get();
		def.pCamera = m_camera.get();
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
	//* yukの読み込み
	m_floorWall[0] = std::make_unique<Obstacle>();
	m_floorWall[0]->SetTrans(Vector3(0.0f, -5.4f, 0.0f));
	m_floorWall[0]->SetScale(Vector3(20.0f, 1.0f, 20.0f));
	m_floorWall[1] = std::make_unique<Obstacle>();
	m_floorWall[1]->SetTrans(Vector3(0.0f, -5.4f, -100.0f));
	m_floorWall[1]->SetScale(Vector3(20.0f, 1.0f, 20.0f));

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

	//* 進んだ記録を左上に表示
	int distance = m_player->GetTrans().z;
	m_DebugText->AddText(Vector2(0, 0), L"Record:%dm", -distance);

	//* 壁のコリジョン判定を考える時間がなさそうなので、領域で判定
	if (m_player->GetTrans().x < 6.0f && 
		m_player->GetTrans().x > -6.0f &&
		m_player->GetTrans().y < 3.5f &&
		m_player->GetTrans().y > -3.5f)
	{//* 領域の外に出ていないならば
		//* プレイヤの更新処理
		m_player->Move();
		//* カメラの更新処理
		m_camera->Update();
	}
	else
	{
		// ゲームオーバーになったら記録とタイトルへ促す文章を表示
		m_DebugText->AddText(Vector2(0, 50), L"Your record is %d m!\nPress SPACE to title.", -distance);
	}

	m_player->Update();
	m_player->UpdateCollision();

	////* プレイヤの更新処理
	//m_player->Move();

	//if (m_player->GetTrans().x > 5)
	//{
	//	m_player->Finalization();
	//}

	//m_player->Update();
	//m_player->UpdateCollision();




	//m_debugCamera->Update();


	//* 壁の更新
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
	//m_ObjSkydome->Draw();

	//* プレイヤの描画
	m_player->Draw();
	m_player->DrawCollision();

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


void Game::EndGame()
{
}
