/**
* Author: Nabira Ahmad
* Assignment:  Escape your nightmare
* Date due: 2024-05-03, 3:00pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/
#include "LevelA.h"
#include "Utility.h"

#define LEVEL_WIDTH 27
#define LEVEL_HEIGHT 63

unsigned int LEVEL_A_DATA[] ={
    0, 0, 0, 0, 0, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,
    0, 0, 0, 0, 0, 24,25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,
    11,12,12,13,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,14,14,14,14,14,15,0,
    59,30,29,46,30,29,30,46,30,29,46,30,29,30,46,30,29,46,30,29,30,29,30,29,46,63,0,
    59,30,29,46,30,29,30,46,30,29,46,30,29,30,46,30,29,46,30,29,30,29,30,29,46,63,0,
    59,30,29,46,30,11,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,14,63,0,
    59,30,29,46,30,27,60,60,61,60,61,60,61,60,61,60,61,60,61,60,61,60,61,60,63,63,0,
    59,30,29,46,30,43,60,60,61,60,61,60,61,60,61,60,61,60,61,60,61,60,61,60,63,63,0,
    59,30,29,46,30,59,60,60,61,60,61,60,61,60,61,60,61,60,61,60,61,60,61,60,63,63,0,
    59,30,29,46,30,75,76,76,76,76,76,76,76,76,77,77,76,76,76,76,76,76,76,76,79,63,0,
    59,30,29,46,30,29,30,46,72,0, 6, 7, 0, 0,77,77, 0, 0, 0, 0, 0,74,30,29,46,63, 0,
    59,30,29,46,30,29,30,46,72, 0,22,23,0, 0,77,77, 0, 0, 0, 0, 0,74,30,29,46,63, 0,
    59,30,29,46,30,29,30,46,72, 0, 0, 0, 0, 0,77,77, 0, 0, 0, 0, 0,74,30,29,46,63,0,
    59,30,29,46,30,29,30,46,72,0, 0, 0, 0, 0,77,77, 0, 0, 0, 0, 0,74,30,29,46,63,0,
    59,30,29,46,30,29,30,46,72,0, 0, 0, 0, 0,77,77, 0, 0, 0, 0, 0,74,30,29,46,63,0,
    59,30,29,46,30,29,30,46,72,0, 0, 0, 0, 0,77,77, 0, 0, 0, 0, 0,74,30,29,46,63,0,
    59,30,29,46,30,29,30,46,72,0, 0, 0, 0, 0,77,77, 0, 0, 0, 0, 0,74,30,29,46,63,0,
    59,30,29,46,30,29,30,46,72,0, 0, 0, 0, 0,77,77, 0, 0, 0, 0, 0,74,30,29,46,63,0,
    59,30,29,46,30,29,30,46,72,0, 0, 0, 0, 0,77,77, 0, 0, 0,68, 0,74,30,29,46,63,0,
    59,30,29,46,30,29,30,46,72,0, 0, 0, 0, 0,77,77, 0, 0, 0,84, 0,74,30,29,46,63,0,
    59,30,29,46,30,29,30,46,72,0, 0, 0, 0, 0,77,77, 0, 0, 0, 0, 0,74,30,29,46,63,0,
    59,30,29,46,30,29,30,46,88,89,89,89,89,89,77,77,89,89,89,89,89,90,30,29,46,63,0,
    59,30,29,46,30,29,30,46,30,29,46,30,29,30,46,30,29,46,30,29,30,29,30,29,46,63,0,
    59,30,29,46,30,29,30,46,30,29,46,30,29,30,46,30,29,46,30,29,30,29,30,29,46,63,0,
    59,30,29,46,30,29,30,46,30,29,46,30,29,30,46,30,29,46,30,29,30,29,30,29,46,63,0,
    59,30,30,30,91,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,93,63,0,
    59,30,29,46,30,29,30,46,30,29,46,30,29,30,46,30,29,46,30,29,30,29,30,29,46,63,0,
    59,30,29,46,30,29,30,46,30,29,46,30,29,30,46,30,29,46,30,29,30,29,30,29,46,63,0,
    59,30,29,46,30,29,30,46,30,29,46,30,29,30,46,30,29,46,30,29,30,29,30,29,46,63,0,
    59,91,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,93,29,46,63,0,
    59,30,29,46,30,29,30,46,30,29,46,30,29,30,46,30,29,46,30,29,30,29,30,29,46,63,0,
    59,30,29,46,30,29,30,46,30,29,46,30,29,30,46,30,29,46,30,29,30,29,30,29,46,63,0,
    59,30,29,46,30,29,30,46,30,29,46,30,29,30,46,30,29,46,30,29,30,29,30,29,46,63,0,
    59,30,29,46,30,29,30,46,30,29,46,30,29,30,46,30,29,46,30,29,30,29,30,29,46,63,0,
    59,30,91,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,93,29,30,63,0,
    59,30,29,46,30,29,30,46,30,29,46,30,29,30,46,30,29,46,30,29,30,29,30,29,46,63,0,
    59,30,29,46,30,29,30,46,30,29,46,30,29,30,46,30,29,46,30,29,30,29,30,29,46,63,0,
    59,30,29,46,30,29,30,46,30,29,46,30,29,30,46,30,29,46,30,29,30,29,30,29,46,63,0,
    59,91,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,93,30,29,46,63,0,
    59,30,29,46,30,29,30,46,30,29,46,30,29,30,46,30,29,46,30,29,30,29,30,29,46,63,0,
    59,30,29,11,12,12,13,14,14,14,14,14,14,14,15,30,29,46,30,29,30,29,30,29,46,63,0,
    59,30,29,27,45,44,45,44,45,44,44,44,45,44,31,30,29,46,30,29,30,29,30,29,46,63,0,
    59,30,29,27,44,45,44,45,45,44,45,45,44,45,31,30,29,46,30,29,30,29,30,29,46,63,0,
    59,91,92,27,45,44,45,44,44,45,44,44,45,44,31,92,92,92,92,92,92,92,92,92,93,63,0,
    59,96,96,59,60,60,60,45,44,45,44,45,44,45,31,96,96,96,96,96,96,96,96,96,96,63,0,
    59,96,96,75,76,76,76,76,77,78,78,78,78,78,79,96,96,96,96,96,96,96,96,96,96,63,0,
    59,96,96,96,96,74,30,46,30,29,46,72,96,96,96,96,96,96,96,96,96,96,96,96,96,63,0,
    59,96,96,96,96,74,30,46,30,29,46,72,96,96,96,96,96,96,96,96,96,96,96,96,96,63,0,
    59,96,96,96,96,74,30,46,30,29,46,72,96,96,96,96,96,96,96,96,96,96,96,96,96,63,0,
    59,96,96,96,96,74,30,46,30,29,46,72,96,96,96,96,96,96,96,96,96,96,96,96,96,63,0,
    59,96,96,96,96,74,30,46,30,29,46,72,96,96,96,96,96,96,96,96,96,96,96,96,96,63,0,
    59,96,96,96,96,74,30,46,30,29,46,72,96,96,96,96,96,96,96,96,96,96,96,96,96,63,0,
    59,96,96,96,96,74,30,46,30,29,46,72,96,96,96,96,96,96,96,96,96,96,96,96,96,63,0,
    59,96,96,96,96,74,30,46,30,29,46,72,96,96,96,96,96,96,96,96,96,96,96,96,96,63,0,
    59,96,96,96,96,74,30,46,30,29,46,72,96,96,96,96,96,96,96,96,96,96,96,96,96,63,0,
    59,96,96,96,96,74,30,46,30,29,46,72,96,96,96,96,96,96,96,96,96,96,96,96,96,63,0,
    59,96,96,96,96,74,30,46,30,29,46,72,96,96,96,96,11,12,12,14,14,14,14,14,15,63,0,
    59,96,96,96,96,74,30,46,30,29,46,72,96,96,96,96,27,46,30,29,94,94,94,94,94,63,0,
    59,96,96,96,96,74,30,46,30,29,91,92,92,92,92,92,92,93,30,29,30,29,30,29,46,63,10,
    59,96,96,96,96,74,30,46,30,29,46,72,96,96,96,96,43,46,30,29,30,29,30,29,46,63,0,
    59,96,96,96,96,86,57,57,57,57,57,87,96,96,96,96,27,46,30,29,30,29,30,29,46,63,0,
    59,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,59,46,30,29,94,94,94,94,94,63,10,
    75,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,79,0
};

//const char V_SHADER_PATH[] = "shaders/vertex_lit.glsl",
//           F_SHADER_PATH[] = "shaders/fragment_lit.glsl";

LevelA::~LevelA()
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

void LevelA::initialise()
{
    GLuint m_font = Utility::load_texture("font2.png");
    GLuint map_texture_id = Utility::load_texture("grave_tileset.png");
    m_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVEL_A_DATA, map_texture_id, 1.5f, 16, 7);
    
    m_state.background = new Entity();
    m_state.background->set_lives(10000);
    m_state.background->set_pos(glm::vec3(18.0f, -13.0f, 0.0f));
    m_state.background->scale(glm::vec3(60.0f, 28.0f, 0.0f));
    m_state.background->m_texture_id = Utility::load_texture("dark_forest.png");
    
    m_state.player = new Entity();
    m_state.player->set_entity_type(PLAYER);
    m_state.player->set_pos(glm::vec3(5.0f, -5.0f, 0.0f));
    m_state.player->set_ortho_position(glm::vec3(0.0f, 0.0f, 0.0f));
    m_state.player->set_movement(glm::vec3(0.0f));
    m_state.player->set_speed(5.0f);
    m_state.player->set_lives(3);
    m_state.player->m_texture_id = Utility::load_texture("girl.png");

    m_state.player->m_walking[m_state.player->LEFT]     = new int[3] {3,4,5};
    m_state.player->m_walking[m_state.player->RIGHT]    = new int[3] {6,7,8};
    m_state.player->m_walking[m_state.player->UP]       = new int[3] {9,10,11};
    m_state.player->m_walking[m_state.player->DOWN]     = new int[3] {0,1,2};

    m_state.player->m_animation_indices = m_state.player->m_walking[m_state.player->DOWN];
    m_state.player->m_animation_frames = 3;
    m_state.player->m_animation_index = 0;
    m_state.player->m_animation_time = 0.0f;
    m_state.player->m_animation_cols = 3;
    m_state.player->m_animation_rows = 4;
    m_state.player->set_height(1.0f);
    m_state.player->set_width(1.0f);
    m_state.player->scale(glm::vec3(1.0f, 2.0f, 0.0f));
    
    glm::vec3 m_skeleton_positions[] = {glm::vec3(15.0f, -4.0f, 0.0f),glm::vec3(14.0f, -29.0f, 0.0f),
        glm::vec3(2.0f, -40.0f, 0.0f),glm::vec3(18.0f, -55.0f, 0.0f), glm::vec3(36.0f, -62.0f, 0.0f), glm::vec3(10.0f, -88.0f, 0.0f)
    };
    
    m_state.enemies = new Entity[SKELETON_COUNT];

    for (int i = 0; i < SKELETON_COUNT; i++) {
        m_state.enemies[i].set_pos(m_skeleton_positions[i]);
        m_state.enemies[i].set_movement(glm::vec3(0.0f));
        m_state.enemies[i].set_speed(5.0f);
        m_state.enemies[i].set_entity_type(ENEMY);
        m_state.enemies[i].set_ai_type(FOLLOWER);
        m_state.enemies[i].set_lives(2);
        m_state.enemies[i].m_texture_id = Utility::load_texture("Skeleton_Move.png");
        
        // Walking
        m_state.enemies[i].m_walking[m_state.enemies[0].LEFT]     = new int[18] {6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10, 11, 11, 11};
        m_state.enemies[i].m_walking[m_state.enemies[0].RIGHT]    = new int[18] {12,12,12,13,13,13,14,14,14,15,15,15,16, 16, 16, 17, 17, 17};
        m_state.enemies[i].m_walking[m_state.enemies[0].UP]    = new int[18] {18, 18, 18, 19, 19, 19, 20, 20, 20, 21, 21, 21, 22, 22, 22, 23, 23, 23};
        m_state.enemies[i].m_walking[m_state.enemies[0].DOWN]    = new int[18] {0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5};
        
        m_state.enemies[i].m_animation_indices = m_state.enemies[0].m_walking[m_state.enemies[0].DOWN] ;
        m_state.enemies[i].m_animation_frames = 18;
        m_state.enemies[i].m_animation_index = 0;
        m_state.enemies[i].m_animation_time = 0.0f;
        m_state.enemies[i].m_animation_cols = 6;
        m_state.enemies[i].m_animation_rows = 4;
        m_state.enemies[i].set_height(0.3f);
        m_state.enemies[i].set_width(0.3f);
        m_state.enemies[i].scale(glm::vec3(6.0f, 9.0f, 0.0f));
    }
    m_state.enemies[0].set_ai_state(IDLE_GUARD);
    m_state.enemies[0].m_animation_indices = m_state.enemies[0].m_walking[m_state.enemies[0].LEFT] ;
    
    m_state.enemies[1].set_ai_state(IDLE_GUARD);
    m_state.enemies[1].m_animation_indices = m_state.enemies[1].m_walking[m_state.enemies[1].UP] ;
    
    m_state.enemies[2].set_ai_state(IDLE);
    m_state.enemies[2].m_animation_indices = m_state.enemies[2].m_walking[m_state.enemies[2].RIGHT] ;
    
    m_state.enemies[3].set_ai_state(IDLE);
    m_state.enemies[3].m_animation_indices = m_state.enemies[3].m_walking[m_state.enemies[3].LEFT] ;
    
    m_state.enemies[4].set_ai_state(IDLE);
    m_state.enemies[4].m_animation_indices = m_state.enemies[4].m_walking[m_state.enemies[4].LEFT] ;
    
    m_state.enemies[5].set_ai_state(IDLE);
    m_state.enemies[5].m_animation_indices = m_state.enemies[5].m_walking[m_state.enemies[5].UP] ;
    
    m_state.bed = new Entity();
    m_state.bed->set_entity_type(BED);
    m_state.bed->m_texture_id = Utility::load_texture("House-bedroom-Sheet.png");
    m_state.bed->set_pos(glm::vec3(35.0f, -88.0f, 0.0f));

    m_state.bed->scale(glm::vec3(3.0f, 3.0f, 1.0f));

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
    Mix_VolumeMusic(8.0f);
    
    m_state.gunshot_sound = Mix_LoadWAV("gunshot.wav");
    m_state.hit_sound = Mix_LoadWAV("blood.wav");
}

void LevelA::update(float delta_time)
{
    if (m_state.player->get_lives() <= 0) return;
        
    m_state.background->set_pos(glm::vec3(m_state.player->get_position().x, m_state.player->get_position().y, 0));
    m_state.background->update(0.0f, m_state.background, NULL, 0, m_state.map);
    
    m_state.player->update(delta_time, m_state.player, m_state.enemies, SKELETON_COUNT, m_state.map);
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
        m_state.missiles[i].update(delta_time, m_state.player, m_state.enemies, SKELETON_COUNT, m_state.map);
    }

    for (int i = 0; i < SKELETON_COUNT; i++)
    {
        if (m_state.enemies[i].m_is_hit == true) {
            Mix_PlayChannel(-1, m_state.hit_sound, 0);
            m_state.enemies[i].m_is_hit = false;
        }
        m_state.enemies[i].update(delta_time, m_state.player, NULL, NULL, m_state.map);
    }
    if (this->m_state.player->check_collision(m_state.bed)){
        m_state.next_scene_id = 1;
        }
  
    if (m_state.player->get_position().x < -1.0f or m_state.player->get_position().x > 39.0f
        or m_state.player->get_position().y> -1.5f or m_state.player->get_position().y< -93.0f) {
        m_state.player->set_lives(0);
    }

}


void LevelA::render(ShaderProgram *program)
{
    glClearColor(0, 0, 0, 0);
    GLuint m_font = Utility::load_texture("font2.png");
    
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
                
        for (int i = 0; i < SKELETON_COUNT; i++)
        {
            m_state.enemies[i].render(program);
        }
        if (m_state.player->get_lives()==3){
            Utility::draw_text(program, m_font, std::string("where's my bed?"),
                      0.7f, -0.1f, glm::vec3(m_state.player->get_position().x, m_state.player->get_position().y + 2.0f, 0));
        }
        
        if (m_state.player->get_lives()==2){
            Utility::draw_text(program, m_font, std::string("this is just a dream."),
                               0.7f, -0.1f, glm::vec3(m_state.player->get_position().x, m_state.player->get_position().y + 2.0f, 0));
        }
        if (m_state.player->get_lives()==1){
            Utility::draw_text(program, m_font, std::string("I NEED TO WAKE UP!"),
                               0.7f, -0.1f, glm::vec3(m_state.player->get_position().x, m_state.player->get_position().y + 2.0f, 0));
        }
    }
}
