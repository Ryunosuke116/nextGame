#pragma once

class WorldSprite;
class Loader;

class Map
{
public:

	Map();
	~Map();
	void Load();
	void Draw();
	const int& GetMapLayer()const { return mapLayer.mapYNum; }
	int** GetMapLayer1()const { return  mapLayer.mapData; }

	const int& GetHandle()const { return mapChipHandle; }


	struct Chip
	{
		VECTOR pos;
		WorldSprite* worldSprite;
		int col;					//��
	};
	struct sMapLayer
	{
		int** mapData; // �}�b�v�`�b�v��2�����z��
		int   mapXNum; // �}�b�v�`�b�v���������ɕ���ł��鐔
		int   mapYNum; // �}�b�v�`�b�v���c�����ɕ���ł��鐔
	};
	sMapLayer mapLayer;

	const Chip& GetChip(int col)const;

	// �}�b�v�`�b�v�̃T�C�Y
	static constexpr float	ChipSize = 0.725f;
	static constexpr int	ChipPixelSize = 32;
	static constexpr int    ChipNum = 30;

private:
	VECTOR Rotate;
	VECTOR pos;
	int mapChipHandle;
	int backGroundHandle;
	int skyHandle;
	std::vector<Chip> chips;
	Loader* loader;

};

