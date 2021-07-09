#include "loader.h"
#include <string.h>

#define INILEN 32

char* loadJson(const char *filename) {
    char *buffer = 0;
    long length;
    FILE *f = fopen(filename, "rb");
    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length+1);
        if (buffer)
            fread(buffer, 1, length, f);
        fclose(f);
    }

    buffer[length] = '\0';
    return buffer;
}

object* loadWorld(const char *filename, int *worldSize) {
    char* json = loadJson(filename);
    cJSON *item = cJSON_Parse(json);
    free(json);

    cJSON *node = item->child;

    // arr is an array of integers, with 2 consecutive indices representing (X, Y) coordinates
    // and the first index representing the size of the array
    object* arr = malloc(sizeof(object)*INILEN);

    int i;

    for (i=0; node != NULL; i++) {
        if (i >= INILEN)
            arr = realloc(arr, (int) (INILEN*1.5) * sizeof(object)); // resize arr to fit more values

        arr[i].x       = node->child->valueint; // x
        arr[i].y       = node->child->next->valueint; // y
        arr[i].texture = node->child->next->next->valueint; // texture index

        node = node->next;
    }

    *worldSize = i;
    arr = realloc(arr, (i) * sizeof(object)); // resize arr to fit world size

    cJSON_Delete(item);

    return arr;
}
