#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double acceleration;
    int flag;
    bounding_box_t bounding_box();
    float radius;
    VAO *object;
     //how the object looks
};

#endif // Magnet_H

Magnet::Magnet(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->acceleration = 1.4;
    int parts = 15;
    float radius[2] = { 0.8,1.2};
    GLfloat vertex_buffer_data_hole[parts*18];
    GLfloat color_buffer_data_hole[parts*18];
    int i,j;
    float angle=M_PI/parts;
    float current_angle = M_PI/2;
   
    for(i=0;i<parts;i++){
      

      vertex_buffer_data_hole[i*9]=0;
      vertex_buffer_data_hole[i*9+1]=0;
      vertex_buffer_data_hole[i*9+2]=0;
      vertex_buffer_data_hole[i*9+3]=radius[1]*cos(current_angle);
      vertex_buffer_data_hole[i*9+4]=radius[1]*sin(current_angle);
      vertex_buffer_data_hole[i*9+5]=0;
      vertex_buffer_data_hole[i*9+6]=radius[1]*cos(current_angle+angle);
      vertex_buffer_data_hole[i*9+7]=radius[1]*sin(current_angle+angle);
      vertex_buffer_data_hole[i*9+8]=0;

      color_buffer_data_hole[i*9]=0;
      color_buffer_data_hole[i*9+1]=0;
      color_buffer_data_hole[i*9+2]=1;
      color_buffer_data_hole[i*9+3]=0;
      color_buffer_data_hole[i*9+4]=0;
      color_buffer_data_hole[i*9+5]=1;
      color_buffer_data_hole[i*9+6]=0;
      color_buffer_data_hole[i*9+7]=0;
      color_buffer_data_hole[i*9+8]=1;

      vertex_buffer_data_hole[i*9+135]=0;
      vertex_buffer_data_hole[i*9+136]=0;
      vertex_buffer_data_hole[i*9+137]=0;
      vertex_buffer_data_hole[i*9+138]=radius[0]*cos(current_angle);
      vertex_buffer_data_hole[i*9+139]=radius[0]*sin(current_angle);
      vertex_buffer_data_hole[i*9+140]=0;
      vertex_buffer_data_hole[i*9+141]=radius[0]*cos(current_angle+angle);
      vertex_buffer_data_hole[i*9+142]=radius[0]*sin(current_angle+angle);
      vertex_buffer_data_hole[i*9+143]=0;

      color_buffer_data_hole[i*9+135]=0;
      color_buffer_data_hole[i*9+136]=0;
      color_buffer_data_hole[i*9+137]=0;
      color_buffer_data_hole[i*9+138]=0;
      color_buffer_data_hole[i*9+139]=0;
      color_buffer_data_hole[i*9+140]=0;
      color_buffer_data_hole[i*9+141]=0;
      color_buffer_data_hole[i*9+142]=0;
      color_buffer_data_hole[i*9+143]=0;

      current_angle+=angle;
    }
    this->flag = 1;
    this->object = create3DObject(GL_TRIANGLES,90, vertex_buffer_data_hole, color_buffer_data_hole, GL_FILL);
    
        
    
    
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}


bounding_box_t Magnet::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}

