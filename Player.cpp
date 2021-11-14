#include "Player.h"
#include "Game.h"
#include "InputHandler.h"
#include "Bullet.h"

void Player::draw()
{
  SDLGameObject::draw(flip);
}

void Player::update()
{
  handleInput();
  checkCollision();
  updateSprite();

  SDLGameObject::update();
}

void Player::handleInput()
{
  if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
  {
    m_velocity.setX(-speed);
  }
  else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
  {
    m_velocity.setX(speed);
  }
  else
  {
    m_velocity.setX(0);
  }

  // 스페이스 바
  if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
  {
    m_velocity.setY(-2);
    setGravity(0.1);
  }
  
  // 마우스 왼쪽
  if(TheInputHandler::Instance()->getMouseButtonState(LEFT))
  {
    TheGame::Instance()->createBulletObject(new Bullet(new LoaderParams(m_position.getX()+m_width/2-10, m_position.getY()+m_height/2-10, 20, 20, "bullet")));
  }
}

void Player::checkCollision()
{
  vector<GameObject*> collisionObjects = TheGame::Instance()->getWallObjects();

  int playerLeft = m_position.getX();
  int playerRight = playerLeft + m_width;
  int playerTop = m_position.getY();
  int playerBottom = playerTop + m_height;

  int count = 0;

  for(int i = 0 ; i < collisionObjects.size() ; i++)
  {
    int objectLeft = collisionObjects[i]->getPosition().getX();
    int objectRight = objectLeft + collisionObjects[i]->getWidth();
    int objectTop = collisionObjects[i]->getPosition().getY();
    int objectBottom = objectTop + collisionObjects[i]->getHeight(); 
    
    // 충돌 시
    if(playerLeft <= objectRight && playerRight >= objectLeft
    && playerTop <= objectBottom && playerBottom >= objectTop)
    {
      // 아랫방향
      if(m_velocity.getY() > 0 && playerBottom >= objectTop && playerBottom < objectBottom && playerLeft != objectRight && playerRight != objectLeft)
      {
        m_position.setY(objectTop - m_height);
        playerTop = m_position.getY();
        playerBottom = playerTop + m_height;

        m_velocity.setY(0);
        setGravity(0.0);
      }
      // 윗방향
      else if(m_velocity.getY() < 0 && playerTop <= objectBottom && playerTop > objectTop && playerLeft != objectRight && playerRight != objectLeft)
      {
        m_position.setY(objectBottom);
        playerTop = m_position.getY();
        playerBottom = playerTop + m_height;

        m_velocity.setY(0);
      }

      // 왼방향
      if(m_velocity.getX() < 0 && playerLeft <= objectRight && playerLeft > objectLeft && playerTop != objectBottom && playerBottom != objectTop)
      {
        m_position.setX(objectRight);
        playerLeft = m_position.getX();
        playerRight = playerLeft + m_width;

        m_velocity.setX(0);
      }
      // 오른방향
      else if(m_velocity.getX() > 0 && playerRight >= objectLeft && playerRight < objectRight && playerTop != objectBottom && playerBottom != objectTop)
      {
        m_position.setX(objectLeft - m_width);
        playerLeft = m_position.getX();
        playerRight = playerLeft + m_width;

        m_velocity.setX(0);
      }
    }
    else
    {
      count++;
    }

    // 충돌 안할 시
    if(count == collisionObjects.size())
    {
      setGravity(0.1);
    }
  }
}

void Player::updateSprite()
{
  if(m_velocity.getX() < 0)
  {
    m_currentFrame = (frameCount++ / 6 + 1) % 6;
    flip = SDL_FLIP_HORIZONTAL;
  }
  else if(m_velocity.getX() > 0)
  {
    m_currentFrame = (frameCount++ / 6 + 1) % 6;
    flip = SDL_FLIP_NONE;
  }
  else
  {
    m_currentFrame = 0;
    frameCount = 0;
  }
}

void Player::setGravity(float gravity)
{
  m_acceleration.setY(gravity);
}