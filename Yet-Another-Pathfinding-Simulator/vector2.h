#pragma once

namespace yaps {

    /**
     *   2D Vector Manipulation and Transformation
     *   @url https://github.com/LaurentGomila/SFML/wiki/Source:-2D-Vector-Manipulation
     */
    class VECTOR2 {
        const float PI = 3.14159265358979323846f;
    public:
        /* The x and y values of this vector */
        float x, y;

        VECTOR2(void);
        VECTOR2(float, float);
        VECTOR2(int, int);
        VECTOR2(unsigned, unsigned);
        ~VECTOR2(void);

        /*
         * Assign operator
         * @VECTOR2     Vector to assign
         * ->VECTOR2    this
         */
        VECTOR2& operator=(const VECTOR2);

        /*
         * Add and assign operator
         * @VECTOR2     Vector to add against
         * ->VECTOR2    this
         */
        VECTOR2& operator+=(const VECTOR2);

        /*
         * Add operator
         * @VECTOR2     Vector for adding against
         * ->VECTOR2    Result
         */
        VECTOR2 operator+(const VECTOR2) const;

        /*
         * Subtract and assign operator
         * @VECTOR2     Vector to subtract against
         * ->VECTOR2    this
         */
        VECTOR2& operator-=(const VECTOR2);

        /*
         * Subtract operator
         * @VECTOR2     Vector for subtracting against
         * ->VECTOR2    Result
         */
        VECTOR2 operator-(const VECTOR2) const;

        /*
         * Multiply and assign operator
         * @float       Scalar for multiplying against
         * ->VECTOR2    this
         */
        VECTOR2& operator*=(float);

        /*
         * Multiply operator
         * @float       Scalar for multiplying against
         * ->VECTOR2    Result
         */
        VECTOR2 operator*(float) const;

        /*
         * Divide and assign operator
         * @float       Scalar for dividing against
         * ->VECTOR2    this
         */
        VECTOR2& operator/=(float);

        /*
         * Divide operator
         * @float       Scalar for dividing against
         * ->VECTOR2    Result
         */
        VECTOR2 operator/(float) const;

        /*
         * Rotate and assign operator
         * @float       Theta for rotating against
         * ->VECTOR2    this
         */
        VECTOR2& operator%=(float);

        /*
         * Rotate operator
         * @float       Theta for rotating against
         * ->VECTOR2    Result
         */
        VECTOR2 operator%(float) const;

        /*
         * Equals operator
         * @VECTOR2     Vector for comparing against
         * ->bool       Result
         */
        bool operator==(const VECTOR2);

        /*
         * Not equals operator
         * @VECTOR2     Vector for comparing against
         * ->bool       Result
         */
        bool operator!=(const VECTOR2);

        /*
         * The dot product of this and another vector
         * @VECTOR2     Vector for comparing against
         * ->float      The dot product
         */
        float dot(const VECTOR2);

        /*
         * The normalization of this vector
         * ->VECTOR2    A new vector that equals this vector normalized
         */
        VECTOR2 norm();

        /*
         * Truncates this vector
         * @float       Value to truncate by
         * ->VECTOR2        this
         */
        VECTOR2& trunc(float);

        /*
         * The angle of this vector
         * ->float      This vector's angle in radians
         */
        float ang();

        /*
         * The magnitude of this vector
         * ->float      This vector's magnitude
         */
        float mag();

        /*
         * Reassigns this vector's values to the specified values
         * @float       The new x value
         * @float       The new y value
         */
        void reassign(float, float);

        /*
         * Reassigns this vector's values to the vector
         * @VECTOR2     The new vector
         */
        void reassign(VECTOR2);

        /*
         * Converts this vector to a SFML vector
         * -> sf::Vector2f  The new vector
         */
        const sf::Vector2f sf() { return sf::Vector2f(this->x, this->y); }

        /*
         * A string representation of this vector
         * ->std::string    This vector to a string
         */
        const std::string to_str();
    };

}