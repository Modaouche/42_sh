/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgheraie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 23:21:56 by mgheraie          #+#    #+#             */
/*   Updated: 2019/09/18 02:15:04 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAM_EXPANSION
# define PARAM_EXPANSION
# include "libft.h"
char	**g_env;

/*
${expression}
${parameter:-word}
${parameter:word}
${parameter:=word}
${parameter=word}
${parameter:?word}
${parameter?word}
${parameter:+word}
${parameter+word}
${#parameter}
${parameter%word}
${parameter%%word}
${parameter#word}
${parameter##word}
*/

//0000 0000 0000 0000
//

typedef struct	s_param
{
	uint16_t signe;
	char    *line;
	char	*param;
	char	*paramvalue;
	char	*word;
}				t_param;


# define UIERROR 2048
# define PARAMDEFAULT 1
# define PARAMASSIGN 2
# define PARAMERROR 4
# define PARAMALTERNATIVE 8
# define PARAMUNSET 16
# define LENGTH 32
# define ONEPER 64
# define DOUBLPER 128
# define ONEDIEZ 256
# define DOUBLDIEZ 512
# define PARMSTRERROR "parameter null or not set"

/*
 * PARSING
 */
void		check_diez(char c, char *arg, uint16_t *signe);
char		pars(char *arg, uint16_t *signe);
char		check_activeflag(uint16_t signe);
void		check_flag(char *arg, uint16_t *signe, int i);
void		check_default(char c, char *arg, uint16_t flag, uint16_t *signe);
void		check_percent(char c, char *arg, uint16_t *signe);

/*
 * TOOLS
 */

char	*get_var(char *name);
t_param		*init_param(uint16_t signe, char *arg);
char	*get_word(char *arg, uint16_t signe);
void        del_struct(t_param **param);

/*
 * param.c
 */
char	*no_param(t_param *param);
char	*param_assign(t_param *param);
char	*param_use(t_param *param);
char	*param_error(t_param *param);
char	*param_alternative(t_param *paramstruct);

/*
 * prambis.c
 */

char	*remove_small_pre_par(t_param *param);
char	*param_length(t_param *param);
char	*remove_small_suf_par(t_param *param);

#endif
