#pragma once

namespace yaps {

	/**
	 *	Class representing 2D coordinates
	 */
	class Coordinates {
	public:
		int x;
		int y;

        /**
         *	Default constructor
         */
        Coordinates() : x(0), y(0) { }

		/**
		 *	Constructor
		 *	@param newX	Init value for x coordinate
		 *	@param newX	Init value for y coordinate
		 */
		Coordinates(int newX, int newY) : x(newX), y(newY) { }

		/**
		 *	Destructor
		 */
		~Coordinates() { }
	};

}