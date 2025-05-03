/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:54:44 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/03 11:52:20 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

//----------------structs-needed------------------//
typedef struct s_path
{
	char	**paths;
	char	*path;
	char	*full_path;
	int		j;
}			t_path;
//------------------------------------------------//

//---------------execution-fucntions--------------//
void     execute_command(char *cmd, char **envp);
char    **copy_env(char **envp);
//------------------------------------------------//

//--------------------memmory-free-----------------//
void    free_env(char **env);
void	free_2d_array(char **arr);
//-------------------------------------------------//

#endif
