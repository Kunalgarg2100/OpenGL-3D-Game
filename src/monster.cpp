#include "monster.h"
#include "main.h"


Monster::Monster(float x, float y, float z, float rad,int u, int num,color_t color1,color_t color2,color_t color3) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 2;
    this->color = color1;
    this->shootcnt = 0;
    this->reqcnt = u;
    speed = 2;
    this->side = rad;
    this->num= num;
    const double PI = 4 * atan(1);

    int ptr=0;
    GLfloat pole_vertex_buffer_data[720];
    for(int i=0;i<80;i++){
        double angle = i * PI/40;
        for(int j=0;j<3;j++)
            pole_vertex_buffer_data[ptr++]=0.0f;
        for(int j=0;j<2;j++)
        {
            pole_vertex_buffer_data[ptr++]=(rad*0.5)*cos(angle);
            pole_vertex_buffer_data[ptr++]=rad*3;
            pole_vertex_buffer_data[ptr++]=(rad*0.5)*sin(angle);
            angle = (i+1) * PI/40;
        }
    };

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -rad,-rad,-rad, // triangle 1 : begin
        -rad,-rad, rad,
        -rad, rad, rad, // triangle 1 : end
        rad, rad,-rad, // triangle 2 : begin
        -rad,-rad,-rad,
        -rad, rad,-rad, // triangle 2 : end
        rad,-rad, rad,
        -rad,-rad,-rad,
        rad,-rad,-rad,
        rad, rad,-rad,
        rad,-rad,-rad,
        -rad,-rad,-rad,
        -rad,-rad,-rad,
        -rad, rad, rad,
        -rad, rad,-rad,
        rad,-rad, rad,
        -rad,-rad, rad,
        -rad,-rad,-rad,
        -rad, rad, rad,
        -rad,-rad, rad,
        rad,-rad, rad,
        rad, rad, rad,
        rad,-rad,-rad,
        rad, rad,-rad,
        rad,-rad,-rad,
        rad, rad, rad,
        rad,-rad, rad,
        rad, rad, rad,
        rad, rad,-rad,
        -rad, rad,-rad,
        rad, rad, rad,
        -rad, rad,-rad,
        -rad, rad, rad,
        rad, rad, rad,
        -rad, rad, rad,
        rad,-rad, rad
    };

    this->head = Sphere(x,rad*3 +y,z,rad,COLOR_RED);
    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color1, GL_FILL);
    this->pole = create3DObject(GL_TRIANGLES, 240, pole_vertex_buffer_data,COLOR_BACKGROUND, GL_FILL);
}

void Monster::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate;
    if(this->num == 1)
      rotate  = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->pole);
    head.draw(VP);
}

void Monster::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Monster::tick() {
    if(this->num != 0){
        this->rotation += speed;
        head.rotation += speed;
    }
}

bounding_box_t Monster::bounding_box() {
    float x = this->position.x;
    float y = this->position.y;
    float z = this->position.z;
    float w = this->side;
    float h = this->side*3;
    float l = this->side;
    bounding_box_t bbox = { x,y,z,w,h,l};
    return bbox;
}
