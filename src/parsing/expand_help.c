/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/02 14:31:18 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/executor.h"

size_t	handle_quoted_dollar(const char *str, size_t *i)
{
	if (str[*i] == '\'' && str[*i + 1] == '$')
	{
		*i += 2;
		return (1);
	}
	return (0);
}

size_t	get_var_length(char *var)
{
	char	*value;
	size_t	len;

	if (!var)
		return (0);
	value = get_env_var(g_shell.envp, var);
	if (value)
	{
		len = ft_strlen(value);
		printf("Var: %s, Value len: %zu\n", var, len);
		free(var);
		return (len);
	}
	free(var);
	return (0);
}
char	*get_env_var(char **envp, const char *var)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(var);
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0 && envp[i][len] == '=')
		{
			return (envp[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}

char	*extract_var_name(const char *str, size_t *i, int braced_flag)
{
	size_t	start;
	char	*var;

	start = *i;
	if (braced_flag)
	{
		(*i)++;
		start = *i;
		while (str[*i] && str[*i] != '}')
			(*i)++;
		if (!str[*i])
			return (NULL);
	}
	else
		while (ft_isalnum(str[*i]) || str[*i] == '_')
			(*i)++;
	var = ft_substr(str, start, *i - start);
	if (braced_flag && str[*i] == '}')
		(*i)++;
	return (var);
}

size_t handle_dollar_expansion(const char *str, size_t *i)
{
    size_t add_len = 0;

    if (str[*i] == '?') // Special case for $?
    {
        add_len = ft_numlen(g_shell.last_exit_status);
        (*i)++;
    }
    else if (str[*i] == '{')
    {
        (*i)++;
        while (str[*i] && str[*i] != '}')
            (*i)++;
        if (str[*i] == '}')
        {
            add_len = get_var_length(extract_var_name(str, i, 1));
            (*i)++;
        }
    }
    else if (ft_isalnum(str[*i]) || str[*i] == '_')
    {
        add_len = get_var_length(extract_var_name(str, i, 0));
    }
    else
    {
        add_len = 1; // Just the $ character
    }

    return (add_len);
}

void handle_dollar(const char *str, size_t *i, char **result, size_t *j)
{
    if (str[*i] == '?') // Handle $?
    {
        handle_exit_status(result, j);
        (*i)++;
    }
    else if (str[*i] == '{') // Handle ${VAR}
    {
        handle_braced_variable(str, i, result, j);
    }
    else if (ft_isalnum(str[*i]) || str[*i] == '_') // Handle $VAR
    {
        handle_unbraced_variable(str, i, result, j);
    }
    else // Just a $ with no valid variable
    {
        (*result)[(*j)++] = '$';
    }
}

char *ft_strjoin_free(char *s1, const char *s2)
{
    if (!s1) // Handle uninitialized s1
        s1 = ft_strdup(""); // Initialize to an empty string
    char *joined = ft_strjoin(s1, s2);
    if (joined && s1) {
        free(s1); // Free the old s1
    }
    return joined;
}
