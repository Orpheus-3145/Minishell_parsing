/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:49:18 by fra               #+#    #+#             */
/*   Updated: 2023/05/20 21:37:29 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_pipes(void)
{
	char *pipe_str;

	pipe_str = "sadasd|fg";
	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasds||g";
	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasd|||fg";
	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss| asdasds | awsdasd ggh | fg";
	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss|| asdasds | awsdasd ggh | fg";
	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sada\"sdss||| a\"sdasds | awsdasd ggh | fg";
	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss || asdasds | awsdasd ggh | fg";
	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasd\'ss ||| a\'sdasds | awsdasd ggh | fg";
	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss |   |asdasds | awsdasd ggh | fg";
	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss| |asdasds | awsdasd ggh | fg";
	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss | || |asdasds | awsdasd ggh | fg";
	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "|sadasdss| asdasds | awsdasd ggh | fg";
	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "| sadasdss| asdasds | awsdasd ggh | fg";
	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "|| sadasdss| asdasds | awsdasd ggh | fg";
	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sa||dasd|ss| asdasds | awsdasd ggh | fg";
	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss| as |dasds | awsdasd ggh | fg";
	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss| as |dasds | awsdasd ggh | fg|";
	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss| as |dasds | awsdasd ggh | fg|  ";
	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss| as |dasds | awsdasd ggh | fg||";
	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss| as |dasds | awsdasd ggh | fg|  a";
	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss| as |dasds | awsdasd ggh | fg |  ";
	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
}

void	test_redirections(void)
{
	char *red_str;

	red_str = "sadasdss> asd";
	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss> asd";
	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss>asd";
	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss > asd";
	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss >>> asd";
	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss <<< asd";
	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss >>> asd";
	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss << < asd";
	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss >> > asd";
	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss < < asd";
	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss > < asd";
	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss > > asd";
	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss < > asd";
	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasds<asd";
	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss >";
	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss <   ";
	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss < \t";
	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss <";
	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss < |";
	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
	red_str = "sadasdss < | adasdas";
	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
}

void	test_quotes(void)
{
	char *quot_str;

	quot_str = "efdsdf\"asdasd\"asdasd";
	ft_printf("str: %s - status %d\n", quot_str, check_quotes(quot_str));
	quot_str = "efdsdf\'asdasd\'asdasd";
	ft_printf("str: %s - status %d\n", quot_str, check_quotes(quot_str));
	quot_str = "efdsdf\'asda\"sd\'asdasd";
	ft_printf("str: %s - status %d\n", quot_str, check_quotes(quot_str));
	quot_str = "efdsdf\'as\'dasd\'asdasd";
	ft_printf("str: %s - status %d\n", quot_str, check_quotes(quot_str));
	quot_str = "efdsdf\'as\"asdasd\"dasd\'asdasd";
	ft_printf("str: %s - status %d\n", quot_str, check_quotes(quot_str));
	quot_str = "efdsdf\'as\"asdasd\"dasd\'asdasdas\'asdasd\'dasd";
	ft_printf("str: %s - status %d\n", quot_str, check_quotes(quot_str));
	quot_str = "efdsdf\'as\"asdasd\"dasd\'asdasd\"asasdasddasd";
	ft_printf("str: %s - status %d\n", quot_str, check_quotes(quot_str));
	quot_str = "efdsdf\'as\"asdasd\"dasd\'asdas\'das\'asdasd\'dasd";
	ft_printf("str: %s - status %d\n", quot_str, check_quotes(quot_str));
	quot_str = "efdsdf\'asdasdasdasd";
	ft_printf("str: %s - status %d\n", quot_str, check_quotes(quot_str));
	quot_str = "efdsdf\'as\'da\"sd\"asdasd";
	ft_printf("str: %s - status %d\n", quot_str, check_quotes(quot_str));
}

void	test_last_pipe(void)
{
	char *red_str;

	red_str = "asdadsd |";
	ft_printf("str: %s - status %d\n", red_str, trailing_pipe(red_str));
	red_str = "asdadsd |   ";
	ft_printf("str: %s - status %d\n", red_str, trailing_pipe(red_str));
	red_str = "asdadsd ";
	ft_printf("str: %s - status %d\n", red_str, trailing_pipe(red_str));
	red_str = "|";
	ft_printf("str: %s - status %d\n", red_str, trailing_pipe(red_str));
	red_str = "|  ";
	ft_printf("str: %s - status %d\n", red_str, trailing_pipe(red_str));
	red_str = " |   ";
	ft_printf("str: %s - status %d\n", red_str, trailing_pipe(red_str));
	red_str = "    ";
	ft_printf("str: %s - status %d\n", red_str, trailing_pipe(red_str));
	red_str = "";
	ft_printf("str: %s - status %d\n", red_str, trailing_pipe(red_str));
}

void	test_trim(void)
{
	char *red_str;

	red_str = "asdadsd";
	ft_printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str));
	red_str = "   asdadsd   ";
	ft_printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str));
	red_str = "\tasdadsd\n";
	ft_printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str));
	red_str = "\nasdadsd";
	ft_printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str));
	red_str = "   ";
	ft_printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str));
	red_str = "";
	ft_printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str));
	red_str = NULL;
	ft_printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str));
	red_str = " 0 ";
	ft_printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str));
	red_str = " sf   ";
	ft_printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str));
}

void	test_next_d_red(void)
{
	char *str;

	str = "asdasd << asdasd";
	ft_printf("str: |%s| - next eof pos |%d|\n", str, find_next_eof_pos(str, 0));
	str = "asdasd <<asdasd";
	ft_printf("str: |%s| - next eof pos |%d|\n", str, find_next_eof_pos(str, 0));
	str = "asdasd < asda<<sd";
	ft_printf("str: |%s| - next eof pos |%d|\n", str, find_next_eof_pos(str, 0));
	str = "asdasd < as < << dasd";
	ft_printf("str: |%s| - next eof pos |%d|\n", str, find_next_eof_pos(str, 0));
	str = "asdasd asdasd";
	ft_printf("str: |%s| - next eof pos |%d|\n", str, find_next_eof_pos(str, 0));
	str = "<<";
	ft_printf("str: |%s| - next eof pos |%d|\n", str, find_next_eof_pos(str, 0));
	str = "   <<";
	ft_printf("str: |%s| - next eof pos |%d|\n", str, find_next_eof_pos(str, 0));
	str = "<< ";
	ft_printf("str: |%s| - next eof pos |%d|\n", str, find_next_eof_pos(str, 0));
	str = "  << ";
	ft_printf("str: |%s| - next eof pos |%d|\n", str, find_next_eof_pos(str, 0));
	str = "<< a";
	ft_printf("str: |%s| - next eof pos |%d|\n", str, find_next_eof_pos(str, 0));
	str = "<< sdsd";
	ft_printf("str: |%s| - next eof pos |%d|\n", str, find_next_eof_pos(str, 0));
	str = "";
	ft_printf("str: |%s| - next eof pos |%d|\n", str, find_next_eof_pos(str, 0));
	str = NULL;
	ft_printf("str: |%s| - next eof pos |%d|\n", str, find_next_eof_pos(str, 0));
}

void	test_eof(void)
{
	char *str;

	str = "asd_asd << asdasd asd";
	ft_printf("str: |%s| - starting in: |%s| = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), find_eof(str + find_next_eof_pos(str, 0)));
	str = "asdsadsdasd <<asdasd   ";
	ft_printf("str: -%s- - starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), find_eof(str + find_next_eof_pos(str, 0)));
	str = "asdfgwfgsasd < asda<<sd\t";
	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), find_eof(str + find_next_eof_pos(str, 0)));
	str = "asdfghasd < as < << dasd  ";
	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), find_eof(str + find_next_eof_pos(str, 0)));
	str = "<<";
	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), find_eof(str + find_next_eof_pos(str, 0)));
	str = "   <<";
	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), find_eof(str + find_next_eof_pos(str, 0)));
	str = "<< ";
	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), find_eof(str + find_next_eof_pos(str, 0)));
	str = "  << ";
	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), find_eof(str + find_next_eof_pos(str, 0)));
	str = "<< a";
	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), find_eof(str + find_next_eof_pos(str, 0)));
	str = "<< sdsd";
	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), find_eof(str + find_next_eof_pos(str, 0)));
	str = "asdhjasd << asdasd|";
	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), find_eof(str + find_next_eof_pos(str, 0)));
	str = "aadfsdasd << asd|asd";
	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), find_eof(str + find_next_eof_pos(str, 0)));
	str = "as@#dasd << asda<sd";
	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), find_eof(str + find_next_eof_pos(str, 0)));
	str = "asda67sd << asd>asd";
	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), find_eof(str + find_next_eof_pos(str, 0)));
	str = "asda|sd << asda >sd";
	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), find_eof(str + find_next_eof_pos(str, 0)));
	str = "asdghasd << asda < sd";
	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), find_eof(str + find_next_eof_pos(str, 0)));
	str = "asda89sd << asda | sd";
	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), find_eof(str + find_next_eof_pos(str, 0)));
	str = "asda89sd asda << \"| sd\"";
	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), find_eof(str + find_next_eof_pos(str, 0)));
	str = "asda89sd asda <<\'| sd\'";
	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), find_eof(str + find_next_eof_pos(str, 0)));
	str = "asda89sd << \"asda\' sd\"";
	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), find_eof(str + find_next_eof_pos(str, 0)));
	str = "asda89sd << \"\"";
	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), find_eof(str + find_next_eof_pos(str, 0)));
	str = "asda89sd << \'\'";
	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), find_eof(str + find_next_eof_pos(str, 0)));
	str = "asda89sd << 'as|asd'";
	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), find_eof(str + find_next_eof_pos(str, 0)));
}