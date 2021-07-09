#pragma once
#include <stdlib.h>
#include <stdio.h>

#include "lib/cJSON.h"

typedef struct {
    int x, y;
    size_t texture;
} object;

object* loadWorld(const char *filename, int *worldSize);
