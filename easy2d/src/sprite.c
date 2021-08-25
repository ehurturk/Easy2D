//
// Created by Emir Hürtürk on 10.07.2021.
//

#include "sprite.h"
#include "util.h"
#include "aabb.h"
#include "stl/vector.h"
#include "scene.h"
#include <glad/glad.h>


struct EZSprite {
    unsigned int vao, vbo, ebo;
    unsigned int vertexCount, indexCount;
    unsigned int texture_slots;
    unsigned int active;
    unsigned int moveable;
    unsigned int go;
    float w, h;

    struct EZTexture **textures;
    /* Shader */
    struct EZShader *shader;
    /* transform */
    struct EZTransform *transform;
    /* name */
    const char *name;
    /* AABB Collision box */
    struct EZAabbBoundingBox *hitbox;
    /* Scripts */
    struct EZScriptManager *script_manager;
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
struct EZSprite *ezSquareSprite(const char *name, float x, float y, float z, float w, float h) {

//    float vertices[] = {
//            /*   Position       UV */
//            x - w/2, y + w/2, 0.0f, 0.0f, 0.0f,// bottom left
//            x + w/2 , y + w/2, 0.0f, 1.0f, 0.0f, // bottom right
//            x + w/2, y - w/2, 0.0f, 1.0f, 1.0f,  // top right
//            x - w/2, y - w/2, 0.0f, 0.0f, 1.0f  // top left
//    };

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
    buff->w = w;
    buff->h = h;
    vec3 pos;
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    vec3 scale;
    scale[0] = w;
    scale[1] = h;
    scale[2] = 1.0f;
    buff->transform->model[3][0] += pos[0];
    buff->transform->model[3][1] += pos[1];
    buff->transform->model[3][2] += pos[2];
//    glm_translate(buff->transform->model, pos);
    glm_scale(buff->transform->model, scale);

    buff->transform->position[0] = x;
    buff->transform->position[1] = y;
    buff->transform->position[2] = 0.0f;

    buff->transform->scale[0] = 1.0f;
    buff->transform->scale[1] = 1.0f;
    buff->transform->scale[2] = 1.0f;

    buff->transform->rotation[0] = 0.0f;
    buff->transform->rotation[1] = 0.0f;
    buff->transform->rotation[2] = 0.0f;

    buff->name = name;
    buff->hitbox = ezInitAabbBoundingBox(buff->w, buff->h, buff->transform->position[0], buff->transform->position[1]);

    buff->script_manager = malloc(sizeof(struct EZScriptManager));
    buff->script_manager->scripts = malloc(sizeof(EZVector));
    buff->script_manager->parent = buff;

    ez_vector_init(buff->script_manager->scripts);

//    ezInitScriptManager(buff, buff->script_manager);
    buff->active = 1;
    buff->moveable  = 1;
    buff->go = 0;
    return buff;
}

struct EZSprite *ezCreateGameObject(const char *name, float x, float y, float z) {

    struct EZSprite *buff = malloc(sizeof(struct EZSprite));
    if (buff == NULL) {
        return NULL;
    }
    buff->vao = EZ_NOT_RENDERABLE;

    buff->shader  = NULL;
    buff->textures = NULL;
    buff->transform = ezInitTransform();
    buff->w = 0.0f;
    buff->h = 0.0f;
    vec3 pos;
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    vec3 scale;
    scale[0] = 0.0f;
    scale[1] = 0.0f;
    scale[2] = 1.0f;
    buff->transform->model[3][0] += pos[0];
    buff->transform->model[3][1] += pos[1];
    buff->transform->model[3][2] += pos[2];
//    glm_translate(buff->transform->model, pos);
    glm_scale(buff->transform->model, scale);

    buff->transform->position[0] = x;
    buff->transform->position[1] = y;
    buff->transform->position[2] = 0.0f;

    buff->transform->scale[0] = 1.0f;
    buff->transform->scale[1] = 1.0f;
    buff->transform->scale[2] = 1.0f;

    buff->transform->rotation[0] = 0.0f;
    buff->transform->rotation[1] = 0.0f;
    buff->transform->rotation[2] = 0.0f;

    buff->name = name;
    buff->hitbox = NULL;

    buff->moveable = 1;

    buff->script_manager = malloc(sizeof(struct EZScriptManager));
    buff->script_manager->scripts = malloc(sizeof(EZVector));

    ez_vector_init(buff->script_manager->scripts);

    buff->active = 1;
    buff->go = 1;
    return buff;
}

/* Constructs an empty gameobject */
struct EZSprite *ezEmptySprite(int type, const char *name, float x, float y, float z) {
    struct EZSprite *buff;
    switch (type) {
        case EZ_SQUARE:
            buff =  ezSquareSprite(name, x, y, z, 0.0f, 0.0f); /* make width and height 0 since it is empty */
            buff->active = 0;
            break;
        case EZ_EMPTY_GAMEOBJ:
            buff  = ezCreateGameObject(name, x, y, z);
            break;
        default:
            return NULL;
    }
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

void ezTranslateSprite(struct EZSprite *sprite, vec3 xyz, int mode) {
    if (sprite->moveable == 0) {
        return;
    }
    extern struct EZScene *scene;
    for (int i = 0; i < ezVectorTotal(scene->vec); i++) {
        struct EZSprite *spr = ezVectorGet(scene->vec, i);
        if (spr != sprite) {
            if (ezCheckSpriteCollision(sprite, spr)) { /* collision resolution, i guess? */
                if ((sprite->transform->rotation[2] < 90.0f && sprite->transform->rotation[2] >= 0.0f) || (sprite->transform->rotation[2] > -360.0f && sprite->transform->rotation[2] < -270.0f)) {
                    sprite->transform->position[0] += 0.0f;
                    sprite->transform->position[1] += 1.0f;
                    sprite->transform->position[2] += 0.0f;
                    sprite->transform->model[3][0] += 0.0f;
                    sprite->transform->model[3][1] += 1.0f;
                    sprite->transform->model[3][2] += 0.0f;
                }
                if ((sprite->transform->rotation[2] < 180.0f && sprite->transform->rotation[2] >= 90.0f) || (sprite->transform->rotation[2] >= -270.0f && sprite->transform->rotation[2] < -180.0f)) {
                    sprite->transform->position[0] += -1.0f;
                    sprite->transform->position[1] += 0.0f;
                    sprite->transform->position[2] += 0.0f;
                    sprite->transform->model[3][0] += -1.0f;
                    sprite->transform->model[3][1] += 0.0f;
                    sprite->transform->model[3][2] += 0.0f;
                }
                if ((sprite->transform->rotation[2] < 270.0f && sprite->transform->rotation[2] >= 180.0f) || (sprite->transform->rotation[2] >= -180.0f && sprite->transform->rotation[2] < -90.0f)) {
                    sprite->transform->position[0] += 0.0f;
                    sprite->transform->position[1] += -1.0f;
                    sprite->transform->position[2] += 0.0f;
                    sprite->transform->model[3][0] += 0.0f;
                    sprite->transform->model[3][1] += -1.0f;
                    sprite->transform->model[3][2] += 0.0f;
                }
                if ((sprite->transform->rotation[2] < 360.0f && sprite->transform->rotation[2] >= 270.0f) || (sprite->transform->rotation[2] >= -90.0f && sprite->transform->rotation[2] < 0.0f)) {
                    sprite->transform->position[0] += 1.0f;
                    sprite->transform->position[1] += 0.0f;
                    sprite->transform->position[2] += 0.0f;
                    sprite->transform->model[3][0] += 1.0f;
                    sprite->transform->model[3][1] += 0.0f;
                    sprite->transform->model[3][2] += 0.0f;
                }

                return;
            }
        }
    }

    struct EZTransform *transform = ezGetSpriteTransform(sprite);

    switch (mode) {
        case EZ_LOCAL_REF:
                  /* adjusting pos */
            if (xyz[0] == 0.0f) { /* The movement is relative to the up axis which is relative to the sprite itself */
                transform->position[0] += -1.0f * xyz[1] * sin(glm_rad(sprite->transform->rotation[2]));
                transform->position[1] += xyz[1] * cos(glm_rad(sprite->transform->rotation[2]));

                transform->model[3][0] += -1.0f * xyz[1] * sin(glm_rad(sprite->transform->rotation[2]));
                transform->model[3][1] += xyz[1] * cos(glm_rad(sprite->transform->rotation[2]));
            }

            if (xyz[1] == 0.0f) { /* the movement is relative to the right axis which is relative to the sprite itself */
                transform->position[0] += xyz[0] * cos(glm_rad(sprite->transform->rotation[2]));
                transform->position[1] += xyz[0] * sin(glm_rad(sprite->transform->rotation[2]));

                transform->model[3][0] += xyz[0] * cos(glm_rad(sprite->transform->rotation[2]));
                transform->model[3][1] += xyz[0] * sin(glm_rad(sprite->transform->rotation[2]));
            }

            transform->position[2] += xyz[2];
            transform->model[3][2] += xyz[2];
            break;
        case EZ_WORLD_REF:
            transform->position[0] += xyz[0];
            transform->position[1] += xyz[1];
            transform->position[2] += xyz[2];
            transform->model[3][0] += xyz[0];
            transform->model[3][1] += xyz[1];
            transform->model[3][2] += xyz[2];
            break;
        default:
            EZ_ERROR_RAW("[EZ2D:ERROR]: Only local and world references are supported, please check your reference mode\n");
            break;
    }
}

void ezScaleSprite(struct EZSprite *sprite, vec3 xyz) {
    struct EZTransform *transform = ezGetSpriteTransform(sprite);
    transform->scale[0] *= xyz[0];
    transform->scale[1] *= xyz[1];
    transform->scale[2] *= xyz[2];
    glm_scale(transform->model, xyz);
}

void ezRotateSprite(struct EZSprite *sprite, float angle_d) {
    struct EZTransform *transform = ezGetSpriteTransform(sprite);
    /*
        model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
        model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    */
    vec3 t1;
    vec3 t2;
    vec3 axis;
    t1[0] = 0.5f * sprite->w;
    t1[1] = 0.5f * sprite->h;
    t1[2] = 0;
    t2[0] = -0.5f * sprite->w;
    t2[1] = -0.5f * sprite->h;
    t2[2] = 0;
    axis[0] = 0.0f;
    axis[1] = 0.0f;
    axis[2] = 1.0f;
    /* Translate back */
    /* SINCE 2D, X AND Y AXIS ROTATIONS DON'T REALLY MATTER */
    transform->rotation[0] += 0;
    transform->rotation[1] += 0;
    transform->rotation[2] += angle_d;

    if (transform->rotation[2] > 360.0f) {
        transform->rotation[2] -= 360.0f;
    }
    else if (transform->rotation[2] < -360.0f) {
        transform->rotation[2] += 360.0f;
    }

    glm_rotate(transform->model, glm_rad(angle_d), axis); /* 0.01 seems ABSURD but it works :)) */
}

void ezSetSpritePosition(struct EZSprite *sprite, float x, float y) {
    struct EZTransform *transform = ezGetSpriteTransform(sprite);

    vec3 t;
    t[0] = x -transform->position[0];
    t[1] = y - transform->position[1];
    t[2] = transform->position[2]; /* 2D: Z = 0 */

    transform->position[0] = x;
    transform->position[1] = y;
    transform->position[2] = 0;

    transform->model[3][0] += t[0];
    transform->model[3][1] += t[1];
    transform->model[3][2] += t[2];
//    glm_translate(transform->model, t); HAS FUCKING ISSUE
}

void ezMakeSpriteActive(struct EZSprite *sprite) {
    sprite->active = 1;
}

void ezSetSpriteMoveable(struct EZSprite *sprite, int value) {
    sprite->moveable = value;
}

void ezSpriteAddScript(struct EZSprite *sprite, struct EZScript *script) {
    ezVectorPushBack(sprite->script_manager->scripts, (void *) script);
}

void ezInitSprite(const struct EZSprite *sprite) {
    ezInitScriptManager(sprite, sprite->script_manager);
}

void ezStartSprite(const struct EZSprite *sprite) {
    ezStartScripts(sprite->script_manager);
}

void ezUpdateSprite(const struct EZSprite *sprite) {
    ezUpdateScripts(sprite->script_manager);
    if (sprite->hitbox != NULL) {
        sprite->hitbox->x = ezGetSpriteTransform(sprite)->position[0];
        sprite->hitbox->y = ezGetSpriteTransform(sprite)->position[1];
    }
}

int ezCheckSpriteCollision(const struct EZSprite *s1, const struct EZSprite *s2) {
    if (!s1->go && !s2->go)
        return ezCheckAabbCollision(s1->hitbox, s2->hitbox);
    return 0;
}

inline struct EZShader *ezGetSpriteShader(const struct EZSprite *sprite) {
    return sprite->shader;
}

inline unsigned int ezGetSpriteTextureIDAt(const struct EZSprite *sprite, int i) {
    struct EZTexture *tex = sprite->textures[i];
    unsigned int id = ezGetTextureId(tex);
    return id;
}

inline unsigned int ezIsSpriteActive(const struct EZSprite *sprite) {
    return sprite->active;
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

const char *ezGetSpriteName(const struct EZSprite *sprite) {
    return sprite->name;
}

float ezGetSpriteWidth(const struct EZSprite *s) { return s->w; }

float ezGetSpriteHeight(const struct EZSprite *s) { return s->h; }

void ezReleaseSprite(struct EZSprite *sprite) {
    EZ_DEBUGC(EZ_COLOR_YELLOW "Releasing a sprite...\n");
    if (sprite->shader != NULL)
        ezReleaseShader(sprite->shader);
    if (sprite->textures != NULL) {
        for (int i = 0; i < sprite->texture_slots; i++)
            ezReleaseTexture(sprite->textures[i]);
    }
    free(sprite->transform);
    if (sprite->hitbox != NULL)
        free(sprite->hitbox);
    ezDestroyScripts(sprite->script_manager);
    ezDeleteManager(sprite->script_manager);
    free(sprite);
}