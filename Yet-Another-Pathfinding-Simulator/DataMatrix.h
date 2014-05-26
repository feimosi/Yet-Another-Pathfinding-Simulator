#pragma once

namespace yaps {

    /**
     *  Class emulating standard 2D array, just for more convenience
     */
    template <class T>
    class DataMatrix {
        T** _arrayOfArrays;
        int _height;
        int _width;
	float _max = -1;
    public:
        /**
         *  Constructor
         *  @param height   Matrix height
         *  @param width    Matrix width
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
         *  Copy constructor performing deep copy
         *  @param toCopy
         */
        DataMatrix(const DataMatrix& toCopy) {
            _height = toCopy._height;
            _width = toCopy._width;
            _arrayOfArrays = new T*[_height];
            for (int i = 0; i < _height; i++) {
                _arrayOfArrays[i] = new T[_width];
                for (int j = 0; j < _width; j++) {
                    _arrayOfArrays[i][j] = toCopy._arrayOfArrays[i][j];
                }
            }
        }

        /**
         *  Destructor
         */
        ~DataMatrix() {
            for (int i = 0; i < _height; i++) {
                delete _arrayOfArrays[i];
            }
            delete _arrayOfArrays;
        }

        /**
         *  Getters and setters
         */
        int getHeight() const { return _height; }
        int getWidth() const { return _width; }
        void setMax(float m) {_max = m;}
        float getMax() const {return _max;}

        /**
         *  Helper class for second dimension
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

            const T &operator[](int index) const {
                if (index >= _width || index < 0)
                    throw "Index out of bound exception";
                return _array[index];
            }
        };

        /**
         *  Overloaded [] operator
         *  @param index
         *  @return 'Proxy' object to access second dimension
         */
        Proxy operator[](int index) {
            if (index >= _height || index < 0)
                throw "Index out of bound exception";
            return Proxy(_arrayOfArrays[index], _width);
        }

        /**
         *  Overloaded [] operator for const objects
         *  @param index
         *  @return 'Proxy' object to access second dimension
         */
        const Proxy operator[](int index) const {
            if (index >= _height || index < 0)
                throw "Index out of bound exception";
            return Proxy(_arrayOfArrays[index], _width);
        }
    };

}
