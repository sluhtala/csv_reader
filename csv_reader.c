
#include "csv_reader.h"

void		error_manager(char *str)
{
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

static int	check_filetype(char *name)
{
	int i;

	i = 0;
	while (name[i])
	{
		if (name[i] == '.')
		{
			if (ft_strcmp(name + i, ".csv" ) == 0)
				return (1);
		}
		i++;
	}
	return (0);
}

void		csv_delete(t_csv_table *csv)
{
	int i;
	int j;
	if (csv->table == NULL)
		return ;
	j = 0;
	while (j < csv->rows)
	{
		i = 0;
		while (i < csv->cols)
		{
			if (csv->table[j][i])
				free(csv->table[j][i]);
			i++;
		}
		if (csv->table[j])
			free(csv->table[j]);
		j++;	
	}
	if (csv->table)
		free(csv->table);
	csv->table = NULL;
}

void	csv_print_table(t_csv_table *csv)
{
	int i;
	int j;

	j = 0;
	if (!csv)
		return ;
	ft_printf("rows: %d columnss: %d\n", csv->rows, csv->cols);
	while (j < csv->rows)
	{
		i = 0;
		while (i < csv->cols)
		{
			if (csv->table[j][i])
				ft_printf("%-5.5s|", csv->table[j][i]);
			else
				ft_printf("%-5s|", "");
			i++;
		}
		ft_putchar('\n');
		while (i > 0)
		{
			i--;
			ft_printf("------");
		}
		ft_putchar('\n');
		j++;
	}
}

t_csv_table csv_read_file(char *filename)
{
	t_csv_table csv;
	char		delim;

	delim = ';';
	if (!check_filetype(filename))
		error_manager("CSV error not .csv file");
	csv.rows = 0;
	csv.cols = 0;
	csv.table = NULL;
	csv.delete = &csv_delete;
	csv.print = &csv_print_table;
	csv_calculate_rows_and_colums(&csv, filename, delim);
	csv_allocate_rows_and_colums(&csv);
	csv_read_cells(&csv, filename, delim);
	return (csv);
}

/*
int main()
{
	t_csv_table csv;
	csv = csv_read_file("scene6.csv");
	csv.print(&csv);
	csv.delete(&csv);

	return (0);
}
*/
