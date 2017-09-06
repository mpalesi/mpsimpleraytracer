// Save to BMP
// 2017 Maurizio Palesi <maurizio.palesi@dieei.unict.it>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "savebmp.h"

int SaveBMP(char *fname, unsigned long *img, int width, int height)
{
  FILE          *f;
  unsigned char *img_rgb;
  int           filesize = 54 + 3 * width * height;  
  int           idx_img, idx_img_rgb;

  img_rgb = (unsigned char*)malloc(width * height * 3);
  if (img_rgb == NULL)
    return -1;

  idx_img = 0;
  idx_img_rgb = 0;
  for (int y=0; y<height; y++)
    for (int x=0; x<width; x++)
    {
      unsigned long pixel = *(img + idx_img++);
      *(img_rgb + idx_img_rgb++) = pixel >> 16;
      *(img_rgb + idx_img_rgb++) = (pixel >> 8) & 0xff;
      *(img_rgb + idx_img_rgb++) = pixel & 0xff;
    }

  unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
  unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
  unsigned char bmppad[3] = {0,0,0};

  bmpfileheader[ 2] = (unsigned char)(filesize    );
  bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
  bmpfileheader[ 4] = (unsigned char)(filesize>>16);
  bmpfileheader[ 5] = (unsigned char)(filesize>>24);

  bmpinfoheader[ 4] = (unsigned char)(width);
  bmpinfoheader[ 5] = (unsigned char)(width >> 8);
  bmpinfoheader[ 6] = (unsigned char)(width >> 16);
  bmpinfoheader[ 7] = (unsigned char)(width >> 24);
  bmpinfoheader[ 8] = (unsigned char)(height);
  bmpinfoheader[ 9] = (unsigned char)(height >> 8);
  bmpinfoheader[10] = (unsigned char)(height >> 16);
  bmpinfoheader[11] = (unsigned char)(height >> 24);

  f = fopen(fname,"wb");
  if (f == NULL)
    return -2;

  fwrite(bmpfileheader, 1, 14, f);
  fwrite(bmpinfoheader, 1, 40, f);
  for(int y=0; y<height; y++)
  {
    fwrite(img_rgb+(width*(height-y-1)*3), 3, width, f);
    fwrite(bmppad, 1, (4-(width*3)%4)%4, f);
  }

  fclose(f);

  return 1;
}
