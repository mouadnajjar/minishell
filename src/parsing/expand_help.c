/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/14 20:29:16 by ahlahfid         ###   ########.fr       */
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
	name = gc_alloc(*var_len + 1, &gc);
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
	*i += var_len - 1;
	if (val)
		return (ft_strlen(val));
	return (0);
}

size_t	get_exit_status_len(void)
{
	char	*num;
	size_t	len;

	num = ft_itoa(g_shell.last_exit_status);
	len = ft_strlen(num);
	gc_add(num, &gc);
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
		{
			i++;
			if (src[i] == '?')
				len += get_exit_status_len();
			else
				len += get_expanded_var_len(src, &i);
		}
		else
			len++;
		i++;
	}
	return (len);
}

// size_t	get_expanded_length(const char *src)
// {
// 	size_t	len = 0;
//     size_t i = 0;
//     while (src[i])
//     {
//         if (src[i] == '$')
//         {
//             i++;
//             if (src[i] == '?')
//             {
//                 len += ft_strlen(ft_itoa(g_shell.last_exit_status));
//             }
//             else
//             {
//                 size_t var_len = 0;
//                 while (src[i + var_len] && (ft_isalnum(src[i + var_len])
// 		|| src[i + var_len] == '_'))
//                     var_len++;
//                 char *name = gc_alloc(var_len + 1, &gc);
//                 ft_strlcpy(name, &src[i], var_len + 1);
//                 char *val = get_env_var(name);
//                 if (val)
//                     len += ft_strlen(val);
//                 i += var_len - 1;
//             }
//         }
//         else
//             len++;
//         i++;
//     }
// 	return (len);
// }
