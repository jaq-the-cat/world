#pragma once
#include <stdlib.h>
#include <stdio.h>

#include "libs/cJSON.h"

#define I(x, y) x + y * 2

int* loadWorld(const char *filename);
