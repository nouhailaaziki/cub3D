#include "../cub3d.h"

void getmap_dimentions(char **map, int *h, int *w)
{
    *h = 0;
    *w = 0;
    int new_width;
    while (map[*h])
    {
        new_width = ft_strlen(map[*h]);
        if (new_width > *w)
            *w = new_width;
        (*h)++;
    }
}

void ft_bspace(int width, char **p)
{
    int i;

    *p = malloc(width + 1);
    i = 0;
    while (i < width)
        p[0][i++] = ' ';
    p[0][i] = '\0';
}

void the_right_line(int width, char **s)
{
    int i;
    int j;
    char *p;

    ft_bspace(width, &p);
    i = 0;
    j = 0;
    while (i < width)
    {
        if (i < ft_strlen(*s))
            p[j++] = (*s)[i];
        i++;
    }
    free(*s);
    *s = p;
}

void fix_map(char ***map_2d, int width)
{
    int i;
    char **new_map_2d = *map_2d;
    i = -1;
    while (new_map_2d[++i])
        the_right_line(width, &new_map_2d[i]);
}

int new_parsing(char *file, t_data *data)
{
    int fd;
    char *line;
    char *map_line;
    int height;
    int width;

    data->so = NULL;
    data->we = NULL;
    data->no = NULL;
    data->ea = NULL;
    data->f = NULL;
    data->c = NULL;
    map_line = NULL;
    int cp = 0;
    fd = openning_file(file);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            return (error_exit("missing f, c, so, no, we or ea"), 0);
        if (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1) || !ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
            extract_elements(line, &cp, data);
        free(line);
        if (cp == 6)
            break;
    }
    if (null_elements(data->so) || null_elements(data->we) || null_elements(data->no) || null_elements(data->ea) || null_elements(data->f) || null_elements(data->c))
        return (error_exit("duplicate in textures/colors"), 0);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        if (ft_strcmp(line, "\n"))
            break;
    }
    if (!line)
        return (error_exit("no map"), 0);
    while (1)
    {
        if (!line)
            break;
        if (!ft_strcmp(line, "\n"))
            return (error_exit("new lines in map"), 0);
        map_line = ft_strjoin(map_line, line);
        line = get_next_line(fd);
    }
    if (check_wrong_el(map_line))
        return (error_exit("something wrong in the map"), 0);
    if (check_colors(data->f, &data->floor) || check_colors(data->c, &data->ceileing))
        return (error_exit("wrong colors"), 0);
    data->map = ft_split(map_line, '\n');

    if (check_boundiries(data->map))
        return (error_exit("Map is not properly closed by walls"), 0);
    getmap_dimentions(data->map, &height, &width);
    fix_map(&data->map, width);
    return 1;
}
