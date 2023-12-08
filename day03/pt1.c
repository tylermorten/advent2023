#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <advent2023.h>

#define MAX_PARTS 2000000

typedef struct {
	int x, y;
	int width;
	bool is_part;
	char* number;
} FoundNumber;

void find_numbers(const Content *c, FoundNumber** nums)
{
	int x = 0, y = 0;
	int found = 0;
	FoundNumber *n = calloc(MAX_PARTS, sizeof(FoundNumber));

	if (n == -1) {
		exit(EXIT_FAILURE);
	}

	for (y = 0; y < c->size; ++y) {
		int start = 0;
		x = 0;
		char* st_ptr = c->lines[y];

		while (*st_ptr != '\0') {
			if (*st_ptr >= '0' && *st_ptr <= '9') {
				char* found_st_ptr = st_ptr;
				int start_x = x;
				while (*st_ptr >= '0' && *st_ptr <= '9') {
					x++;
					st_ptr++;
				}
				n[found].number = found_st_ptr;
				n[found].width = x - start_x;
				n[found].x = start_x;
				n[found].y = y;
				found++;
			}
			x++;
			st_ptr++;
		}
	}
	*nums = n;
}

int match_parts(Content* c, FoundNumber* nums)
{
	FoundNumber* p;
	int max_x = 0;
	for (char* ptr = c->lines[0]; *(ptr) != '\0'; ++ptr) {
		max_x++;
	}

	for (p = nums; p->number != NULL; ++p) {
		for (int i = 0; i < p->width; i++) {
			for (int y = -1; y < 2; ++y) {
				for (int x = -1; x < 2; ++x) {
					int cur_x = p->x + x + i;
					int cur_y = p->y + y;

					if (cur_x == -1 || cur_x > (max_x - 1)) {
						continue;
					}
					if (cur_y == -1 || cur_y > (c->size - 1)) {
						continue;
					}

					char chr = c->lines[cur_y][cur_x];
					
					if (chr != '.' && chr != '\n' && chr != '\0' && !(chr >= '0' && chr <= '9')) {
						p->is_part = true;
					}
				}
			}
		}
	}

}

int sum_parts(FoundNumber* n)
{
	long sum = 0;
	FoundNumber* ptr;
	for (ptr = n; n->number != NULL; ++n) {
		if (n->is_part) {
			char* num = malloc(n->width * sizeof(char) + 1);
			if (NULL == num) {
				exit(EXIT_FAILURE);
			}
			strncpy(num, n->number, n->width);
			num[n->width] = '\0';
			sum += atol(num);
			free(num);
		}
	}
	return sum;
}

int main(void)
{
	Content c;
	read_input(&c);

	FoundNumber* n;
	find_numbers(&c, &n);

	match_parts(&c, n);
	printf("%ld\n", sum_parts(n));
	free(n);
	free_content(&c);
	return 0;
}