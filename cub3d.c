/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:07:39 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/09/03 18:49:41 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
    t_data data;

    if (validate_args(argc, argv) != 0)
    {
        free_cub3d(&data);
        return (1);
    }
    if (new_parsing(argv[1], &data) == 0)
    {
        write(2, "Error: Parsing failed\n", 22);
        free_cub3d(&data);
        return (1);
    }
    /////printing data and map just for testing
    printf("ceileing\n");
    printf("|%d|\n", data.ceileing.r);
    printf("|%d|\n", data.ceileing.g);
    printf("|%d|\n", data.ceileing.b);
    printf("floor\n");
    printf("|%d|\n", data.floor.r);
    printf("|%d|\n", data.floor.g);
    printf("|%d|\n", data.floor.b);
    printf("ea\n");
    printf("|%s|\n", data.ea);
    printf("no\n");
    printf("|%s|\n", data.no);
    printf("so\n");
    printf("|%s|\n", data.so);
    printf("we\n");
    printf("|%s|\n", data.we);
    int i = 0;
    while (data.map[i])
        printf("|%s|\n", data.map[i++]);
    /////////////////////////
    free_cub3d(&data);
    return (0);
}
