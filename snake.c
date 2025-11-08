#include "raylib.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 550
<<<<<<< HEAD
//
#define SNAKE_SPEED 1200.0
#define SNAKE_SEGMENT_WIDTH 15
#define SNAKE_SEGMENT_HEIGHT 15
#define SNAKE_MAX_LENGTH 500
#define SNAKE_FOOD_WIDTH 15
#define SNAKE_FOOD_HEIGHT 15

uint32_t score = 0;
uint8_t game_over = 0;
float snake_move_interval = 0.09; // in seconds
=======
#define FRAME_LIMIT 60
//
#define SNAKE_SPEED 15.0  // don't update this to change speed. update the move_interval instead
#define SNAKE_SEGMENT_WIDTH 15
#define SNAKE_SEGMENT_HEIGHT 15
#define SNAKE_MAX_LENGTH 500
#define SNAKE_FOOD_WIDTH 32
#define SNAKE_FOOD_HEIGHT 30

uint32_t score = 0;
uint8_t game_over = 0;
float snake_move_interval = 0.06; // in seconds
>>>>>>> 7b9ca5a (updates)
typedef enum { Up, Down, Right, Left } Direction;
typedef Rectangle SnakeSegment;
typedef struct {
  Vector2 velocity;
  Color color;
  Direction direction;
  float last_move_time;
  uint16_t length;
  SnakeSegment segments[];
} Snake;

<<<<<<< HEAD
typedef Rectangle Food;
=======
typedef struct {
  Rectangle rect;
  Texture2D tex;
} Food;
>>>>>>> 7b9ca5a (updates)

Snake *alloc_init_snake() {
  // allocate and initialise the snake at the start of the game.
  // the snake has only 1 segment at the first which is snake head.
  Snake *snake =
      (Snake *)malloc(sizeof(Snake) + SNAKE_MAX_LENGTH * sizeof(SnakeSegment));
  if (snake == NULL) {
    printf("Error when allocating memory for the snake");
    CloseWindow();
  }
  snake->color = RED;
  snake->velocity = (Vector2){SNAKE_SPEED, 0};
  snake->direction = Right;
  snake->last_move_time = 0.0;
  snake->length = 1;
  const SnakeSegment head = {350, 250, SNAKE_SEGMENT_WIDTH,
                             SNAKE_SEGMENT_HEIGHT};
  snake->segments[0] = head;
  return snake;
}

void add_segment_to_snake(Snake *snake) {
  snake->length++;
  snake->segments[(snake->length - 1)] =
      (SnakeSegment){0, 0, SNAKE_SEGMENT_WIDTH, SNAKE_SEGMENT_HEIGHT};
}

void draw_sanke(Snake *snake) {
  for (int i = 0; i < snake->length; i++) {
    if (i == 0) {
      DrawRectangleRec(snake->segments[i], RED);
    } else {
      DrawRectangleRec(snake->segments[i], RAYWHITE);
    }
  }
}

void draw_food(Food *food) {
<<<<<<< HEAD
  DrawRectangle(food->x, food->y, SNAKE_FOOD_WIDTH, SNAKE_FOOD_HEIGHT, GOLD);
}

void update_snake_pos(Snake *snake, float delta_time) {
=======
  DrawTexture(food->tex, food->rect.x, food->rect.y, RAYWHITE);
}

void update_snake_pos(Snake *snake) {
>>>>>>> 7b9ca5a (updates)
  // check if the time since the last move exceeded the interval
  if (snake->last_move_time < snake_move_interval) {
    return;
  }
  snake->last_move_time = 0.0; // reset the timer
  // shift the other segments
  for (int i = snake->length - 1; i > 0; i--) {
    snake->segments[i].x = snake->segments[i - 1].x;
    snake->segments[i].y = snake->segments[i - 1].y;
  }
  // update the head segment according to keyboard input
  SnakeSegment *head = &(snake->segments[0]);
<<<<<<< HEAD
  head->x += (snake->velocity.x * delta_time);
  head->y += (snake->velocity.y * delta_time);
}

void renew_food(Food *food) {
  food->x = GetRandomValue(50, SCREEN_WIDTH - 50);
  food->y = GetRandomValue(50, SCREEN_HEIGHT - 50);
=======
  head->x += snake->velocity.x;
  head->y += snake->velocity.y;
}

void renew_food(Food *food) {
  food->rect.x = GetRandomValue(50, SCREEN_WIDTH - 50);
  food->rect.y = GetRandomValue(50, SCREEN_HEIGHT - 50);
>>>>>>> 7b9ca5a (updates)
}

void handle_keyboard_events(Snake *snake, Food *food) {
  if (IsKeyPressed(KEY_UP) && snake->direction != Down) {
    snake->direction = Up;
    snake->velocity = (Vector2){0.0, -SNAKE_SPEED};
  }
  if (IsKeyPressed(KEY_DOWN) && snake->direction != Up) {
    snake->direction = Down;
    snake->velocity = (Vector2){0.0, SNAKE_SPEED};
  }
  if (IsKeyPressed(KEY_RIGHT) && snake->direction != Left) {
    snake->direction = Right;
    snake->velocity = (Vector2){SNAKE_SPEED, 0.0};
  }
  if (IsKeyPressed(KEY_LEFT) && (snake->direction != Right)) {
    snake->direction = Left;
    snake->velocity = (Vector2){-SNAKE_SPEED, 0.0};
  }
}

void check_collision(Snake *snake, Food *food, Sound *sound_to_play) {
  SnakeSegment *snake_head = &(snake->segments[0]);
  // snake with walls
  if (snake_head->x < 0 ||
      snake_head->x > GetScreenWidth() - SNAKE_SEGMENT_WIDTH)
    game_over = 1;
  if (snake_head->y < 0 ||
      snake_head->y > GetScreenHeight() - SNAKE_SEGMENT_HEIGHT)
    game_over = 1;

  // snake with food
<<<<<<< HEAD
  if (CheckCollisionRecs(*snake_head, *food)) {
=======
  if (CheckCollisionRecs(*snake_head, food->rect)) {
>>>>>>> 7b9ca5a (updates)
    score++;
    PlaySound(*sound_to_play);
    renew_food(food);
    add_segment_to_snake(snake);
  }

  // snake with itself
  for (int i = 1; i < snake->length; i++) {
    if (CheckCollisionRecs(*snake_head, snake->segments[i])) {
      game_over = 1;
    }
  }
}

int main(void) {
  float delta_time;
  Snake *snake = alloc_init_snake();
<<<<<<< HEAD
  Food food = {GetRandomValue(70.0, SCREEN_WIDTH),
               GetRandomValue(70.0, SCREEN_HEIGHT), SNAKE_FOOD_WIDTH,
               SNAKE_FOOD_HEIGHT};

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "noor snake game");
=======
  Rectangle food_rect = {GetRandomValue(70.0, SCREEN_WIDTH),
                         GetRandomValue(70.0, SCREEN_HEIGHT), SNAKE_FOOD_WIDTH,
                         SNAKE_FOOD_HEIGHT};

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "noor snake game");
  Texture2D food_tex = LoadTexture("./pie32.png");
  Food food = {food_rect, food_tex};
>>>>>>> 7b9ca5a (updates)
  InitAudioDevice();
  Sound eee = LoadSound("./EEE.mp3");
  Music bg = LoadMusicStream("./bg.mp3");

<<<<<<< HEAD
  SetTargetFPS(60);
  SetSoundVolume(eee, 0.4); // too loud sound
=======
  SetTargetFPS(FRAME_LIMIT);
  SetSoundVolume(eee, 0.3); // too loud sound
>>>>>>> 7b9ca5a (updates)
  PlayMusicStream(bg);

  // Main game loop
  while (!WindowShouldClose()) {
    UpdateMusicStream(bg);
    delta_time = GetFrameTime();
    snake->last_move_time += delta_time;
    if (game_over) {
      BeginDrawing();
      DrawText("player lost", 320, 230, 25, RED);
      EndDrawing();
    } else {

      handle_keyboard_events(snake, &food);
<<<<<<< HEAD
      update_snake_pos(snake, delta_time);
      check_collision(snake, &food, &eee);
=======
      update_snake_pos(snake);
>>>>>>> 7b9ca5a (updates)
      // drawing
      BeginDrawing();
      ClearBackground(BLACK);
      DrawText(TextFormat("score = %d", score), 20, 10, 25, RAYWHITE);
      draw_sanke(snake);
      draw_food(&food);
      EndDrawing();
<<<<<<< HEAD
=======
      check_collision(snake, &food, &eee);
>>>>>>> 7b9ca5a (updates)
    }
  }
  UnloadSound(eee);
  UnloadMusicStream(bg);
  CloseAudioDevice();
<<<<<<< HEAD
=======
  UnloadTexture(food.tex);
>>>>>>> 7b9ca5a (updates)
  CloseWindow();
  return 0;
}
