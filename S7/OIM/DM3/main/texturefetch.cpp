#include "texturefetch.hpp"
#include <iostream>

/*
 *  Pour la documentation de ces fonctions, se rapporter à la page "Textures" de la documentation
 */
/*
 * @brief getTexel Get a single texel from a texture.
 * This function access the texture at coordinates (row, column) and fetch the value of the corresponding texel (pixel from a texture)
 * @param pixels    The image to access, organized as a linear array of texel arranged by row
 * @param width     Width of the image
 * @param height    Height of the image
 * @param depth     Depth of the image (number of component by texel)
 * @param row       Row coordinate of the requested texel
 * @param column    Column coordinate of the requested texel
 * @return          The value of the texel
 * @todo            Transfom the 2D coordinates in a 1D index and get the corresponding texel value
 */
Color getTexel(unsigned char *pixels, int width, int height, int depth, int column, int row){
    Color color(1.0, 1.0, 1.0);

    if(depth == 1){
    	color = (float) pixels[(column+row*width)*depth]/255.f;
    } else {
    	color = Color (pixels[(column+row*width)*depth]/255.f, pixels[column*depth+row*width*depth+1]/255.f, pixels[column*depth+row*width*depth+2]/255.f);
    }

    return color;
}

/*
 * @brief interpolateTexture Get a texel linearly interpolated from its neighbors
 * @param pixels    The image to access, organized as a linear array of texel arranged by row
 * @param width     Width of the image
 * @param height    Height of the image
 * @param depth     Depth of the image (number of component by texel)
 * @param s         The column coordinate of the requested texel as a floating point
 * @param t         The row coordinate of the requested texel as a floating point
 * @return          The value of the interpolated texel
 * @todo            Devoir 3, 2014 : From the floating point coordinates, compute the integer part and the fractional part. The integer part is the used to acces the 4 texels implied in the interpolation (One texel and its 3 up and right neighors), the fractional part is used to linearly interpolate from neighbors.
 */

  float f(float x){
  	return x-floor(x);
  }

 Color interpolateTexture(unsigned char *pixels, int width, int height, int depth, float s, float t){
 	Color q11, q12, q21, q22, r1, r2;
 	q11 = getTexel(pixels, width, height, depth, (int) s, (int) t);
 	q12 = getTexel(pixels, width, height, depth, (int) s, (int) t+1); 
 	q21 = getTexel(pixels, width, height, depth, (int) s + 1, (int) t); 
 	q22 = getTexel(pixels, width, height, depth, (int) s + 1, (int) t+1);
 	
 	r1  = q11+Color(q21[0]-q11[0],q21[1]-q11[1],q21[2]-q11[2])*f(s);
 	r2  = q12+Color(q22[0]-q12[0],q22[1]-q12[1],q22[2]-q12[2])*f(s);
 	
 	return (r1+Color(r2[0]-r1[0], r2[1]-r1[1], r2[2]-r1[2])*f(t));
 }
/*
 * @brief integrateTexture Get a texel by computing the mean of the color on a neighborood of size (deltas x deltat)
 * @param pixels    The image to access, organized as a linear array of texel arranged by row
 * @param width     Width of the image
 * @param height    Height of the image
 * @param depth     Depth of the image (number of component by texel)
 * @param s         The column coordinate of the requested texel as a floating point
 * @param t         The row coordinate of the requested texel as a floating point
 * @param deltas    The size, in the column dimension, of the neighborood
 * @param deltat    The size, in the row dimension, of the neighborood
 * @return
 * @todo
 */
Color integrateTexture(unsigned char *pixels, int width, int height, int depth, float s, float t, int deltas, int deltat){
	int intOfS = std::floor(s);
	int intOfT = std::floor(t);
	int i,j;
	Color color = Color(0.f);

	for(i = intOfS; i < (intOfS + deltas); i++){
		for(j = intOfT; j < (intOfT + deltat); j++){
			color = color + getTexel(pixels, width, height, depth, i, j) ;
		}
	}

	float deltats = (float) 1/(deltas * deltat);
	color = color * deltats;

	return color;
}
/*
 * @brief getPixel Get a single pixel from a image.
 * This function access the pixel at coordinates (row, column)
 * @param pixels    The image to access, organized as a linear array of texel arranged by row
 * @param width     Width of the image
 * @param height    Height of the image
 * @param depth     Depth of the image (number of component by texel)
 * @param row       Row coordinate of the requested texel
 * @param column    Column coordinate of the requested texel
 * @return          The value of the texel
 */
 Color getPixel(unsigned char *pixels, int width, int height, int depth, int column, int row) {
	Color color(0.f);
    int i,j;

    for (i = 2*column; i <= (2*column)+1; i++) {
    	for (j = 2*row; j <= (2*row)+1; j++)
            	color = color + getTexel(pixels, width, height, depth, i, j);
    }
    color = color * (1.0/4.0);

	return color;
}
/*
 * @brief prefilterTexture Compute an array of images with geometrically decreasing resolution from the original image.
 * @param imagearray The array of images to compute. element at index 0 in this array is the full resolution image and must not be modified
 * @param width     Width of the full resolution image
 * @param height    Height of the full resolution image
 * @param depth     Depth of the image (number of component by texel)
 * @param nblevels  Number of level to compute : nblevels = log2(min(width, height))
 * @return          if the array may be filled, return true, else return false
 */
bool prefilterTexture(unsigned char **imagearray, int width, int height, int depth, int nblevels){
 	int I, oldWidth, oldHeight, column, row;

 	for (I = 1; I < nblevels; I++) {
		oldWidth = width;
		oldHeight = height;
		width = (oldWidth/2);
		height = (oldHeight/2);

		imagearray[I] = (unsigned char*)malloc(sizeof(unsigned char)*(width*height*depth));

		if (width < 2 || height < 2){
			return true;
		}

		for (column = 0; column < width; column++) {
			for (row = 0; row < height; row++) {
				Color color = getPixel(imagearray[I-1], oldWidth, oldHeight, depth, column, row);
				int index = (row * width + column) * depth;
				imagearray[I][index] 	= (unsigned char)std::floor(color[0] * 255);
				imagearray[I][index+1] 	= (unsigned char)std::floor(color[1] * 255);
				imagearray[I][index+2] 	= (unsigned char)std::floor(color[2] * 255);
			}
		}
	}
	
	return false;
 }
