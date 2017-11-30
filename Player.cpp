// �w�b�_�t�@�C���̃C���N���[�h
#include "player.h"

using namespace MyLibrary;
//using namespace MyLibrary::Obj3D;
using namespace DirectX;
using namespace DirectX::SimpleMath;

Player::Player()
{
	LoadModel(L"ball2");
}


Player::~Player()
{
}

void Player::Move()
{
	//* ������ꏊ�ɁA���ݍ��W���X�V
	m_Trans = GetTrans();

	//* ��ɑO�Ɍ������Đi�ݑ�����
	m_Trans.z = m_Trans.z - 0.1f;

	//* A�L�[�������ꂽ��
	if (KeyboardUtil::GetInstance()->IsPressed(Keyboard::Keys::A))
	{
		m_Trans.x = m_Trans.x - 0.3f;
	}
	//* D�L�[�������ꂽ��
	if (KeyboardUtil::GetInstance()->IsPressed(Keyboard::Keys::D))
	{
		m_Trans.x = m_Trans.x + 0.3f;
	}
	//* W�L�[�������ꂽ��
	if (KeyboardUtil::GetInstance()->IsPressed(Keyboard::Keys::W))
	{
		m_Trans.y = m_Trans.y + 0.3f;
	}
	//* S�L�[�������ꂽ��
	if (KeyboardUtil::GetInstance()->IsPressed(Keyboard::Keys::S))
	{
		m_Trans.y = m_Trans.y - 0.3f;
	}

	//* �ړ���̍��W�����ݍ��W�ɐݒ�
	SetTrans(m_Trans);
}
