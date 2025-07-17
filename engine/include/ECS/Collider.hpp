#pragma once

struct Collider {
    float width, height;
    bool isStatic = false; // true for platforms, false for moving entities
};
