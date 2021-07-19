//
// Created by Emir Hürtürk on 10.07.2021.
//

#include "renderer.h"
#include "util.h"
#include <glad/glad.h>

void ezRenderSprite(const struct EZSprite *sprite) {
    ASSERT(sprite, "[EZ2D:ERROR]: Can't render a sprite which is NULL\n");

    struct EZShader *shader = ezGetSpriteShader(sprite);
    unsigned int prid = ezGetShaderProgramId(shader);
    glUseProgram(prid);

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
    glClear(GL_COLOR_BUFFER_BIT);
}