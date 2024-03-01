/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:11:56 by gde-win           #+#    #+#             */
/*   Updated: 2024/02/29 12:47:52 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

FILE		*fd;
int			scan;
static char	window[300][300];

typedef struct s_tab
{
	int		W;
	int		H;
	char	c;
}	t_tab;
t_tab	tab;

typedef struct s_circle
{
	char	type;
	float	X;
	float	Y;
	float	W;
	float	H;
	char	c;
}	t_circle;

void ft_display()
{
	int	i;

	i = 0;
	while (i < tab.H)
	{
		write(1, window[i], tab.W);
		write(1, "\n", 1);
		i++;
	}
}

int	ft_isCircle(t_circle c, float i, float j)
{
	float result;

	result = c.R - (float)sqrt((c.X - j) * (c.X - j) + (c.Y - i) * (c.Y - i));
	if (0 <= result)
	{
		if (1 <= result && c.type == 'c')
			return (0);
		return (1);
	}
	return (0);
}

void	ft_draw(t_circle c)
{
	int	i;
	int	j;

	i = 0;
	while (i < tab.H)
	{
		j = 0;
		while (j < tab.W)
		{
			if (ft_isCircle(c, (float)i, (float)j))
				window[i][j] = c.c;
			j++;
		}
		i++;
	}
}

int	ft_invalidCircle(t_circle circle)
{
	if (circle.type != 'r' && circle.type != 'R')
		return (1);
	if (circle.W <= 0 || circle.H <= 0)
		return (1);
	return (0);
}

int	ft_outOfBounds(int W, int H)
{
	if (W <= 0 || 300 < W || H <= 0 || 300 < H)
		return (1);
	return (0);
}

int	ft_error(int flag)
{
	if (flag == 0)
		write(1, "Error: argument\n", 16);
	if (flag == 1)
		write(1, "Error: Operation file corrupted\n", 32);
	return (1);
}

int	main(int ac, char **av)
{
	t_circle	circle;

	if (ac != 2)
		return (ft_error(0));
	fd = fopen(av[1], "r");
	if (fd == NULL)
		return (ft_error(1));
	scan = fscanf(fd, " %i %i %c ", &tab.W, &tab.H, &tab.c);
	if (scan != 3 || ft_outOfBounds(tab.W, tab.H))
		return (ft_error(1));
	memset(window, tab.c, sizeof(char) * 300 * 300);
	while (scan != 0 && scan != EOF)
	{
		scan = fscanf(fd, " %c %f %f %f %f %c ", &circle.type, &circle.X, &circle.Y, &circle.W, &circle.H, &circle.c);
		if (scan == 0 || scan == EOF)
			break ;
		if (scan != 6 || ft_invalidCircle(circle))
			return (ft_error(1));
		ft_draw(circle);
	}
	ft_display();
	return (0);
}
