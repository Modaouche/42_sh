/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgheraie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 05:21:32 by mgheraie          #+#    #+#             */
/*   Updated: 2019/08/03 02:14:27 by mgheraie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TEST_H
# define FT_TEST_H
# include "libft.h"
# include "shell.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdint.h>

# define TEST_E 1
# define TEST_B 2
# define TEST_C 3
# define TEST_D 4
# define TEST_F 5
# define TEST_G 6
# define TEST_L 7
# define TEST_P 8
# define TEST_SS 9
# define TEST_U 10
# define TEST_R 11
# define TEST_W 12
# define TEST_X 13
# define TEST_S 14
# define TEST_Z 15
# define TEST_EQUAL 16
# define TEST_DIFF 17
# define TEST_EQ 18
# define TEST_NE 19
# define TEST_GE 20
# define TEST_LT 21
# define TEST_LE 22
# define TEST_NO 23

# define TEST_STRE "-e"
# define TEST_STRB "-b"
# define TEST_STRC "-c"
# define TEST_STRD "-d"
# define TEST_STRF "-f"
# define TEST_STRG "-g"
# define TEST_STRL "-L"
# define TEST_STRP "-p"
# define TEST_STRSS "-S"
# define TEST_STRU "-u"
# define TEST_STRR "-r"
# define TEST_STRW "-w"
# define TEST_STRX "-x"
# define TEST_STRS "-s"

# define TEST_STRZ "-z"
# define TEST_STREQUAL "="
# define TEST_STRDIFF "!="

# define TEST_STREQ "-eq"
# define TEST_STRNE "-ne"
# define TEST_STRGE "-ge"
# define TEST_STRLT "-lt"
# define TEST_STRLE "-le"
# define TEST_STRNO "!"

# define TRUE 1
# define FALSE 0
# define ERROR 2

char			test_check_chmod_file(struct stat buf, uint8_t flag);

char			test_othr(mode_t mode);
char			test_othw(mode_t mode);
char			test_othx(mode_t mode);
char			test_grpw(mode_t mode);
char			test_grpr(mode_t mode);

char			test_check_type_file(uint8_t flag, mode_t mode);

char			ft_test(uint16_t flag, char **arg);
char			go(char **av);

char			test_nbr_error(char **arg);
void			print_no_int(char **args);
char			test_pars_nbr(char **args);
char			test_flag_nbr(uint16_t flag, void *s);

void			test_get_strflag(uint16_t flag);
char			test_flag_str(uint16_t flag, void *s);
char			test_flag_z(uint16_t flag, void *s);

char			test_flag_file(uint16_t flag, void *s);

char			test_fifo(mode_t m);
char			test_blk(mode_t m);
char			test_chr(mode_t m);
char			test_dir(mode_t m);
char			test_reg(mode_t m);

uint16_t		test_get_id_flag_str(char *tmp);
uint16_t		test_get_id_flag_file(char *tmp);
uint16_t		test_get_id_flag_nbr(char *tmp);
uint16_t		test_get_id_flag(char *tmp);
uint16_t		test_set_id_flag(char **tmp);

char			*test_get_pathname(char *s);
char			test_get_stat(char *p, char *n, struct stat *t, DIR *d);
DIR				*test_opendir(char *s);
char			*test_get_filename(char *s, char *buf);

size_t			ft_dstrlen(char **s);
int				ft_strgetlastocc(char *s, char c);
int				ft_strchri(char *str, char c);

#endif
