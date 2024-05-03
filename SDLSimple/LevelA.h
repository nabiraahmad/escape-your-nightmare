#include "Scene.h"

class LevelA : public Scene {
public:
    int SKELETON_COUNT = 6;
    int MISSILE_COUNT = 25;
    int HEART_COUNT = 3;
    ~LevelA();
    
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
};
