#ifndef SETTINGS_HPP
#define SETTINGS_HPP

class GlobalVar {
    //TODOP , I am not sure if this is the best way to do it, but you never know...
    // as I need to write a lot of code for each variable.

public:
    static GlobalVar& getInstance() {
        static GlobalVar instance;
        instance.init();
        return instance;
    }
    void init() {
        //TODO0: init the non specified variables
        gravity = 9.81;
        fieldSizeX_Y[0] = 700;
        fieldSizeX_Y[1] = 500;
        particleR = 0.1;

    }
    double getGravity() const { return gravity; }
    void setGravity(double g) { gravity = g; }
    int getFieldSizeX() const { return fieldSizeX_Y[0]; }
    int getFieldSizeY() const { return fieldSizeX_Y[1]; }
    void setFieldSizeX_Y(int sizeX, int sizeY) { fieldSizeX_Y[0] = sizeX; fieldSizeX_Y[1] = sizeY; }
    double getParticleSize() const { return particleR; }
    void setParticleSize(double size) { particleR = size; }

private:
    GlobalVar() = default;
    
    GlobalVar(const GlobalVar&) = delete;
    GlobalVar& operator=(const GlobalVar&) = delete;

    ~GlobalVar() = default;
    double gravity;
    int fieldSizeX_Y[2] ;
    double particleR;
    
    // Prevent external instantiation
    //TODO3:
    //Settings() = default;
    //Settings(const Settings&) = delete;
    //Settings& operator=(const Settings&) = delete;
};

#endif 
    