#include "main.h"

#ifndef GROUND_H
#define GROUND_H


class Ground {
public:
    Ground() {}
    Ground(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_t bounding_box();
    float len;
    float radius;
    VAO *object; //how the object looks
    void createRectangle();

};

#endif // GROUND_H
void Ground::createRectangle() {
   
    
  // GL3 accepts only Triangles. Quads are not supported
 
  static const GLfloat vertex_buffer_data [] = {
         -300.0,-2.5,0,// vertex 1
          300.0,-2.5,0,   // vertex 2
         -300.0,-2.8,0,// vertex 3
      
         -300.0,-2.8,0,// vertex 3
          300.0,-2.8,0,// vertex 4
          300.0,-2.5,0,// vertex 1

         -300.0,-2.8,0,// vertex 1
         300.0,-2.8,0,   // vertex 2
         -300.0,-8.0,0,// vertex 3
    
         -300.0,-8.0,0,// vertex 3
         300.0,-8.0,0,// vertex 4
         300.0,-2.8,0,// vertex 1

         
      };
    
      static const GLfloat color_buffer_data [] = {
        0,1,0, // color 1
        0,1,0, // color 2
        0,1,0, // color 3
    
        0,1,0, // color 3
        0,1,0, // color 4
        0,1,0,  // color 1

        0.502, 0.000, 0.000, // color 1
        0.502, 0.000, 0.000, // color 2
        0.502, 0.000, 0.000, // color 3
    
        0.502, 0.000, 0.000, // color 3
        0.502, 0.000, 0.000, // color 4
        0.502, 0.000, 0.000 // color 1
      };
  this->object = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data, color_buffer_data, GL_FILL);
  

    
}

void Ground::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}




bounding_box_t Ground::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
