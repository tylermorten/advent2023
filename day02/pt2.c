#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <advent2023.h>

typedef struct Set_t {
	int red;
	int blue;
	int green;
} Set;

typedef struct {
	unsigned int id;
	size_t set_count;
	Set *sets;
} Game;

void parse_color(const char* color, Set* s)
{
	int c_val = 0;
	char* saveptr;
	char* token = strtok_s(color, " ", &saveptr);

	int cnt = 0;
	while (token != NULL) {
		if (cnt == 0) {
			c_val = atoi(token);
		}
		if (cnt == 1) {
			if (strcmp("red", token) == 0) {
				s->red += c_val;
			}
			else if (strcmp("blue", token) == 0) {
				s->blue += c_val;
			}
			else if (strcmp("green", token) == 0) {
				s->green += c_val;
			}
		}
		token = strtok_s(NULL, " ", &saveptr);
		cnt++;
	}
}

void parse_set(const char* set, Game *g)
{
	char* saveptr;
	char* token = strtok_s(set, ",", &saveptr);

	while (token != NULL) {
		parse_color(token, g);
		token = strtok_s(NULL, ",", &saveptr);
	}
}

void parse_game(const char* line, Game *g)
{
	char* colon = strchr(line, ':');
	size_t g_len = colon - line;
	char* game = (char*)malloc(g_len + 1);

	if (game == NULL) {
		fprintf(stderr, "Failed to allocate memory.");
		exit(EXIT_FAILURE);
	}
	strncpy(game, line, g_len);
	game[g_len] = '\0';
	
	if (sscanf(game, "Game %d", &g->id) != 1) {
		fprintf(stderr, "Failed to parse game ID.");
		exit(EXIT_FAILURE);
	}
		
	const char* sets = line + g_len + 1;
	char* saveptr;

	char* token = strtok_s(sets, ";", &saveptr);
	g->sets = malloc(sizeof(Set) * 10);

	if (NULL == g->sets) {
		fprintf(stderr, "Unable to allocate memory for a default set of 10.");
		exit(EXIT_FAILURE);
	}

	memset(g->sets, 0, sizeof(Set) * 10);
	
	size_t cnt = 0;
	while (token != NULL) {
		Set* ptr = g->sets;
		parse_set(token, (ptr+cnt));

		token = strtok_s(NULL, ";", &saveptr);

		if (cnt % 10 == 0 && cnt != 0) {
			Set* new_ptr = realloc(g->sets, sizeof(Set) * (cnt + 10));

			if (NULL == new_ptr) {
				fprintf(stderr, "Failed to realloc room for sets.");
				exit(EXIT_FAILURE);
			}
			memset(new_ptr + cnt, 0, sizeof(Set) * 10);
			g->sets = new_ptr;
		}

		if (token != NULL) {
			cnt++;
		}
	}
	g->set_count = cnt+1;

	free(game);

}

int main(void)
{
	Content c;
	read_input(&c);

	Game games[128] = { 0 };
	int cnt_games = 0;

	for (int l = 0; l < c.size; ++l) {
		parse_game(c.lines[l], &games[l]);
		cnt_games++;
	}

	//for (int i = 0; i < (sizeof(input) / sizeof(char*)); ++i) {
	//	sum += (long)line_digits(input[i]);
	//}
	//

	int red = 12, green = 13, blue = 14;
	long sum = 0;
	int id_cnt = 0;

	for (int i = 0; i < cnt_games; ++i) {
		printf("Game %d:\n", games[i].id);

		int min_red = 1, min_blue = 1, min_green = 1;

		for (int s = 0; s < games[i].set_count; ++s) {
			printf("\tset red: %d, blue %d, green %d\n",
				games[i].sets[s].red,
				games[i].sets[s].blue,
				games[i].sets[s].green);
			if (games[i].sets[s].red > min_red) {
				min_red = games[i].sets[s].red;

			}
			if (games[i].sets[s].blue > min_blue) {
				min_blue = games[i].sets[s].blue;
			}
			if (games[i].sets[s].green > min_green) {
				min_green = games[i].sets[s].green;
			}
		}
		sum += min_red * min_blue * min_green;
		printf("%d\n", min_red * min_blue * min_green);
	}

	for (int i = cnt_games; i < 0; ++i) {
		free(games[i].sets);
	}
	printf("%ld\n", sum);
	free_content(&c);
	return 0;
}
