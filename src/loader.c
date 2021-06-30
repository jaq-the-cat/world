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
    cJSON *item = cJSON_Parse(loadJson(filename));
    cJSON *node = item->child;

    int* arr = malloc(sizeof(int)*2*INILEN); // alocate certain size

    int i;
    arr[I(0, 0)] = 0; // initialize world length location
    arr[I(0, 0)] = 0;

    for (i=1; node != NULL; i++) {
        arr[I(i, 0)] = node->child->valueint; // x
        arr[I(i, 1)] = node->child->next->valueint; // y
        /*printf("x: %d, y: %d\n", arr[i][0], arr[i][1]);*/

        if (i >= INILEN)
            arr = realloc(arr, (int) (INILEN*1.5) * sizeof(int)*2); // resize arr to fit more values

        node = node->next;
    }

    arr[I(0, 0)] = i+1;
    arr = realloc(arr, (i+1) * sizeof(int)*2); // resize arr to fit world size

    cJSON_Delete(item);

    return arr;
}