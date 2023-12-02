#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "advent2023.h"

//const static char* input[] = {
//	{ "two1nine" },
//	{ "eightwothree" },
//	{ "abcone2threexyz" },
//	{  "xtwone3four" },
//	{ "4nineeightseven2" },
//	{ "zoneight234" },
//	{ "7pqrstsixteen" }
//};

#define MAX_LINE 4096

typedef struct {
	char* key;
	int val;
	int size;
} DigitMap;

static const DigitMap digit_map[] = {
	{.key = "one", .val = 1, .size = 3 },
	{.key = "two", .val = 2, .size = 3 },
	{.key = "three", .val = 3, .size = 5 },
	{.key = "four", .val = 4, .size = 4 },
	{.key = "five", .val = 5, .size = 4 },
	{.key = "six", .val = 6, .size = 3 },
	{.key = "seven", .val = 7, .size = 5 },
	{.key = "eight", .val = 8, .size = 5 },
	{.key = "nine", .val = 9, .size = 4 },
};

static unsigned int map_to_digit(const char* str)
{
	for (size_t i = 0; i < (sizeof(digit_map) / sizeof(DigitMap)); ++i) {
		if (strncmp(digit_map[i].key, str, digit_map[i].size) == 0) {
			return digit_map[i].val;
		}
	}
	return 0;
}

static long line_digits(const char* l)
{
	char val[3] = { 0 };
	bool found_first = false;
	size_t length = strlen(l);

	while (*l != '\0') {
		if (*l >= '1' && *l <= '9') {
			if (found_first)
				val[1] = *l;
			else {
				val[0] = *l;
				val[1] = *l;
				found_first = true;
			}
		}
		else {
			for (int i = length; i > 2; --i) {
				for (int v = 0; v < (sizeof(digit_map) / sizeof(DigitMap)); ++v) {
					if (strncmp(l, digit_map[v].key, i) == 0) {
						if (found_first) {
							char* p = val + 1;
							sprintf(p, "%d", map_to_digit(digit_map[v].key));
						}
						else {
							sprintf(val, "%d%d", 
								map_to_digit(digit_map[v].key),
								map_to_digit(digit_map[v].key));
							found_first = true;
						}
					}
				}
			}

		}

		++l;
	}
	int result = atoi(val);

	return result;
}

int main(void)
{
	const char* line1 = "1abc2";
 	assert(line_digits(line1) == 12);

	const char* line2 = "nine";
	assert(line_digits(line2) == 99);

	Content c = read_input();

	long sum = 0;
/*	for (int i = 0; i < (sizeof(input) / sizeof(char*)); ++i) {
		int calc = line_digits(input[i]);
		sum += (long)calc;
	}
	*/
	printf("%ld\n", sum);
	return 0;
}