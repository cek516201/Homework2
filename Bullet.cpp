#include "Bullet.h"
#include "InputHandler.h"
#include "Game.h"

void Bullet::moveToMouse()
{
  Vector2D* vec = TheInputHandler::Instance()->getMousePosition();

  m_velocity = (*vec - m_position - *new Vector2D(m_width/2, m_height/2)) / (*vec - m_position).length() * speed;
}

void Bullet::draw()
{
  SDLGameObject::draw();
}

void Bullet::update()
{
  checkDelete();

  SDLGameObject::update();
}

void Bullet::checkDelete()
{
  // 화면 밖으로 나갈 시
  if(m_position.getX() + m_width >= 640 || m_position.getX() <= 0
  || m_position.getY() + m_height >= 480 || m_position.getY() <= 0)
  {
    TheGame::Instance()->deleteBulletObject(this);
  }

  // 벽과 부딛힐 시
  vector<GameObject*> collisionObjects = TheGame::Instance()->getWallObjects();

  int BulletLeft = m_position.getX();
  int BulletRight = BulletLeft + m_width;
  int BulletTop = m_position.getY();
  int BulletBottom = BulletTop + m_height;

  for(int i = 0 ; i < collisionObjects.size() ; i++)
  {
    int objectLeft = collisionObjects[i]->getPosition().getX();
    int objectRight = objectLeft + collisionObjects[i]->getWidth();
    int objectTop = collisionObjects[i]->getPosition().getY();
    int objectBottom = objectTop + collisionObjects[i]->getHeight();

    // 충돌 시
    if(BulletLeft <= objectRight && BulletRight >= objectLeft
    && BulletTop <= objectBottom && BulletBottom >= objectTop)
    {
      TheGame::Instance()->deleteBulletObject(this);
    } 
  }
}