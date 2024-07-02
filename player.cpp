#include <math.h>
#include <vector>
#include "DxLib.h"
#include "Collision.h"
#include "Map.h"
#include"player.h"

Player::Player() 
{
    modelHandle = MV1LoadModel("material/Barbarian.mv1");   

    pos = VGet(0, 0, 0);

}

Player::~Player()
{
    // モデルのアンロード.
    MV1DeleteModel(modelHandle);
}

void Player::Initilize()
{
    pos = VGet(0, -10, 0);
    MV1SetScale(modelHandle, VGet(3.0f, 3.0f, 3.0f));

    auto playerRect = new Collision();
    playerRect->initRect(pos,*playerRect, 50, 50);
    hitRect.playerRect = playerRect;
   // HitRects.push_back(hitRect);


    // 3Dのポジション設定
    MV1SetPosition(modelHandle, pos);

    currentJumpSpeed = 0;	 // 現在のジャンプのスピード
    jumpPower = 1.2f;
    Gravity = 0.1f;
    jumpDistance = 6.0f / 24.0f;       //一度のジャンプで6ずつ進むようにする
    jumpFlag = false;
    onGround = true;					 // 着地しているか？
    hitOnGround = true;				 // 着地しているか？
    touchFlg = false;
    fallingFlg = false;

}

void Player::Update(const Map& map)
{

    if (CheckHitKey(KEY_INPUT_W))
    {
        pos.y += 0.1f;
      
    }
    if (CheckHitKey(KEY_INPUT_S))
    {
        pos.y -= 0.1f;
      
    }
    if (CheckHitKey(KEY_INPUT_A))
    {
        pos.z -= 0.1f;
    }
    if (CheckHitKey(KEY_INPUT_D))
    {
        pos.z += 0.1f;
    }

    if (CheckHitKey(KEY_INPUT_SPACE))
    {
        //ジャンプキーが押されてないかつ地面に足がついていればならジャンプする
        if (!jumpFlag)
        {
            if (onGround)
            {
                currentJumpSpeed += jumpPower;
                onGround = false;
            }
        }
        jumpFlag = true;
    }
    else
    {
        jumpFlag = false;
    }

    //空中にいるときの処理
    if (!onGround)
    {
        pos.y += currentJumpSpeed;
        currentJumpSpeed -= Gravity;
        pos.z -= jumpDistance;
    }

    if (!onGround)
    {
        if (pos.y < -10.0f)
        {
            fallingFlg = true;
        }
        if (pos.y < -100.0f)
        {
            fallingFlg = false;
            
        }

        if ((pos.y + currentJumpSpeed) < -10.0f && !fallingFlg)
        {
             CheckIsGround(map);
            if (onGround)
            {
               currentJumpSpeed = 0.0f;
               pos.y = -10.0f;
            }
        }
    }

    hitRect.playerRect->updateWorldRect(*hitRect.playerRect, pos, 50, 50);
    //HitRects.push_back(hitRect);

    // 3Dのポジション設定
    MV1SetPosition(modelHandle, pos);
}

void Player::Draw()
{
    // ３Ｄモデルの描画
    MV1DrawModel(modelHandle);
    
}

bool Player::IsHitWithMapChip(const VECTOR& futurePos, const Map::Chip& mapChip)
{
    // 当たっているかどうか調べる
    float futurePosLeft = futurePos.x - 50 * 0.5f;
    float futurePosRight = futurePos.x + 50 * 0.5f;
    float futurePosTop = -3.0f + futurePos.z;
    float futurePosBottom = 3.0f + futurePos.z;
    float targetLeft = mapChip.pos.x - 50 * 0.5f;
    float targetRight = mapChip.pos.x + 50 * 0.5f;
    float targetTop = -3.0f + mapChip.pos.z;
    float targetBottom = 3.0f + mapChip.pos.z;

    
    // 矩形同士の当たり判定
    if (((targetLeft <= futurePosLeft && futurePosLeft < targetRight) ||
        (targetLeft > futurePosLeft && targetLeft < futurePosRight)) &&
        ((targetTop <= futurePosTop && futurePosTop < targetBottom) ||
            (targetTop > futurePosTop && targetTop < futurePosBottom)))
    {
        return true;
    }

    return false;
}

void Player::CheckIsGround(const Map& map)
{
    bool isHit = false;
    int count = map.GetMapLayer();
    int**const count1 = map.GetMapLayer1();

    for (int i = 0; i < count; i++)
    {
            isHit = IsHitWithMapChip(pos, map.GetChip(i));
            if (isHit)
            {
                break;
            }
    }
    
    if (isHit)
    {
        onGround = true;
    }
}