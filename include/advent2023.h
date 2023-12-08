// advent2023.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stb_ds.h>

#define MAX_LINE 4096

typedef struct {
	size_t size;
	char** lines;
} Content;


void read_input(Content *c);
void free_content(Content* c);

// TODO: Reference additional headers your program requires here.
