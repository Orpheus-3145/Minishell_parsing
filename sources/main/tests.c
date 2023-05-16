/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:49:18 by fra               #+#    #+#             */
/*   Updated: 2023/05/16 20:31:12 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void test_pipes(void)
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

void test_redirections(void)
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
