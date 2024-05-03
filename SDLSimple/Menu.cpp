/**
* Author: Nabira Ahmad
* Assignment:  Escape your nightmare
* Date due: 2024-05-03, 3:00pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/
#include "Menu.h"
#include "Utility.h"

#define MENU_WIDTH 1
#define MENU_HEIGHT 1

unsigned int MENU_DATA[] = {0};

GLuint m_font_texture_id;

Menu::~Menu()
{
    delete [] m_state.enemies;
    delete    m_state.gun;
    delete [] m_state.missiles;
    delete    m_state.player;
    delete    m_state.background;
    delete    m_state.map;
    Mix_FreeChunk(m_state.gunshot_sound);
    Mix_FreeChunk(m_state.hit_sound);
    Mix_FreeMusic(m_state.bgm);
}

void Menu::initialise()
{
    // change all these variable names
    GLuint map_texture_id = Utility::load_texture("alien_tileset.png");
    m_state.map = new Map(MENU_WIDTH, MENU_HEIGHT, MENU_DATA, map_texture_id, 1.0f, 4, 1);
    

    m_state.background = new Entity();
    m_state.background->set_pos(glm::vec3(0.0f, 0.0f, 0.0f));
    m_state.background->scale(glm::vec3(60.0f, 28.0f, 0.0f));
    m_state.background->m_texture_id = Utility::load_texture("dark_forest.png");
    m_state.background->update(0.0f, m_state.background, NULL, 0, m_state.map);
    
    m_state.title = new Entity();
    m_state.title->set_pos(glm::vec3(0.0f, 0.0f, 0.0f));
    m_state.title->scale(glm::vec3(100.0f, 50.0f, 0.0f));
    m_state.title->m_texture_id = Utility::load_texture("escape_nightmare.png");
    m_state.title->update(0.0f, m_state.title, NULL, 0, m_state.map);
    
    m_state.player = new Entity();

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_state.bgm = Mix_LoadMUS("music_box.mp3");
    Mix_VolumeMusic(MIX_MAX_VOLUME/4);
    Mix_PlayMusic(m_state.bgm, -1);
}

void Menu::update(float delta_time){}

void Menu::render(ShaderProgram *program)
{
    m_state.map->render(program);
    m_state.background->render(program);
    m_state.title->render(program);
}
