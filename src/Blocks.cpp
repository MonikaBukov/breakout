//
// Created by monik on 29/01/2023.
//

#include "Blocks.h"
Block::Block()
{
  colour = Blue;
}
bool Block::initialiseSprite(
  sf::Texture& texture, std::string filename, Block::Colour col)
{
  GameObject::initialiseSprite(texture,filename);
  colour = col;

  return true;
}
Block::~Block() {};

bool Block::isVisible() const
{
  return is_visible;
}
void Block::setIsVisible(bool isVisible)
{
  is_visible = isVisible;
}
Block::Colour Block::getColour() const
{
  return colour;
}
void Block::setColour(Block::Colour colour)
{
  Block::colour = colour;
}
