/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 00:55:08 by fra               #+#    #+#             */
/*   Updated: 2023/05/27 19:53:13 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


bool	is_valid_pipe(char *string, uint32_t pos_to_check)
{
	if (string[pos_to_check] != '|')
		return (false);
	else
		return (is_outside_quotes(string, pos_to_check));
}

bool	is_valid_space(char *string, uint32_t pos_to_check)
{
	if (! ft_isspace(string[pos_to_check]))
		return (false);
	else
		return (is_outside_quotes(string, pos_to_check));
}

bool	is_valid_arrow(char *string, uint32_t pos_to_check)
{
	if (! is_arrow(string[pos_to_check]))
		return (false);
	else
		return (is_outside_quotes(string, pos_to_check));
}

bool	is_quote(char to_check)
{
	return ((to_check == '\'') || (to_check == '\"'));
}

bool	is_arrow(char to_check)
{
	return ((to_check == '<') || (to_check == '>'));
}
