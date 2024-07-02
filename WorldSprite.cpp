#include "DxLib.h"
#include "WorldSprite.h"


void WorldSprite::Initialize(int chipGraph, int chipPixelSize,int spriteNo)
{

    this->textureGraph = chipGraph;

    int texW, texH;
    GetGraphTextureSize(textureGraph, &texW, &texH);
    int chipNum = texW / chipPixelSize;
    int chipNoX = spriteNo % chipNum;
    int chipNoY = spriteNo / chipNum;
    float oneChipUVRate = 1.0f / (float)chipNum;   // テクスチャ全部を1.0とした時のcihp一個に対するuvのサイズ
   
    //uは左上端、vは右下端
    Vertex[0].u = (chipNoX + 0.0f) * oneChipUVRate;
    Vertex[0].v = (chipNoY + 0.0f) * oneChipUVRate;
    Vertex[1].u = (chipNoX + 1.0f) * oneChipUVRate;
    Vertex[1].v = (chipNoY + 0.0f) * oneChipUVRate;
    Vertex[2].u = (chipNoX + 0.0f) * oneChipUVRate;
    Vertex[2].v = (chipNoY + 1.0f) * oneChipUVRate;
    Vertex[3].u = (chipNoX + 1.0f) * oneChipUVRate;
    Vertex[3].v = (chipNoY + 1.0f) * oneChipUVRate;

   

    //ディフューズ、スペキュラは初期化時に固定
    for (int i = 0; i < 4; i++)
    {
        Vertex[i].dif = GetColorU8(255, 255, 255, 255);
        Vertex[i].spc = GetColorU8(0, 0, 0, 0);
        Vertex[i].norm = VGet(0.0f, 0.0f, -1.0f);    //回転をサポートしないのでノーマルも固定

       //  補助テクスチャをサポートしないのでuv固定
        Vertex[i].su = 0.0f;
        Vertex[i].sv = 0.0f;
    }

   //２ポリゴン分のインデックスデータをセット
    Index[0] = 0;
    Index[1] = 1;
    Index[2] = 2;
    Index[3] = 3;
    Index[4] = 2;   
    Index[5] = 1;

}

void WorldSprite::SetPos(const VECTOR pos)
{
    //  ポジション
    Vertex[0].pos = VAdd(pos, VGet(-2.5f, 0, 2.5f));
    Vertex[1].pos = VAdd(pos, VGet(2.5f, 0, 2.5f));
    Vertex[2].pos = VAdd(pos, VGet(-2.5f, 0, -2.5f));
    Vertex[3].pos = VAdd(pos, VGet(2.5f, 0, -2.5f));
}

void WorldSprite::getPos(VECTOR pos[])
{
    pos[0] = Vertex[0].pos;
    pos[1] = Vertex[1].pos;
    pos[2] = Vertex[2].pos;
    pos[3] = Vertex[3].pos;
}

void WorldSprite::Draw()
{
    // ２ポリゴンの描画
    DrawPolygonIndexed3D(Vertex, 4, Index, 2, textureGraph, FALSE);
}
