#include "Scene.h"

class LevelB : public Scene {
public:
    int WITCH_DOCTOR_COUNT = 4;
    int MISSILE_COUNT = 14;
    int HEART_COUNT = 3;
    ~LevelB();
    
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
};
