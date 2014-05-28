#pragma once

namespace yaps {

    /**
        *Class for reading depth values from heat maps
        *Finds avarage value of a 4 by 4 pixels square by:
        * - reading RGB value of each pixel
        * - converting it to HSV and then HSV to integer
        * - if it's in range[0, 264] integer value is normalized else discarded
        Returns avarage value of calculated values [if all were discarded returns -nan]
        **/
    class MapParse
    {
    public:
        /**
        * Constructor
        * @param image data
        **/
        MapParse(sf::Image img);


        /**
            *return avarage value of a 4x4 square with x, y coordinates
            * @param x - x coordinate of square
            * @param y - y coordinate
            **/
        float avarageValue(int, int);


        /**
        * Destructor
        **/
        ~MapParse();

    protected:
    private:
        sf::Image img;                              // Variable with image data
        /**
            * Converts HSV to a int value in [0, 1]
            * @param h  value of H channel
            * @param s  value of S channel
            * @param v  value of V channel
            * @param value  reference to result variable
            **/
        void hsvtoint(float, float, float, float&);
        /**
        * Converts RGB to HSV model, based on http://en.wikipedia.org/wiki/HSL_and_HSV article.
        * @param r  value of R channel
        * @param g  value of G channel
        * @param b  value of B channel
        * @param h  reference to H variable
        * @param s  reference to S variable
        * @param v  reference to V variable
        **/
        void rgbtohsv(int, int, int,
            float&, float&, float&);      //Function for RGB to HSV conversion

    };

}
