/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tests.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 16:49:18 by fra           #+#    #+#                 */
/*   Updated: 2023/05/17 15:46:49 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_pipes(void)
{
	char *pipe_str;

	pipe_str = "sadasdss| asdasds | awsdasd ggh | fg";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss|| asdasds | awsdasd ggh | fg";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sada\"sdss||| a\"sdasds | awsdasd ggh | fg";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss || asdasds | awsdasd ggh | fg";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasd\'ss ||| a\'sdasds | awsdasd ggh | fg";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss |   |asdasds | awsdasd ggh | fg";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss| |asdasds | awsdasd ggh | fg";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss | || |asdasds | awsdasd ggh | fg";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "|sadasdss| asdasds | awsdasd ggh | fg";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "| sadasdss| asdasds | awsdasd ggh | fg";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "|| sadasdss| asdasds | awsdasd ggh | fg";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sa||dasd|ss| asdasds | awsdasd ggh | fg";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss| as |dasds | awsdasd ggh | fg";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss| as |dasds | awsdasd ggh | fg|";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss| as |dasds | awsdasd ggh | fg|  ";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss| as |dasds | awsdasd ggh | fg||";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss| as |dasds | awsdasd ggh | fg|  a";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss| as |dasds | awsdasd ggh | fg |  ";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
}

void	test_redirections(void)
{
	char *red_str;

	red_str = "sadasdss> asd";
	printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss> asd";
	printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss>asd";
	printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss > asd";
	printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss >>> asd";
	printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss <<< asd";
	printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss >>> asd";
	printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss << < asd";
	printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss >> > asd";
	printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss < < asd";
	printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss > < asd";
	printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss > > asd";
	printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss < > asd";
	printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasds<asd";
	printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss >";
	printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss <   ";
	printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss < \t";
	printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss <";
	printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss < |";
	printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss < | adasdas";
	printf("str: %s - status %d\n", red_str, check_redirections(red_str));
}

void	test_last_pipe(void)
{
	char *red_str;

	red_str = "asdadsd |";
	printf("str: %s - status %d\n", red_str, trailing_pipe(red_str));
	red_str = "asdadsd |   ";
	printf("str: %s - status %d\n", red_str, trailing_pipe(red_str));
	red_str = "asdadsd ";
	printf("str: %s - status %d\n", red_str, trailing_pipe(red_str));
	red_str = "|";
	printf("str: %s - status %d\n", red_str, trailing_pipe(red_str));
	red_str = "|  ";
	printf("str: %s - status %d\n", red_str, trailing_pipe(red_str));
	red_str = " |   ";
	printf("str: %s - status %d\n", red_str, trailing_pipe(red_str));
	red_str = "    ";
	printf("str: %s - status %d\n", red_str, trailing_pipe(red_str));
	red_str = "";
	printf("str: %s - status %d\n", red_str, trailing_pipe(red_str));
}

void	test_trim(void)
{
	char *red_str;

	red_str = malloc_str("asdadsd");
	printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str));
	red_str = malloc_str("   asdadsd   ");
	printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str));
	red_str = malloc_str("\tasdadsd\n");
	printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str));
	red_str = malloc_str("\nasdadsd");
	printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str));
	red_str = malloc_str("   ");
	printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str));
	red_str = malloc_str("");
	printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str));
	red_str = malloc_str(NULL);
	printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str));
	red_str = malloc_str(" 0 ");
	printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str));
	red_str = malloc_str(" sf   ");
	printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str));
}

char *malloc_str(const char *str)
{
	uint32_t	i;

	if (! str )
		return ((char *) str);
	char *new_str = (char *) ft_calloc(ft_strlen(str) + 1, 1);
	i = 0;
	while (i < (uint32_t) ft_strlen(str))
	{
		new_str[i] = str[i];
		i++;
	}
	return (new_str);
}
