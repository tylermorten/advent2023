// advent2023.cpp : Defines the entry point for the application.
//

#include <advent2023.h>

Content read_input()
{
	Content res = {
		.size = 0,
		.lines = NULL,
	};

	int line_cnt = 0;

	char *lines = malloc(sizeof(char*) * 20);

	if (lines == NULL) {
		fprintf(stderr, "Failed to allocate memory.");
		exit(-1);
	}

	while (true) {
		char line[MAX_LINE] = { 0 };
		if (fgets(line, MAX_LINE, stdin) == NULL)
			break;


		if (line_cnt % 20 == 0 && line_cnt != 0) {
			char* l_ptr = realloc(*lines, (line_cnt + 20) * sizeof(char*));
			*lines = l_ptr;
		}

		if (*line == '\0') {
			break;
		}
		else {
			size_t line_len = strlen(line);
			*(lines+line_cnt) = malloc(line_len);
			res.lines[line_len] = '\0';
			strcpy(*(lines+line_cnt), line);
		}
		line_cnt++;
	}
	res.lines = lines;
	res.size = line_cnt;
	return res;
}

void free_content(Content* c)
{
	for (int i = 0; i < c->size; ++i) {
		free(c->lines[i]);
	}
	free(c->lines);
}

