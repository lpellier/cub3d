#include "cub3d.h"

void    drawLine(data_t data, int x0, int y0, int x1, int y1)
{
    int dx, dy, p, x, y, target;

    dx = abs(x1 - x0);
    dy = abs(y1 - y0);

    x = min(x0, x1);
    y = min(y0, y1);
    target = max(x0, x1);

    p = 2 * dy - dx;
    while (x < target)
    {
        if (p >= 0)
        {
            mlx_pixel_put(data.mlx_ptr, data.win_ptr, x, y, 16777215);
            y += 1;
            p += 2 * dy - 2 * dx;
        }
        else
        {
            mlx_pixel_put(data.mlx_ptr, data.win_ptr, x, y, 16777215);
            p += 2 * dy;
        }
        x += 1;
    } 
}

void    drawVerticalLine(data_t data, int x, int drawStart, int drawEnd, int color)
{
    int y;
    int target;
    y = drawStart > drawEnd ? drawEnd : drawStart;
    target = drawStart > drawEnd ? drawStart : drawEnd;
    while  (y < target)
    {
        mlx_pixel_put(data.mlx_ptr, data.win_ptr, x, y, color);
        y += 1;
    }
}

void putVerticalLineToImage(data_t *data, int x, int drawStart, int drawEnd, int color) {
	int count_h = -1;
	int width = 640;
	while (++count_h < width) {
		if (count_h < drawStart) {
			data->img.data[count_h * width + x] = 0xFFFFFF;
		}
		else if (count_h >= drawStart && count_h <= drawEnd) {
			data->img.data[count_h * width + x] = color;
		}
		else
		{
			data->img.data[count_h * width + x] = 0xFFFFFF;
		}
	}
}

void        drawSquare(data_t data, int x, int y, int width, int height)
{
    drawLine(data, x, y, x + width, y); // first horizontal
    drawVerticalLine(data, x, y, x, y + height); // first vertical
    drawVerticalLine(data, x + width, y, x + width, y + height); // second vertical
    drawLine(data, x + width, y + height, x, y + height); //second horizontal
}