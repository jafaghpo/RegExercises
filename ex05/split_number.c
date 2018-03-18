#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <regex.h>
#include <unistd.h>

static int	parse_input(char *line)
{
    regex_t preg;
    int     match = 0;
    int     error = 0;
    char    regex[] = "^([0-9]{1,3}[- ]){2}[0-9]{4,10}$";

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
			return (0);
	}
	return (1);
}

int       	main()
{
	char	*line;
	char	*tmp;
	size_t	n = 1024;
	size_t	nb_lines = 0;

	if (!(line = malloc(sizeof(char) * 1024)))
		return (1);
	if (getline(&line, &n, stdin) == -1)
		return (1);
	nb_lines = atoi(line);
    while (nb_lines)
    {
		if (getline(&line, &n, stdin) == -1)
			return (1);
		tmp = strchr(line, '\n');
		if (tmp)
			*tmp = 0;
        if (!parse_input(line))
			return (1);
		nb_lines--;
    }
	free(line);
    return (0);
}
