/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/28 16:20:22 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

char	*get_env_var(const char *name)
{
	int		i;
	size_t	len;

	len = ft_strlen(name);
	i = 0;
	while (g_shell.envp[i])
	{
		if (!ft_strncmp(g_shell.envp[i], name, len)
			&& g_shell.envp[i][len] == '=')
			return (&g_shell.envp[i][len + 1]);
		i++;
	}
	return (NULL);
}

char	*get_env_name(const char *src, size_t i, size_t *var_len)
{
	char	*name;

	*var_len = 0;
	while (src[i + *var_len] && (ft_isalnum(src[i + *var_len]) || src[i
				+ *var_len] == '_'))
		(*var_len)++;
	name = gc_alloc(*var_len + 1);
	ft_strlcpy(name, &src[i], *var_len + 1);
	return (name);
}

size_t	get_expanded_var_len(const char *src, size_t *i)
{
	size_t	var_len;
	char	*name;
	char	*val;

	var_len = 0;
	name = get_env_name(src, *i, &var_len);
	val = get_env_var(name);
	*i += var_len;
	if (val)
		return (ft_strlen(val));
	return (0);
}

size_t	dollar_sign_len(const char *src, size_t *i)
{
	size_t	len;

	len = 0;
	(*i)++;
	if (src[*i] == '?')
	{
		len += get_exit_status_len();
		(*i)++;
	}
	else if (ft_isalnum(src[*i]) || src[*i] == '_')
	{
		len += get_expanded_var_len(src, i);
	}
	else
	{
		len++;
	}
	return (len);
}

size_t	get_expanded_length(const char *src)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (src[i])
	{
		if (src[i] == '$')
			len += dollar_sign_len(src, &i);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}
