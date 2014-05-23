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