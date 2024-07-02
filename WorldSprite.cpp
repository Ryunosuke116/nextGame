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
    float oneChipUVRate = 1.0f / (float)chipNum;   // �e�N�X�`���S����1.0�Ƃ�������cihp��ɑ΂���uv�̃T�C�Y
   
    //u�͍���[�Av�͉E���[
    Vertex[0].u = (chipNoX + 0.0f) * oneChipUVRate;
    Vertex[0].v = (chipNoY + 0.0f) * oneChipUVRate;
    Vertex[1].u = (chipNoX + 1.0f) * oneChipUVRate;
    Vertex[1].v = (chipNoY + 0.0f) * oneChipUVRate;
    Vertex[2].u = (chipNoX + 0.0f) * oneChipUVRate;
    Vertex[2].v = (chipNoY + 1.0f) * oneChipUVRate;
    Vertex[3].u = (chipNoX + 1.0f) * oneChipUVRate;
    Vertex[3].v = (chipNoY + 1.0f) * oneChipUVRate;

   

    //�f�B�t���[�Y�A�X�y�L�����͏��������ɌŒ�
    for (int i = 0; i < 4; i++)
    {
        Vertex[i].dif = GetColorU8(255, 255, 255, 255);
        Vertex[i].spc = GetColorU8(0, 0, 0, 0);
        Vertex[i].norm = VGet(0.0f, 0.0f, -1.0f);    //��]���T�|�[�g���Ȃ��̂Ńm�[�}�����Œ�

       //  �⏕�e�N�X�`�����T�|�[�g���Ȃ��̂�uv�Œ�
        Vertex[i].su = 0.0f;
        Vertex[i].sv = 0.0f;
    }

   //�Q�|���S�����̃C���f�b�N�X�f�[�^���Z�b�g
    Index[0] = 0;
    Index[1] = 1;
    Index[2] = 2;
    Index[3] = 3;
    Index[4] = 2;   
    Index[5] = 1;

}

void WorldSprite::SetPos(const VECTOR pos)
{
    //  �|�W�V����
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
    // �Q�|���S���̕`��
    DrawPolygonIndexed3D(Vertex, 4, Index, 2, textureGraph, FALSE);
}
