/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 01:49:19 by fra               #+#    #+#             */
/*   Updated: 2023/05/29 15:39:16 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_vars(char *input, t_env *env_vars)
{
	uint32_t	i;
	uint32_t	end;
	char		*var_name;
	char		*var_value;
	char		*exp_input;

	exp_input = ft_strdup(input);
	if (exp_input == NULL)
		return (NULL);
	i = 0;
	while (exp_input[i])
	{
		if (is_valid_d_sign(exp_input, i++))
		{
			end = i;
			while (exp_input[end] && (! ft_isspace(exp_input[end])) && (exp_input[end] != '|'))
				end++;
			var_name = ft_substr(exp_input, i, end - i);
			if (var_name == NULL)
				return (ft_free(exp_input));
			var_value = get_var_value(env_vars, var_name);
			ft_free(var_name);
			exp_input = insert_var(exp_input, var_value, i, end);
			if (exp_input == NULL)
				return (ft_free(exp_input));
			i += ft_strlen(var_value) - 1;
		}
	}
	return (exp_input);
}

char	*get_var_value(t_env *env_vars, char *var_name)
{
	while (env_vars)
	{
		if (ft_strncmp(env_vars->key, var_name, ft_strlen(var_name)) == 0)
			return (env_vars->value);
		env_vars = env_vars->next;
	}
	return (NULL);
}

char	*insert_var(char *input, char *var, uint32_t start, uint32_t end)
{
	uint32_t	old_len;
	uint32_t	new_len;
	uint32_t	var_len;
	char		*update_str;
	char		*tmp;

	old_len = ft_strlen(input);
	var_len = ft_strlen(var);
	new_len = start - 1 + var_len + old_len - end;
	update_str = ft_calloc(new_len + 1, sizeof(char));
	if (update_str)
	{
		tmp = update_str;
		ft_strlcpy(tmp, input, start);
		tmp += start - 1;
		ft_strlcpy(tmp, var, var_len + 1);
		tmp += var_len;
		ft_strlcpy(tmp, input + end, old_len - end + 1);
		ft_free(input);
	}
	return (update_str);
}
