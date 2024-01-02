#include "clock.h"
#include "input_reader.h"
#include "game.h"
#include "renderer.h"

void setup()
{
  zClock_Init();
  zInputReader_Init();
  zGame_Init();
  zRenderer_Init();
}

void loop()
{
  zClock_StartFrame();

  zInputReader_ReadInput();
  zGame_Update();
  zRenderer_Render();

  zClock_EndFrame();
}
