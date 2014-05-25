#pragma once
#include "Simulator.h"

namespace yaps {

	/**
	 *  Main application window and user interface
	 */
	class GUIView {
        static const int WINDOW_WIDTH = 800,
            WINDOW_HEIGHT = 600,
            MAP_WIDTH = 200,
            MAP_HEIGHT = 200,
            RED = 0, GREEN = 1, BLUE = 2,
            MAX_DEPTH = 6;
        Simulator simulator;
        
        /**
         *	Generate pixel array by upscaling data matrix and converting it to RGBA
         */
        sf::Uint8 *generateMapImage(const DataMatrix<float> &, sf::Uint8 *);
        
        /**
         *	Convert value from [0; MAX_DEPTH] to RGBA determined by flag
         *  @param value    Value to convert
         *  @param rgba     Flag describing color channel
         */
        sf::Uint8 castColor(float, int);
	public:
		/**
		 *	Constructor
		 *	@param width        Init value for simulator constructor
		 *	@param distance     Init value for simulator constructor
         *  @param dataSource   Path to the file
		 */
        GUIView(int, int, std::string);

		/**
		 *	Destructor
		 */
		~GUIView();
		
		/**
		 *	Main loop and user interface start point
		 */
		void run();
	};

}