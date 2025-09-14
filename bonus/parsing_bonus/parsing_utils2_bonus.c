/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:40:03 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/09/14 09:01:22 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/launchpad_bonus.h"

int null_elements(char *el)
{
    if (!el || !*el)
        return 1;
    return 0;
}

int check_wrong_el(char *line)
{
    int i = 0;
    int cp = 0;
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\n' && line[i] != '0' && line[i] != '1' && line[i] != 'S' && line[i] != 'N' && line[i] != 'W' && line[i] != 'E' && line[i] != 'D' && line[i] != '\r')
            return 1;
        if (line[i] == 'S' || line[i] == 'N' || line[i] == 'W' || line[i] == 'E')
            cp++;

        i++;
    }
    if (cp != 1)
        return 1;

    return 0;
}

int check_colors(char *line, t_colors *color)
{
    char **colors;
    int i;
    int j;

    i = ft_strlen(line) - 1;
    while (line[i] && (line[i] == '\n' || line[i] == '\r'))
    {
        line[i] = '\0';
        i--;
    }
    colors = ft_split(line, ',');
    i = 0;
    while (colors[i])
    {
        j = 0;
        while (colors[i][j])
        {
            if (colors[i][j] > '9' || colors[i][j] < '0')
                return (error_exit("wrong colors not a number"), 1);
            j++;
        }
        if (j > 3 || j < 1)
            return (error_exit("wrong colors out of 0 - 255 "), 1);
        i++;
    }
    if (i != 3)
        return (error_exit("wrong colors missing color number "), 1);
    color->r = ft_atoi(colors[0]);
    color->g = ft_atoi(colors[1]);
    color->b = ft_atoi(colors[2]);
    if (color->r > 255 || color->g > 255 || color->b > 255)
        return (error_exit("wrong colors grater then 255"), 1);
    return 0;
}

int check_zero(char c)
{
    if (c == ' ' || c == '\0')
        return 1;
    return 0;
}

int check_boundiries(char **map)
{
    int i;
    int j;
    int height;

    height = 0;
    while (map[height])
        height++;
    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == '0')
            {
                if (j + 1 >= ft_strlen(map[i]) || check_zero(map[i][j + 1]))
                    return 1;
                if (j - 1 < 0 || check_zero(map[i][j - 1]))
                    return 1;
                if (i + 1 >= height || j >= ft_strlen(map[i + 1]) || check_zero(map[i + 1][j]))
                    return 1;
                if (i - 1 < 0 || j >= ft_strlen(map[i - 1]) || check_zero(map[i - 1][j]))
                    return 1;
            }
            j++;
        }
        i++;
    }
    return 0;
}


// int check_boundiries(char **map)
// {
//     int i;
//     int j;

//     i = 0;
//     while (map[i])
//     {
//         j = 0;
//         while (map[i][j])
//         {
//             if (map[i][j] == '0' && (i == 0 || j == 0 || !map[i][j + 1] || !map[i][j - 1] || !map[i + 1][j] || !map[i - 1][j] ||
//                                      check_zero(map[i][j + 1]) || check_zero(map[i][j - 1]) || check_zero(map[i + 1][j]) || check_zero(map[i - 1][j])))
//                 return 1;

//             j++;
//         }
//         i++;
//     }
//     return 0;
// }
