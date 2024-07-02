#pragma once
#include "Collision.h"
#include "Map.h"

class Collision;
class Map;

class Player 
{
private:
    int modelHandle;    //���f���n���h��
    VECTOR pos;         //�|�W�V����

    bool jumpFlag;
    bool onGround;					 // ���n���Ă��邩�H
    bool hitOnGround;				 // ���n���Ă��邩�H
    bool touchFlg;
    bool fallingFlg;

    float moveSpeed;
    float currentJumpSpeed;	 // ���݂̃W�����v�̃X�s�[�h
    float jumpPower;
    float Gravity;
    float jumpDistance;
    struct HitRect
    {
        Collision* playerRect;
    };
    HitRect hitRect;
    std::vector<HitRect> HitRects;
    bool IsHitWithMapChip(const VECTOR& futurePos, const Map::Chip& mapChip);

public:
    Player();
    ~Player();

    void Initilize();
    void Update(const Map& map);
    void Draw();
    const Collision& GetRect() { return *hitRect.playerRect; }
    const VECTOR& GetPos() { return pos; }
    void CheckIsGround(const Map& map);
};