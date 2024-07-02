#include "DxLib.h"
#include<vector>
#include"player.h"
#include"Camera.h"
#include "Map.h"

/// <summary>
/// ���C���֐�
/// </summary>
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	// ��ʃ��[�h�̃Z�b�g
	ChangeWindowMode(TRUE);
	SetGraphMode(1600, 900, 16);

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;	// �G���[���N�����璼���ɏI��
	}

	Player* player = new Player();
	Camera* camera = new Camera();
	Map*	map	   = new Map();

	//������
	player->Initilize();

	//���[�h
	map->Load();

	// �G�X�P�[�v�L�[��������邩�E�C���h�E��������܂Ń��[�v
	LONGLONG frameTime = 0;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		frameTime = GetNowHiPerformanceCount();

		player->Update(*map);
		camera->Update(*player);

		//��ʂ̏�����
		ClearDrawScreen();

		// �f�o�b�O�`��
		// XYZ��
		float lineSize = 300.0f;
		DrawLine3D(VGet(-lineSize, 0, 0), VGet(lineSize, 0, 0), GetColor(255, 0, 0));
		DrawLine3D(VGet(0, -lineSize, 0), VGet(0, lineSize, 0), GetColor(0, 255, 0));
		DrawLine3D(VGet(0, 0, -lineSize), VGet(0, 0, lineSize), GetColor(0, 0, 255));

		map->Draw();
		player->Draw();

		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();

		// �G��60fps�Œ�
		while ((GetNowHiPerformanceCount() - frameTime) < 16667) {}
	}	


	// �c�w���C�u�����̌�n��
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}