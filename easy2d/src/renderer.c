//
// Created by Emir Hürtürk on 10.07.2021.
//

#include "renderer.h"
#include "util.h"
#include <cglm/cglm.h>
#include <glad/glad.h>

enum projections {ORTHOGRAPHIC, PERSPECTIVE};
enum types {BATCH, PLAIN};

struct EZRendererConfig {
    enum projections proj_type;
    enum types renderer_type;
};

void ezRenderSprite(const struct EZSprite *sprite, const struct EZCamera *cam) {
    ASSERT(sprite, "[EZ2D:ERROR]: Can't render a sprite which is NULL\n");

    struct EZShader *shader = ezGetSpriteShader(sprite);

    ezUseShader(shader);

    mat4 proj, model, view;

    ezGetProjMatrix(cam, proj);
    ezGetTransformModel(ezGetSpriteTransform(sprite), model);
    ezGetViewMatrix(cam, view);

    ezSetShaderUniformMat4(shader, "ez_Projection", proj);
    ezSetShaderUniformMat4(shader, "ez_Model", model);
    ezSetShaderUniformMat4(shader, "ez_View", view);

    /* Textures aren't necessary, however shaders are. */
    if (ezGetSpriteTextures(sprite) != NULL) {
        for (int i = 0; i < ezGetSpriteTextureSlots(sprite); i++) {
            /* texture array in the sprite */
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, ezGetSpriteTextureIDAt(sprite, i));
        }
    }

    glBindVertexArray(ezGetSpriteVAO(sprite));
    glDrawElements(GL_TRIANGLES, ezGetSpriteIndexCount(sprite), GL_UNSIGNED_INT, 0);
}

void ezRenderScene(const struct EZScene *scene) {
    ASSERT(scene, "[EZ2D:ERROR]: Can't render a scene which is NULL\n");

    struct EZSprite *sprite = (struct EZSprite *) ezGetSceneComponent(scene, EZ_GAMEOBJECT);
    struct EZShader *shader = ezGetSpriteShader(sprite);
    struct EZCamera *cam = (struct EZCamera *) ezGetSceneComponent(scene, EZ_CAMERA);
    ezUpdateCamera(cam);
    ezUseShader(shader);

    mat4 proj, model, view;

    ezGetProjMatrix(cam, proj);
    ezGetTransformModel(ezGetSpriteTransform(sprite), model);
    ezGetViewMatrix(cam, view);

    ezSetShaderUniformMat4(shader, "ez_Projection", proj);
    ezSetShaderUniformMat4(shader, "ez_Model", model);
    ezSetShaderUniformMat4(shader, "ez_View", view);

    printf("MAT BEGIN\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            printf("%f ", model[j][i]);
        printf("\n");
    }
    printf("MAT END\n");

    /* Textures aren't necessary, however shaders are. */
    if (ezGetSpriteTextures(sprite) != NULL) {
        for (int i = 0; i < ezGetSpriteTextureSlots(sprite); i++) {
            /* texture array in the sprite */
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, ezGetSpriteTextureIDAt(sprite, i));
        }
    }

    glBindVertexArray(ezGetSpriteVAO(sprite));
    glDrawElements(GL_TRIANGLES, ezGetSpriteIndexCount(sprite), GL_UNSIGNED_INT, 0);
}

void ezClearFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ezSetBackgroundColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}