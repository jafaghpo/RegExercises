#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <regex.h>
#include <unistd.h>

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
    char    regex[] = "^[1-9][0-9]{4}[ \t]+(BASH|BRAINFUCK|C(LISP|LOJURE|PP|SHARP)?|D(ART)?|ERLANG|GO|GROOVY|HASKELL|JAVA(SCRIPT)?|LUA|OBJECTIVEC|OCAML|PASCAL|PERL|PHP|PYTHON|R(UBY)?|SBCL|SCALA)[\t ]?[\n$]";

    error = regcomp(&preg, regex, REG_NOSUB | REG_EXTENDED);
	if (!error)
	{
    	match = regexec(&preg, line, 0, NULL, 0);
    	regfree(&preg);
    	if (!match)
        	printf("VALID\n");
    	else if (match == REG_NOMATCH)
			printf("INVALID\n");
		else
			display_error(&preg);
	}
}

int       	main()
{
	char	*line;
	size_t	n = 1024;
	size_t	nb_lines = 0;

	if (!(line = malloc(sizeof(char) * 1024)))
	{
        fprintf(stderr, "Not enough memory available\n");
        exit(EXIT_FAILURE);
    }	
	if (getline(&line, &n, stdin) == -1)
	{
		fprintf(stderr, "Nothing to read in standard input\n");
		exit(EXIT_FAILURE);
	}
	nb_lines = atoi(line);
    while (nb_lines)
    {
		if (getline(&line, &n, stdin) == -1)
		{
			fprintf(stderr, "Nothing to read in standard input\n");
			exit(EXIT_FAILURE);
		}
        parse_input(line);
		nb_lines--;
    }
	free(line);
    return (0);
}
