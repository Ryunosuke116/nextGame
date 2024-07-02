#pragma once
#include "DxLib.h"
#include "Collision.h"
class WorldSprite
{
private:
	VECTOR		pos;			// 描画ポジション
	VERTEX3D	Vertex[4];		// 頂点バッファ
	WORD		Index[6];		// インデックスバッファ
	int			textureGraph;	// スプライトを作成する元テクスチャのグラフィックハンドル
public:

	void Initialize(int chipGraph, int chipPixelSize,int spriteNo);
	void SetPos(const VECTOR pos);
	void Draw();

	void getPos(VECTOR pos[]);
};

