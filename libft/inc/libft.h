/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:58:46 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/10/10 15:01:37 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include "ft_printf.h"
# include "get_next_line.h"

typedef struct s_alloc	t_alloc;

typedef enum e_alloc_code
{
	FALSE,
	TRUE,
	ALLOC,
	UNLINK,
	FREE,
	CLEAR,
	SIZE
}	t_alloc_code;

typedef struct s_alloc
{
	void			*ptr;
	int				critical;
	struct s_alloc	*next;
}	t_alloc;

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}	t_list;

int			ft_abs(int n);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isblank(int c);
int			ft_issign(int c);
int			ft_isspace(int c);
int			ft_isascii(int c);
int			ft_islove(int c);
int			ft_isseparator(int c);
int			ft_issplitable(int c);
int			ft_ispunct(int c);
int			ft_isprint(int c);
int			ft_ischevron(int c);
int			ft_isquote(int c);
int			ft_ispipe(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_nlen_base(long long int n, int base);
int			ft_nlen_ubase(unsigned long int n, int base);
int			ft_putnbr_base(long long int n, char *base);
int			ft_putchar(char c);
int			ft_putstr(char *s);

int			ft_int_ovcheck(const char *number);
int			ft_long_ovcheck(const char *number);
int			check_long_long_overflow(const char *number);
int			ft_atoi(const char *nptr);
long int	ft_atol(const char *nptr);
long long	ft_atoll(const char *nptr);

size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);

void		ft_bzero(void *s, size_t n);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_free_tab(char **tab, int height);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putnbr(int n);

void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_calloc(size_t nmemb, size_t size, int critical);

char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strdup(const char *s, int critical);
char		*ft_substr(char const *s, unsigned int start, size_t len, int crt);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strjoin(char const *s1, char const *s2, int critical);
char		*ft_free_strjoin(char *s1, char *s2, int critical);
char		*ft_strtrim(char const *s1, char const *set, int critical);
char		*ft_itoa(int n, int critical);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char), int crt);

char		**ft_split(char const *s, char c, int critical);
char		**ft_strdup_array(char **to_copy, int height, int critical);
char		**ft_lstsplit(t_list *lst, int critical);

//t_list
int			ft_lstsize(t_list *lst);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstnew(void *data, int critical);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), \
			void (*del)(void *), int crt);

//allocator
void		*walloc(int size, int critical);
void		wclear(int free_critical);
void		wfree(void *ptr);
void		wunlink(void *ptr);
void		*ft_allocator(int size, t_alloc_code code, void *ptr, int critical);
void		al_lstadd(t_alloc **al_lst, t_alloc *new);
int			al_lstdelone(t_alloc **al_lst_head, t_alloc *al_to_del);
void		al_lstclear(t_alloc **al_lst, int free_critical);
t_alloc		*al_lstnew(void *content, int critical);

#endif
