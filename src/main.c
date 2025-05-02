/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:17 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/02 16:25:34 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parce.h"

int main(void)
{
    char *line;
    t_cmd *cmd;
	t_cmd *tmp;
	int i;

    while (1)
    {
        line = readline(PROMPT);
		if (!input)
        {
            write(1, "exit\n", 6);
            break ;
        }

/////////// start the parcing //
        cmd = parse_input(line);
////////////////////////////////

////////// Print the parsed commands//

		tmp = cmd;
		while (tmp)
		{
			i = 0;
			while (tmp->args[i])
			{
				printf("arg[%d]: %s\n", i, tmp->args[i]);
				i++;
			}
			if (tmp->is_pipe)
				printf("-> PIPE\n");
			tmp = tmp->next;
		}
        free_cmds(cmd);
        free(line);
/////////////////////////////////////
    }
    return 0;
}

