/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:18:17 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/28 14:29:49 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	*reg_calloc(size_t nmemb, size_t size, t_list **alloc)
{
	void	*ptr;
	t_list	*new_node;

	ptr = ft_calloc(nmemb, size);
	if (!ptr)
		return (NULL);
	new_node = ft_lstnew(ptr);
	if (!new_node)
		return (NULL);
	if (!*alloc)
		*alloc = new_node;
	else
		ft_lstadd_back(*alloc, new_node);
	return (ptr);
}

/*
	Counts the number of words in the string str separated by delim
*/
static int	count_words(const char *str, char delim)
{
	int		i;
	int		nwords;

	i = 0;
	nwords = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] == delim)
			i++;
		if (str[i] == '\0')
			break ;
		while (str[i] != '\0' && str[i] != delim)
			i++;
		nwords++;
	}
	return (nwords);
}

/*
	Takes the string pstr passed by reference and moves the pointer to the start
	of the first word it finds, ignoring all delim chars it finds.
*/
static int	find_next_word(const char **pstr, char delim, int prev_wlen)
{
	int	wlen;

	wlen = 0;
	*pstr += prev_wlen;
	while (**pstr != '\0' && **pstr == delim)
		*pstr += 1;
	if (**pstr == '\0')
		return (0);
	while ((*pstr)[wlen] != '\0' && (*pstr)[wlen] != delim)
		wlen += 1;
	return (wlen);
}

/*
	Frees all allocated strings in the string array and the array itself.
	Returns NULL.
*/
static void	*protect_alloc(char	***strtab)
{
	int	i;

	i = 0;
	while ((*strtab)[i] != NULL)
	{
		free((*strtab)[i]);
		i++;
	}
	free(*strtab);
	return (NULL);
}

char	**ft_reg_split(char const *s, char c, t_list *alloc)
{
	char	**strtab;
	int		nwords;
	int		wi;
	int		wlen;

	nwords = count_words(s, c);
	strtab = (char **) reg_calloc(nwords + 1, sizeof(char *), &alloc);
	if (strtab == NULL)
		return (NULL);
	strtab[nwords] = NULL;
	if (nwords == 0)
		return (strtab);
	wi = 0;
	wlen = 0;
	while (wi < nwords)
	{
		wlen = find_next_word(&s, c, wlen);
		strtab[wi] = (char *) reg_calloc(wlen + 1, sizeof(char), &alloc);
		if (strtab[wi] == NULL)
			return (protect_alloc(&strtab));
		ft_strlcpy(strtab[wi], s, wlen + 1);
		wi++;
	}	
	return (strtab);
}
