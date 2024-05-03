/**
* Author: Nabira Ahmad
* Assignment:  Escape your nightmare
* Date due: 2024-05-03, 3:00pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "LevelB.h"
#include "Utility.h"

#define LEVEL_WIDTH 39
#define LEVEL_HEIGHT 40


unsigned int LEVEL_B_DATA[] ={
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    464,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,
     16,  9, 10, 51, 52, 10, 10, 10, 10, 10, 10, 10, 10, 57, 58, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 59, 60, 10, 10, 10, 10, 63, 10, 10, 18,
     16, 65, 65, 67, 68, 65, 65, 65, 65, 65, 65, 65, 65, 73, 74, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 75, 76, 65, 65, 65, 65, 65, 65, 65, 18,
     16, 81, 81, 83, 84, 81, 81, 81, 81, 81, 81, 81, 81, 89, 89, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 91, 92, 81, 81, 81, 81, 81, 81, 81, 18,
     16,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 18,
     16,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 18,
     16,  37, 4, 37,  4, 37,  4,  5,  6,  37, 4, 37,  4,  4, 37,  4,  4, 37,  4, 37,  4, 37,  4, 37,  4,  37, 4,  37, 4, 37,  4, 37,  4, 37,  4, 37, 4,  37, 18,
     16,  4, 37,  4,  37,19, 20, 21, 22,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 18,
     16,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 18,
     16,  37, 4, 37,  4, 37,  4, 37,  4,  37, 4, 37,  4,  4, 37,  4,  4, 37,  4, 37,  4, 37,  4, 37,  4,  37, 4,  37, 4, 37,  4, 37,  4, 37,  4, 37, 4,  37, 18,
     16,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 18,
     16,  37, 4, 37,  4, 37,  4, 37,  4,  37, 4, 37,  4,  4, 37,  4,  4, 37,  4, 37,  4, 37,  4, 37,  4,  37, 4,  37, 4, 37,  4, 37,  4, 37,  4, 37, 4,  37, 18,
     16,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 18,
     16,  37, 4, 37,  4, 37,  4, 37,  4,  37, 4, 37,  4,  4, 37,  4,  4, 37,  4, 37,  4, 37,  4, 37,  4,  37, 4,  37, 4, 37,  4, 37,  4, 37,  4, 37, 4,  37, 18,
     16,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 18,
     16,  37, 4, 37,  4, 37,  4, 37,  4,  37, 4, 37,  4,  4, 37,  4,  4, 37,  4, 37,  4, 37,  4, 37,  4,  37, 4,  37, 4, 37,  4, 37,  4, 37,  4, 37, 4,  37, 18,
     16,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 18,
     16,  37, 4, 37,  4, 37,  4, 37,  4,  37, 4, 37,  4,  4, 37,  4,  4, 37,  4, 37,  4, 37,  4, 37,  4,  37, 4,  37, 4, 37,  4, 37,  4, 37,  4, 37, 4,  37, 18,
     16,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 18,
     16,  37, 4, 37,  4, 37,  4, 37,  4,  37, 4, 37,  4,  4, 37,  4,  4, 37,  4, 37,  4, 37,  4, 37,  4,  37, 4,  37, 4, 37,  4, 37,  4, 37,  4, 37, 4,  37, 18,
     16,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 18,
     16,  37, 4, 37,  4, 37,  4, 37,  4,  37, 4, 37,  4,  4, 37,  4,  4, 37,  4, 37,  4, 37,  4, 37,  4,  37, 4,  37, 4, 37,  4, 37,  4, 37,  4, 37, 4,  37, 18,
     16,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 18,
     32, 33, 33, 33, 33, 33, 33, 33, 33, 33,  2, 37,  4,  4, 37,  4,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,464, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16, 37,  4,  4, 37,  4,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16,100, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37, 99, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16,116,  4,  4, 37,  4,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4,115, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16,132, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,131, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16, 37,  4,  4, 37,  4,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16, 37,  4,  4, 37,  4,  4, 37,  4, 37,  4, 37,  4, 37,  5,  6,  4, 37, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 21, 22, 37,  4, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,464,  1,  1,  1,  1,  1,  1,  1,  1, 34, 37,  4,  4, 37,  4,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37, 32,  1,  1,  1,  1,  1,  1,  1,  1,  2,  0,
      0, 16, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37, 18,  0,
      0, 16,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 18,  0,
      0, 16,  37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37, 4, 37, 18,  0,
      0, 16,   4,128,129,130,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 37,  4, 18,  0,
      0, 32, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34,  0
};


LevelB::~LevelB()
{
    delete [] m_state.enemies;
    delete    m_state.gun;
    delete [] m_state.missiles;
    delete    m_state.player;
    delete    m_state.background;
    delete    m_state.map;
    delete    m_state.candle;
    Mix_FreeChunk(m_state.gunshot_sound);
    Mix_FreeChunk(m_state.hit_sound);
    Mix_FreeMusic(m_state.bgm);
}

void LevelB::initialise()
{
    
    GLuint map_texture_id = Utility::load_texture("hospital.png");
    m_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVEL_B_DATA, map_texture_id, 1.0f, 16, 29);
    
    m_state.background = new Entity();
    m_state.background->set_lives(10000);
    m_state.background->set_pos(glm::vec3(18.0f, -13.0f, 0.0f));
    m_state.background->scale(glm::vec3(60.0f, 28.0f, 0.0f));
    m_state.background->m_texture_id = Utility::load_texture("dark_forest.png");
    
    // Existing
    m_state.player = new Entity();
    m_state.player->set_entity_type(PLAYER);
    m_state.player->set_pos(glm::vec3(5.0f, -5.0f, 0.0f));
    m_state.player->set_ortho_position(glm::vec3(0.0f, 0.0f, 0.0f));
    m_state.player->set_movement(glm::vec3(0.0f));
    m_state.player->set_speed(3.0f);
    m_state.player->set_lives(3);
    m_state.player->m_texture_id = Utility::load_texture("girl.png");

    // Walking
    m_state.player->m_walking[m_state.player->LEFT]     = new int[3] {3,4,5};
    m_state.player->m_walking[m_state.player->RIGHT]    = new int[3] {6,7,8};
    m_state.player->m_walking[m_state.player->UP]       = new int[3] {9,10,11};
    m_state.player->m_walking[m_state.player->DOWN]     = new int[3] {0,1,2};

    m_state.player->m_animation_indices = m_state.player->m_walking[m_state.player->DOWN];  // start George looking left
    m_state.player->m_animation_frames = 3;
    m_state.player->m_animation_index = 0;
    m_state.player->m_animation_time = 0.0f;
    m_state.player->m_animation_cols = 3;
    m_state.player->m_animation_rows = 4;
    m_state.player->set_height(1.0f);
    m_state.player->set_width(1.0f);
    m_state.player->scale(glm::vec3(1.0f, 2.0f, 0.0f));
    
    // —————————— ENEMY SET-UP —————————— //
    glm::vec3 m_witch_doctor_positions[] = {glm::vec3(15.0f, -4.0f, 0.0f),glm::vec3(30.0f, -15.0f, 0.0f),
        glm::vec3(2.0f, -20.0f, 0.0f),glm::vec3(25.0f, -35.0f, 0.0f),
    };
    
    m_state.enemies = new Entity[WITCH_DOCTOR_COUNT];

    for (int i = 0; i < WITCH_DOCTOR_COUNT; i++) {
        m_state.enemies[i].set_pos(m_witch_doctor_positions[i]);
        m_state.enemies[i].set_movement(glm::vec3(0.0f));
        m_state.enemies[i].set_speed(3.0f);
        m_state.enemies[i].set_entity_type(ENEMY);
        m_state.enemies[i].set_ai_type(FOLLOWER);
        m_state.enemies[i].set_lives(3);
        m_state.enemies[i].m_texture_id = Utility::load_texture("Witch_Doctor_Move.png");
        
        // Walking
        m_state.enemies[i].m_walking[m_state.enemies[0].LEFT]     = new int[18] {6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10, 11, 11, 11};
        m_state.enemies[i].m_walking[m_state.enemies[0].RIGHT]    = new int[18] {12,12,12,13,13,13,14,14,14,15,15,15,16, 16, 16, 17, 17, 17};
        m_state.enemies[i].m_walking[m_state.enemies[0].UP]    = new int[18] {18, 18, 18, 19, 19, 19, 20, 20, 20, 21, 21, 21, 22, 22, 22, 23, 23, 23};
        m_state.enemies[i].m_walking[m_state.enemies[0].DOWN]    = new int[18] {0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5};
        
        m_state.enemies[i].m_animation_frames = 18;
        m_state.enemies[i].m_animation_index = 0;
        m_state.enemies[i].m_animation_time = 0.0f;
        m_state.enemies[i].m_animation_cols = 6;
        m_state.enemies[i].m_animation_rows = 4;
        m_state.enemies[i].set_height(0.3f);
        m_state.enemies[i].set_width(0.3f);
        m_state.enemies[i].scale(glm::vec3(6.0f, 8.0f, 0.0f));
        m_state.enemies[i].set_ai_state(IDLE_GUARD);
    }
    m_state.enemies[0].m_animation_indices = m_state.enemies[0].m_walking[m_state.enemies[0].DOWN] ;
    m_state.enemies[1].m_animation_indices = m_state.enemies[1].m_walking[m_state.enemies[1].LEFT] ;
    m_state.enemies[2].m_animation_indices = m_state.enemies[2].m_walking[m_state.enemies[2].RIGHT] ;
    m_state.enemies[3].m_animation_indices = m_state.enemies[3].m_walking[m_state.enemies[3].LEFT] ;
    
    
    m_state.bed = new Entity();
    m_state.bed->set_entity_type(BED);
    m_state.bed->m_texture_id = Utility::load_texture("House-bedroom-Sheet.png");
    m_state.bed->set_pos(glm::vec3(35.0f, -35.0f, 0.0f));
    m_state.bed->scale(glm::vec3(3.0f, 3.0f, 1.0f));


    
    // —————————— BOW SET-UP —————————— //
    m_state.gun = new Entity();
    m_state.gun->set_entity_type(GUN);
    m_state.gun->set_missile(0);
    m_state.gun->scale(glm::vec3(5.0f, 4.0f, 0.0f));
    m_state.gun->m_texture_id = Utility::load_texture("beam rifle.png");
    m_state.gun->deactivate();
    
    m_state.candle = new Entity();
    m_state.candle->set_entity_type(CANDLE);
    m_state.candle->scale(glm::vec3(1.0f, 2.0f, 0.0f));
    m_state.candle->m_texture_id = Utility::load_texture("candle.png");
    int* candle_animation = new int[3] {0, 1, 2};
    
    m_state.candle->m_animation_frames = 3;
    m_state.candle->m_animation_index = 0;
    m_state.candle->m_animation_time = 0.0f;
    m_state.candle->m_animation_cols = 3;
    m_state.candle->m_animation_rows = 1;
    m_state.candle->set_height(1.0f);
    m_state.candle->set_width(1.0f);
    m_state.candle->scale(glm::vec3(1.0f, 1.0f, 0.0f));
    m_state.candle->m_animation_indices = candle_animation;
    
    
    // —————————— ARROWS SET-UP —————————— //
    m_state.missiles = new Entity[MISSILE_COUNT];

    for (int i = 0; i < MISSILE_COUNT; i++) {
        m_state.missiles[i].set_speed(7.5f);
        m_state.missiles[i].set_acceleration(glm::vec3(0.0f, -3.0f, 0.0f));
        m_state.missiles[i].set_entity_type(MISSILE);
        m_state.missiles[i].scale(glm::vec3(0.5f, 1.5f, 0.0f));
        m_state.missiles[i].m_texture_id = Utility::load_texture("missile.png");
        m_state.missiles[i].deactivate();
    }

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    m_state.bgm = Mix_LoadMUS("scarymusic.mp3");
    Mix_PlayMusic(m_state.bgm, -1);
    Mix_VolumeMusic(5.0f);
    
    m_state.gunshot_sound = Mix_LoadWAV("gunshot.wav");
    m_state.hit_sound = Mix_LoadWAV("blood.wav");
}

void LevelB::update(float delta_time)
{
    if (m_state.player->get_lives() <= 0) return;
        
    m_state.background->set_pos(glm::vec3(m_state.player->get_position().x, m_state.player->get_position().y, 0));
    m_state.background->update(0.0f, m_state.background, NULL, 0, m_state.map);
    
    m_state.player->update(delta_time, m_state.player, m_state.enemies, WITCH_DOCTOR_COUNT, m_state.map);
    if (m_state.player->m_is_hit == true) {
        Mix_PlayChannel(-1, m_state.hit_sound, 0);
        m_state.player->m_is_hit = false;
    }
    
    m_state.gun->set_pos(glm::vec3(m_state.player->get_position().x, m_state.player->get_position().y, 0.0f));
    m_state.gun->update(0.0f, m_state.gun, NULL, 0, m_state.map);
    
    m_state.candle->set_pos(glm::vec3(m_state.player->get_position().x-0.4f, m_state.player->get_position().y - 0.5f, 0.0f));
    m_state.candle->update(delta_time, m_state.candle, NULL, 0, m_state.map);

    m_state.bed->update(delta_time, m_state.bed, NULL, 0, m_state.map);
    
    for (int i = 0; i < MISSILE_COUNT; i++)
    {
        m_state.missiles[i].update(delta_time, m_state.player, m_state.enemies, WITCH_DOCTOR_COUNT, m_state.map);
    }
    

    for (int i = 0; i < WITCH_DOCTOR_COUNT; i++)
    {
        if (m_state.enemies[i].m_is_hit == true) {
            Mix_PlayChannel(-1, m_state.hit_sound, 0);
            m_state.enemies[i].m_is_hit = false;
        }
        m_state.enemies[i].update(delta_time, m_state.player, NULL, NULL, m_state.map);
    }
    if (this->m_state.player->check_collision(m_state.bed)){
        m_state.next_scene_id = 2;
        }

}


void LevelB::render(ShaderProgram *program)
{
    GLuint m_font = Utility::load_texture("font2.png");
    glClearColor(0, 0, 0, 0);
    
    if (m_state.player->get_lives() <= 0) {
        m_state.background->render(program);
        Utility::draw_text(program, m_font, std::string("you're dead"),
                  2.0f, -0.8f, glm::vec3(m_state.player->get_position().x - 6.0, m_state.player->get_position().y, 0));
    } else {
        m_state.map->render(program);
        m_state.bed->render(program);
        m_state.player->render(program);
        m_state.candle->render(program);
        m_state.gun->render(program);
        
        for (int i = 0; i < MISSILE_COUNT; i++)
        {
            m_state.missiles[i].render(program);
        }
                
        for (int i = 0; i < WITCH_DOCTOR_COUNT; i++)
        {
            m_state.enemies[i].render(program);
        }
        if (m_state.player->get_lives()==3){
            Utility::draw_text(program, m_font, std::string("wait. where am i??"),
                      0.7f, -0.1f, glm::vec3(m_state.player->get_position().x, m_state.player->get_position().y + 2.0f, 0));
        }
        
        if (m_state.player->get_lives()==2){
            Utility::draw_text(program, m_font, std::string("i have to go back to bed.."),
                               0.7f, -0.1f, glm::vec3(m_state.player->get_position().x, m_state.player->get_position().y + 2.0f, 0));
        }
        if (m_state.player->get_lives()==1){
            Utility::draw_text(program, m_font, std::string("THIS CAN'T BE REAL"),
                               0.7f, -0.1f, glm::vec3(m_state.player->get_position().x, m_state.player->get_position().y + 2.0f, 0));
        }
    }
}
