#ifndef VECTOR2D_H
#define VECTOR2D_H

struct Vector2D {
  float x;
  float y;

  Vector2D() : x(0.0f), y(0.0f) {}
  Vector2D(float x_, float y_) : x(x_), y(y_) {}

  Vector2D operator+(const Vector2D &rhs) const {
    return Vector2D(this->x + rhs.x, this->y + rhs.y);
  }

  Vector2D operator-(const Vector2D &rhs) const {
    return Vector2D(this->x - rhs.x, this->y - rhs.y);
  }

  Vector2D &operator+=(const Vector2D &rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
  }

  Vector2D &operator-=(const Vector2D &rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
  }

  Vector2D operator*(float scalar) const {
    return Vector2D(this->x * scalar, this->y * scalar);
  }
};

#endif // VECTOR2D_H
