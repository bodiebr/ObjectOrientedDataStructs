#include <iostream>
#include <cmath>
#include <cstdlib>

#include "uiuc/PNG.h"
#include "uiuc/HSLAPixel.h"
#include "ImageTransform.h"

/* ******************
(Begin multi-line comment...)

Write your name and email address in the comment space here:

Name:
Email:

(...end multi-line comment.)
******************** */

using uiuc::PNG;
using uiuc::HSLAPixel;

/**
 * Returns an image that has been transformed to grayscale.
 *
 * The saturation of every pixel is set to 0, removing any color.
 *
 * @return The grayscale image.
 */
PNG grayscale(PNG image) {
  /// This function is already written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);

      // `pixel` is a reference to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly. No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }

  return image;
}



/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the luminance of a pixel based on the distance the pixel
 * is away from the center by decreasing the luminance by 0.5% per 1 pixel euclidean
 * distance away from the center.
 *
 * For example, a pixel 3 pixels above and 4 pixels to the right of the center
 * is a total of `sqrt((3 * 3) + (4 * 4)) = sqrt(25) = 5` pixels away and
 * its luminance is decreased by 2.5% (0.975x its original value).  At a
 * distance over 160 pixels away, the luminance will always decreased by 80%.
 * 
 * The modified PNG is then returned.
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 *
 * @return The image with a spotlight.
 */
PNG createSpotlight(PNG image, int centerX, int centerY) {
    for (unsigned x = 0; x < image.width(); x++) {
        for (unsigned y = 0; y < image.height(); y++) {
            HSLAPixel & pixel = image.getPixel(x, y);
            double distance_from_center;
            int xdistance = x - centerX;
            int ydistance = y - centerY;
            distance_from_center = pow(xdistance, 2.0) + pow(ydistance, 2.0);
            distance_from_center = sqrt(distance_from_center);
            double amount_decreased;
            if (distance_from_center > 160){
                amount_decreased = 0.2;
            }
            else{
                amount_decreased = (1 - (0.005*distance_from_center));
            }
            pixel.l *= amount_decreased;
        }
    }
  return image;
  
}
 

/**
 * Returns a image transformed to Illini colors.
 *
 * The hue of every pixel is set to the a hue value of either orange or
 * blue, based on if the pixel's hue value is closer to orange than blue.
 *
 * @param image A PNG object which holds the image data to be modified.
 *
 * @return The illinify'd image.
**/
PNG illinify(PNG image) {
      for (unsigned x = 0; x < image.width(); x++) {
          for (unsigned y = 0; y < image.height(); y++) {
              HSLAPixel & pixel = image.getPixel(x, y);
              int orange_diff1 = pixel.h -11;
              if (orange_diff1<0){orange_diff1*=-1;}
              int orange_diff2 = 371 - pixel.h;
              int orange_diff = (orange_diff1<orange_diff2)?orange_diff1:orange_diff2;
              int blue_diff1 = pixel.h -216;
              if (blue_diff1<0){blue_diff1*=-1;}
              int blue_diff2 = 576 - pixel.h;
              int blue_diff = (blue_diff1<blue_diff2)?blue_diff1:blue_diff2;
              if (orange_diff < blue_diff){
                  pixel.h = 11;
              }
              else{
                  pixel.h = 216;
              }
        }
      }
      return image;
  }
 

/**
* Returns an immge that has been watermarked by another image.
*
* The luminance of every pixel of the second image is checked, if that
* pixel's luminance is 1 (100%), then the pixel at the same location on
* the first image has its luminance increased by 0.2.
*
* @param firstImage  The first of the two PNGs, which is the base image.
* @param secondImage The second of the two PNGs, which acts as the stencil.
*
* @return The watermarked image.
*/
PNG watermark(PNG firstImage, PNG secondImage) {
    for (unsigned x = 0; x < secondImage.width(); x++) {
        for (unsigned y = 0; y < secondImage.height(); y++) {
            HSLAPixel & pixel = secondImage.getPixel(x, y);
            if (pixel.l == 1){
                HSLAPixel & pixel1 = firstImage.getPixel(x, y);
                pixel1.l += 0.2;
            }
        }
    }
  return firstImage;
}
