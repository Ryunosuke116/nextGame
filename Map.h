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
		int col;					//列
	};
	struct sMapLayer
	{
		int** mapData; // マップチップの2次元配列
		int   mapXNum; // マップチップが横方向に並んでいる数
		int   mapYNum; // マップチップが縦方向に並んでいる数
	};
	sMapLayer mapLayer;

	const Chip& GetChip(int col)const;

	// マップチップのサイズ
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

