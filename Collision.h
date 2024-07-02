#pragma once
class Collision
{
private:
		VECTOR pos;
		float w = 0;		// �������`���s�N�Z����
		float h = 0;        // �������`�����s�N�Z����
		float worldLX = 0;  // ����X���W
		float worldLY = 0;  // ����Y���W
		float worldRX = 0;  // �E��X���W
		float worldRY = 0;  // �E��Y���W
public:
	bool isHitRect(const Collision& rect1, const Collision& rect2);

	void initRect(VECTOR pos, Collision& dstRect, float w, float h);

	void drawRect(Collision& dstRect, int scrollX);

	void updateWorldRect(Collision& dstRect,VECTOR pos, float x, float y);

};

