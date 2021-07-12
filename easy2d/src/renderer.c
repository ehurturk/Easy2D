//
// Created by Emir Hürtürk on 10.07.2021.
//

#include "renderer.h"
#include "util.h"
#include <glad/glad.h>

void ezRenderSprite(const struct EZSprite *sprite) {
    ASSERT(sprite, "[EZ2D:ERROR]: Can't render a sprite which is NULL\n");
    glUseProgram(ezGetShaderProgramId(ezGetShaderOfSpite(sprite)));
    glBindVertexArray(ezGetSpriteVAO(sprite));
    glDrawElements(GL_TRIANGLES, ezGetIndexCountOfSprite(sprite), GL_UNSIGNED_INT, 0);
}
