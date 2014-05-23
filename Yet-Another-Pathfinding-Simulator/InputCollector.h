#pragma once

namespace yaps {

	/**
	 *  Class responible for loading data from input
	 */
	class InputCollector {
		DataMatrix<float> &riverBottom; // Reference to data matrix where read data should be put
		std::ifstream dataFile;			// File input stream
		sf::Image dataImage;			// RiverBottom map source (as image)
		bool parseImage;				// Flag to determin what kind of input do we have
		short errorCode;				// In case of an error, the code describing it should be placed here;

		/**
		 *	Load data from given text file to the matrix (distance x width)
		 *	@return true on success, false otherwise
		 */
		bool loadDataFromFile();

		/**
		 *	Load data from given image to the matrix (distance x width)
		 *	@return true on success, false otherwise
		 */
		bool loadDataFromImage();
	public:
		/**
		 *	Constructor
		 *	@param riverBottomRef Init value for riverBottom 
		 */
		InputCollector(DataMatrix<float> &);
		
		/**
		 *	Destructor
		 */
		~InputCollector();
		
		/**
		 *	Prepare file for reading data and check whether it is an image of text file
		 *	@param filePath Standard path to data source
		 *	@return true on success, false otherwise
		 */
		bool openFile(std::string);

		/**
		 *	Load proper data
		 *	@return true on success, false otherwise
		 */
		bool loadData();
	};

}
