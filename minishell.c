/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorres <ptorres@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 12:02:38 by pablo             #+#    #+#             */
/*   Updated: 2021/12/14 15:12:20 by ptorres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/minishell.h"

void	__init_vars(t_data *data, char **env)
{
	data->raw_cmd = "";
	data->status = 0;
	data->env = env;
	data->exportables = save_exportables(env);
	data->first_env = 1;
	data->session_env = NULL;
	data->asignation = 0;
	g_status = 0;
	getcwd(data->path, 2000);
}

void	main_exec(t_data *data, char **path_aux)
{
	if (ft_strlen(data->raw_cmd))
		add_history(data->raw_cmd);
	if (ft_strlen(data->raw_cmd) > 0)
	{
		if (parse_comands(data))
			execute_commands(data);
		ft_bi_free(data->paths), free(*path_aux);
		*path_aux = get_env_ms(data, "PATH");
		data->paths = ft_split(*path_aux, ':');
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*route;
	t_data	data;
	char	*path_aux;

	argc = 0;
	argv = NULL;
	__init_vars(&data, env);
	path_aux = get_env_ms(&data, "PATH");
	data.paths = ft_split(path_aux, ':');
	route = "\033[1;34mminishell$ \033[0m";
	while (1)
	{
		if (g_status != 130)
			g_status = 0;
		signal(SIGQUIT, handle_sigquit2);
		signal(SIGINT, handle_sigint);
		data.cmds = NULL;
		data.raw_cmd = readline(route);
		if (!data.raw_cmd)
			printf(""), exit(0);
		main_exec(&data, &path_aux);
		free_command(&data), free(data.raw_cmd);
	}
	return (0);
}
