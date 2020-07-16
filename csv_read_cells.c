#include "csv_reader.h"

static	int ft_strclen(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static void csv_cpy_cell_cols(t_csv_table *csv, char *line, int row, char delim)
{
	int i;
	char *split;
	int len;
	int col;

	i = 0;
	col = 0;
	while (line[i])
	{
		if (line[i] != delim && col < csv->cols)
		{
			len = ft_strclen(line + i, delim);
			split = ft_strnew(len + 1);
			if (len > 0)
				split = ft_strncpy(split, line + i,ft_strclen(line + i, delim));
			csv->table[row][col] = split;
			col++;
		}
		i += len;
		i++;
	}
}

void		csv_read_cells(t_csv_table *csv, char *file, char delim)
{
	int fd;
	int ret;
	int row;
	char *line;

	row = 0;
	if (!(fd = open(file, O_RDONLY)))
		error_manager("CSV error reading file.");
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		csv_cpy_cell_cols(csv, line, row, delim);
		row++;
		free(line);
	}
	if (ret == -1)
		error_manager("CSV error reading file");
	close(fd);
}

void		csv_allocate_rows_and_colums(t_csv_table *csv)
{
	int i;
	int j;

	i = 0;
	if (!(csv->table = (char***)malloc(sizeof(char**) * csv->rows)))
		error_manager("CSV error allocating table");	
	while (i < csv->rows)
	{
		j = 0;
		if (!(csv->table[i] = (char**)malloc(sizeof(char*) * csv->cols)))
			error_manager("CSV error allocating table");	
		while (j < csv->cols)
		{
			csv->table[i][j] = NULL;
			j++;
		}
		i++;
	}
}

void	csv_calculate_rows_and_colums(t_csv_table *csv, char *file, char delim)
{
	int		cols;
	char	*line;
	int		i;
	int		fd;

	if (!(fd = open(file, O_RDONLY)))
		error_manager("CSV error reading file.");
	csv->rows = 0;
	csv->cols = 0;
	while (get_next_line(fd, &line) > 0)
	{
		cols = 0;
		i = 0;
		while (line[i])
		{
			if (line[i] == delim)
				cols++;
			i++;
		}
		if (cols > csv->cols)
			csv->cols = cols;
		free(line);
		csv->rows++;
	}
	close(fd);
}
