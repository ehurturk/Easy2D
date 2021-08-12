//
// Created by Emir Hürtürk on 10.07.2021.
//

#include "renderer.h"
#include "util.h"
#include "stl/vector.h"
#include <cglm/cglm.h>
#include <glad/glad.h>

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

    /* General structs */
    EZVector *vec = (EZVector *) ezGetSceneComponent(scene, EZ_GAMEOBJS);

    struct EZCamera *cam = (struct EZCamera *) ezGetSceneComponent(scene, EZ_CAMERA);
    ezUpdateCamera(cam); /* no need to have this since the viewport doesn't really change */
    mat4 proj, model, view;

    ezGetProjMatrix(cam, proj);
    ezGetViewMatrix(cam, view);

    /* TODO: Batch this whole sprite draw call */
    for (int j = 0; j < ezVectorTotal(vec); j++) {
        /* Sprite specific structs - in a gameobj loop */
//        struct EZSprite *sprite = (struct EZSprite *) ezGetSceneComponent(scene, EZ_S_GAMEOBJECT);
        struct EZSprite *sprite = (struct EZSprite *) ezVectorGet(vec, j); /* a problem occurs here */
        /* VECTOR GIVES SEG FAULT - TODO: SOLVE THISSSS */
        /* FIXME: SOLVE SEG FAULT */

        ezGetTransformModel(ezGetSpriteTransform(sprite), model);

        struct EZShader *shader = ezGetSpriteShader(sprite);
        ezUseShader(shader);
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
}

void ezClearFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ezSetBackgroundColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}