#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

/*const static char* input[] = {
	{ "1abc2" },
	{ "pqr3stu8vwx" },
	{ "a1b2c3d4e5f" },
	{ "treb7uchet" },
}; */

static long line_digits(const char* l)
{
	// create enough space in heap for 15 char digit (minus the null character)
	char val[3] = { 0 };

	if (val == NULL) {
		fprintf(stderr, "Failed to alloc memory.");
		exit(-1);
	}

	bool found_first = false;

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
		++l;
	}
	int result = atoi(val);

	return result;
}

int main(void)
{
	const char* line1 = "1abc2";
	assert(line_digits(line1) == 12);

	long sum = 0;
	

	//for (int i = 0; i < (sizeof(input) / sizeof(char*)); ++i) {
	//	sum += (long)line_digits(input[i]);
	//}
	//
	printf("%d", sum);
	return 0;
}