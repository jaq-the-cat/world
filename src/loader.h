#pragma once
#include <stdlib.h>
#include <stdio.h>

#include "lib/cJSON.h"

typedef struct {
    int x, y;
    char *texture;
} object;

object* loadWorld(const char *filename, int *worldSize);
