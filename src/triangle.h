
#include "main.h"

#ifndef TRIANGLE_H
#define TRIANGLE_H


class Triangle {
public:
    Triangle() {}
    Triangle(double len,int num,double speed);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box();
    double len;
    double xLeft;
    double speed;
    double xRight;
    double height;
    double yBot;
    int flag ;
    void movePorcupine();
    VAO *object; //how the object looks
   
};

#endif

Triangle::Triangle(double len,int num,double speedX) {
    
    // this->rotation = 0;
    this->speed = speedX;
    int x = num*9;
    GLfloat vertex_buffer_data_hole[x];
    int LO1 = -2,HI1 = 4;
    float temp = LO1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI1-LO1)));
    this->yBot = -2.5;
    
    this->xLeft = temp;
    for(int i = 0;i < num;i++)
    { 

      vertex_buffer_data_hole[i*9]=temp;
      vertex_buffer_data_hole[i*9+1]=this->yBot;
      vertex_buffer_data_hole[i*9+2]=0;
      vertex_buffer_data_hole[i*9+3]=temp+len;
      vertex_buffer_data_hole[i*9+4]=this->yBot;
      vertex_buffer_data_hole[i*9+5]=0;
      vertex_buffer_data_hole[i*9+6]=temp+len/2;
      vertex_buffer_data_hole[i*9+7]=this->yBot+0.5;
      vertex_buffer_data_hole[i*9+8]=0;
      temp+=len;
    }
    
    this->flag = 0;
    this->xRight = this->xLeft+3*len;
   
    
    this->len = len;
    this->object = create3DObject(GL_TRIANGLES, num*3, vertex_buffer_data_hole, COLOR_BLACK, GL_FILL);
    
    
}

void Triangle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


bounding_box_t Triangle::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
void Triangle::movePorcupine(){
  
  if(this->position.x >= 25)
  {
    this->speed = -this->speed;
  }
  else if(this->position.x <= -25)
  {
    this->speed = -this->speed;
  }
  
  this->position.x += this->speed;
  // this->position. += this->speed;

  this->xLeft += this->speed;
  this->xRight += this->speed;
  }