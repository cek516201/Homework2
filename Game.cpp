#include "Game.h"
#include "TextureManager.h"
#include "Wall.h"
#include "Player.h"
#include "InputHandler.h"

Game* Game::s_pInstance = 0;

bool Game::init(const char *title, int xpos, int ypos,  int width, int height, int flags) 
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    return false; // SDL 초기화 실패
  }

  m_pWindow = SDL_CreateWindow(title, xpos, ypos, width,height, flags);
  if (m_pWindow == 0)
  {
    return false; // 윈도우 생성 실패
  }

  m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
  if (m_pRenderer == 0)
  {
    return false; // 랜더러 생성 실패
  }

  if( TheTextureManager::Instance()->load("Assets/animate.png", "animate", m_pRenderer) == false)
  {
    return false; // 고양이 이미지 로드 실패 
  }

  if( TheTextureManager::Instance()->load("Assets/wall.png", "wall", m_pRenderer) == false)
  {
    return false; // 벽 이미지 로드 실패
  }

  if( TheTextureManager::Instance()->load("Assets/bullet.png", "bullet", m_pRenderer) == false)
  {
    return false; // 총알 이미지 로드 실패
  }

  for(int xpos = 160 ; xpos <= 480 ; xpos += 40)
  {
    createWallObject(new Wall(new LoaderParams(xpos, 240, 40, 40, "wall")));
  }
  createWallObject(new Wall(new LoaderParams(320, 200, 40, 40, "wall")));

  createPlayerObject(new Player(new LoaderParams(300, 100, 128, 82, "animate")));

  SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);

  m_bRunning = true;

  return true;
}

void Game::render()
{
  SDL_RenderClear(m_pRenderer);

  for(int i = 0 ; i < m_wallObjects.size() ; i++)
  {
    m_wallObjects[i]->draw();
  }

  for(int i = 0 ; i < m_playerObjects.size() ; i++)
  {
    m_playerObjects[i]->draw();
  }

  for(int i = 0 ; i < m_bulletObjects.size() ; i++)
  {
    m_bulletObjects[i]->draw();
  }
   
  SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
  for(int i = 0 ; i < m_playerObjects.size() ; i++)
  {
    m_playerObjects[i]->update();
  }

  for(int i = 0 ; i < m_bulletObjects.size() ; i++)
  {
    m_bulletObjects[i]->update();
  }
}

bool Game::running()
{ 
  return m_bRunning; 
}

void Game::handleEvents() 
{
  TheInputHandler::Instance()->update();
}

void Game::clean() 
{
  TheInputHandler::Instance()->clean();
  
  SDL_DestroyWindow(m_pWindow);
  SDL_DestroyRenderer(m_pRenderer);
  SDL_Quit();
}