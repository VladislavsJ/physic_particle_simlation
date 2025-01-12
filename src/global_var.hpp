#ifndef SETTINGS_HPP
#define SETTINGS_HPP

class GlobalVar {
    //TODOP , I am not sure if this is the best way to do it, but you never know...
    // as I need to write a lot of code for each variable.

public:
    static GlobalVar& getInstance() {
        static GlobalVar instance;
        return instance;
    }

    double getGravity() const { return gravity; }
    void setGravity(double g) { gravity = g; }
    int getFieldSizeX() const { return fieldSizeX_Y[0]; }
    int getFieldSizeY() const { return fieldSizeX_Y[1]; }
    void setFieldSizeX_Y(int sizeX, int sizeY) { fieldSizeX_Y[0] = sizeX; fieldSizeX_Y[1] = sizeY; }
    double getParticleSize() const { return particleR; }
    void setParticleSize(double size) { particleR = size; }

private:
    double gravity = 9.8;
    int fieldSizeX_Y[2] = { 400, 400 };
    double particleR= 0.1;
    
    // Prevent external instantiation
    //TODO3:
    //Settings() = default;
    //Settings(const Settings&) = delete;
    //Settings& operator=(const Settings&) = delete;
};

#endif 
    