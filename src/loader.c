#include "loader.h"

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

int* loadWorld(const char *filename) {
    char* json = loadJson(filename);
    cJSON *item = cJSON_Parse(json);
    free(json);

    cJSON *node = item->child;

    // arr is an array of integers, with 2 consecutive indices representing (X, Y) coordinates
    // and the first index representing the size of the array
    int* arr = malloc(sizeof(int)*2*INILEN);

    int i;

    for (i=0; node != NULL; i++) {
        if (i >= INILEN)
            arr = realloc(arr, (int) (INILEN*1.5) * sizeof(int)*2); // resize arr to fit more values

        arr[I(i, 0)] = node->child->valueint; // x
        arr[I(i, 1)] = node->child->next->valueint; // y

        node = node->next;
    }

    arr[0] = i;
    arr = realloc(arr, (i+1) * sizeof(int)*2); // resize arr to fit world size

    cJSON_Delete(item);

    return arr;
}
