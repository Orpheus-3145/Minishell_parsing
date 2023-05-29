/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 00:55:08 by fra               #+#    #+#             */
/*   Updated: 2023/05/29 19:35:50 by fra              ###   ########.fr       */
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

bool	is_valid_d_sign(char *string, uint32_t pos_to_check)
{
	uint32_t	i;
	bool		open_quotes;
	
	if (string[pos_to_check] != '$')
		return (false);
	if ((string[pos_to_check + 1] == '\0' ) || ft_isspace(string[pos_to_check + 1]))
		return (false);
	i = 0;
	open_quotes = false;
	while (i < pos_to_check)
	{
		if (string[i] == '\'')
			open_quotes = ! open_quotes;
		i++;
	}
	return (! open_quotes);
}

bool	is_valid_quote(char *string, uint32_t pos_to_check)
{
	uint32_t	i;
	char		open_quote;

	if (! is_quote(string[pos_to_check]))
		return (false);
	else
	{
		if (is_outside_quotes(string, pos_to_check))
			return (true);
		else
		{
			i = 0;
			while (string[i] && (i < pos_to_check))
			{
				if (is_quote(string[i]))
				{
					if (string[i] == open_quote)
						open_quote = '\0';
					else if (open_quote == '\0')
						open_quote = string[i];
				}
				i++;
			}
			return (string[pos_to_check] == open_quote);
		}
	}
}

