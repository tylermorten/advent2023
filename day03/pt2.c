#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <advent2023.h>

#define MAX_PARTS 2000000


typedef struct {
	int x, y;
} Point;

typedef struct {
	Point start;
	int height, width;
} Box;

typedef struct {
	int x, y;
	int width;
	bool is_part;
	char* number;
} FoundNumber;

typedef struct {
	int x, y;
	bool is_gear;
	int num_cnt;
	int num1, num2;
} FoundGear;

bool detect_collision(Box *obj1, Box *obj2) {
	if (obj1->start.x + obj1->width >= obj2->start.x
		&& obj1->start.x <= obj2->width + obj2->start.x
		&& obj1->start.y + obj1->height >= obj2->start.y
		&& obj1->start.y <= obj2->start.y + obj2->height) {
		return true;
	} 
	return false;
}

int number_to_int(FoundNumber* num)
{
	int i = 0;
	if (num->number != NULL) {
		int cur_x = num->x;
			char* ni = malloc(num->width * sizeof(char) + 1);
			if (NULL == ni) {
				exit(EXIT_FAILURE);
			}
			strncpy(ni, num->number, num->width);
			ni[num->width] = '\0';
			i = atoi(ni);
			free(ni);
	}
	return i;
}

void find_gears(const Content* c, FoundGear** gears, int* count_gears)
{
	int x = 0, y = 0;
	int found = 0;
	FoundGear* n = calloc(MAX_PARTS, sizeof(FoundGear));

	if (n == -1) {
		exit(EXIT_FAILURE);
	}

	for (y = 0; y < c->size; ++y) {
		x = 0;
		char* st_ptr = c->lines[y];

		while (*st_ptr != '\0') {
			if (*st_ptr == '*') {

				n[found].x = x;
				n[found].y = y;
				found++;
			}
			x++;
			st_ptr++;
		}
	}
	*count_gears = found;
	*gears = n;
}

void find_numbers(const Content* c, FoundNumber** nums)
{
	int x = 0, y = 0;
	int found = 0;
	FoundNumber* n = calloc(MAX_PARTS, sizeof(FoundNumber));

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

long match_collision(FoundNumber* nums, FoundGear* gear, int gear_count)
{
	long sum = 0;
	for (int i = 0; i < gear_count; ++i) {

		FoundNumber* ptr;
		bool found_one = false;
		for (ptr = nums; ptr->number != NULL; ++ptr) {
			Box box_g = {
				.start = {.x = gear[i].x - 1, .y = gear[i].y - 1 },
				.height = 2,
				.width = 2,
			};

			Box box_n = {
				.start = {.x = ptr->x, .y = ptr->y },
				.width = ptr->width - 1,
				.height = 0,
			};

			bool col = detect_collision(&box_g, &box_n);

			if (col) {
				if (!found_one) {
					gear[i].num1 = number_to_int(ptr);
					found_one = true;
				}
				else {
					gear[i].num2 = number_to_int(ptr);
					sum = sum + (gear[i].num1 * gear[i].num2);
				}
			}
		}
	}
	return sum;
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
	FoundGear* g;
	int cols = 0, rows = 0;

	find_numbers(&c, &n);

	int count_gears = 0;
	find_gears(&c, &g, &count_gears);

	printf("%ld\n", match_collision(n, g, count_gears));

	//printf("%ld\n", sum_parts(n));
	free(n);
	free(g);
	free_content(&c);
	return 0;
}
