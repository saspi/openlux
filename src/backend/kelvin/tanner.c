/*
  Copyright (c) 2015 Anonymous Meerkat

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#include "kelvin.h"

#include "../../util.h"
#include <math.h>
#include <stddef.h>

int
ol_backend_kelvin_tanner_init(struct ol_backend_kelvin_s* self)
{
  OL_UTIL_UNUSED(self);
  return 0;
}

void
ol_backend_kelvin_tanner_uninit(struct ol_backend_kelvin_s* self)
{
  OL_UTIL_UNUSED(self);
}


/* Implementation of
   http://www.tannerhelland.com/4435/convert-temperature-rgb-algorithm-code/ */
struct ol_color_s
ol_backend_kelvin_tanner_kelvin(struct ol_backend_kelvin_s* self,
                                ol_kelvin_t kelvin)
{
  OL_UTIL_UNUSED(self);

  ol_color_channel_t red   = 0.;
  ol_color_channel_t green = 0.;
  ol_color_channel_t blue  = 0.;

  kelvin /= 100.;

  if (kelvin <= 66.)
    {
      red = 255.;

      green = 99.4708025861 * log(kelvin) - 161.1195681661;
    }
  else
    {
      red = 329.698727446 * pow((kelvin - 60.), -0.1332047592);

      green = 288.1221695283 * pow((kelvin - 60.), -0.0755148492);
    }

  if (kelvin >= 66.)
    {
      blue = 255.;
    }
  else
    {
      if (kelvin <= 19.)
        {
          blue = 0.;
        }
      else
        {
          blue = 138.5177312231 * log(kelvin - 10.) - 305.0447927307;
        }
    }

  red   /= 255.;
  green /= 255.;
  blue  /= 255.;

  red   = OL_COLOR_LIMIT(red);
  green = OL_COLOR_LIMIT(green);
  blue  = OL_COLOR_LIMIT(blue);

  return OL_COLOR_INIT(red, green, blue);
}


struct ol_backend_kelvin_s ol_backend_kelvin_tanner =
{
  .data     = NULL,

  .init     = ol_backend_kelvin_tanner_init,
  .uninit   = ol_backend_kelvin_tanner_uninit,

  .kelvin   = ol_backend_kelvin_tanner_kelvin
};
