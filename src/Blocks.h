//
// Created by monik on 29/01/2023.
//

#ifndef BREAKOUTSFML_BLOCKS_H
#define BREAKOUTSFML_BLOCKS_H
#include "GameObject.h"

class Block : public GameObject
{
 public:
  Block();
  ~Block();
  enum Colour {Blue, Green, Purple, Red, Yellow};
  bool initialiseSprite(sf::Texture &texture, std::string filename, Colour col);
  bool isVisible() const;
  void setIsVisible(bool isVisible);
  Colour getColour() const;
  void setColour(Colour colour);


 private:
  Colour colour;
  bool is_visible = true;



};

#endif // BREAKOUTSFML_BLOCKS_H
