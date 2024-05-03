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
#define GL_GLEXT_PROTOTYPES 1
#define FIXED_TIMESTEP 0.0166666f
#define LEVELA_WIDTH 14
#define LEVELA_HEIGHT 8
#define LEVELA_LEFT_EDGE 18.0f

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "cmath"
#include <ctime>
#include <vector>
#include "Utility.h"
#include "Scene.h"
#include "Menu.h"
#include "LevelA.h"
#include "LevelB.h"
#include "LevelC.h"
#include "Effects.h"

// ————— CONSTANTS ————— //
const int WINDOW_WIDTH  = 640 * 1.5,
          WINDOW_HEIGHT = 480 * 1.5;

// ————— MOUSE POLLING ————— //
enum Coordinate { x_coordinate, y_coordinate };

int x, y;

const Coordinate X_COORDINATE = x_coordinate;
const Coordinate Y_COORDINATE = y_coordinate;
Effects *g_effects;

float ORTHO_WIDTH  = 7.5f * 3.5,
      ORTHO_HEIGHT = 10.0f * 3.5;

const float BG_RED     = 0.1922f,
            BG_BLUE    = 0.549f,
            BG_GREEN   = 0.9059f,
            BG_OPACITY = 1.0f;

const int VIEWPORT_X = 0,
          VIEWPORT_Y = 0,
          VIEWPORT_WIDTH  = WINDOW_WIDTH,
          VIEWPORT_HEIGHT = WINDOW_HEIGHT;

const char V_SHADER_PATH[] = "shaders/vertex_textured.glsl",
           F_SHADER_PATH[] = "shaders/fragment_textured.glsl";

const char   V_SHADER_PATH1[] = "shaders/vertex_lit.glsl",
             F_SHADER_PATH1[] = "shaders/fragment_lit.glsl";

const float MILLISECONDS_IN_SECOND = 1000.0;

// ————— GLOBAL VARIABLES ————— //
Scene  *g_current_scene;
Menu   *g_menu;
LevelA *g_level_a;
LevelB *g_level_b;
LevelC *g_level_c;
Scene  *g_levels[3];

SDL_Window* g_display_window;
bool g_game_is_running = true;

ShaderProgram g_shader_program;
glm::mat4 g_view_matrix, g_projection_matrix;

float g_previous_ticks = 0.0f;
float g_accumulator = 0.0f;

int g_player_lives = 3;

float get_screen_to_ortho(float coordinate, Coordinate axis)
{
    switch(axis)
    {
        case x_coordinate: return ((coordinate / WINDOW_WIDTH) * ORTHO_WIDTH) - (ORTHO_WIDTH / 2.0);
        case y_coordinate: return (((WINDOW_HEIGHT - coordinate) / WINDOW_HEIGHT) * ORTHO_HEIGHT) - (ORTHO_HEIGHT / 2.0);
        default          : return 0.0f;
    }
}

void switch_to_scene(Scene *scene)
{
    g_current_scene = scene;
    g_current_scene->initialise();
}

void initialise()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    g_display_window = SDL_CreateWindow("escape your nightmare",
                                      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                      WINDOW_WIDTH, WINDOW_HEIGHT,
                                      SDL_WINDOW_OPENGL);
    
    SDL_GLContext context = SDL_GL_CreateContext(g_display_window);
    SDL_GL_MakeCurrent(g_display_window, context);
    
#ifdef _WINDOWS
    glewInit();
#endif
    glViewport(VIEWPORT_X, VIEWPORT_Y, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
    g_shader_program.load(V_SHADER_PATH, F_SHADER_PATH);

    g_view_matrix = glm::mat4(1.0f);
    g_projection_matrix = glm::ortho(-5.0f * 3.5, 5.0f * 3.5, -3.75f * 3.5, 3.75f * 3.5, -1.0f * 3.5, 1.0f * 3.5);

    g_shader_program.set_projection_matrix(g_projection_matrix);
    g_shader_program.set_view_matrix(g_view_matrix);
    
    glUseProgram(g_shader_program.get_program_id());
    
    glClearColor(BG_RED, BG_BLUE, BG_GREEN, BG_OPACITY);
    
    g_menu = new Menu();
    g_level_a = new LevelA();
    g_level_b = new LevelB();
    g_level_c = new LevelC();
    
    g_levels[0] = g_level_a;
    g_levels[1] = g_level_b;
    g_levels[2] = g_level_c;

    switch_to_scene(g_menu);
    g_effects = new Effects(g_projection_matrix, g_view_matrix);
    // ————— BLENDING ————— //
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
}

void process_input()
{
    g_current_scene->m_state.player->set_movement(glm::vec3(0.0f));
    
    SDL_Event event;
    
    while (SDL_PollEvent(&event))
    {
        switch (event.type) {
            case SDL_QUIT:
            case SDL_WINDOWEVENT_CLOSE:
                g_game_is_running  = false;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT && g_current_scene != g_menu){
                    SDL_GetMouseState(&x, &y);
                    g_current_scene->m_state.gun->set_missile(g_current_scene->m_state.gun->get_missile() + 1);
                    g_current_scene->m_state.gun->position_gun(get_screen_to_ortho(x, x_coordinate), get_screen_to_ortho(y, y_coordinate));
                    g_current_scene->m_state.gun->activate();
                    g_current_scene->m_state.missiles[g_current_scene->m_state.gun->get_missile()].set_pos(g_current_scene->m_state.player->get_position());
                    g_current_scene->m_state.missiles[g_current_scene->m_state.gun->get_missile()].missile_velocity(get_screen_to_ortho(x,x_coordinate),
                                                                                                                  get_screen_to_ortho(y, y_coordinate));
                    g_current_scene->m_state.missiles[g_current_scene->m_state.gun->get_missile()].activate();
                    Mix_PlayChannel(-1, g_current_scene->m_state.gunshot_sound, 0);
                }
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_q:
                        // Quit the game with a keystroke
                        g_game_is_running  = false;
                        break;
                            
                    case SDLK_RETURN:
                        if (g_current_scene == g_menu) {
                            switch_to_scene(g_level_a);
                        }
                        break;

                    default:
                        break;
                    }

            default:
                break;
            }
    }

    const Uint8* key_state = SDL_GetKeyboardState(NULL);
    
    
    if (key_state[SDL_SCANCODE_LEFT])
    {
        g_current_scene->m_state.player->move_left();
        g_current_scene->m_state.player->m_animation_indices = g_current_scene->m_state.player->m_walking[g_current_scene->m_state.player->LEFT];
    }
    else if (key_state[SDL_SCANCODE_RIGHT])
    {
        g_current_scene->m_state.player->move_right();
        g_current_scene->m_state.player->m_animation_indices = g_current_scene->m_state.player->m_walking[g_current_scene->m_state.player->RIGHT];
    }
    else if (key_state[SDL_SCANCODE_UP])
    {
        g_current_scene->m_state.player->move_up();
        g_current_scene->m_state.player->m_animation_indices = g_current_scene->m_state.player->m_walking[g_current_scene->m_state.player->UP];
    }
    else if (key_state[SDL_SCANCODE_DOWN])
    {
        g_current_scene->m_state.player->move_down();
        g_current_scene->m_state.player->m_animation_indices = g_current_scene->m_state.player->m_walking[g_current_scene->m_state.player->DOWN];
    }

    if (glm::length(g_current_scene->m_state.player->get_movement()) > 1.0f)
    {
        g_current_scene->m_state.player->set_movement(glm::normalize(g_current_scene->m_state.player->get_movement()));
    }
}

void update()
{
    float ticks = (float)SDL_GetTicks() / MILLISECONDS_IN_SECOND;
    float delta_time = ticks - g_previous_ticks;
    g_previous_ticks = ticks;
    
    delta_time += g_accumulator;
    
    if (delta_time < FIXED_TIMESTEP)
    {
        g_accumulator = delta_time;
        return;
    }
    
    while (delta_time >= FIXED_TIMESTEP) {
        g_current_scene->update(FIXED_TIMESTEP);
        delta_time -= FIXED_TIMESTEP;
    }
    g_effects->update(FIXED_TIMESTEP);
    g_accumulator = delta_time;
    
    if (g_current_scene == g_menu) {
        return;
    }
    
    g_view_matrix = glm::mat4(1.0f);
    g_view_matrix = glm::translate(g_view_matrix, glm::vec3(-g_current_scene->m_state.player->get_position().x, -g_current_scene->m_state.player->get_position().y, 0));
       
    g_player_lives = g_current_scene->m_state.player->get_lives();
    g_view_matrix = glm::translate(g_view_matrix, g_effects->m_view_offset);
    g_shader_program.set_light_position(g_current_scene->m_state.player->get_position());
}

void render()
{
    g_shader_program.set_view_matrix(g_view_matrix);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(g_shader_program.get_program_id());
    g_current_scene->render(&g_shader_program);
    g_effects->render();
        
    SDL_GL_SwapWindow(g_display_window);
}

void shutdown()
{
    SDL_Quit();
    
    delete g_level_c;
    delete g_level_b;
    delete g_level_a;
    delete g_menu;
    delete g_effects;
}

int main(int argc, char* argv[])
{
    initialise();
    
    while (g_game_is_running)
    {
        process_input();
        update();
        
        if (g_current_scene->m_state.next_scene_id > 0) {
            switch_to_scene(g_levels[g_current_scene->m_state.next_scene_id]);
            g_current_scene->m_state.player->set_lives(g_player_lives);
        }
        render();
    }
    
    shutdown();
    return 0;
}
