/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:17 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/09 17:04:22 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

t_list *gc = NULL;

int main(void)
{
    char *line;
    t_cmd *cmd;
    t_cmd *tmp;
    int i;

    while (1)
    {
        line = readline(PROMPT);
        if (!line)
        {
            write(1, "exit\n", 6);
            break;
        }
        if (line[0] == '\0')
        {
            free(line);
            continue;
        }
        cmd = parse_input(line);
        if (!cmd)
        {
            printf("Error: Failed to parse input\n");
            free(line);
            continue;
        }
        tmp = cmd;
		tmp = cmd;
		int cmd_num = 1;
		while (tmp)
		{
			printf("----- Command #%d -----\n", cmd_num++);

			// Print argv
			if (tmp->argv)
			{
				i = 0;
				while (tmp->argv[i])
				{
					printf("argv[%d]: %s\n", i, tmp->argv[i]);
					i++;
				}
			}
			else
				printf("argv: (null)\n");

			// Print redirections
			if (tmp->redirs)
			{
				i = 0;
				while (tmp->redirs[i].target)
				{
					const char *type_str =
						tmp->redirs[i].type == IN ? "<" :
						tmp->redirs[i].type == OUT ? ">" :
						tmp->redirs[i].type == APPEND ? ">>" :
						tmp->redirs[i].type == HEREDOC ? "<<" :
						"UNKNOWN";

					printf("redir[%d]: %s (%s)\n", i, tmp->redirs[i].target, type_str);
					i++;
				}
			}
			else
				printf("redirs: (none)\n");

			// Pipe info
			printf("is_pipe: %s\n", tmp->is_pipe ? "YES" : "NO");

			tmp = tmp->next;
		}
    return 0;
}
}
