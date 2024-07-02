#include"Dxlib.h"
#include"Windows.h"
#include "Loader.h"


bool Loader::mapLayerLoader(int** &mapData, int &mapXNum, int& mapYNum, const char* mapCSVFileName)
{
	// dst������
	mapData = NULL;
	mapXNum = 0;
	mapYNum = 0;

	// �t�@�C�����J��
	FILE* fp;
	errno_t err = fopen_s(&fp, mapCSVFileName, "rt");;
	if (!fp)
	{
		printf("�t�@�C�����J���܂���");
		return 0;
	}

	// �t�@�C�����P�s����ǂ݂��A�P�s�̃f�[�^���𐔂���
	char c = 0;
	while (c != '\n')
	{
		// �ǂݎ�����������J���}�Ȃ�1�J�E���g���₷
		c = fgetc(fp);
		if (',' == c)
		{
			mapXNum++;
		}
	}
	mapXNum++;

	//�P�f�[�^ 16bit�ő�l "65535,"(6����)�Ƃ��ĕ���������Ă����Ƃ��̂P�s�T�C�Y
	int bufferLen = mapXNum * 6 + 1;

	//�P�s���̃o�b�t�@�m��
	char* buf = new char[bufferLen];
	char* ptmp = buf;

	//�t�@�C���|�C���^��擪�ɖ߂��s����ǂ�
	fseek(fp, 0, SEEK_SET);
	bool firstRow = true;
	while (fgets(buf, bufferLen - 1, fp) != NULL)
	{
		mapYNum++;
	}

	//2�����z��𓮓I�m�ۂ��� map[row][col] �Ƃ��ē��I�m�ۂ���
	mapData = new int* [mapYNum];

	int ix, iy;
	for (iy = 0; iy < mapYNum; iy++)
	{
		mapData[iy] = new int[mapXNum];
	}

	//�t�@�C���|�C���^��擪�ɖ߂�
	fseek(fp, 0, SEEK_SET);
	// �t�@�C������f�[�^��z��Ɉڂ�
	char* readPoint;
	char* firstPoint;
	for (iy = 0; iy < mapYNum; iy++)
	{
		// 1�s��荞��
		fgets(buf, bufferLen - 1, fp);
		readPoint = firstPoint = buf;

		for (ix = 0; ix < mapXNum; ix++)
		{
			//�J���}�܂�readPoint�̈ʒu��i�߂�
			while (',' != *readPoint && '\n' != *readPoint)
			{
				readPoint++;
			}
			// �J���}��NULL�����ɒu������
			*readPoint = '\0';
			//���̎��_��firstPoint - readPoint�Ԃŕ����񂪊�������̂Ő��l�ɕϊ�
			mapData[iy][ix] = atoi(firstPoint);

			//���̃f�[�^�ǂݎ��ʒu�܂Ői�߂�
			readPoint++;
			firstPoint = readPoint;
		}
	}

	// �t�@�C�������
	fclose(fp);

	// �o�b�t�@�J��
	delete[] buf;

	return true;
}