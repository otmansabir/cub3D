#include "mlx.h"



void draw_line(t_globel **globle, int color)
{
    int dx;
    int dy;
    int line;
    double x;
    double y;
    double px;
    double py;
    
    dx = (*globle)->g_player->line_x - (*globle)->g_player->pos_x;
    dy = (*globle)->g_player->line_y - (*globle)->g_player->pos_y;
    if (abs(dx) > abs(dy))
        line = abs(dx);
    else
        line = abs(dy);
    x = (double)dx / (double)line;
    y = (double)dy / (double)line;
    px = (*globle)->g_player->pos_x;
    py = (*globle)->g_player->pos_y;
    
    // Get image data address and other parameters
    char *image_data;
    int bits_per_pixel;
    int size_line;
    int endian;
    image_data = mlx_get_data_addr((*globle)->mlx->mlx_window, &bits_per_pixel, &size_line, &endian);
    
    while (line--)
    {
        // Calculate pixel position in the image data buffer
        int pixel_pos = ((int)py * size_line) + ((int)px * (bits_per_pixel / 8));
        // Write pixel color to the image data buffer
        image_data[pixel_pos] = color & 0xFF;               // Blue component
        image_data[pixel_pos + 1] = (color >> 8) & 0xFF;    // Green component
        image_data[pixel_pos + 2] = (color >> 16) & 0xFF;   // Red component
        // The alpha component is not used in this case
        
        px += x;
        py += y;
    }
}




































int main() {
    void *mlx_ptr;
    void *mlx_win;
    void *img_ptr;
    char *img_data;
    int bpp;
    int size_line;
    int endian;

    // Initialize mlx_ptr and mlx_win
    mlx_ptr = mlx_init();
    mlx_win = mlx_new_window(mlx_ptr, 800, 600, "My Window");

    // Create an image
    img_ptr = mlx_new_image(mlx_ptr, 800, 600);

    // Get image information
    img_data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);

    // Use img_data to manipulate image pixels
    // e.g., img_data[offset] = color;

    // Display image on window
    mlx_put_image_to_window(mlx_ptr, mlx_win, img_ptr, 0, 0);

    // Start event loop
    mlx_loop(mlx_ptr);

    return 0;
}
