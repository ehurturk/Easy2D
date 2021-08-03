//
// Created by Emir Hürtürk on 10.07.2021.
//

#include "sprite.h"
#include "util.h"

#include <glad/glad.h>


struct EZSprite {
    unsigned int vao, vbo, ebo;
    unsigned int vertexCount, indexCount;
    unsigned int texture_slots;

    struct EZTexture **textures;
    /* Shader */
    struct EZShader *shader;
    /* Texture */
    /* transform */
    struct EZTransform *transform;
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

    struct EZShader *shader = ezSequentialShaderPipeline();

    const char *default_vs = "#version 330 core\n"
                             "layout (location = 0) in vec3 pos;\n"
                             "layout (location = 1) in vec2 uv;\n"
                             "uniform mat4 ez_Projection;\n"
                             "uniform mat4 ez_Model;\n"
                             "uniform mat4 ez_View;\n"
                             "void main() {\n"
                             "    gl_Position = ez_Projection * ez_View * ez_Model * vec4(pos, 1.0f);\n"
                             "}";

    const char *default_fs = "#version 330 core\n"
                             "out vec4 color;\n"
                             "void main() {\n"
                             "    color = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
                             "}";

    ezAddToShaderPipeline(shader, EZ_VERTEX_SHADER_STR, default_vs);
    ezAddToShaderPipeline(shader, EZ_FRAGMENT_SHADER_STR, default_fs);
    ezFinishShaderPipeline(shader);

    buff->shader  = shader;
    buff->texture_slots = 0;
    int max_units;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_units);
    buff->textures = malloc(max_units * sizeof(ezGetSizeofTexture()));
    for (int i = 0; i < max_units; i++)
        buff->textures[i] = NULL;
    buff->transform = ezInitTransform();
    return buff;
}

/*
 * Create a new sprite containing the default shaders. (it will be a white square if no shaders are specified)
*/
struct EZSprite *ezSquareSprite(float x, float y, float z, float w, float h) {

    float vertices[] = {
            /*   Position       UV */
            x - w/2, y + w/2, 0.0f, 0.0f, 0.0f,// bottom left
            x + w/2 , y + w/2, 0.0f, 1.0f, 0.0f, // bottom right
            x + w/2, y - w/2, 0.0f, 1.0f, 1.0f,  // top right
            x - w/2, y - w/2, 0.0f, 0.0f, 1.0f  // top left
    };

//    float vertices[] = {
//            /*   Position       UV */
//            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,// bottom left
//            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
//            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,  // top right
//            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f  // top left
//    };

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
    buff->texture_slots = 0;

    /* Position Data */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *) 0);
    glEnableVertexAttribArray(0);

    /* UV Data */
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    /* Unbind */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    /* Create the default shader for the sprite */
    struct EZShader *shader = ezSequentialShaderPipeline();

    const char *default_vs = "#version 330 core\n"
                             "layout (location = 0) in vec3 pos;\n"
                             "layout (location = 1) in vec2 uv;\n"
                             "uniform mat4 ez_Model;\n"
                             "uniform mat4 ez_Projection;\n"
                             "uniform mat4 ez_View;\n"

                             "void main() {\n"
                             "    gl_Position = ez_Projection * ez_View * ez_Model * vec4(pos, 1.0f);\n"
                             "}";

    const char *default_fs = "#version 330 core\n"
                             "out vec4 color;\n"
                             "void main() {\n"
                             "    color = vec4(1.0f);\n"
                             "}";

    ezAddToShaderPipeline(shader, EZ_VERTEX_SHADER_STR, default_vs);
    ezAddToShaderPipeline(shader, EZ_FRAGMENT_SHADER_STR, default_fs);
    ezFinishShaderPipeline(shader);

    buff->shader  = shader;
    int max_units;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_units);
    buff->textures = malloc(sizeof(ezGetSizeofTexture()) * max_units);
    for (int i = 0; i < max_units; i++)
        buff->textures[i] = NULL;
    buff->transform = ezInitTransform();
    return buff;
}

void ezSetSpriteShader(struct EZSprite *sprite, struct EZShader *shader) {
    sprite->shader = shader;
}

void ezSetSpriteTexture(struct EZSprite *sprite, struct EZTexture *texture) {
    int max_units;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_units);
    if (sprite->texture_slots <= max_units) {
        sprite->textures[sprite->texture_slots] = texture;
        sprite->texture_slots++;
    }
    else
        EZ_ERROR_RAW("[EZ2D:ERROR]: Maximum number of textures is exceeded. Can't add more textures\n");
}

void ezTranslateSprite(struct EZSprite *sprite, vec3 xyz) {
    struct EZTransform *transform = ezGetSpriteTransform(sprite);
    glm_translate(transform->model, xyz);
}

void ezScaleSprite(struct EZSprite *sprite, vec3 xyz) {
    printf("scale\n");
    for (int i = 0; i < 3; i++)
        printf("%f ", xyz[i]);
    printf("end\n");
    struct EZTransform *transform = ezGetSpriteTransform(sprite);
    glm_scale(transform->model, xyz);

}

void ezRotateSprite(struct EZSprite *sprite, float angle_d, vec3 axis) {
    struct EZTransform *transform = ezGetSpriteTransform(sprite);
    glm_rotate(transform->model, glm_rad(angle_d), axis);
}

inline struct EZShader *ezGetSpriteShader(const struct EZSprite *sprite) {
    return sprite->shader;
}

inline unsigned int ezGetSpriteTextureIDAt(const struct EZSprite *sprite, int i) {
    struct EZTexture *tex = sprite->textures[i];
    unsigned int id = ezGetTextureId(tex);
    return id;
}

inline struct EZTexture **ezGetSpriteTextures(const struct EZSprite *sprite) {
    return sprite->textures;
}

inline struct EZTexture *ezGetSpriteTextureAt(const struct EZSprite *sprite, int i) {
    return sprite->textures[i];
}

inline unsigned int ezGetSpriteVAO(const struct EZSprite *sprite) {
    return sprite->vao;
}

inline unsigned int ezGetSpriteVBO(const struct EZSprite *sprite) {
    return sprite->vbo;
}

inline unsigned int ezGetSpriteEBO(const struct EZSprite *sprite) {
    return sprite->ebo;
}

inline unsigned int ezGetSpriteIndexCount(const struct EZSprite *sprite) {
    return sprite->indexCount;
}

inline unsigned int ezGetSpriteVertexCount(const struct EZSprite *sprite) {
    return sprite->vertexCount;
}

inline unsigned int ezGetSpriteTextureSlots(const struct EZSprite *sprite) {
    return sprite->texture_slots;
}

struct EZTransform *ezGetSpriteTransform(const struct EZSprite *sprite) {
    return sprite->transform;
}

void ezReleaseSprite(struct EZSprite *sprite) {
    EZ_DEBUGC(EZ_COLOR_YELLOW "Releasing a sprite...\n");
    ezReleaseShader(sprite->shader);
    if (sprite->textures != NULL) {
        for (int i = 0; i < sprite->texture_slots; i++)
            ezReleaseTexture(sprite->textures[i]);
    }
    free(sprite);
}