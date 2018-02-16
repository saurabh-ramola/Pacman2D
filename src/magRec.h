#include "main.h"

#ifndef MAGREC_H
#define MAGREC_H


class Magrec {
public:
    Magrec() {}
    void magrec();
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    int flag;
    bounding_box_t bounding_box();
    VAO *object;
     //how the object looks
};

#endif // magRec_H

void Magrec::magrec() {
    
    this->rotation = 0;
   
    
    GLfloat vertex_buffer_data_hole[36];
   
    vertex_buffer_data_hole[0]=-2.7;
    vertex_buffer_data_hole[0+1]=3.1;
    vertex_buffer_data_hole[0+2]=0;
    vertex_buffer_data_hole[0+3]=-2.7 + 0.3;
    vertex_buffer_data_hole[0+4]=3.5;
    vertex_buffer_data_hole[0+5]=0;
    vertex_buffer_data_hole[0+6]=-2.7;
    vertex_buffer_data_hole[0+7]=3.5;
    vertex_buffer_data_hole[0+8]=0;
    
    vertex_buffer_data_hole[9]=-2.7;
    vertex_buffer_data_hole[9+1]=3.1;
    vertex_buffer_data_hole[9+2]=0;
    vertex_buffer_data_hole[9+3]=-2.7 + 0.3;
    vertex_buffer_data_hole[9+4]=3.1;
    vertex_buffer_data_hole[9+5]=0;
    vertex_buffer_data_hole[9+6]=-2.7 + 0.3;
    vertex_buffer_data_hole[9+7]=3.5;
    vertex_buffer_data_hole[9+8]=0;
    
    vertex_buffer_data_hole[18]=-2.7;
    vertex_buffer_data_hole[18+1]=1.5;
    vertex_buffer_data_hole[18+2]=0;
    vertex_buffer_data_hole[18+3]=-2.7;
    vertex_buffer_data_hole[18+4]=1.1;
    vertex_buffer_data_hole[18+5]=0;
    vertex_buffer_data_hole[18+6]=-2.7 + 0.3;
    vertex_buffer_data_hole[18+7]=1.1;
    vertex_buffer_data_hole[18+8]=0;

    vertex_buffer_data_hole[27]=-2.7;
    vertex_buffer_data_hole[27+1]=1.5;
    vertex_buffer_data_hole[27+2]=0;
    vertex_buffer_data_hole[27+3]=-2.7 + 0.3;
    vertex_buffer_data_hole[27+4]=1.5;
    vertex_buffer_data_hole[27+5]=0;
    vertex_buffer_data_hole[27+6]=-2.7 + 0.3;
    vertex_buffer_data_hole[27+7]=1.1;
    vertex_buffer_data_hole[27+8]=0;

   
    this->flag = 1;
    
    this->object = create3DObject(GL_TRIANGLES,12, vertex_buffer_data_hole, COLOR_RED, GL_FILL);
  //his->object1 = create3DObject(GL_TRIANGLES,12, vertex_buffer_data_hole, color_buffer_data_hole, GL_FILL);
    
        
    
    
}

void Magrec::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Magrec::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}


bounding_box_t Magrec::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}

