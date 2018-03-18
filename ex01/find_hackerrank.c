#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <regex.h>
#include <unistd.h>

// Max values

#define NB_LINES		(10)
#define INT_SIZE		(2)
#define NB_WORDS		(100)
#define WORD_SIZE		(20)
#define NB_SPACES		(NB_WORDS - 1)
#define NB_NEWLINES		(NB_LINES + 1)
#define BUFFER_SIZE		(NB_LINES * (NB_WORDS * WORD_SIZE + NB_SPACES) + NB_LINES + INT_SIZE)


static void display_error(regex_t *preg)
{
    char    *text;
    size_t  size;

    size = regerror(0, preg, NULL, 0);
    text = malloc(sizeof (*text) * size);
    if (text)
    {
        regerror(0, preg, text, size);
        fprintf(stderr, "%s\n", text);
        free(text);
    }
    else
    {
        fprintf(stderr, "Not enough memory available\n");
        exit(EXIT_FAILURE);
    }
}

static void parse_input(char *line)
{
    regex_t preg;
    int     match = 0;
    int     error = 0;
    char    regex[3][15] = {"^hackerrank$", "^hackerrank.+", ".+hackerrank$"};
    int     i = 0;
    
    while (i < 3)
    {
        error = regcomp(&preg, regex[i], REG_NOSUB | REG_EXTENDED);
        if (error)
            return ;
        match = regexec(&preg, line, 0, NULL, 0);
        regfree(&preg);
        if (!match)
        {
            printf("%d\n", i);
            return ;
        }
        else if (match != REG_NOMATCH)
            display_error(&preg);
        i++;
    }
    printf("%d\n", -1);
}

int       	main()
{
	char	*buffer;
	char	*tmp;
	char	*start_ptr;
	int		ret;
	int		nb_lines = 0;

	if (!(buffer = malloc(sizeof(*buffer) * (BUFFER_SIZE + 1))))
		exit(EXIT_FAILURE);
	if ((ret = read(0, buffer, BUFFER_SIZE)) == -1)
		exit(EXIT_FAILURE);
	buffer[ret] = 0;
	start_ptr = buffer;
	if (!(buffer = strchr(buffer, '\n')))
		exit(EXIT_FAILURE);
	*buffer = 0;
	buffer++;
	nb_lines = atoi(start_ptr);
    while (nb_lines)
    {
		if (!(tmp = strchr(buffer, '\n')))
			exit(EXIT_FAILURE);
		*tmp = 0;
        parse_input(buffer);
		buffer = tmp + 1;
		nb_lines--;
    }
	free(start_ptr);
    return (0);
}
