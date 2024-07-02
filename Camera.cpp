#include "DxLib.h"
#include <vector>
#include "Camera.h"


Camera::Camera()
{
	// �O���t�B�b�N�̕`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(0.1f, 2000.0f);

    pos = VGet(0, 0, 0);

}

Camera::~Camera()
{

}

void Camera::Update(Player& player)
{
	VECTOR AimPos = VGet(0, 25, player.GetPos().z - 30.0f);
	VECTOR LookPos = VGet(0, -10, player.GetPos().z -15);

	VECTOR SubPos = VSub(AimPos, pos);
	VECTOR AddPos = VAdd(pos, SubPos);
	pos = AddPos;

    SetCameraPositionAndTarget_UpVecY(pos,
		LookPos);
}
