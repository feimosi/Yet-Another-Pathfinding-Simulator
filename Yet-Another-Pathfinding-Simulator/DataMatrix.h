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
    public:
        const int RESERVED_HEIGHT;
        const int RESERVED_WIDTH;

        /**
         *  Constructor
         *  @param height   Matrix height
         *  @param width    Matrix width
         */
        DataMatrix(int height, int width) : RESERVED_HEIGHT(height), RESERVED_WIDTH(width), _width(0), _height(0) {
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
            _height = toCopy._height < RESERVED_HEIGHT ? toCopy._height : RESERVED_HEIGHT;
            _width = toCopy._width < RESERVED_WIDTH ? toCopy._width : RESERVED_WIDTH;
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
            for (int i = 0; i < RESERVED_HEIGHT; i++) {
                delete _arrayOfArrays[i];
            }
            delete _arrayOfArrays;
        }

        /**
         *  Getters and setters
         *  You can set width and height only less than actual matrix dimensions (reserved in memory)
         */
        int getHeight() const { return _height; }
        int getWidth() const { return _width; }
        
        int setHeight(int newHeight) {
            int oldHeight = _height;
            if (newHeight <= RESERVED_HEIGHT)
                _height = newHeight;
            return oldHeight;
        }

        int setWidth(int newWidth) {
            int oldWidth = _width;
            if (newWidth <= RESERVED_WIDTH)
                _width = newWidth;
            return oldWidth;
        }

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
            if (index >= RESERVED_HEIGHT || index < 0)
                throw "Index out of bound exception";
            return Proxy(_arrayOfArrays[index], RESERVED_WIDTH);
        }

        /**
         *  Overloaded [] operator for const objects
         *  @param index
         *  @return 'Proxy' object to access second dimension
         */
        const Proxy operator[](int index) const {
            if (index >= RESERVED_HEIGHT || index < 0)
                throw "Index out of bound exception";
            return Proxy(_arrayOfArrays[index], RESERVED_WIDTH);
        }

        /**
         *  Copy data from another matrix performing deep copy
         *  @param toCopy
         */
        void copy(const DataMatrix& toCopy) {
            _height = toCopy._height < RESERVED_HEIGHT ? toCopy._height : RESERVED_HEIGHT;
            _width = toCopy._width < RESERVED_WIDTH ? toCopy._width : RESERVED_WIDTH;
            for (int i = 0; i < _height; i++) {
                _arrayOfArrays[i] = new T[_width];
                for (int j = 0; j < _width; j++) {
                    _arrayOfArrays[i][j] = toCopy._arrayOfArrays[i][j];
                }
            }
        }
    };

}
