#include "mlx.h"
#include "minirt.h"

int main()
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	if (mlx_ptr == NULL)
		exit(1);
	win_ptr = mlx_new_window(mlx_ptr, 640, 640, "TEST");
	mlx_loop(mlx_ptr);
}