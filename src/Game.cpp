
#include "Game.h"
#include <iostream>
/*bool Game::is_collide(sf::Sprite sprite1, sf::Sprite sprite2)
{
  if (
    (sprite1.getPosition().x + sprite1.getGlobalBounds().width >
     sprite2.getPosition().x) &&
    sprite1.getPosition().x <
      sprite2.getPosition().x + sprite2.getLocalBounds().width &&
    (sprite1.getPosition().y + sprite1.getGlobalBounds().height) >
      sprite2.getPosition().y &&
    sprite1.getPosition().y <
      sprite2.getPosition().y + sprite2.getGlobalBounds().height)
  {
    return true;
  }
  else
    return false;
}
*/

void Game::menuSetText()
{
  if (!tittle_font.loadFromFile("Data/Fonts/breakaway.ttf"))
  {
    std::cout << "font did not load";
  }
  menu_text.setString("BREAKOUT");
  menu_text.setFont(tittle_font);
  menu_text.setCharacterSize(180);
  menu_text.setFillColor(sf::Color(48, 108, 203));
  menu_text.setPosition(
    window.getSize().x / 2 - menu_text.getGlobalBounds().width / 2.,
    window.getSize().y / 4 - menu_text.getGlobalBounds().height / 2);



  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "font did not load";
  }
  start_text.setString("Press enter to start");
  start_text.setFont(font);
  start_text.setCharacterSize(40);
  start_text.setFillColor(sf::Color(240, 102, 84));

  start_text.setPosition(
    window.getSize().x / 2 - start_text.getGlobalBounds().width / 2.,
    window.getSize().y / 2 - start_text.getGlobalBounds().height / 2);

  menu_text.setPosition(
    window.getSize().x / 2 - menu_text.getGlobalBounds().width / 2.,
    window.getSize().y / 4 - menu_text.getGlobalBounds().height / 2);

}

void Game::sateTexts()
  {
    if (game_state == GameStates::GAME_OVER)
    {
      start_text.setString(std::to_string(score));
      menu_text.setString("GAME OVER");
    }
    if (game_state == GameStates::WIN_GAME)
    {
      start_text.setString(std::to_string(score));
      menu_text.setString("YOU WON");
    }
    start_text.setPosition(
      window.getSize().x / 2 - start_text.getGlobalBounds().width / 2.,
      window.getSize().y / 2 - start_text.getGlobalBounds().height / 2);
    start_text.setCharacterSize(100);
  };
void Game::scoreSetText()
{
  score_text.setString("0");
  score_text.setFont(font);
  score_text.setCharacterSize(45);score_text.setPosition( window.getSize().x - score_text.getGlobalBounds().width - 30, 10);
  score_text.setFillColor(sf::Color::White);
}
void Game::setLives()
{
  for (int i = 0; i < live; i++)
  {
    lives[i].initialiseSprite(hearts,"Data/Images/heart.png");
    lives[i].getSprite()->setScale(0.15, 0.15);
    lives[i].getSprite()->setPosition(
      25 + 30 * i, 10);

  }
}
void Game::startPositions()
{
  paddle.getSprite()->setPosition(
    window.getSize().x / 2 - paddle.getSprite()->getLocalBounds().width / 2,
    window.getSize().y - 50);
  paddle.getSprite()->setScale(1.3,1);
  paddle.speed = 200;
  ball.getSprite()->setPosition(
    window.getSize().x / 2 - ball.getSprite()->getGlobalBounds().width / 2,
    window.getSize().y - 50 - paddle.getSprite()->getGlobalBounds().height);
  ball.speed = 250;
  ball.direction.x = 0;
  ball.direction.y = -10;
  ball.direction.normalise();
}

void Game::resetBallPosition()
{
  ball.getSprite()->setPosition(
    window.getSize().x / 2 - ball.getSprite()->getGlobalBounds().width / 2,
    window.getSize().y - 50 - paddle.getSprite()->getGlobalBounds().height);
  ball.speed = 250;
  ball.direction.x = 0;
  ball.direction.y = -10;
  ball.direction.normalise();
}

bool Game::outOffScreen(GameObject& sprite)
{
  if (
    (sprite.getSprite()->getPosition().x +
       sprite.getSprite()->getGlobalBounds().width <=
     0) ||
    (sprite.getSprite()->getPosition().y +
       sprite.getSprite()->getGlobalBounds().height <=
     0) ||
    (sprite.getSprite()->getPosition().y >= window.getSize().y) ||
    (sprite.getSprite()->getPosition().x >= window.getSize().x))
  {
    return true;
  }
  else
    return  false;
}

void Game::bounceFromWalls(GameObject& sprite1)
{
  if(sprite1.getSprite()->getPosition().y <= 0)
  {
    sprite1.direction.y = -sprite1.direction.y;
  }
  if(sprite1.getSprite()->getPosition().x <= 0)
  {
    sprite1.direction.x = -sprite1.direction.x;
  }
  if(sprite1.getSprite()->getPosition().x + sprite1.getSprite()->getGlobalBounds().width >= window.getSize().x)
  {
    sprite1.direction.x = -sprite1.direction.x;
  }
}

void Game::setGems()
{
  for (int i = 0; i < number_of_gems; i++)
  {
    if (i % 3 == 0)
    {
      gems[i].initialiseSprite(
        blue_gem, "Data/Images/element_blue_diamond_glossy.png", Block::Blue);
    }
    else if (i % 3 == 1)
    {
      gems[i].initialiseSprite(
        purple_gem,
        "Data/Images/element_purple_polygon_glossy.png",
        Block::Purple);
    }
    else
    {
      gems[i].initialiseSprite(
        green_gem,
        "Data/Images/element_green_polygon_glossy.png",
        Block::Green);
    }
    gems[i].setIsVisible(false);
    gems[i].getSprite()->setPosition(rand()% window.getSize().x,
                                     0 - gems[i].getSprite()->getGlobalBounds().height);
    gems[i].direction.y = 100;
    gems[i].direction.x = - rand() % 50 + 25;
    gems[i].direction.normalise();
    gems[i].speed = 0;
  }
}
void::Game::gemSpawn()
{
  static bool gemSpawned = false;

  sf::Time current_time = clock.getElapsedTime();
  int now = current_time.asSeconds();
  if (now % 3 == 1)
  {
    if (!gemSpawned)
    {

      int gem_num = rand() % number_of_gems;
      int i = 0;
      do
      {
        int tmp = (gem_num + i) % number_of_gems;
        if ((!gems[tmp].isVisible()))
        {
          gems[tmp].setIsVisible(true);
          gems[tmp].speed = 200;
          gemSpawned = true;
        }
        ++i;
      }
      while(i < number_of_gems && !gemSpawned);
    }
  }
  else
  {
    gemSpawned = false;
  }
}

void::Game::gemRespawn()
{
  for (int i = 0; i < number_of_gems; i++)
  {
    if (
      gems[i].isVisible() && gems[i].is_collide(paddle) ||
      gems[i].getSprite()->getPosition().y > window.getSize().y)
    {
      if (gems[i].is_collide(paddle))
      {
        score ++;
      }
      gems[i].getSprite()->setPosition(
        rand() % window.getSize().x,
        0 - gems[i].getSprite()->getGlobalBounds().height);
      gems[i].direction.y = 100;
      gems[i].direction.x = -rand() % 50 + 25;
      gems[i].direction.normalise();
      gems[i].speed = 0;
      gems[i].setIsVisible(false);

    }
  }
}

void Game::setBlocks()
{
  for (int i = 0; i < column_size; i++)
  {
    for (int j = 0; j < grid_size; j++)
    {
      if (i % 3 == 2 && j == 2)
      {
        blocks[i * grid_size + j].initialiseSprite(
          yellow_texture,
          "Data/Images/element_yellow_rectangle_glossy.png",
          Block::Yellow);
      }
      else if (j == 4 || j==0 || i == 0 || i == 10)
      {
        blocks[i * grid_size + j].initialiseSprite(
          blue_texture,
          "Data/Images/element_blue_rectangle_glossy.png",
          Block::Blue);
      }
      else if ((j == 3 || j==1) && i % 2 == 0 )
      {
        blocks[i * grid_size + j].initialiseSprite(
          purple_texture,
          "Data/Images/element_purple_rectangle_glossy.png",
          Block::Purple);
      }
      else if (i % 2 == 1 && j == 2)
      {
        blocks[i * grid_size + j].initialiseSprite(
          green_texture,
          "Data/Images/element_green_rectangle_glossy.png",
          Block::Green);
      }
      else
      {
        blocks[i * grid_size + j].initialiseSprite(
          red_texture,
          "Data/Images/element_red_rectangle_glossy.png",
          Block::Red);
      }
      blocks[i * grid_size + j].getSprite()->setScale(1.2, 1.2);
      blocks[i * grid_size + j].getSprite()->setPosition(
        25 + 95 * i, 75 + 55 * j);
    }
  }
}
Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
  game_state = GameStates::MENU;
  menuSetText();
  scoreSetText();
  setBlocks();
  setLives();
  setGems();
  paddle.initialiseSprite(paddle_texture, "Data/Images/paddleBlue.png");
  ball.initialiseSprite(ball_texture, "Data/Images/ballBlue.png");
  startPositions();
  return true;

}

void Game::update(float dt)
{
  sateTexts();
  if (game_state == GameStates::PLAY_GAME)
  {
    paddle.move_object(dt);
    ball.move_object(dt);
    bounceFromWalls(ball);
    gemSpawn();
    gemRespawn();

    if (ball.is_collide(paddle))
    {
      ball.bounce(paddle);
    }
    if (outOffScreen(ball))
    {
      live --;
      if (live == 0)
      {
        game_state = GameStates::GAME_OVER;
      }
      else
      {
        resetBallPosition();
      }
    }
    for (int i = 0; i < column_size * grid_size; i++)
    {
      if (blocks[i].is_collide(ball) && blocks[i].isVisible())
      {
        ball.bounce(blocks[i]);
        blocks[i].setIsVisible(false);
        switch (blocks[i].getColour())
        {
          case Block::Blue:
          {
            score++;
            break ;
          }
          case Block::Green:
          {
            score += 2;
            break ;
          }
          case Block::Purple:
          {
            score += 3;
            break ;
          }
          case Block::Red:
          {
            score += 4;
            break ;
          }
          case Block::Yellow:
          {
            score += 5;
            break ;
          }
        }
        destroyed_block++;
        if (destroyed_block == number_of_blocks)
        {
          game_state = GameStates::WIN_GAME;
        }
      }
    }
    for (int i = 0; i < number_of_gems; i++)
    {
      gems[i].move_object(dt);

    }
  }
}

void Game::render()
{
  if (game_state == GameStates::PLAY_GAME)
  {
    window.draw(score_text);
    score_text.setPosition( window.getSize().x - score_text.getGlobalBounds().width - 30, 10);
    score_text.setString(std::to_string(score));
    ball.drawObject(window);
    paddle.drawObject(window);
    for (int i = 0; i < column_size * grid_size; i++)
    {
      if (blocks[i].isVisible())
      {
        blocks[i].drawObject(window);
      }
    }
    for (int i = 0; i < live; i++)
    {
      lives[i].drawObject(window);
    }

   for (int i = 0; i < number_of_gems; i++)
    {
      if (gems[i].isVisible())
      {
        gems[i].drawObject(window);
      }
    }
  }
  else
  {
      window.draw(menu_text);
      window.draw(start_text);
    }}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
}

void Game::keyPressed(sf::Event event)
{
  if (game_state == GameStates::MENU)
  {
    if (event.key.code == sf::Keyboard::Enter && event.type == sf::Event::KeyPressed)
    {
      game_state = GameStates::PLAY_GAME;
    }
    else if (event.key.code == sf::Keyboard::Escape &&
        event.type == sf::Event::KeyPressed)
    {
      window.close();
    }
  }
  if (game_state == GameStates::PLAY_GAME)
  {
    if (event.key.code == sf::Keyboard::A)
    {
      if ( paddle.getSprite()->getPosition().x > 0 )
      {
        paddle.direction.x = -1;
      }
      else
      {
        paddle.direction.x = 0;
      }
    }
    else if (event.key.code == sf::Keyboard::D)
    {
      if ( paddle.getSprite()->getPosition().x + paddle.getSprite()->getGlobalBounds().width < window.getSize().x )
      {
        paddle.direction.x = 1;
      }
      else
      {
        paddle.direction.x = 0;
      }
    }
    if (event.key.code == sf::Keyboard::Escape &&
      event.type == sf::Event::KeyPressed)
    {
      game_state = GameStates::MENU;
    }
  }
}
void  Game::keyReleased(sf::Event event)
{
  paddle.direction.x = 0;
}



