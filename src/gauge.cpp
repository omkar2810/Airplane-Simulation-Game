#include "main.h"
#include "gauge.h"

Gauge::Gauge(int a)
{ 
    glm::vec3 posi(2.6,-3.3,0);
    Polygon pol = Polygon(4,1,{25,25,25},glm::vec3(1.30,0.35,0),posi,3.14/4);
    this->poly.push_back(pol);   
    pol = Polygon(4,1,{255,0,0},glm::vec3(0.2,0.25,0),{1.9,-3.3,0},3.14/4);
    this->poly.push_back(pol);
    pol = Polygon(4,1,{225,100,0},glm::vec3(0.2,0.25,0),{2.25,-3.3,0},3.14/4);
    this->poly.push_back(pol);
    pol = Polygon(4,1,{238,201,0},glm::vec3(0.2,0.25,0),{2.60,-3.3,0},3.14/4);
    this->poly.push_back(pol);
    pol = Polygon(4,1,{127,255,0},glm::vec3(0.2,0.25,0),{2.95,-3.3,0},3.14/4);
    this->poly.push_back(pol);
    pol = Polygon(4,1,{0,225,0},glm::vec3(0.2,0.25,0),{3.30,-3.3,0},3.14/4);
    this->poly.push_back(pol);
}

void Gauge::draw(glm::mat4 VP,float fuel)
{
    int bar = ((int)fuel/2)+1;
    bar = std::min(bar,5);
    if(fuel==0.0)
        bar=0;
    for(int i=0;i<=bar;i++)
        this->poly[i].draw(VP);
}

void Gauge::tick()
{
//    this->position.x += this->velocity.x;
//    this->position.y += this->velocity.y; 
//    this->position.z += this->velocity.z; 
}