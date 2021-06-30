#pragma once
#include <stdlib.h>
#include <stdio.h>

#include "lib/cJSON.h"

#define I(x, y) x*2 + y

int* loadWorld(const char *filename);
