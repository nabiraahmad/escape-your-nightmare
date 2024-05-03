/**
* Author: Nabira Ahmad
* Assignment:  Escape your nightmare
* Date due: 2024-05-03, 3:00pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/
#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Entity.h"

Entity::Entity()
{
    // ––––– PHYSICS ––––– //
    m_position = glm::vec3(0.0f);
    m_velocity = glm::vec3(0.0f);
    m_acceleration = glm::vec3(0.0f);

    // ––––– TRANSLATION ––––– //
    m_movement = glm::vec3(0.0f);
    m_speed = 0;
    m_model_matrix = glm::mat4(1.0f);
}

Entity::~Entity()
{
    delete[] m_animation_up;
    delete[] m_animation_down;
    delete[] m_animation_left;
    delete[] m_animation_right;
    delete[] m_walking;
}

void Entity::draw_sprite_from_texture_atlas(ShaderProgram* program, GLuint texture_id, int index)
{

    float u_coord = (float)(index % m_animation_cols) / (float)m_animation_cols;
    float v_coord = (float)(index / m_animation_cols) / (float)m_animation_rows;

    float width = 1.0f / (float)m_animation_cols;
    float height = 1.0f / (float)m_animation_rows;
    
    float tex_coords[] =
    {
        u_coord, v_coord + height, u_coord + width, v_coord + height, u_coord + width, v_coord,
        u_coord, v_coord + height, u_coord + width, v_coord, u_coord, v_coord
    };

    float vertices[] =
    {
        -0.5, -0.5, 0.5, -0.5,  0.5, 0.5,
        -0.5, -0.5, 0.5,  0.5, -0.5, 0.5
    };

    glBindTexture(GL_TEXTURE_2D, texture_id);

    glVertexAttribPointer(program->get_position_attribute(), 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->get_position_attribute());

    glVertexAttribPointer(program->get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, tex_coords);
    glEnableVertexAttribArray(program->get_tex_coordinate_attribute());

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(program->get_position_attribute());
    glDisableVertexAttribArray(program->get_tex_coordinate_attribute());
}

void Entity::ai_activate(Entity* player)
{
    switch (m_ai_type)
    {
        case FOLLOWER:
            ai_follower(player);
            break;
    }
}

void Entity::ai_follower(Entity* player)
{
    switch (m_ai_state) {
        case IDLE:
            if (glm::distance(m_position, player->get_position()) < 5.0f) {
                m_ai_state = ATTACKING;
            }
            break;
        case IDLE_GUARD:
            if (glm::distance(m_position, player->get_position()) < 10.0f) {
                m_ai_state = ATTACKING;
            }

            break;

        case ATTACKING:
            m_speed = 1.0f;
            glm::vec3 direction = glm::normalize(player->get_position() - get_position());
            m_movement = direction * m_speed;

            if (std::abs(direction.x) > std::abs(direction.y)) {
                if (direction.x < 0) {
                    m_animation_indices = m_walking[LEFT];
                } else {
                    m_animation_indices = m_walking[RIGHT];
                }
            } else {
                if (direction.y < 0) {
                    m_animation_indices = m_walking[DOWN];
                } else {
                    m_animation_indices = m_walking[UP];
                }
            }

            if (glm::distance(m_position, player->get_position()) > 14.0f) {
                m_ai_state = IDLE_GUARD;
            }
            break;
    }
}

void Entity::position_gun(float x, float y){
    if (y == 0 && x > 0) m_rotation = 0.0f;
    else if (y == 0 && x < 0) m_rotation = glm::radians(180.0f);
    else if (y > 0 && x == 0) m_rotation = glm::radians(90.0f);
    else if (y < 0 && x == 0) m_rotation = glm::radians(270.0f);
    else m_rotation = atan2(y,x);
    return;
}
void Entity::position_candle(float x, float y){
    if (y == 0 && x > 0) m_rotation = 0.0f;
    else if (y == 0 && x < 0) m_rotation = glm::radians(180.0f);
    else if (y > 0 && x == 0) m_rotation = glm::radians(90.0f);
    else if (y < 0 && x == 0) m_rotation = glm::radians(270.0f);
    else m_rotation = atan2(y,x);
    return;
}


void Entity::missile_velocity(float x, float y) {
    m_movement = glm::normalize(glm::vec3(x, y, 0));
    m_rotation = atan2(y,x) + glm::radians(90.0f);
    return;
}

void Entity::update(float delta_time, Entity* player, Entity* objects, int object_count, Map* map)
{
    if (m_lives <= 0 && m_entity_type == ENEMY) deactivate();
    if (!m_is_active) return;
    
    m_collided_top = false;
    m_collided_bottom = false;
    m_collided_left = false;
    m_collided_right = false;
    m_collided_with_bed = false;
    
    if (m_entity_type == ENEMY) ai_activate(player);
    
    if (m_animation_indices != NULL)
    {
        if (glm::length(m_movement) != 0)
        {
            m_animation_time += delta_time;
            float frames_per_second = (float)1 / SECONDS_PER_FRAME;
            
            if (m_animation_time >= frames_per_second)
            {
                m_animation_time = 0.0f;
                m_animation_index++;
                
                if (m_animation_index >= m_animation_frames)
                {
                    m_animation_index = 0;
                }
            }
        }
    }
    if (m_entity_type == CANDLE){
        m_animation_time += delta_time;
        float frames_per_second = (float)1 / SECONDS_PER_FRAME;
        if (m_animation_time >= frames_per_second)
        {
            m_animation_time = 0.0f;
            m_animation_index++;
            
            if (m_animation_index >= m_animation_frames)
            {
                m_animation_index = 0;
            }
        }
    }
    
    if (m_entity_type != MISSILE) {
        m_velocity.x = m_movement.x * m_speed;
    } else {
        m_velocity = m_movement * m_speed;
    }
    
    m_velocity.x = m_movement.x * m_speed;
    m_velocity.y = m_movement.y * m_speed;
    m_velocity += m_acceleration * delta_time;
    m_position.y += m_velocity.y * delta_time;
    m_position.x += m_velocity.x * delta_time;

    if (m_entity_type == MISSILE) {
        for (int i = 0; i < object_count; i++) {
            Entity* collidable_entity = &objects[i];
            if (check_collision(collidable_entity)){
                bool m_shoot = true;
                missile_pos = m_position;
                collidable_entity->set_lives(collidable_entity->get_lives() - 1);
                collidable_entity->m_is_hit = true;
                deactivate();
            }
        }
        if (m_collided_top || m_collided_left || m_collided_right || m_collided_bottom) {
            m_movement = glm::vec3(0.0f, 0.0f, 0.0f);
        }
    }
    else if (m_entity_type == PLAYER) {
        for (int i = 0; i < object_count; i++) {
            Entity* collidable_entity = &objects[i];
            if (check_collision(collidable_entity)){
                if (collidable_entity[i].m_entity_type == BED){
                    m_collided_with_bed = true;
                }
                if (m_position.x < collidable_entity[i].get_position().x) m_position.x = m_position.x - .75;
                if (m_position.x > collidable_entity[i].get_position().x) m_position.x = m_position.x + .75;
                m_lives = m_lives - 1;
                m_is_hit = true;
            }
        }
    } else {
        check_collision_y(objects, object_count);
        check_collision_x(objects, object_count);
    }
    

    // ————— ATTACKING ————— //
    if (m_is_active && m_entity_type == GUN && curr_gun_time < 3) {
        curr_gun_time += 0.2f;
    } else if (m_entity_type == GUN && curr_gun_time > 3) {
        deactivate();
        curr_gun_time = 0.0f;
    }
    
    m_model_matrix = glm::mat4(1.0f);
    m_model_matrix = glm::translate(m_model_matrix, m_position);
    if (m_entity_type == GUN || m_entity_type ==MISSILE) {
        m_model_matrix = glm::rotate(m_model_matrix, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    }
    m_model_matrix = glm::scale(m_model_matrix, m_scale_size);
}

void const Entity::check_collision_y(Entity* collidable_entities, int collidable_entity_count)
{
    for (int i = 0; i < collidable_entity_count; i++)
    {
        Entity* collidable_entity = &collidable_entities[i];

        if (check_collision(collidable_entity))
        {
            float y_distance = fabs(m_position.y - collidable_entity->get_position().y);
            float y_overlap = fabs(y_distance - (m_height / 2.0f) - (collidable_entity->get_height() / 2.0f));
            if (m_velocity.y > 0) {
                m_position.y -= y_overlap;
                m_velocity.y = 0;
                m_collided_top = true;
            }
            else if (m_velocity.y < 0) {
                m_position.y += y_overlap;
                m_velocity.y = 0;
                m_collided_bottom = true;
            }
        }
    }
}

void const Entity::check_collision_x(Entity* collidable_entities, int collidable_entity_count)
{
    for (int i = 0; i < collidable_entity_count; i++)
    {
        Entity* collidable_entity = &collidable_entities[i];

        if (check_collision(collidable_entity))
        {
            float x_distance = fabs(m_position.x - collidable_entity->get_position().x);
            float x_overlap = fabs(x_distance - (m_width / 2.0f) - (collidable_entity->get_width() / 2.0f));
            if (m_velocity.x > 0) {
                m_position.x -= x_overlap;
                m_velocity.x = 0;
                m_collided_right = true;
            }
            else if (m_velocity.x < 0) {
                m_position.x += x_overlap;
                m_velocity.x = 0;
                m_collided_left = true;
            }
        }
    }
}


void const Entity::check_collision_y(Map* map)
{
    glm::vec3 top = glm::vec3(m_position.x, m_position.y + (m_height / 2), m_position.z);
    glm::vec3 top_left = glm::vec3(m_position.x - (m_width / 2), m_position.y + (m_height / 2), m_position.z);
    glm::vec3 top_right = glm::vec3(m_position.x + (m_width / 2), m_position.y + (m_height / 2), m_position.z);
    glm::vec3 bottom = glm::vec3(m_position.x, m_position.y - (m_height / 2), m_position.z);
    glm::vec3 bottom_left = glm::vec3(m_position.x - (m_width / 2), m_position.y - (m_height / 2), m_position.z);
    glm::vec3 bottom_right = glm::vec3(m_position.x + (m_width / 2), m_position.y - (m_height / 2), m_position.z);

    float penetration_x = 0;
    float penetration_y = 0;

    if (map->is_solid(top, &penetration_x, &penetration_y) && m_velocity.y > 0)
    {
        m_velocity.y = 0;
        m_collided_top = true;
    }
    else if (map->is_solid(top_left, &penetration_x, &penetration_y) && m_velocity.y > 0)
    {
        m_position.y -= penetration_y;
        m_velocity.y = 0;
        m_collided_top = true;
    }
    else if (map->is_solid(top_right, &penetration_x, &penetration_y) && m_velocity.y > 0)
    {
        m_velocity.y = 0;
        m_collided_top = true;
    }
    if (map->is_solid(bottom, &penetration_x, &penetration_y) && m_velocity.y < 0)
    {
        m_velocity.y = 0;
        m_collided_bottom = true;
    }
    else if (map->is_solid(bottom_left, &penetration_x, &penetration_y) && m_velocity.y < 0)
    {
        m_velocity.y = 0;
        m_collided_bottom = true;
    }
    else if (map->is_solid(bottom_right, &penetration_x, &penetration_y) && m_velocity.y < 0)
    {
        m_velocity.y = 0;
        m_collided_bottom = true;
    }
}

void const Entity::check_collision_x(Map* map)
{
    // Probes for tiles; the x-checking is much simpler
    glm::vec3 left = glm::vec3(m_position.x - (m_width / 2), m_position.y, m_position.z);
    glm::vec3 right = glm::vec3(m_position.x + (m_width / 2), m_position.y, m_position.z);

    float penetration_x = 0;
    float penetration_y = 0;

    if (map->is_solid(left, &penetration_x, &penetration_y) && m_velocity.x < 0)
    {
        m_velocity.x = 0;
        m_collided_left = true;
    }
    if (map->is_solid(right, &penetration_x, &penetration_y) && m_velocity.x > 0)
    {
        m_velocity.x = -m_velocity.x;
        
        m_collided_right = true;
    }
}


void Entity::render(ShaderProgram* program)
{
    if (!m_is_active) return;

    program->set_model_matrix(m_model_matrix);

    if (m_animation_indices != NULL)
    {
        draw_sprite_from_texture_atlas(program, m_texture_id, m_animation_indices[m_animation_index]);
        return;
    }

    float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float tex_coords[] = { 0.0,  1.0, 1.0,  1.0, 1.0, 0.0,  0.0,  1.0, 1.0, 0.0,  0.0, 0.0 };

    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    glVertexAttribPointer(program->get_position_attribute(), 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->get_position_attribute());
    glVertexAttribPointer(program->get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, tex_coords);
    glEnableVertexAttribArray(program->get_tex_coordinate_attribute());

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(program->get_position_attribute());
    glDisableVertexAttribArray(program->get_tex_coordinate_attribute());
}


bool const Entity::check_collision(Entity* other) const
{
    if (other == this) return false;
    if (!m_is_active || !other->m_is_active) return false;

    float x_distance = fabs(m_position.x - other->m_position.x) - ((m_width + other->m_width) / 2.0f);
    float y_distance = fabs(m_position.y - other->m_position.y) - ((m_height + other->m_height) / 2.0f);

    return x_distance < 0.0f && y_distance < 0.0f;
}
