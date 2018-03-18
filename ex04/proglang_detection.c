/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proglang_detection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jafaghpo <jafaghpo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 11:25:39 by jafaghpo          #+#    #+#             */
/*   Updated: 2018/03/18 11:48:23 by jafaghpo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <regex.h>
#include <unistd.h>

int			main()
{
	char	buffer[1001];
	int		size;
	regex_t preg;
	char	regex[3][20] = {"(#include)", "(java)", "(print[\t ]|def[\t ])"};
	char	solution[3][10] = {"C", "Java", "Python"};
    int     match = 0;
	int		error = 0;
	int     i = 0;

	size = read(0, buffer, 1000);
	if (size < 0)
		return (1);
	buffer[size] = 0;
    while (i < 3)
    {
        error = regcomp(&preg, regex[i], REG_NOSUB | REG_EXTENDED);
        if (error)
            return (1);
        match = regexec(&preg, buffer, 0, NULL, 0);
        regfree(&preg);
        if (!match)
        {
            printf("%s\n", solution[i]);
            return (1);
        }
        else if (match != REG_NOMATCH)
            return (1);
        i++;
    }
}
