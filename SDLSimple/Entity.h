#include "Map.h"

enum EntityType { PLATFORM, PLAYER, ENEMY, GUN, MISSILE, CANDLE, BED};
enum AIType     { FOLLOWER};
enum AIState    { IDLE_GUARD, IDLE, ATTACKING  };

class Entity
{
private:
    bool m_is_active = true;

    // ––––– ANIMATION ––––– //
    int* m_animation_right = NULL, // move to the right
        * m_animation_left = NULL, // move to the left
        * m_animation_up   = NULL, // move upwards
        * m_animation_down = NULL; // move downwards

    // ––––– PHYSICS (GRAVITY) ––––– //
    glm::vec3 m_position;
    glm::vec3 m_ortho_position;
    glm::vec3 m_velocity;
    glm::vec3 m_acceleration;

    // ————— TRANSFORMATIONS ————— //
    float     m_speed;
    glm::vec3 m_movement;
    glm::mat4 m_model_matrix;
    glm::vec3 m_scale_size = glm::vec3(1.0f, 1.0f, 0.0f);
    float     m_rotation;

    // ————— ENEMY AI ————— //
    EntityType m_entity_type;
    AIType     m_ai_type;
    AIState    m_ai_state;

    float m_width = 1;
    float m_height = 1;


public:
    // ————— STATIC VARIABLES ————— //
    static const int    SECONDS_PER_FRAME = 16;
    static const int    LEFT    = 0,
                        RIGHT   = 1,
                        UP      = 2,
                        DOWN    = 3;

    // ————— ANIMATION ————— //
    int** m_walking = new int* [4]
        {
            m_animation_left,
            m_animation_right,
            m_animation_up,
            m_animation_down
        };

    bool m_collided_with_bed = false;

    int m_animation_frames  = 0,
        m_animation_index   = 0,
        m_animation_cols    = 0,
        m_animation_rows    = 0;

    int*    m_animation_indices = NULL;
    float   m_animation_time = 0.0f;

    // ––––– PHYSICS (JUMPING) ––––– //
    bool  m_is_jumping = false;
    float m_jumping_power = 0;

    // ––––– PHYSICS (COLLISIONS) ––––– //
    bool m_collided_top = false;
    bool m_collided_bottom = false;
    bool m_collided_left = false;
    bool m_collided_right = false;
    
    // ––––– HEALTH ––––– //
    int m_lives = 0;
    bool m_is_hit = false;
    bool m_shoot = false;
    
    float curr_gun_time = 0.0f;
    int curr_missile = 0;
    glm::vec3 missile_pos;
    
    glm::vec3 m_missile_direction;
    GLuint    m_texture_id;

    // ————— METHODS ————— //
    Entity();
    ~Entity();

    void draw_sprite_from_texture_atlas(ShaderProgram* program, GLuint texture_id, int index);
    void update(float delta_time, Entity* player, Entity* objects, int object_count, Map* map);
    void render(ShaderProgram* program);

    bool const check_collision(Entity* other) const;
    void const check_collision_y(Entity* collidable_entities, int collidable_entity_count);
    void const check_collision_x(Entity* collidable_entities, int collidable_entity_count);
    void const check_collision_y(Map* map);
    void const check_collision_x(Map* map);

    void move_left()    { m_movement.x = -1.0f; };
    void move_right()   { m_movement.x = 1.0f; };
    void move_up()      { m_movement.y = 1.0f; };
    void move_down()    { m_movement.y = -1.0f; };
    float m_rotationAngle;
    glm::vec3 m_rotationAxis;

    void ai_activate(Entity* player);
    void ai_follower(Entity* player);
    
    void position_gun(float x, float y);
    void position_candle(float x, float y);
    void set_door(float x, float y);
    void missile_velocity(float x, float y);
    
    void activate() { m_is_active = true; };
    void deactivate() { m_is_active = false; };

    // ————— GETTERS ————— //
    EntityType const get_entity_type()    const { return m_entity_type;     };
    AIType     const get_ai_type()        const { return m_ai_type;         };
    AIState    const get_ai_state()       const { return m_ai_state;        };
    glm::vec3  const get_position()       const { return m_position;        };
    glm::vec3  const get_ortho_position() const { return m_ortho_position;  };
    glm::vec3  const get_movement()       const { return m_movement;        };
    glm::vec3  const get_velocity()       const { return m_velocity;        };
    glm::vec3  const get_acceleration()   const { return m_acceleration;    };
    float      const get_jumping_power()  const { return m_jumping_power;   };
    float      const get_speed()          const { return m_speed;           };
    int        const get_width()          const { return m_width;           };
    int        const get_height()         const { return m_height;          };
    int        const get_lives()         const { return m_lives;          };
    int        const get_missile()          const { return curr_missile;   };
    bool       const get_active()         const { return m_is_active;       };
    float get_rotation() const {
        return m_rotation;
    }


    // ————— SETTERS ————— //
    void const set_entity_type(EntityType new_entity_type)  { m_entity_type = new_entity_type;      };
    void const set_ai_type(AIType new_ai_type)              { m_ai_type = new_ai_type;              };
    void const set_ai_state(AIState new_state)              { m_ai_state = new_state;               };
    void const set_pos(glm::vec3 new_position)         { m_position = new_position;            };
    void const set_ortho_position(glm::vec3 new_position)   { m_ortho_position = new_position;      };
    void const set_movement(glm::vec3 new_movement)         { m_movement = new_movement;            };
    void const set_velocity(glm::vec3 new_velocity)         { m_velocity = new_velocity;            };
    void const set_speed(float new_speed)                   { m_speed = new_speed;                  };
    void const set_jumping_power(float new_jumping_power)   { m_jumping_power = new_jumping_power;  };
    void const set_acceleration(glm::vec3 new_acceleration) { m_acceleration = new_acceleration;    };
    void const set_width(float new_width)                   { m_width = new_width;                  };
    void const set_height(float new_height)                 { m_height = new_height;                };
    void const set_lives(float new_health)                 { m_lives = new_health;                };
    void const set_missile(int missle)                     { curr_missile = missle;          };
    void const scale(glm::vec3 new_size)                 { m_scale_size = new_size;
                                                              m_width     *= m_scale_size.x;
                                                              m_height    *= m_scale_size.y;        };

};
