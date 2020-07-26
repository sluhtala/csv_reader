#include "include/csv_reader.h"
#include "libft.h"
#include "ft_printf.h"

int main(int ac, char **av)
{
	t_csv_table csv;
	if (ac != 2)
	{
		ft_printf("Usage: %s filename\n", av[0]);
		return (0);
	}
	csv = csv_read_file(av[1]);	
	csv.print(&csv);
	csv.delete(&csv);
	return (0);
}
