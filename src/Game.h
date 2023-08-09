
#ifndef BREAKOUT_GAME_H
#define BREAKOUT_GAME_H


#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "GameObject.h"
#include "Blocks.h"


class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);

  enum GameStates
  {
    MENU = 1,
    PLAY_GAME = 2,
    GAME_OVER = 3,
    WIN_GAME = 4
  };

  GameStates game_state;

 private:
  sf::RenderWindow& window;
  sf::Texture ball_texture;
  GameObject ball;

  sf::Texture paddle_texture;
  GameObject paddle;

  /*bool is_collide(sf::Sprite sprite1, sf::Sprite sprite2);*/
  void menuSetText();
  sf::Font tittle_font;
  sf::Font font;

  sf::Text menu_text;
  sf::Text start_text;

  void scoreSetText();
  sf::Text score_text;
  int score = 0;

  void setLives();
  int live = 6;
  GameObject lives[6];
  sf::Texture hearts;

  void setBlocks();
  int column_size = 11;
  int grid_size = 5;
  int number_of_blocks = column_size*grid_size;
  int destroyed_block = 0;
  Block blocks[5*11];
  sf::Texture blue_texture;
  sf::Texture green_texture;
  sf::Texture purple_texture;
  sf::Texture red_texture;
  sf::Texture yellow_texture;

  void setGems();
  Block gems[6];
  int number_of_gems = 6;
  sf::Texture blue_gem;
  sf::Texture green_gem;
  sf::Texture purple_gem;
  void gemRespawn();
  void gemSpawn();


  void startPositions();
  void bounceFromWalls(GameObject& sprite1);
  bool outOffScreen(GameObject& sprite);
  void resetBallPosition();
  sf::Clock clock;

  void sateTexts();
};

#endif // BREAKOUT_GAME_H
