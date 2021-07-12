//
// Created by Emir Hürtürk on 11.07.2021.
//

#include "resource.h"
#include "util.h"
#include "stb_image.h"

/* Struct representing a resource file that can be used to store resource data. Now, it only supports text and image files. */
struct EZResource {
    char *data;
    size_t size;
    int length;
};

struct EZResource *ezLoadFile(const char *file, int *err) {
    ASSERT(file, "Can't load a NULL resource file.\n");
    char *buffer;
    size_t length; /* bytes */
    FILE *f = fopen(file, "rb");
    size_t read_length;

    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);

        /* 1 G, best not to load a whole large file in one string */
        if (length > 1073741824) {
            *err = EZ_FILE_TOO_LARGE;
            return NULL;
        }

        buffer = (char *) malloc(length + 1);
        if (buffer == NULL) {
            return NULL;
        }

        if (length) {
            read_length = fread(buffer, 1, length, f);
            if (length != read_length) {
                free(buffer);
                *err = 3;
                return NULL;
            }
        }

        fclose(f);
        *err           = EZ_FILE_OK;
        buffer[length] = '\0';
    } else {
        *err = EZ_FILE_DOES_NOT_EXIST;
        return NULL;
    }
    printf("%s\n", buffer);
    struct EZResource *res = malloc(sizeof(struct EZResource));
    res->data = buffer;
    res->size = read_length;
    /* Since each char is exactly 1 bytes, file length (in characters) is equal to file size (in bytes) */
    res->length = read_length;

    return res;
}

/* loads image file based on OpenGL standards, starting from the bottom left corner */
struct EZResource *ezLoadImage(const char *file, int *err) {
    ASSERT(file, "[EZ2D:ERROR]: Can't load a NULL image file.\n");
    stbi_set_flip_vertically_on_load(1);

    int w, h, n_channels;
    unsigned char *data = stbi_load(file, &w, &h, &n_channels, 4);
    if (data == NULL) {
        *err = EZ_FILE_DOES_NOT_EXIST;
        stbi_image_free(data);
        return NULL;
    }
    struct EZResource *res = malloc(sizeof(struct EZResource));
    res->data = (char *) data; /* TODO: Bug source? */
    res->size = w * h; /* in pixels, not bytes! */
    /*
     * IMPORTANT NOTICE HERE:
     * Length is assigned here as width, and size is assigned as width * height. I want to represent both a text file and an image file as an EZResource,
     * thus there is no way I can separate width and height, since it wouldn't be useful for text files. Thereby, to retrieve width and height of the
     * image file (in pixels) use the following:
     *
     *              int width = res->length;
     *              int height = res->size / width;
     *
     * This would extract both the width and the height of the image file.
    */
    res->length = w;
    return res;
}

const char *ezGetResourceContent(struct EZResource *res) {
    return res->data;
}

size_t ezGetResourceSize(struct EZResource *res) {
    return res->size;
}

int ezGetResourceLength(struct EZResource *res) {
    return res->length;
}

void ezReleaseResource(struct EZResource *res) {

    free(res->data); /* critical */
    res->size = 0;
    free(res);
}