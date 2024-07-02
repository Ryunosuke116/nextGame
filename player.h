#pragma once
#include "Collision.h"
#include "Map.h"

class Collision;
class Map;

class Player 
{
private:
    int modelHandle;    //モデルハンドル
    VECTOR pos;         //ポジション

    bool jumpFlag;
    bool onGround;					 // 着地しているか？
    bool hitOnGround;				 // 着地しているか？
    bool touchFlg;
    bool fallingFlg;

    float moveSpeed;
    float currentJumpSpeed;	 // 現在のジャンプのスピード
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