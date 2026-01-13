#include <raylib.h>

int main() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(800, 600, "some Game");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    EndDrawing();
  }

  CloseWindow();
}
