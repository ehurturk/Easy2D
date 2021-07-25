#include <iostream>

#include <Easy2D/easy2d.h>
#define EZ_DEBUG_ENABLED

void init();
void update();
void destroy();

EZApplication *app;
EZScene *scene;

int main() {
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
    app->window   = ezCreateWindow("Easy2DSandbox", 800, 600);
    scene         = ezCreateScene();
    EZCamera *cam = ezCreateCamera(EZ_ORTHOGRAPHIC);
    ezAddToScene(scene, (void *)cam, EZ_CAMERA);

    /* Create a sprite with default shader which implements proj and model matrices by default */
    EZSprite *sprite = ezSquareSprite();

    /* Create shaders & texture - and bind them to the sprite */

    /*
    EZShader *shader      = ezDirectShaderPipeline(2, (EZShaderInfo){.type = EZ_VERTEX_SHADER, .src = "../res/simple.vs"},
                                    (EZShaderInfo{.type = EZ_FRAGMENT_SHADER, .src = "../res/simple.fs"}));
    ezSetSpriteShader(sprite, shader);

    EZTexture *tex1 = ezLoadTexture("../res/barack.jpeg");
    ezSetSpriteTexture(sprite, tex1);
    */

    ezAddToScene(scene, (void *)sprite, EZ_GAMEOBJECT);
}

void update() {
    while (!ezIsWindowOpen(app->window)) {
        ezSetBackgroundColor(0.0f, 0.0f, 0.0f, 1.0f);
        ezClearFrame();

        ezRenderScene(scene);
        ezUpdateWindow(app->window);
    }
}

void destroy() {
    ezFreeApp(app); /* deallocate the app */
    ezDestroyScene(scene);
}
