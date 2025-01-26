#ifndef SETTINGS_HPP
#define SETTINGS_HPP

class GlobalVar {
  // Singleton class to store global settings and variables.
public:
  // Retrieves the singleton instance and initializes variables if needed.
  static GlobalVar &getInstance() {
    static GlobalVar instance;
    instance.init();
    return instance;
  }

  // Initializes variables with default values.
  void init() {
    gravity = 09.81;       // Gravitational acceleration (m/s^2).
    fieldSizeX_Y[0] = 500; // Default field size X.
    fieldSizeX_Y[1] = 500; // Default field size Y.
    particleMaxR = 25;     // Default particle radius.
  }

  // Getters
  double getGravity() const { return gravity; }
  int getFieldSizeX() const { return fieldSizeX_Y[0]; }
  int getFieldSizeY() const { return fieldSizeX_Y[1]; }
  double getMaxPartSize() const { return particleMaxR; }

  // Setters
  void setGravity(double g) { gravity = g; }
  void setFieldSizeX_Y(int sizeX, int sizeY) {
    fieldSizeX_Y[0] = sizeX;
    fieldSizeX_Y[1] = sizeY;
  }
  void setParticleSize(double size) { particleMaxR = size; }

private:
  GlobalVar() = default;  // Private constructor to enforce singleton pattern.
  ~GlobalVar() = default; // Private destructor.

  // Deleted copy constructor and assignment operator to prevent copying.
  GlobalVar(const GlobalVar &) = delete;
  GlobalVar &operator=(const GlobalVar &) = delete;

  // Member variables
  double gravity;      // Gravitational acceleration.
  int fieldSizeX_Y[2]; // Field dimensions [X, Y].
  double particleMaxR; // Default particle radius.
};

enum class InteractionType { // interaction types, for each button
  None,
  AddParticles,
  White_Ball,
  Stop,
  Slider,
};
#endif // SETTINGS_HPP