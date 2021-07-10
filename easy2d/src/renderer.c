//
// Created by Emir Hürtürk on 10.07.2021.
//

#include "renderer.h"
#include <glad/glad.h>

void ezRenderSprite(const struct EZSprite *sprite) {
    glUseProgram(ezGetShaderProgramId(ezGetShaderOfSpite(sprite)));
    glBindVertexArray(ezGetSpriteVAO(sprite));
    glDrawElements(GL_TRIANGLES, ezGetIndexCountOfSprite(sprite), GL_UNSIGNED_INT, 0);
}
