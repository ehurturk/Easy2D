//
// Created by Emir Hürtürk on 10.07.2021.
//

#include "texture.h"
#include "resource.h"
#include "util.h"
#include "stb_image.h"

#include <glad/glad.h>

struct EZTexture {
    unsigned int texid;
    unsigned int w, h; /* also could be struct EZResource *res; but this doesn't store *both* width and height, instead it multiplies it. */
};

struct EZTexture *ezLoadTexture(const char *file) {
    struct EZTexture *tex = malloc(sizeof(struct EZTexture));
    if (tex == NULL)
    {
        return NULL;
    }
    glGenTextures(1, &(tex->texid));
    glBindTexture(GL_TEXTURE_2D, tex->texid);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     /* s axis, repeat */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);     /* t axis, repeat */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* linear => more realistic (blur) */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /* nearest => to avoid blurred texture, and to achieve 8-bit look */

    int err;
    struct EZResource *res = ezLoadImage(file, &err);
    ASSERTF(!err, "[EZ2D:ERROR]: Image file located at %s doesn't exist\n", file);
    const char *data = ezGetResourceContent(res);

    int w = ezGetResourceLength(res); /* FIXME HERE IS THE PROBLEM! */
    int h = (int)ezGetResourceSize(res) / w; /* awkward, but I couldn't come up with any better solution yet */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    tex->w = w;
    tex->h = h;
    ezReleaseResource(res);
    return tex;
}

struct EZTexture *ezLoadTextureFromSpritesheet(const char *file, int x, int y, int w, int h) {
    
}

unsigned int ezGetTextureId(const struct EZTexture *tex) {
    unsigned int id = tex->texid; /* error is here - tex is NULL - FIXME: Tex is null. */
    return id;
}


size_t ezGetSizeofTexture() {
    return sizeof(struct EZTexture);
}

void ezReleaseTexture(struct EZTexture *tex) {
    EZ_DEBUGC(EZ_COLOR_YELLOW "Releasing a texture...\n");
    free(tex);
}