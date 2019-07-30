#include "main.h"
#include "smoke.h"

Smoke::Smoke(glm::vec3 pos,float ang)
{
    int n = 50;
    float angle = float(2.0*3.14)/float(n);
	float rotation[3][3] = {(float)cos(angle),(float)-sin(angle),0.0,(float)sin(angle),(float)cos(angle),0.0,0.0,0.0,1.0};
	float xarr[n],xarr1[n];
	float yarr[n],yarr1[n];
	xarr[0]=0.0;
	yarr[0]=1.0;
    xarr1[0]=0.0;
    yarr1[0]=0.9;
    GLfloat vertex_buffer_data[1000];
	for(int i=1;i<n;i++)
	{
		float x =rotation[0][0]*xarr[i-1] + rotation[0][1]*yarr[i-1];
		float y =rotation[1][0]*xarr[i-1] + rotation[1][1]*yarr[i-1];
		xarr[i] = x;
		yarr[i] = y;
        float x1 =rotation[0][0]*xarr1[i-1] + rotation[0][1]*yarr1[i-1];
		float y1 =rotation[1][0]*xarr1[i-1] + rotation[1][1]*yarr1[i-1];
		xarr1[i] = x1;
		yarr1[i] = y1;
	}
    for(int i=0;i<n;i++)
	{
		vertex_buffer_data[18*i]=xarr[i];
        vertex_buffer_data[18*i+1]=yarr[i];
        vertex_buffer_data[18*i+2]=0.0f;

        vertex_buffer_data[18*i+3]=xarr[(i+1)%n];
        vertex_buffer_data[18*i+4]=yarr[(i+1)%n];
        vertex_buffer_data[18*i+5]=0.0f;

        vertex_buffer_data[18*i+6]=xarr1[i];
        vertex_buffer_data[18*i+7]=yarr1[i];
        vertex_buffer_data[18*i+8]=0.0f;

        vertex_buffer_data[18*i+9]=xarr1[i];
        vertex_buffer_data[18*i+10]=yarr1[i];
        vertex_buffer_data[18*i+11]=0.0f;

        vertex_buffer_data[18*i+12]=xarr1[(i+1)%n];
        vertex_buffer_data[18*i+13]=yarr1[(i+1)%n];
        vertex_buffer_data[18*i+14]=0.0f;

        vertex_buffer_data[18*i+15]=xarr[(i+1)%n];
        vertex_buffer_data[18*i+16]=yarr[(i+1)%n];
        vertex_buffer_data[18*i+17]=0.0;
        
        
	}
	this->object = create3DObject(GL_TRIANGLES,6*n, vertex_buffer_data,{255,255,0}, GL_FILL);
    this->position = pos;
    this->rotation = glm::rotate(float(ang),glm::vec3(0,1,0));
    this->scale = {0.6,0.6,0.6}; 
}

void Smoke::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale = glm::scale(this->scale);

    Matrices.model *= (translate*scale*this->rotation);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}