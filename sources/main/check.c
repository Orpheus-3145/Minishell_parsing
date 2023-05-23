/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 00:55:08 by fra               #+#    #+#             */
/*   Updated: 2023/05/24 01:25:47 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


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

bool	is_valid_quote(char *string, uint32_t pos_to_check)
{
	if (! is_quote(string[pos_to_check]))
		return (false);
	else
		return (is_outside_quotes(string, pos_to_check));
}

// bool	is_valid_symbol(char *string, uint32_t pos_to_check)
// {
// 	if (string[pos_to_check] != '|' && (! is_arrow(string[pos_to_check])) && (! is_quote(string[pos_to_check])))
// 		return (false);
// 	else
// 		return (is_outside_quotes(string, pos_to_check));
// }

bool	is_outside_quotes(char *string, uint32_t pos_to_check)
{
	uint32_t	i;
	char		quotes;
	bool		open_quotes;

	i = 0;
	open_quotes = false;
	while (string[i] && (i < pos_to_check))
	{
		if (is_quote(string[i]))
		{
			if ((open_quotes == true) && (string[i] == quotes))
			{
				quotes = '\0';
				open_quotes = false;
			}
			else if (open_quotes == false)
			{
				quotes = string[i];
				open_quotes = true;
			}
		}
		i++;
	}
	return (! open_quotes);
}

bool	has_trailing_pipe(char	*cmd)
{
	uint32_t	len_cmd;

	if (! cmd || (*cmd == '\0'))
		return (false);
	len_cmd = ft_strlen(cmd) - 1;
	while (len_cmd && ft_isspace(cmd[len_cmd]))
		len_cmd--;
	if (len_cmd <= 1)
		return (false);
	else
		return (cmd[len_cmd] == '|');
}

bool	is_quote(char to_check)
{
	return ((to_check == '\'') || (to_check == '\"'));
}

bool	is_arrow(char to_check)
{
	return ((to_check == '<') || (to_check == '>'));
}

bool	is_not_symbol(char *string, uint32_t pos)
{
	if (is_quote(string[pos]) || is_arrow(string[pos]) || ft_isspace(string[pos]) || (string[pos] == '|'))
		return (! is_outside_quotes(string, pos));
	else
		return (true);
}
