#include "main.h"

#ifndef PACMAN_H
#define PACMAN_H


class Pacman {
public:
    Pacman() {}
    Pacman(float x,float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speedX;
    double speedY;
    double jumpAcc;
    double acceleration;
    float radius;
    int moveX;
    VAO *object; //how the object looks
};

#endif // Pacman_H

Pacman::Pacman(float x,float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speedX = 0.04f;
    this->speedY = 1.0;
    this->moveX = 0;
    int parts = 30;
    float radius = 0.3;
    GLfloat vertex_buffer_data_hole[parts*9];
    GLfloat color_buffer_data_hole[parts*9];
    this->acceleration = -0.0025;

    int i,j=0;
    float angle=(2*M_PI/parts);
    float current_angle = 0;
    
    for(i=0;i<parts;i++){
      
      
      
        if(current_angle>=0 && i<= 5*angle)
        {  
          color_buffer_data_hole[j++]=1;
          color_buffer_data_hole[j++]=0;
          color_buffer_data_hole[j++]=0.4;
        }
        else if(current_angle > 5*angle && i<= 10*angle)
        {
          color_buffer_data_hole[j++]=1;
          color_buffer_data_hole[j++]=1;
          color_buffer_data_hole[j++]=0; 
        }
        else if(current_angle > 10*angle && current_angle <= 15*angle)
        {
          color_buffer_data_hole[j++]=1;
          color_buffer_data_hole[j++]=0;
          color_buffer_data_hole[j++]=1; 
        }
        else if(current_angle > 15*angle && current_angle <= 20*angle)
        {
          color_buffer_data_hole[j++]=0;
          color_buffer_data_hole[j++]=1;
          color_buffer_data_hole[j++]=0; 
        }
        else if(current_angle > 20*angle && current_angle <= 25*angle)
        {
          color_buffer_data_hole[j++]=0;
          color_buffer_data_hole[j++]=0;
          color_buffer_data_hole[j++]=0.804; 
        }
         else if(current_angle > 25*angle && current_angle <= 30*angle)
        {
          color_buffer_data_hole[j++]=0;
          color_buffer_data_hole[j++]=1;
          color_buffer_data_hole[j++]=1; 
        }
      
      vertex_buffer_data_hole[i*9]=0;
      vertex_buffer_data_hole[i*9+1]=0;
      vertex_buffer_data_hole[i*9+2]=0;
      vertex_buffer_data_hole[i*9+3]=radius*cos(current_angle);
      vertex_buffer_data_hole[i*9+4]=radius*sin(current_angle);
      vertex_buffer_data_hole[i*9+5]=0;
      vertex_buffer_data_hole[i*9+6]=radius*cos(current_angle+angle);
      vertex_buffer_data_hole[i*9+7]=radius*sin(current_angle+angle);
      vertex_buffer_data_hole[i*9+8]=0;
      current_angle+=angle;
    }
    this->radius = radius;
    this->object = create3DObject(GL_TRIANGLES, (parts*9)/3, vertex_buffer_data_hole, color_buffer_data_hole, GL_FILL);
    
    
}

void Pacman::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Pacman::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Pacman::tick() {
    
      // if(this->moveX==0)
      // { 
      //   printf("22");
        
        
      // }
}

