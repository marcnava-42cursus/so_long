#include "../include/so_long.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct s_game
{
	mlx_t	*mlx;
	mlx_image_t	*image;
	int32_t	speed;
} t_game;

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	t_game *game = param;

	// Verifica que la imagen está correctamente inicializada
	if (game->image == NULL)
	{
		fprintf(stderr, "Error: game->image is NULL\n");
		return;
	}

	for (uint32_t i = 0; i < game->image->width; ++i)
	{
		for (uint32_t y = 0; y < game->image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(game->image, i, y, color);
		}
	}
}

void ft_hook(void* param)
{
	t_game *game = param;

	// Verifica que la imagen y las instancias están correctamente inicializadas
	if (game->image == NULL || game->image->instances == NULL)
	{
		fprintf(stderr, "Error: game->image or game->image->instances is NULL\n");
		return;
	}

	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP) || mlx_is_key_down(game->mlx, MLX_KEY_W))
		game->image->instances[0].y -= game->speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN) || mlx_is_key_down(game->mlx, MLX_KEY_S))
		game->image->instances[0].y += game->speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT) || mlx_is_key_down(game->mlx, MLX_KEY_A))
		game->image->instances[0].x -= game->speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT) || mlx_is_key_down(game->mlx, MLX_KEY_D))
		game->image->instances[0].x += game->speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_KP_SUBTRACT) && game->speed > 0)
		game->speed -= 1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_KP_ADD))
		game->speed += 1;
}

// -----------------------------------------------------------------------------

int32_t main(void)
{
	mlx_t* mlx;
	t_game	*game;

	// Asignar memoria para la estructura game
	game = malloc(sizeof(t_game));  // <-- Aquí está la asignación de memoria

	if (!game)
	{
		perror("Failed to allocate memory for game structure");
		return (EXIT_FAILURE);
	}

	game->speed = 5;

	// Inicializar MLX
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		free(game);  // No olvides liberar la memoria al final si fallas
		return(EXIT_FAILURE);
	}

	// Crear la imagen
	if (!(game->image = mlx_new_image(mlx, 128, 128)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		free(game);  // Liberar memoria en caso de error
		return(EXIT_FAILURE);
	}

	// Verifica que la imagen fue creada correctamente
	if (game->image == NULL)
	{
		fprintf(stderr, "Error: Failed to create image\n");
		free(game);
		return(EXIT_FAILURE);
	}

	// Poner la imagen en la ventana
	if (mlx_image_to_window(mlx, game->image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		free(game);  // Liberar memoria en caso de error
		return(EXIT_FAILURE);
	}

	// Registrar los hooks
	mlx_loop_hook(mlx, ft_randomize, game);
	mlx_loop_hook(mlx, ft_hook, game);

	mlx_loop(mlx);
	mlx_terminate(mlx);

	// Liberar la memoria al final
	free(game);  // Liberar la memoria de la estructura game
	return (EXIT_SUCCESS);
}
