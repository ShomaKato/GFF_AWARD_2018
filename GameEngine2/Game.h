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


	// デバッグカメラ
	std::unique_ptr<MyLibrary::DebugCamera> m_debugCamera;
	// 天球
	std::unique_ptr<MyLibrary::Obj3D> m_ObjSkydome;
	std::unique_ptr<MyLibrary::Obj3D> m_ObjTest;


	//* プレイヤ
	std::unique_ptr<Player> m_player;
	//* 仮障害物
	std::unique_ptr<Obstacle> m_obstacle;

	//* カメラ
	std::unique_ptr<MyLibrary::Camera> m_camera;

};