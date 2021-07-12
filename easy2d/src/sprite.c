//
// Created by Emir Hürtürk on 10.07.2021.
//

#include "sprite.h"
#include "util.h"

#include <glad/glad.h>

struct EZSprite {
    unsigned int vao, vbo, ebo;
    unsigned int vertexCount, indexCount;

    /* Shader */
    struct EZShader *shader;
    /* Texture */
    struct EZTexture *texture;
    /* transform */
};


struct EZSprite *ezCreateSpriteWithVertices(const float *vertices, size_t vsize, const unsigned int *indices, size_t isize, size_t vertexSize, struct VertexLayout layout) {
    ASSERT(vertices, "[EZ2D:ERROR]: Can't create a sprite with NULL vertices\n");
    ASSERT(indices, "[EZ2D:ERROR]: Can't create a sprite with NULL indices\n");
    struct EZSprite *buff = malloc(sizeof(struct EZSprite));
    if (buff == NULL) {
        return NULL;
    }
    glGenVertexArrays(1, &(buff->vao));
    glGenBuffers(1, &(buff->vbo));
    glGenBuffers(1, &(buff->ebo));
    /* bind the vertex array first to be able to associate other buffers with the array as well */
    glBindVertexArray(buff->vao);

    glBindBuffer(GL_ARRAY_BUFFER, buff->vbo);
    glBufferData(GL_ARRAY_BUFFER, vsize, vertices, GL_STATIC_DRAW); /* for dynamically modifying vertex attributes, change this */

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buff->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize, indices, GL_STATIC_DRAW);

    buff->indexCount  = isize / vertexSize;
    buff->vertexCount = vsize / vertexSize;

    glVertexAttribPointer(0, layout.positionCount, GL_FLOAT, GL_FALSE, vertexSize, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, layout.uvCount, GL_FLOAT, GL_FALSE, vertexSize, (void *) (layout.positionCount * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    buff->shader  = NULL;
    buff->texture = NULL;
    return buff;
}

struct EZSprite *ezSquareSprite() {
    float vertices[] = {
            /*   Position       UV */
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,// bottom left
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,  // top right
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {
            0, 1, 3,// first Triangle
            1, 2, 3 // second Triangle
    };
    struct EZSprite *buff = malloc(sizeof(struct EZSprite));
    if (buff == NULL) {
        return NULL;
    }
    /* Generate required buffers */
    glGenVertexArrays(1, &(buff->vao));
    glGenBuffers(1, &(buff->vbo));
    glGenBuffers(1, &(buff->ebo));

    glBindVertexArray(buff->vao);

    /* VBO */
    glBindBuffer(GL_ARRAY_BUFFER, buff->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /* EBO */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buff->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    size_t stride = sizeof(float) * 5;

    buff->vertexCount = 4;
    buff->indexCount  = 6;

    /* Position Data */
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void *) 0);
    glEnableVertexAttribArray(0);

    /* UV Data */
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    /* Unbind */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    buff->shader  = NULL;
    buff->texture = NULL;

    return buff;
}

struct EZSprite *ezCreateQuad(int width, int height) {
}

void ezSetSpriteShader(struct EZSprite *sprite, struct EZShader *shader) {
    sprite->shader = shader;
}

void ezSetSpriteTexture(struct EZSprite *sprite, struct EZTexture *texture) {
    sprite->texture = texture;
}

struct EZShader *ezGetShaderOfSpite(const struct EZSprite *sprite) {
    return sprite->shader;
}

struct EZTexture *ezGetTextureOfSprite(const struct EZSprite *sprite) {
    return sprite->texture;
}

unsigned int ezGetSpriteVAO(const struct EZSprite *sprite) {
    return sprite->vao;
}

unsigned int ezGetSpriteVBO(const struct EZSprite *sprite) {
    return sprite->vbo;
}

unsigned int ezGetIndexCountOfSprite(const struct EZSprite *sprite) {
    return sprite->indexCount;
}

unsigned int ezGetVertexCountOfSprite(const struct EZSprite *sprite) {
    return sprite->vertexCount;
}

void ezReleaseSprite(struct EZSprite *sprite) {
    EZ_DEBUGC(EZ_COLOR_YELLOW "Releasing a sprite...\n");
    ezReleaseShader(sprite->shader);
    ezReleaseTexture(sprite->texture);
    free(sprite);
}