#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Vec2 {
  int x;
  int y;
} Vec2;

typedef struct Entity {
  Vec2 pos;
  Vec2 dir;
} Entity;

typedef struct Color {
  int r;
  int g;
  int b;
} Color;

#endif
