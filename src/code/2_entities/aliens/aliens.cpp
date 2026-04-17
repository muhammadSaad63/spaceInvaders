#include "aliens.hpp"


Alien::Alien() : active(true) {}

void Alien::draw(){
    if (active){
        // DrawTexture(texture, posX,);

    }
}
void Alien::update(){
    // 
}

void Aliens::draw(){
    for (auto& rowOfAliens : aliens){
        for (auto& alien : rowOfAliens){
            alien.draw();
        }
    }
}
void Aliens::update(){
    for (auto& rowOfAliens : aliens){
        for (auto& alien : rowOfAliens){
            alien.update();
        }
    }
}