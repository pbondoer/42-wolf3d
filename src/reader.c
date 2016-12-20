/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 21:49:22 by pbondoer          #+#    #+#             */
/*   Updated: 2016/12/20 13:17:50 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "wolf.h"
#include <fcntl.h>

static void		*cleanup(t_list *lst, t_map *m)
{
	t_list	*next;
	int		i;

	i = 0;
	while (lst)
	{
		next = lst->next;
		ft_memdel(&lst->content);
		ft_memdel((void **)&lst);
		lst = next;
	}
	if (m)
	{
		if (m->values)
			while (i < m->height)
				if (m->values[i])
					ft_memdel((void **)(m->values + i));
		ft_memdel((void **)&m);
	}
	return (NULL);
}

static t_list	*get_lines(int fd)
{
	static int	expected = -1;
	t_list		*lst;
	t_list		*temp;
	char		*line;
	int			ret;

	lst = NULL;
	while ((ret = get_next_line(fd, &line)))
	{
		if (expected == -1)
			expected = ft_countwords(line, ' ');
		if (expected == 0 || ft_countwords(line, ' ') != expected ||
			(temp = ft_lstnew(line, ft_strlen(line) + sizeof(char))) == NULL)
			return (cleanup(lst, NULL));
		ft_strdel(&line);
		ft_lstadd(&lst, temp);
	}
	if (ret == -1)
		return (cleanup(lst, NULL));
	ft_lstrev(&lst);
	return (lst);
}

static t_map	*populate_map(t_map *m, t_list *list, int max)
{
	t_list	*lst;
	char	**split;
	int		x;
	int		y;

	lst = list;
	y = 0;
	while (y < m->height)
	{
		x = 0;
		if ((split = ft_strsplit(lst->content, ' ')) == NULL)
			return (cleanup(list, m));
		while (x < m->width)
		{
			if ((m->values[x][y] = ft_atoi(split[x])) < 0 ||
					m->values[x][y] > max)
				return (cleanup(list, m));
			x++;
		}
		ft_splitdel(&split);
		lst = lst->next;
		y++;
	}
	cleanup(list, NULL);
	return (m);
}

static t_map	*new_map(int w, int h)
{
	t_map	*m;
	int		i;

	if ((m = (t_map *)ft_memalloc(sizeof(t_map))) == NULL)
		return (NULL);
	m->width = w;
	m->height = h;
	if ((m->values = (int **)ft_memalloc(sizeof(int *) * w)) == NULL)
	{
		ft_memdel((void **)&m);
		return (NULL);
	}
	i = 0;
	while (i < h)
	{
		if ((m->values[i] = (int *)ft_memalloc(sizeof(int) * h)) == NULL)
		{
			while (i > 0)
				ft_memdel((void **)(m->values + --i));
			ft_memdel((void **)&m);
			return (NULL);
		}
		i++;
	}
	return (m);
}

t_map			*read_map(char *file, int max)
{
	t_list	*lst;
	t_map	*map;
	int		fd;

	if ((fd = open(file, O_RDONLY)) == -1 ||
			(lst = get_lines(fd)) == NULL)
		return (NULL);
	map = new_map(ft_countwords((char *)lst->content, ' '), ft_lstcount(lst));
	if (map == NULL || populate_map(map, lst, max) == NULL)
		return (cleanup(lst, NULL));
	return (map);
}
