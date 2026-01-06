#include <raylib.h>

int main() {
  InitWindow(800, 600, "some Game");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    EndDrawing();
  }

  CloseWindow();
}