#include "main.h"
#include "fuel.h"

Fuel::Fuel(glm::vec3 pos)
{
    this->position = pos;
      GLfloat vertex_color_data[2000];
    int n=4;
    // add color
    for(int i=0;i<n;i++)
    {
      //circle 1  
      {
        vertex_color_data[9*i]   = rgb(255);
		vertex_color_data[9*i+1] = rgb(225);
		vertex_color_data[9*i+2] = rgb(0);

		vertex_color_data[9*i+3] = rgb(255);
		vertex_color_data[9*i+4] = rgb(87);
		vertex_color_data[9*i+5] = rgb(80);

		vertex_color_data[9*i+6] = rgb(255);
		vertex_color_data[9*i+7] = rgb(215);
		vertex_color_data[9*i+8] = rgb(0);
      } 
      //cirle2 
      {
        vertex_color_data[9*(i+n)]   = rgb(255);
		vertex_color_data[9*(i+n)+1] = rgb(255);
		vertex_color_data[9*(i+n)+2] = rgb(0);

		vertex_color_data[9*(i+n)+3] = rgb(255);
		vertex_color_data[9*(i+n)+4] = rgb(87);
		vertex_color_data[9*(i+n)+5] = rgb(80);

		vertex_color_data[9*(i+n)+6] = rgb(255);
		vertex_color_data[9*(i+n)+7] = rgb(215);
		vertex_color_data[9*(i+n)+8] = rgb(80);
      }

      {
        vertex_color_data[9*(i+2*n)]   = rgb(255);	
        vertex_color_data[9*(i+2*n)+1] = rgb(255);
		vertex_color_data[9*(i+2*n)+2] = rgb(0);

		vertex_color_data[9*(i+2*n)+3] = rgb(255);
		vertex_color_data[9*(i+2*n)+4] = rgb(255);
		vertex_color_data[9*(i+2*n)+5] = rgb(0);

		vertex_color_data[9*(i+2*n)+6] = rgb(255);
		vertex_color_data[9*(i+2*n)+7] = rgb(255);
		vertex_color_data[9*(i+2*n)+8] = rgb(0);
      } 
      {  
        vertex_color_data[9*(i+3*n)]   = rgb(255);
		vertex_color_data[9*(i+3*n)+1] = rgb(87);
		vertex_color_data[9*(i+3*n)+2] = rgb(80);

		vertex_color_data[9*(i+3*n)+3] = rgb(255);
		vertex_color_data[9*(i+3*n)+4] = rgb(99);
		vertex_color_data[9*(i+3*n)+5] = rgb(71);

		vertex_color_data[9*(i+3*n)+6] = rgb(255);
		vertex_color_data[9*(i+3*n)+7] = rgb(215);
		vertex_color_data[9*(i+3*n)+8] = rgb(0);
      } 
    }
    this->base = Frustum(pos,{pos.x,pos.y,pos.z+0.8/sqrt(2)},0.4,0.4,4,vertex_color_data);
    this->base.rotationz = 3.14/4;
}

void Fuel::draw(glm::mat4 VP)
{
    this->base.draw(VP,glm::mat4(1.0));
}