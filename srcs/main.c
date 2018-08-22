/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 00:42:15 by srabah            #+#    #+#             */
/*   Updated: 2015/02/11 21:55:00 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_global		*g(void)
{
	static t_global *sg = NULL;

	if (!sg)
		sg = malloc(sizeof(t_global));
	return (sg);
}

static void		ft_check_env(char **penv)
{
	char	*tmp2;
	int		i;

	i = 0;
	g()->cmd = NULL;
	tmp2 = NULL;
	if (penv[0])
	{
		duplik_env(penv, 0, NULL);
		i = ft_atoi(env_chr_return_val("SHLVL=")) + 1;
		env_change_val("SHLVL", ft_itoa(i));
	}
	else
	{
		g()->env = (char **)ft_memalloc(sizeof(char*) * 3);
		g()->env[0] = ft_strjoin("PWD=", getcwd(tmp2, 1024));
		g()->env[1] = ft_strdup("SHLVL=1");
	}
	signal(SIGINT, ft_sigint);
}

static	void	ft_main(char *line)
{
	char **m_line;

	if (ft_strchr(line, ';'))
	{
		m_line = ft_strsplit(line, ';');
		while (*m_line)
		{
			ft_sh(*m_line);
			m_line++;
		}
	}
	else
		ft_sh(line);
}

int				main(int argc, char *argv[], char **penv)
{
	char	*line;
	int		i;

	line = NULL;
	argv = argv;
	argc = argc;
	ft_check_env(penv);
	while (ft_promt())
	{
		if (((i = get_next_line(1, &line)) >= 0) && (check_cmd(line)) == 1)
			ft_main(line);
		else if (i == 0)
			break ;
	}
	return (0);
}
