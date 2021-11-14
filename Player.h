#ifndef _Player_H_
#define _Player_H_

#include "SDLGameObject.h"

class Player : public SDLGameObject
{
public:
  Player(const LoaderParams* pParams) : SDLGameObject(pParams) {}
  void draw();
  void update();
  void handleInput();
  void checkCollision();
  void updateSprite();
  void setGravity(float gravity);
  void clean() {}

private:
  const float speed = 2.0;
  SDL_RendererFlip flip = SDL_FLIP_NONE;
  int frameCount = 0;
};

#endif