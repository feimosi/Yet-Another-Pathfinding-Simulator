#pragma once

namespace yaps {
	
	/**
	 *	Class emulating standard 2D array, just for more convenience
	 */
	template <class T>
	class DataMatrix {
		T** _arrayOfArrays;
		int _height;
		int _width;
	public:
		/**
		 *	Constructor
		 *	@param height	Matrix height
		 *	@param width	Matrix width
		 */
		DataMatrix(int height, int width) : _width(width), _height(height) {
			// Allocate memory
			_arrayOfArrays = new T*[height];
			for (int i = 0; i < height; i++) {
				_arrayOfArrays[i] = new T[width];
				// Initilise with zeros
				for (int j = 0; j < width; j++) {
					_arrayOfArrays[i][j] = NULL;
				}
			}
		}

		/**
		 *	Destructor
		 */
		~DataMatrix() {
			for (int i = 0; i < _height; i++) {
				delete _arrayOfArrays[i];
			}
			delete _arrayOfArrays;
		}

		/**
		 *	Getters
		 */
		int getHeight() { return _height; }
		int getWidth() { return _width; }

		/**
		 *	Helper class for second dimension
		 */
		class Proxy {
			T* _array;
			int _width;
		public:
			Proxy(T* _array, int width) : _array(_array), _width(width) { }

			T &operator[](int index) {
				if (index >= _width || index < 0)
					throw "Index out of bound exception";
				return _array[index];
			}
		};

		/**
		 *	Overloaded [] operator
		 *	@param index
		 */
		Proxy operator[](int index) {
			if (index >= _height || index < 0)
				throw "Index out of bound exception";
			return Proxy(_arrayOfArrays[index], _width);
		}
	};

}