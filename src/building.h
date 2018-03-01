#include "main.h"

#ifndef BALL_H
#define BALL_H


class Building {
public:
    Building() {}
    Building(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    void left();
    void right();
private:
    VAO *object;
    VAO *object2;
};

#endif // BALL_H
