#pragma once
#include"player.h"

class Camera
{
private:
    VECTOR pos;

public:

    Camera();
    ~Camera();

    void Update(Player& player);
};

