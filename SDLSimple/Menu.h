#include "Scene.h"

class Menu : public Scene {
public:
    int ENEMY_COUNT = 0;
    ~Menu();
    
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
};
