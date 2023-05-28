/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 01:49:19 by fra               #+#    #+#             */
/*   Updated: 2023/05/28 03:50:26 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sub_var(char *input, t_env *env_vars)
{
	uint32_t	i;
	uint32_t	start;
	uint32_t	end;
	char		*var_name;
	// char		*var_value;

	env_vars++;
	i = 0;
	while (input[i])
	{
		if (is_valid_d_sign(input, i))
		{
			i++;
			start = i;
			end = start;
			while (input[end] && (! ft_isspace(input[end])) && (input[end] != '|'))
				end++;
			var_name = ft_substr(input, start, end - start);
			if (var_name == NULL)
				return (false);
			// ft_printf("isolated var name: %s\n", var_name);
			if (var_exists(env_vars, var_name))
			{
				var_value = get_var_value(env_vars, var_name);
				if (var_value == NULL)
				{
					ft_free(var_name);
					return (false);
				}
			}
			else
				var_value = NULL;
		}
		i++;
	}
}

char	*get_var_value(t_env *env_vars, char *var_name)
{
	while (env_vars)
	{
		if (ft_strncmp(env_vars->key, var_name, ft_strlen(var_name) == 0))
			return (env_vars->value);
		env_vars = env_vars->next;
	}
	return (NULL);
}

bool	var_exists(t_env *env_vars, char *var_name)
{
	while (env_vars)
	{
		if (ft_strncmp(env_vars->key, var_name, ft_strlen(var_name) == 0))
			return (true);
		env_vars = env_vars->next;
	}
	return (false);
}

char	*insert_var(char *input, char *var_value, uint32_t start, uint32_t end)
{
	uint32_t	new_len;
	uint32_t	len_var_value;
	char		*update_str;
	char		*tmp;

	len_var_value = ft_strlen(var_value);
	new_len = start - 1 + len_var_value + ft_strlen(input) - end;
	update_str = ft_calloc(new_len + 1, sizeof(char));
	if (update_str)
	{
		tmp = update_str;
		ft_strlcpy(tmp, input, start);
		tmp += start;
		ft_strlcpy(tmp, var_value, len_var_value + 1);
		tmp += len_var_value;
		input += end;
		ft_strlcpy(tmp, input, ft_strlen(input) - end + 1);
	}
	return (update_str);
}
