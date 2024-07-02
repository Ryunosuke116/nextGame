#include "DxLib.h"
#include <math.h>
#include <vector>
#include "Map.h"
#include "Collision.h"
#include "WorldSprite.h"
#include "Loader.h"



Map::Map()
{
	mapChipHandle = LoadGraph("material/Island2.png");
	skyHandle = LoadGraph("material/sky.png");
	pos = VGet(0, 0, 0);
	Rotate = VGet(1.7f, 0, 0);
	loader = new Loader();
}

Map::~Map()
{
	
}

void Map::Load()
{
	loader->mapLayerLoader(mapLayer.mapData, mapLayer.mapXNum,
							mapLayer.mapYNum, "material/map.csv");
	for (int i = 0; i < mapLayer.mapYNum; i++)
	{
		for (int j = 0; j < mapLayer.mapXNum; j++)
		{
			if (mapLayer.mapData[i][j] > 0)
			{
				auto worldSprite = new WorldSprite();
				worldSprite->Initialize(mapChipHandle, ChipPixelSize,mapLayer.mapData[i][j]);
				Chip chip;
				chip.worldSprite = worldSprite;
				VECTOR chipPos = VGet(0,-10, i * -6.0f);
				worldSprite->SetPos(chipPos);
				chip.pos = chipPos;
				chip.col = i;
				//chip.chipRect.
				chips.push_back(chip);
			}
		}
	}
}

void Map::Draw()
{
	MV1DrawModel(backGroundHandle);
	DrawGraph(0, 0, skyHandle, false);
	for (const auto& chip : chips)
	{
		chip.worldSprite->Draw();
	}
}

const Map::Chip& Map::GetChip(int col) const
{
	for (const auto& chip : chips)
	{
		if (col == chip.col)
		{
			return chip;
		}
	}
	
}

