
#ifndef BREAKOUT_GAMEOBJECT_H
#define BREAKOUT_GAMEOBJECT_H
#include <SFML/Graphics.hpp>
#include <string>
#include "Vector2.h"

class GameObject{
public:
  GameObject();
  ~GameObject();

  bool initialiseSprite(sf::Texture &texture, std::string filename);
  sf::Sprite* getSprite();

  void drawObject(sf::RenderWindow & window);
  Vector2 direction = {0,0};

  int mid_point_x;
  int getMidPointX();
  int getMidPointY();
  int mid_point_y;
  int speed = 0;

  void move_object(const float& dt);
  bool is_collide(const GameObject& sprite1);
  void bounce(GameObject& sprite1);


 private:

 sf::Sprite* sprite;
 bool top_collide(const GameObject& sprite1);
 bool left_collide(const GameObject& sprite1);
 bool right_collide(const GameObject& sprite1);
 bool bottom_collide(const GameObject& sprite1);
};

#endif // BREAKOUT_GAMEOBJECT_H
