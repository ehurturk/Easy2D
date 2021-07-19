#include <iostream>
#include "Easy2D/shader.h"
#include "Easy2D/sprite.h"
#include "Easy2D/texture.h"

#define EZ_DEBUG_ENABLED
#include <Easy2D/easy2d.h>

void init();
void update();
void destroy();

EZApplication *app;
EZSprite *sprite;
EZShader *shader;
EZTexture *tex1;

int main() {
    /* First of all, you need to create an application to bind your 3 main functions (init, update, destroy) to Easy2D */
    app = ezCreateApplication();
    /* After creating the application, you need to register it to Easy2D */
    ezRegisterAsApplication(app);
    /* The bind the functions */
    ezBindAppInitCallback(init);
    ezBindAppUpdateCallback(update);
    ezBindAppDestroyCallback(destroy);
    ezStart();

    return 0;
}

void init() {

    app->window = ezCreateWindow("Easy2DSandbox", 800, 600);

    sprite = ezSquareSprite();

    /* There are 2 ways to create the shader pipeline.
        * First one is a sequential pipeline, which you add shaders as you go - like tunnels:

            shader = ezSequentialShaderPipeline();
            ezAddToShaderPipeline(shader, EZ_VERTEX_SHADER, "../res/simple.vs");
            ezAddToShaderPipeline(shader, EZ_FRAGMENT_SHADER, "../res/simple.fs");
            ezFinishShaderPipeline(shader);

        * The second one is the direct pipeline, which you specify the shaders all at once.

            shader = ezDirectShaderPipeline(2, (EZShaderInfo){.type = EZ_VERTEX_SHADER, .src = "../res/simple.vs"},
                                            (EZShaderInfo{.type = EZ_FRAGMENT_SHADER, .src = "../res/simple.fs"}));
            ezSetSpriteShader(sprite, shader);

        * There are no techinical differences, in the end they all do construct the same pipeline, but the process is just a bit different
        * and it was fun to make these functions.

    */
    shader = ezDirectShaderPipeline(2, (EZShaderInfo){.type = EZ_VERTEX_SHADER, .src = "../res/simple.vs"},
                                    (EZShaderInfo{.type = EZ_FRAGMENT_SHADER, .src = "../res/simple.fs"}));
    ezSetSpriteShader(sprite, shader);

    /* Note when setting different textures for sprites:
       * Max numbers of unique active textures at once depends on your hardware. Therefore, each sprite can have limited number of different textures at once.
       * Thereby, each sprite has a texture array containing every texture that is bound.
    */
    tex1 = ezLoadTexture("../res/barack.jpeg"); /* load the texture */
    ezSetSpriteTexture(sprite, tex1); /* set sprite texture */

}

void update() {
    /* Here goes the game loop - a simple one */
    while (!ezIsWindowOpen(app->window)) {
        ezClearFrame();         /* necessary for dynamic objects, otherwise the previous frame would be on top of the previous frames */
        ezRenderSprite(sprite); /* render the sprite */
        ezUpdateWindow(app->window); /* update the window to swap buffers (double buffering) and handle window events */
    }
}

void destroy() {
    ezFreeApp(app);          /* deallocate the app */
    ezReleaseSprite(sprite); /* deallocate the resources used by the sprite */
}
