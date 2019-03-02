/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 11:16:46 by modaouch          #+#    #+#             */
/*   Updated: 2019/03/02 11:08:05 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		init_term(void)
{
	char		*term_type;
	int			ret;

	if (!(term_type = getenv("TERM")))
		return (-1);
	ret = tgetent(NULL, term_type);
	if (ret == 1 && ft_strcmp("dumb", term_type))
		return (0);
	g_errorno = (ret > 0 && ft_strcmp("dumb", term_type))
    ? ER_DBACCES : ER_DBINFO;
	return (-1);
}

int main(int ac, char **av, char **envp)
{
	t_edit line_e;

	(void)av;
	(void)ac;
	(void)envp;
	ft_bzero(&line_e, sizeof(line_e));
    line_e.tc_onoff = (init_term() == -1) ? 1 : 0;//ici set off l'utilisation des termcaps au cas ou TERM = (rien || dumb)
	set_terminal(&line_e);  
	//ft_signal_handle();
	while (1)
	{
		line_e.len_max = BUFFER_LEN;
		line_e.cursor_pos = 0;
		ft_putstr_fd("\e[1;32m42🐚\033[0m $> ", STDERR_FILENO);
		line_edition(&line_e);
		//parser();
		//execution();
		if (line_e.line && !ft_strcmp(line_e.line, "exit"))
			break ;
		ft_nlcr();
		ft_strdel(&(line_e.line));
	}
	ft_strdel(&(line_e.line));
	if (tcsetattr(STDERR_FILENO, TCSADRAIN, line_e.termiold) == -1)
		toexit(0, "tcsetattr");
    return (0);
}