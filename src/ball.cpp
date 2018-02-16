#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color,double speedX) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = speedX;
    int parts = 15;
    float radius[3] = { 0.14,0.19,0.24};
    GLfloat vertex_buffer_data_hole[parts*9];
    int i,j;
    float angle=(2*M_PI/parts);
    float current_angle = 0;
    int k = rand()%3;
    for(i=0;i<parts;i++){
      

      vertex_buffer_data_hole[i*9]=0;
      vertex_buffer_data_hole[i*9+1]=0;
      vertex_buffer_data_hole[i*9+2]=0;
      vertex_buffer_data_hole[i*9+3]=radius[k]*cos(current_angle);
      vertex_buffer_data_hole[i*9+4]=radius[k]*sin(current_angle);
      vertex_buffer_data_hole[i*9+5]=0;
      vertex_buffer_data_hole[i*9+6]=radius[k]*cos(current_angle+angle);
      vertex_buffer_data_hole[i*9+7]=radius[k]*sin(current_angle+angle);
      vertex_buffer_data_hole[i*9+8]=0;
      current_angle+=angle;
    }
    this->flag = 1;
    this->flag1=0;
    
    this->radius = radius[k];
    if(this->radius == float(0.14))
      this->object = create3DObject(GL_TRIANGLES, (parts*9)/3, vertex_buffer_data_hole, DM, GL_FILL);
    else if(this->radius == float(0.19))
      this->object = create3DObject(GL_TRIANGLES, (parts*9)/3, vertex_buffer_data_hole, LG, GL_FILL);
    else 
      this->object = create3DObject(GL_TRIANGLES, (parts*9)/3, vertex_buffer_data_hole, FB, GL_FILL);
        
    
    
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    if(flag1 == 1)
    {
      draw3DObject(this->plank);
    }
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    this->position.x -= this->speed;
    if(this->position.x >= 20 || this->position.x <= -20)
    {
    	this->speed = -this->speed;
    }
    // this->xTop += this->speed;
    // this->xBot += this->speed;
}

void Ball::attachPlank(float angle,float length,int flag1)
{ 

  if(flag1 == 1)
  { 
    this->flag1 =1;
    GLfloat plank_vertices_data[] = {
            this->radius*cos(angle)- length*sin(angle), this->radius*sin(angle)+length*cos(angle), 0, // vertex 1
            this->radius*cos(angle)+ length*sin(angle), this->radius*sin(angle)-length*cos(angle), 0, // vertex 1
            (this->radius+0.07)*cos(angle)+ length*sin(angle), (this->radius+0.07)*sin(angle)-length*cos(angle) , 0, // vertex 2
    
            (this->radius+0.07)*cos(angle)+ length*sin(angle), (this->radius+0.07)*sin(angle)-length*cos(angle) , 0, // vertex 2
            (this->radius+0.07)*cos(angle)- length*sin(angle), (this->radius+0.07)*sin(angle)+length*cos(angle), 0, // vertex 1
            this->radius*cos(angle)- length*sin(angle), this->radius*sin(angle)+length*cos(angle), 0, // vertex 1
        };
        this->xTop = (this->radius+0.07)*cos(angle)- length*sin(angle);
        this->xBot = (this->radius+0.07)*cos(angle)+ length*sin(angle);
        this->yTop = (this->radius+0.07)*sin(angle)+length*cos(angle);
        this->yBot = (this->radius+0.07)*sin(angle)-length*cos(angle);
       
        this->length = length;
        this->angle = angle;
      
        this->plank = create3DObject(GL_TRIANGLES,6, plank_vertices_data, COLOR_RED, GL_FILL);
  }
}
bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}


