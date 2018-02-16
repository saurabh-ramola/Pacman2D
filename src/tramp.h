#include "main.h"

#ifndef TRAMP_H
#define TRAMP_H

class Tramp {
public:
    Tramp() {}
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float centreX,centreY;
    float radius;
    VAO *object; //how the object looks
    void createTramp();
    
    
};

#endif

void Tramp::createTramp() {
    int parts;
    GLfloat vertex_buffer_data_hole[171];
    GLfloat color_buffer_data_hole[171];
    parts = 15;
   
    this->rotation = 0;
    this->centreX = 2.8f;
    this->centreY = -1.8f;
    float angle=(M_PI/parts);
    float current_angle = 0;
    float radius = 0.6f;
    int i,j;
    for(i=0;i<parts;i++){
       for(j=0;j<3;j++){
          color_buffer_data_hole[i*9+j*3]=1.000;  
          color_buffer_data_hole[i*9+j*3+1]=0.647;
          color_buffer_data_hole[i*9+j*3+2]=0.000;
      }

      vertex_buffer_data_hole[i*9]=2.8f;
      vertex_buffer_data_hole[i*9+1]=-1.8f;
      vertex_buffer_data_hole[i*9+2]=0;
      vertex_buffer_data_hole[i*9+3]=2.8+radius*cos(current_angle);
      vertex_buffer_data_hole[i*9+4]=-1.8-radius*sin(current_angle);
      vertex_buffer_data_hole[i*9+5]=0;
      vertex_buffer_data_hole[i*9+6]=2.8+radius*cos(current_angle+angle);
      vertex_buffer_data_hole[i*9+7]=-1.8-radius*sin(current_angle+angle);
      vertex_buffer_data_hole[i*9+8]=0;
      current_angle+=angle;
    }
    vertex_buffer_data_hole[135] = 2.0f;
    vertex_buffer_data_hole[136] = -2.5f;
    vertex_buffer_data_hole[137] = 0;

    vertex_buffer_data_hole[138] = 2.0f;
    vertex_buffer_data_hole[139] = -1.8f;
    vertex_buffer_data_hole[140] = 0;

    vertex_buffer_data_hole[141] = 2.2f;
    vertex_buffer_data_hole[142] = -1.8f;
    vertex_buffer_data_hole[143] = 0;

    vertex_buffer_data_hole[144] = 2.2f;
    vertex_buffer_data_hole[145] = -1.8f;
    vertex_buffer_data_hole[146] = 0;

    vertex_buffer_data_hole[147] = 2.0f;
    vertex_buffer_data_hole[148] = -2.5f;
    vertex_buffer_data_hole[149] = 0;

    vertex_buffer_data_hole[150] = 2.2f;
    vertex_buffer_data_hole[151] = -2.5f;
    vertex_buffer_data_hole[152] = 0;

    float x = 2*radius;
    //Right side rectangle
    vertex_buffer_data_hole[153] = x+0.2+2.0f;
    vertex_buffer_data_hole[154] = -2.5f;
    vertex_buffer_data_hole[155] = 0;

    vertex_buffer_data_hole[156] = x+0.2+2.0f;
    vertex_buffer_data_hole[157] = -1.8f;
    vertex_buffer_data_hole[158] = 0;

    vertex_buffer_data_hole[159] = x+0.2+2.2f;
    vertex_buffer_data_hole[160] = -1.8f;
    vertex_buffer_data_hole[161] = 0;

    vertex_buffer_data_hole[162] = x+0.2+2.2f;
    vertex_buffer_data_hole[163] = -1.8f;
    vertex_buffer_data_hole[164] = 0;

    vertex_buffer_data_hole[165] = x+0.2+2.0f;
    vertex_buffer_data_hole[166] = -2.5f;
    vertex_buffer_data_hole[167] = 0;

    vertex_buffer_data_hole[168] = x+0.2+2.2f;
    vertex_buffer_data_hole[169] = -2.5f;
    vertex_buffer_data_hole[170] = 0;

    for(i=135;i<171;i++){
       
        color_buffer_data_hole[i]=0.498;
        color_buffer_data_hole[i+1]=1.000;
        color_buffer_data_hole[i+2]=0.831;
      
    }
    this->object = create3DObject(GL_TRIANGLES,57, vertex_buffer_data_hole, color_buffer_data_hole, GL_FILL);
    this->radius = radius;
        
}

void Tramp::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


