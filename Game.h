#ifndef _Game_H_
#define _Game_H_

#include "SDL.h"
#include <vector>
#include "GameObject.h"

class Game;

typedef Game TheGame;

class Game
{
private:
  Game() {}
  static Game* s_pInstance;

public:
  static Game* Instance()
  {
    if(s_pInstance == 0)
      s_pInstance = new Game();

    return s_pInstance;
  }

  ~Game() {}

  bool init(const char *title, int xpos, int ypos,  int width, int height, int flags);
  void render();
  void update(); 
  bool running();
  void handleEvents();
  void clean();
  void quit() { m_bRunning = false; }

  void createPlayerObject(GameObject* pGameObject) { m_playerObjects.push_back(pGameObject); }
  void createWallObject(GameObject* pWallObject) { m_wallObjects.push_back(pWallObject); }
  void createBulletObject(GameObject* pBulletObject) { m_bulletObjects.push_back(pBulletObject); }
  void deleteBulletObject(GameObject* pBulletObject)
  {
    for(int i = 0 ; i < m_bulletObjects.size() ; i++)
    {
      if(m_bulletObjects[i] == pBulletObject)
      {
        m_bulletObjects.erase(m_bulletObjects.begin() + i);

        return;
      }
    }
  }

  vector<GameObject*> getWallObjects() const { return m_wallObjects; }
  SDL_Renderer* getRenderer() const { return m_pRenderer; }

private:
  vector<GameObject*> m_playerObjects;
  vector<GameObject*> m_wallObjects;
  vector<GameObject*> m_bulletObjects;

  SDL_Window* m_pWindow = 0;
  SDL_Renderer* m_pRenderer = 0;

  bool m_bRunning = false;
};

#endif