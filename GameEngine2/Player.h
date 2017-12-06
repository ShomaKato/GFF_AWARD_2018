///-------------------------------------------------------------------
//*
//*	@�쐬��		2017/11/16
//*
//*	@���O		Player.h
//*
//*	@����		���� ���n
//*
//* @����		Obj3D�N���X���p�����A�ړ��@�\��ǋL�������@�N���X�̃w�b�_�[
//*
///----------------------------------------------------------------

// ���d�C���N���[�h�̖h�~
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
//#include <DirectXMath.h>
//#include <DirectXColors.h>

//#include "..\MyLibrary\3D\Obj3D.h"
//#include "..\MyLibrary\Input\KeyboardUtil.h"
//#include "..\MyLibrary\Collision\CollisionNode.h"

#include "MyLibrary.h"


//////////////////////
//* �v���C���N���X *//
//////////////////////
class Player :
	public MyLibrary::Obj3D
{
public:
	Player(bool isPlayer);
	~Player();

	// �ړ��֐�
	void Move();

	// �����蔻��̍X�V�֐�
	void UpdateCollision();
	// �����蔻��̕`��֐�
	void DrawCollision();
	// �I���֐�
	void Finalization();
	// �I�����ǂ����̔���֐�
	bool isEnded();
	// �����蔻��̎擾
	const MyLibrary::SphereNode& GetCollision() { return m_collision; }

private:
	// �����蔻��i����j
	//SphereNode m_collision;�@NOTE:�R���W�����m�[�h�̓R���X�g���N�^�̂���N���X�Ȃ̂ŁA�܂�������N�������Ȃ��ƃ_��
	//std::unique_ptr<MyLibrary::SphereNode> m_collision;
	MyLibrary::SphereNode m_collision;

	//* �Q�[���I�[�o�[����
	bool m_isOver;
};

