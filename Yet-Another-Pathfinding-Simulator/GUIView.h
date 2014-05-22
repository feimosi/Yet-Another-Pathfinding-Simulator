#pragma once

namespace yaps {

	/**
	 *  Main application window and user interface
	 */
	class GUIView {
		static const int SCREEN_WIDTH = 800;
		static const int SCREEN_HEIGHT = 600;
	public:
		/**
		 *	Constructor
		 *	@param width	Init value for riverBottom constructor
		 *	@param distance	Init value for riverBottom constructor
		 */
		GUIView();

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