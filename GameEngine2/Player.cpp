///-------------------------------------------------------------------
//*
//*	@�쐬��		2017/11/16
//*
//*	@���O		Player.cpp
//*
//*	@����		���� ���n
//*
//* @����		Obj3D�N���X���p�����A�ړ��@�\��ǋL�������@�N���X�̃\�[�X
//*
///----------------------------------------------------------------

// �w�b�_�t�@�C���̃C���N���[�h
#include "Player.h"

// ���O��Ԃ̒�`
using namespace MyLibrary;
using namespace DirectX;
using namespace DirectX::SimpleMath;


////////////////////////
//* �����o�ϐ��̒�` *//
////////////////////////

////----------------------------------------------------------------------
////! @�֐����FPlayer
////!
////! @�����F�v���C���N���X�̃R���X�g���N�^
////!
////! @�����F�Ȃ�(void)
////!
////! @�߂�l�F���݂��Ȃ�
////----------------------------------------------------------------------
Player::Player(bool isPlayer)
	:m_isOver(false)
{
	// �����蔻��̐ݒ�
	//m_collision = std::make_unique<SphereNode>();
	m_collision.Initialize();
	m_collision.SetDebugVisible(false);
	//m_collision.SetLength(0.1f);
	m_collision.SetTrans(GetTrans());
	//m_collision.SetRot(Vector3(0, 0, 0));

	// �����ɂ���āA�v���C�����f������Q�����f�����؂�ւ���
	if (isPlayer)
	{
		// �v���C�����f���̓ǂݍ���
		LoadModel(L"ball2");
		m_collision.SetLocalRadius(0.9f);
	}
	else
	{
		// ��Q�����f���̓ǂݍ���
		LoadModel(L"ball3");
		m_collision.SetLocalRadius(1.45f);
	}
}


////----------------------------------------------------------------------
////! @�֐����F~Player
////!
////! @�����F�v���C���N���X�̃f�X�g���N�^
////!
////! @�����F���݂��Ȃ�
////!
////! @�߂�l�F���݂��Ȃ�
////----------------------------------------------------------------------
Player::~Player()
{

}


////----------------------------------------------------------------------
////! @�֐����FMove
////!
////! @�����F�L�[�{�[�h�ō��E�㉺�ړ����\�ɂ���֐�
////!
////! @�����F�Ȃ�(void)
////!
////! @�߂�l�F�Ȃ�(void)
////----------------------------------------------------------------------
void Player::Move()
{
	//* ������ꏊ�ɁA���ݍ��W���X�V
	m_Trans = GetTrans();

	//* ��ɑO�Ɍ������Đi�ݑ�����
	m_Trans.z = m_Trans.z - 0.2f;

	//* A�L�[�������ꂽ��
	if (KeyboardUtil::GetInstance()->IsPressed(Keyboard::Keys::A))
	{
		m_Trans.x = m_Trans.x - 0.2f;
	}
	//* D�L�[�������ꂽ��
	if (KeyboardUtil::GetInstance()->IsPressed(Keyboard::Keys::D))
	{
		m_Trans.x = m_Trans.x + 0.2f;
	}
	//* W�L�[�������ꂽ��
	if (KeyboardUtil::GetInstance()->IsPressed(Keyboard::Keys::W))
	{
		m_Trans.y = m_Trans.y + 0.2f;
	}
	//* S�L�[�������ꂽ��
	if (KeyboardUtil::GetInstance()->IsPressed(Keyboard::Keys::S))
	{
		m_Trans.y = m_Trans.y - 0.2f;
	}

	//* �ړ���̍��W�����ݍ��W�ɐݒ�
	SetTrans(m_Trans);
}


////----------------------------------------------------------------------
////! @�֐����FUpdateCollision
////!
////! @�����F�����蔻����X�V����֐�
////!
////! @�����F�Ȃ�(void)
////!
////! @�߂�l�F�Ȃ�(void)
////----------------------------------------------------------------------
void Player::UpdateCollision()
{
	// �X�y�[�X�L�[�������ꂽ������t���O�̃I���I�t
	if (KeyboardUtil::GetInstance()->IsTriggered(Keyboard::Keys::Space))
	{
		m_collision.SetDebugVisible(!m_collision.GetDebugVisible());
	}
	// �����蔻��̍X�V
	m_collision.SetTrans(GetTrans());
	m_collision.Update();

}


////----------------------------------------------------------------------
////! @�֐����FDrawCollision
////!
////! @�����F�����蔻���`�悷��֐�
////!
////! @�����F�Ȃ�(void)
////!
////! @�߂�l�F�Ȃ�(void)
////----------------------------------------------------------------------
void Player::DrawCollision()
{
	// �����t���O���I���Ȃ瓖���蔻���\������
	if (m_collision.GetDebugVisible())
	{
		// �����蔻��̕`��
		m_collision.Draw();
	}
}


////----------------------------------------------------------------------
////! @�֐����FFinalization
////!
////! @�����F�v���C���N���X�̃C���X�^���X����������֐�
////!
////! @�����F�Ȃ�(void)
////!
////! @�߂�l�F�Ȃ�(void)
////----------------------------------------------------------------------
bool Player::isEnded()
{
	if (m_isOver)
	{
		return true;
	}
	return false;
}


////----------------------------------------------------------------------
////! @�֐����FFinalization
////!
////! @�����F�v���C���N���X�̃C���X�^���X����������֐�
////!
////! @�����F�Ȃ�(void)
////!
////! @�߂�l�F�Ȃ�(void)
////----------------------------------------------------------------------
void Player::Finalization()
{
	m_isOver = 1;
}
