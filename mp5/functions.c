#include "functions.h"
#include "math.h"
/*
 * getRadius - returns the radius based on the sigma value
 * INPUTS: sigma - sigma in the Guassian distribution
 * OUTPUTS: none
 * RETURN VALUE: radius - radius of the filter
 */
int getRadius(double sigma)
{
  /*Write your function here*/
int radius;
    radius = ceil(3*sigma);
  return radius;
}

/*
 * calculateGausFilter - calculates the Gaussian filter
 * INTPUTS: gausFitler - pointer to the array for the gaussian filter
 *          sigma - the sigma in the Gaussian distribution
 * OUTPUTS: none
 * RETURN VALUE: none
 */
void calculateGausFilter(double *gausFilter,double sigma)
{
  /*Write your function here*/
int radius = getRadius(sigma);
int x,y;
double sum=0,Gx,Gx_each;
for (x=radius;x>=-radius;x--)
{
 for (y=radius;y>=-radius;y--)
 {
  Gx = (1/sqrt(2*M_PI*pow(sigma,2)))*exp(-(pow(x,2)+pow(y,2))/(2*pow(sigma,2)));
  sum = sum+Gx;
 }
}
for (x=radius;x>=-radius;x--)
{
 for (y=radius;y>=-radius;y--)
 {
  Gx_each = (1/sqrt(2*M_PI*pow(sigma,2)))*exp(-(pow(x,2)+pow(y,2))/(2*pow(sigma,2)))/sum;
  *gausFilter=Gx_each;
   gausFilter++;
 }
}

  return;
}

/* convolveImage - performs a convolution between a filter and image
 * INPUTS: inRed - pointer to the input red channel
 *         inGreen - pointer to the input green channel
 *         inBlue - pointer to the input blue channel
 *         inAlpha - pointer to the input alpha channel
 *         filter - pointer to the convolution filter
 *         radius - radius of the convolution filter
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel
 *          outGreen - pointer to the output green channel
 *          outBlue - pointer to the output blue channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void convolveImage(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                   uint8_t *inAlpha, uint8_t *outRed,uint8_t *outGreen,
                   uint8_t *outBlue,uint8_t *outAlpha,const double *filter,
                   int radius,int width,int height)
{
  /*Write your function here*/
int x,y,i,j,n;
double red=0.0,blue=0.0,green=0.0;
  if (radius<1)
  {
for (x=0;x<=height-1;x++)
{
for (y=0;y<=width-1;y++)
 {
  outRed[x*width+y]=inRed[x*width+y];
  outGreen[x*width+y]=inGreen[x*width+y];
  outBlue[x*width+y]=inBlue[x*width+y];
  }
}
}
else{
for (x=0;x<=height-1;x++)
{
 for (y=0;y<=width-1;y++)
 {
	red=0.0;
	blue=0.0;
	green=0.0;
	n=0;
   for (i=-radius;i<=radius;i++)
   {
   for (j=-radius;j<=radius;j++)
   {
    if ((x+i)>=0 && (x+i)<height && (y+j)>=0 && (y+j)<width)
    {
     red=red+inRed[(x+i)*width+(y+j)]*filter[n];
     blue=blue+inBlue[(x+i)*width+(y+j)]*filter[n];
     green=green+inGreen[(x+i)*width+(y+j)]*filter[n];
    }
	n++;
   }
   }
red=max(red,0.0);
red=min(red,255.0);
green=max(green,0.0);
green=min(green,255.0);
blue=max(blue,0.0);
blue=min(blue,255.0);

outRed[x*width+y]=red;
outGreen[x*width+y]=green;
outBlue[x*width+y]=blue;
outAlpha[x*width+y]=inAlpha[x*width+y];
}
 }
}

  return;
}

/* convertToGray - convert the input image to grayscale
 * INPUTS: inRed - pointer to the input red channel
 *         inGreen - pointer to the input green channel
 *         inBlue - pointer to the input blue channel
 *         inAlpha - pointer to the input alpha channel
 *         gMonoMult - pointer to array with constants to be multipiled with 
 *                     RBG channels to convert image to grayscale
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel
 *          outGreen - pointer to the output green channel
 *          outBlue - pointer to the output blue channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void convertToGray(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                   uint8_t *inAlpha,uint8_t *outRed,uint8_t *outGreen,
                   uint8_t *outBlue,uint8_t *outAlpha,
                   const double *gMonoMult,int width,int height)
{
  /*Challenge- Write your function here*/
  return;
}

/* invertImage - inverts the colors of the image
 * INPUTS: inRed - pointer to the input red channel
 *         inGreen - pointer to the input green channel
 *         inBlue - pointer to the input blue channel
 *         inAlpha - pointer to the input alpha channel
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel
 *          outGreen - pointer to the output green channel
 *          outBlue - pointer to the output blue channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void invertImage(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                 uint8_t *inAlpha,uint8_t *outRed,uint8_t *outGreen,
                 uint8_t *outBlue,uint8_t *outAlpha,int width,int height)
{
  /*Challenge- Write your function here*/
    int j=0;
    int i=0;
    for(j=0;j<height;j++){
	for(i=0;i<width;i++){
		outRed[j*width+i]=255.0-inRed[j*width+i];
		outBlue[j*width+i]=255.0-inBlue[j*width+i];
		outGreen[j*width+i]=255.0-inGreen[j*width+i];
		outAlpha[j*width+i]=inAlpha[j*width+i];
	}
    }
  return;
}

/* pixelate - pixelates the image
 * INPUTS: inRed - pointer to the input red channel
 *         inGreen - pointer to the input green channel
 *         inBlue - pointer to the input blue channel
 *         inAlpha - pointer to the input alpha channel
 *         pixelateY - height of the block
 *         pixelateX - width of the block
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel
 *          outGreen - pointer to the output green channel
 *          outBlue - pointer to the output blue channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void pixelate(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,uint8_t *inAlpha,
              uint8_t *outRed,uint8_t *outGreen,uint8_t *outBlue,
              uint8_t *outAlpha,int pixelY,int pixelX,int width,int height)
{
  /*Challenge- Write your function here*/
  return;
}

/* colorDodge - blends the bottom layer with the top layer
 * INPUTS: aRed - pointer to the bottom red channel
 *         aGreen - pointer to the bottom green channel
 *         aBlue - pointer to the bottom blue channel
 *         aAlpha - pointer to the bottom alpha channel
 *         bRed - pointer to the top red channel
 *         bGreen - pointer to the top green channel
 *         bBlue - pointer to the top blue channel
 *         bAlpha - pointer to the top alpha channel
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel
 *          outGreen - pointer to the output green channel
 *          outBlue - pointer to the output blue channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void colorDodge(uint8_t *aRed,uint8_t *aGreen,uint8_t *aBlue,
                uint8_t *aAlpha,uint8_t *bRed,uint8_t *bGreen,
                uint8_t *bBlue,uint8_t *bAlpha,uint8_t *outRed,
                uint8_t *outGreen,uint8_t *outBlue,uint8_t *outAlpha,
                int width,int height)
{
   /*Challenge- Write your function here*/
   return;
}

/* pencilSketch - creates a pencil sketch of the input image
 * INPUTS: inRed - pointer to the input red channel
 *         inGreen - pointer to the input green channel
 *         inBlue - pointer to the input blue channel
 *         inAlpha - pointer to the input alpha channel
 *         invRed - pointer to temporary red channel for inversion
 *         invGreen - pointer to temporary green channel for inversion
 *         invBlue - pointer to temporary blue channel for inversion
 *         invAlpha - pointer to temporary alpha channel for inversion
 *         blurRed - pointer to temporary red channel for blurring
 *         blurGreen - pointer to temporary green channel for blurring
 *         blurBlue - pointer to temporary blue channel for blurring
 *         blurAlpha - pointer to temporary alpha channel for blurring
 *         filter - pointer to the gaussian filter to blur the image
 *         radius - radius of the gaussian filter
 *         width - width of the input image
 *         height - height of the input image
 *         gMonoMult - pointer to array with constants to be multipiled with 
 *                     RBG channels to convert image to grayscale
 * OUTPUTS: outRed - pointer to the output red channel
 *          outGreen - pointer to the output green channel
 *          outBlue - pointer to the output blue channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void pencilSketch(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                  uint8_t *inAlpha,uint8_t *invRed,uint8_t *invGreen,
                  uint8_t *invBlue,uint8_t *invAlpha,uint8_t *blurRed,
                  uint8_t *blurGreen,uint8_t *blurBlue,uint8_t *blurAlpha,
                  uint8_t *outRed,uint8_t *outGreen,uint8_t *outBlue,
                  uint8_t *outAlpha,const double *filter,int radius,int width,
                  int height,const double *gMonoMult)
{
    /*Challenge- Write your function here*/
    return;
}

/* transformImage - Computes an linear transformation of the input image
 * INPUTS: inRed - pointer to the input red channel
 *         inGreen - pointer to the input green channel
 *         inBlue - pointer to the input blue channel
 *         inAlpha - pointer to the input alpha channel
 *	    transform - two dimensional array containing transform coefficients of matrix T and vector S
 *         width - width of the input and output image
 *         height - height of the input and output image
 * OUTPUTS: outRed - pointer to the output red channel
 *          outGreen - pointer to the output green channel
 *          outBlue - pointer to the output blue channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void transformImage(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,uint8_t *inAlpha,
              uint8_t *outRed,uint8_t *outGreen,uint8_t *outBlue,
              uint8_t *outAlpha,double transform[2][3],int width,int height)
{
     /*Write your function here*/
int x,y,trans_x,trans_y;
for (trans_x=0;trans_x<=height-1;trans_x++)
{
 for (trans_y=0;trans_y<=width-1;trans_y++)
 {
  nearestPixel(trans_x,trans_y,transform,&x,&y,width,height);
  if (x>=0 && x<=height-1 && y>=0 && y<=width-1)
  {
  outGreen[trans_x*width+trans_y]=inGreen[x*width+y];
  outAlpha[trans_x*width+trans_y]=inAlpha[x*width+y];
  outRed[trans_x*width+trans_y]=inRed[x*width+y];
  outBlue[trans_x*width+trans_y]=inBlue[x*width+y];

  }
  else
  {
  outRed[trans_x*width+trans_y]=0.0;
  outBlue[trans_x*width+trans_y]=0.0;
  outGreen[trans_x*width+trans_y]=0.0;
  outAlpha[trans_x*width+trans_y]=255.0;
  }
 }
}
     return;
}

/* nearestPixel - computes the inverse transform to find the closest pixel in the original image
 * INPUTS: pixelYtransform - row value in transformed image
 *         pixelXtransform - column value in transformed image
 *         transform - two dimensional array containing transform coefficients of matrix T and vector S
 *         width - width of the input and output image
 *         height - height of the input and output image
 * OUTPUTS: pixelY - pointer to row value in original image
 *	    pixelX - pointer to column value in original image
 * RETURN VALUES: none
 */
void nearestPixel(int pixelYTransform, int pixelXTransform, double transform[2][3],
              int *pixelY, int *pixelX, int width, int height)
{
     /*Write your function here*/
double coeff,x_s,y_s;
coeff = 1/(transform[0][0]*transform[1][1]-transform[0][1]*transform[1][0]);
x_s=pixelXTransform-transform[0][2]-(width-1)/2;
y_s=pixelYTransform-transform[1][2]-(height-1)/2;
*pixelX=round(coeff*(transform[1][1]*x_s-transform[0][1]*y_s)+(width-1)/2);
*pixelY=round(coeff*(-transform[1][0]*x_s+transform[0][0]*y_s)+(height-1)/2);


     return;
}

