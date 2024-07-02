#include "DxLib.h"
#include <vector>
#include "Collision.h"
#include "math.h"

bool Collision::isHitRect(const Collision& rect1, const Collision& rect2)
{
	// “ñ‚Â‚Ì‹éŒ`‚Ì“–‚½‚è”»’è‚ÌŒöŽ®‚æ‚è
	return (rect1.worldLX < rect2.worldRX &&
		rect2.worldLX < rect1.worldRX &&
		rect1.worldLY < rect2.worldRY &&
		rect2.worldLY < rect1.worldRY);
}

void Collision::initRect(VECTOR pos, Collision& dstRect, float w, float h)
{
	dstRect.w = w;
	dstRect.h = h;

	dstRect.worldLX = pos.x - w;
	dstRect.worldRX = pos.x + w;
	dstRect.worldLY = pos.z - h;
	dstRect.worldRY = pos.z + h;
}

void Collision::drawRect(Collision& dstRect, int scrollX)
{
	DrawBox(static_cast<int>(dstRect.worldLX) - scrollX,
		static_cast<int>(dstRect.worldLY),
		static_cast<int>(dstRect.worldRX) - scrollX,
		static_cast<int>(dstRect.worldRY),
		GetColor(255, 0, 0), FALSE);
}

void Collision::updateWorldRect(Collision& dstRect, VECTOR pos, float x, float y)
{
	float X = 1600 / 2;
	float Y = 900 / 2;

	dstRect.worldLX = X - dstRect.w;
	dstRect.worldRX = X + dstRect.w;
	dstRect.worldLY = Y + dstRect.h;
	dstRect.worldRY = Y - dstRect.h;
}