// 플레이어 점프 적용
// 플레이어 장애물 충돌 적용
// 총알 장애물 충돌 또는 화면 이탈 시 총알 삭제 적용
// 나머지는 하지 못했습니다
// 키보드 : 이동
// 스페이스 바 : 점프
// 마우스 왼쪽 클릭 : 총알 발사

#include <iostream>
#include "Game.h"

using namespace std;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* argv[])
{
  if( TheGame::Instance()->init("Chapter 1", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, false) == false )
  {
    cout << "game init failure " << SDL_GetError() << endl;

    return 1; // 초기화 실패
  }

  Uint32 frameStart, frameTime;

  while( TheGame::Instance()->running() )
  {
    frameStart = SDL_GetTicks();

    TheGame::Instance()->handleEvents();
    TheGame::Instance()->update();
    TheGame::Instance()->render();

    frameTime = SDL_GetTicks() - frameStart;

    if(frameTime < DELAY_TIME)
    {
      SDL_Delay((int)(DELAY_TIME - frameTime));
    }
  }

  TheGame::Instance()->clean();

  return 0;
}