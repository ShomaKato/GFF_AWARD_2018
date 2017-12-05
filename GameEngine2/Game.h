//
// Game.h
//

#pragma once

#include <DirectXMath.h>
#include <DirectXColors.h>
//
//#include "MyLibrary.h"
#include "Player.h"
#include "Obstacle.h"


class Game : public MyLibrary::Framework
{
public:
	Game(HINSTANCE hInstance, int nCmdShow);

    void Initialize() override;

	void Finalize() override;

private:

    void Update(MyLibrary::StepTimer const& timer);
    void Render();

	//* ゲームオーバー関数
	void EndGame();

	// デバッグカメラ
	std::unique_ptr<MyLibrary::DebugCamera> m_debugCamera;
	// 天球
	std::unique_ptr<MyLibrary::Obj3D> m_ObjSkydome;
	std::unique_ptr<MyLibrary::Obj3D> m_ObjTest;


	//* プレイヤ
	std::unique_ptr<Player> m_player;
	//* 壁
	std::unique_ptr<Obstacle> m_leftWall[2];
	std::unique_ptr<Obstacle> m_rightWall[2];
	std::unique_ptr<Obstacle> m_roofWall[2];
	std::unique_ptr<Obstacle> m_floorWall[2];

	//* 障害物
	std::unique_ptr<Player> m_obstacle;
	//* step1:奥行き3以内に二個以上存在しない
	//* 訂正：奥行き3ごとに一個ずつ配置

	//* step2:奥行きの感覚をある程度ランダムに

	//* step3:一ラインに二個以上配置可能に



	//* extra:進むごとに壁を自動生成				完了
	//* 壁を二個作って、進むごとに手前のを消して奥へ表示、という手法がよく使われる

	//* extra:記録を何処かに表示	*				完了


	//* カメラ
	std::unique_ptr<MyLibrary::Camera> m_camera;

	//* 壁の判定用変数
	bool m_whichWall;

	//* どれくらい進んだら壁が新たに表示されるか
	float m_wallInterval;

	//* どれくらい進んだら障害物が新たに表示されるか
	float m_obstacleInterval;
};