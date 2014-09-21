

/* Fast DCT algorithm due to Arai, Agui, Nakajima 
 * Implementation due to Tim Kientzle
 *
 * cf http://en.wikipedia.org/wiki/Discrete_cosine_transform "Multidimensional DCTs"
 *
 * taken from http://unix4lyfe.org/dct/
 */

#include "image.h"

#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

pixel_t pixel(image * img, int x, int y){
  return img->data[y*img->w +x];
}

pixel_t * pixelPtr(image * img, int x, int y){
  return &(img->data[y*img->w +x]);
}

void dct(image *tga, float data[8*8],
	const int xpos, const int ypos)
{
	int i;
	int rows[8][8];

	static const int	c1=1004 /* cos(pi/16) << 10 */,
				s1=200 /* sin(pi/16)  << 10 */,
				c3=851 /* cos(3pi/16) << 10 */,
				s3=569 /* sin(3pi/16) << 10 */,
				r2c6=554 /* sqrt(2)*cos(6pi/16) << 10 */,
				r2s6=1337 /* sqrt(2)*sin(6pi/16) << 10 */,
				r2=181; /* sqrt(2) << 7*/

	int x0,x1,x2,x3,x4,x5,x6,x7,x8;

	/* transform rows */
	for (i=0; i<8; i++)
	{
		x0 = pixel(tga, xpos+0, ypos+i);
		x1 = pixel(tga, xpos+1, ypos+i);
		x2 = pixel(tga, xpos+2, ypos+i);
		x3 = pixel(tga, xpos+3, ypos+i);
		x4 = pixel(tga, xpos+4, ypos+i);
		x5 = pixel(tga, xpos+5, ypos+i);
		x6 = pixel(tga, xpos+6, ypos+i);
		x7 = pixel(tga, xpos+7, ypos+i);

		/* Stage 1 */
		x8=x7+x0;
		x0-=x7;
		x7=x1+x6;
		x1-=x6;
		x6=x2+x5;
		x2-=x5;
		x5=x3+x4;
		x3-=x4;

		/* Stage 2 */
		x4=x8+x5;
		x8-=x5;
		x5=x7+x6;
		x7-=x6;
		x6=c1*(x1+x2);
		x2=(-s1-c1)*x2+x6;
		x1=(s1-c1)*x1+x6;
		x6=c3*(x0+x3);
		x3=(-s3-c3)*x3+x6;
		x0=(s3-c3)*x0+x6;

		/* Stage 3 */
		x6=x4+x5;
		x4-=x5;
		x5=r2c6*(x7+x8);
		x7=(-r2s6-r2c6)*x7+x5;
		x8=(r2s6-r2c6)*x8+x5;
		x5=x0+x2;
		x0-=x2;
		x2=x3+x1;
		x3-=x1;

		/* Stage 4 and output */
		rows[i][0]=x6;
		rows[i][4]=x4;
		rows[i][2]=x8>>10;
		rows[i][6]=x7>>10;
		rows[i][7]=(x2-x5)>>10;
		rows[i][1]=(x2+x5)>>10;
		rows[i][3]=(x3*r2)>>17;
		rows[i][5]=(x0*r2)>>17;
	}

	/* transform columns */
	for (i=0; i<8; i++)
	{
		x0 = rows[0][i];
		x1 = rows[1][i];
		x2 = rows[2][i];
		x3 = rows[3][i];
		x4 = rows[4][i];
		x5 = rows[5][i];
		x6 = rows[6][i];
		x7 = rows[7][i];

		/* Stage 1 */
		x8=x7+x0;
		x0-=x7;
		x7=x1+x6;
		x1-=x6;
		x6=x2+x5;
		x2-=x5;
		x5=x3+x4;
		x3-=x4;

		/* Stage 2 */
		x4=x8+x5;
		x8-=x5;
		x5=x7+x6;
		x7-=x6;
		x6=c1*(x1+x2);
		x2=(-s1-c1)*x2+x6;
		x1=(s1-c1)*x1+x6;
		x6=c3*(x0+x3);
		x3=(-s3-c3)*x3+x6;
		x0=(s3-c3)*x0+x6;

		/* Stage 3 */
		x6=x4+x5;
		x4-=x5;
		x5=r2c6*(x7+x8);
		x7=(-r2s6-r2c6)*x7+x5;
		x8=(r2s6-r2c6)*x8+x5;
		x5=x0+x2;
		x0-=x2;
		x2=x3+x1;
		x3-=x1;

		/* Stage 4 and output */
		data[0*8+i]=(float)((x6+16)>>3);
		data[4*8+i]=(float)((x4+16)>>3);
		data[2*8+i]=(float)((x8+16384)>>13);
		data[6*8+i]=(float)((x7+16384)>>13);
		data[7*8+i]=(float)((x2-x5+16384)>>13);
		data[1*8+i]=(float)((x2+x5+16384)>>13);
		data[3*8+i]=(float)(((x3>>8)*r2+8192)>>12);
		data[5*8+i]=(float)(((x0>>8)*r2+8192)>>12);
	}
}



#define COEFFS(Cu,Cv,u,v) { \
	if (u == 0) Cu = 1.0 / sqrt(2.0); else Cu = 1.0; \
	if (v == 0) Cv = 1.0 / sqrt(2.0); else Cv = 1.0; \
	}

void idct(image *tga, float data[8*8], const int xpos, const int ypos)
{
	int u,v,x,y;
	for (y=0; y<8; y++)
	for (x=0; x<8; x++)
	{
		float z = 0.0;

		for (v=0; v<8; v++)
		for (u=0; u<8; u++)
		{
			float S, q;
			float Cu, Cv;
			
			COEFFS(Cu,Cv,u,v);
			S = data[v*8+u];

			q = Cu * Cv * S *
				cos((float)(2*x+1) * (float)u * M_PI/16.0) *
				cos((float)(2*y+1) * (float)v * M_PI/16.0);

			z += q;
		}

		z /= 4.0;
		if (z > 127.0) z = 127.0;
		if (z < -128) z = -128.0;

		*pixelPtr(tga, x+xpos, y+ypos) = (pixel_t) z;
	}
}

