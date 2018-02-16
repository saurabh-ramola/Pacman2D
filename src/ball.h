#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color,double speedX);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    double acceleration;
    int flag;
    bounding_box_t bounding_box();
    float radius;
    float angle;
    float length;
    float xTop;
    float xBot;
    float yTop;
    float yBot;
    int flag1;
    void attachPlank(float angle,float length,int flag);
    VAO *object; //how the object looks
    VAO *plank;
};

#endif // BALL_H
