#pragma once
#include <stdlib.h>
#include <stdio.h>

#include "lib/cJSON.h"

#define I(x, y) x*2 + (y + 1)

int* loadWorld(const char *filename);
