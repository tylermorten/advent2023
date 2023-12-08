// advent2023.cpp : Defines the entry point for the application.
//

#include <advent2023.h>

static void replace_newline(char* str)
{
	char* ptr;
	if ((ptr = strchr(str, '\n')) != NULL) {
		*ptr = '\0';
	}
}

void read_input(Content *res)
{
	int line_cnt = 0;

	res->lines = malloc(sizeof(char*) * 20);

	if (res->lines == NULL) {
		fprintf(stderr, "Failed to allocate memory.");
		exit(-1);
	}

	while (true) {
		char line[MAX_LINE] = { 0 };
		if (fgets(line, MAX_LINE, stdin) == NULL)
			break;


		if (line_cnt % 20 == 0 && line_cnt != 0) {
			char* l_ptr = realloc(res->lines, (line_cnt + 20) * sizeof(char*));
			res->lines = l_ptr;
		}

		if (*line == '\0') {
			break;
		}
		else {
			size_t line_len = strlen(line);
			*(res->lines+line_cnt) = malloc(line_len + 1);
			strcpy(*(res->lines+line_cnt), line);
			replace_newline(*(res->lines + line_cnt));
		}
		line_cnt++;
	}
	res->size = line_cnt;
	return res;
}

void free_content(Content* c)
{
	for (int i = 0; i < c->size; ++i) {
		free(c->lines[i]);
	}
	free(c->lines);
}

