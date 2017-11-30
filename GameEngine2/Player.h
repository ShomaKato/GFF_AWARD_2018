// ���d�C���N���[�h�̖h�~
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
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

	// �ړ��֐�
	void Move();

	// �����蔻��̍X�V�֐�
	void UpdateCollision();
	// �����蔻��̕`��֐�
	void DrawCollision();
	//// �����蔻��̎擾
	//SphereNode* GetCollision() { return m_collision; }

protected:
	// �����蔻��i�J�v�Z����j
	//SphereNode m_collision;�@NOTE:�R���W�����m�[�h�̓R���X�g���N�^�̂���N���X�Ȃ̂ŁA�܂�������N�������Ȃ��ƃ_��
	//std::unique_ptr<MyLibrary::SphereNode> m_collision;
	MyLibrary::SphereNode* m_collision;
};

