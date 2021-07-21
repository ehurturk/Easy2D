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

//    mat4 proj;
//    glm_ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f, proj);
//    mat4 model, view;
//    glm_mat4_identity(model);
//    glm_mat4_identity(view);
//
    mat4 proj, model, view;

    ezGetProjMatrix(cam, proj);
    ezGetModelMatrix(cam, model);
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

void ezClearFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ezSetBackgroundColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}