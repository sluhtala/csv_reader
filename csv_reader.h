
#ifndef CSV_READER_H
# define CSV_READER_H

# include "libft/include/libft.h"
# include <fcntl.h>
typedef struct	s_csv_table
{
	int		cols;
	int		rows;
	char	***table;
	void(*delete)(struct s_csv_table*);
	void(*print)(struct s_csv_table*);
}				t_csv_table;

t_csv_table csv_read_file(char *filename);
void		csv_read_cells(t_csv_table *csv, char *file, char delim);
void	csv_print_table(t_csv_table *csv);
void		csv_delete(t_csv_table *csv);
void		error_manager(char *str);
void	csv_calculate_rows_and_colums(t_csv_table *csv, char *file, char delim);
void		csv_allocate_rows_and_colums(t_csv_table *csv);


# endif
