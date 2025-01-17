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
    gravity = 9.81;        // Gravitational acceleration (m/s^2).
    fieldSizeX_Y[0] = 500; // Default field size X.
    fieldSizeX_Y[1] = 500; // Default field size Y.
  }

  // Getters
  double getGravity() const { return gravity; }
  int getFieldSizeX() const { return fieldSizeX_Y[0]; }
  int getFieldSizeY() const { return fieldSizeX_Y[1]; }
  double getParticleSize() const { return particleR; }

  // Setters
  void setGravity(double g) { gravity = g; }
  void setFieldSizeX_Y(int sizeX, int sizeY) {
    fieldSizeX_Y[0] = sizeX;
    fieldSizeX_Y[1] = sizeY;
  }
  void setParticleSize(double size) { particleR = size; }

private:
  GlobalVar() = default;  // Private constructor to enforce singleton pattern.
  ~GlobalVar() = default; // Private destructor.

  // Deleted copy constructor and assignment operator to prevent copying.
  GlobalVar(const GlobalVar &) = delete;
  GlobalVar &operator=(const GlobalVar &) = delete;

  // Member variables
  double gravity;      // Gravitational acceleration.
  int fieldSizeX_Y[2]; // Field dimensions [X, Y].
  double particleR;    // Default particle radius.
};

#endif // SETTINGS_HPP