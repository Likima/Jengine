#pragma once
#include <array>
#include <string>
#include <vector>

#include "Dependancies/libs.h"
#include "KeyHandler/KeyHandler.h"
#include "Renderer/Renderer.h"

class Entity {
public:
  Entity() = default;
  virtual ~Entity() = default;
  Entity(Entity const &e)
      : x_left(e.x_left), y_up(e.y_up), x_right(e.x_right), y_down(e.y_down),
        kh(e.kh) {}
  Entity(float center_x, float center_y, float width, float height)
      : kh(nullptr) {
    setCenterAndSize(center_x, center_y);
  }

  virtual void update() = 0;
  virtual void render(Renderer *r) = 0;
  virtual void onStart() = 0;

  void setImgPath(std::string filepath) { this->filepath = filepath; }
  void setCenterAndSize(float center_x, float center_y) {
    x_mid = center_x;
    y_mid = center_y;

    float half_width = width / 2.0f;
    float half_height = height / 2.0f;
    x_left = center_x - half_width;
    x_right = center_x + half_width;
    y_up = center_y - half_height;
    y_down = center_y + half_height;
  }

  void setSpeed(int speed) {
    this->speed = ((float)(speed) * 5.0f / ((float)(SCREEN_WIDTH)));
  }

  void setWidth(int width) {
    this->width = ((float)(width) * 5.0f /
                   (float)(std::min(SCREEN_HEIGHT, SCREEN_WIDTH)));
  }

  // == Movement controls == //
  void moveRight() {
    x_left += speed;
    x_right += speed;
  }
  void moveLeft() {
    x_left -= speed;
    x_right -= speed;
  }
  void moveUp() {
    y_up += speed;
    y_down += speed;
  }
  void moveDown() {
    y_up -= speed;
    y_down -= speed;
  }
  // == / == //

  void updateVertices() {
    vertices = {
        x_left,  y_up,   // 0: top left
        x_right, y_up,   // 1: top right
        x_right, y_down, // 2: bottom right
        x_left,  y_down  // 3: bottom left
    };

    indices = {
        0, 1, 2, // first triangle
        2, 3, 0  // second triangle
    };
  }

  void attachKeyHandler(KeyHandler *kh) { this->kh = kh; }

protected:
  float x_left;
  float y_up;
  float x_right;
  float y_down;

  float width = 0.2f;
  float height = 0.2f;

  float x_mid = 0.0f;
  float y_mid = 0.0f;

  float speed = 0.02f;

  std::string filepath;
  KeyHandler *kh;
  bool onScreen;

  std::vector<float> vertices;
  std::vector<int> indices;
};
