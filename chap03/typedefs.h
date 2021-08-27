
#ifndef  __TYPEDEFS_H_
#define  __TYPEDEFS_H_

#define PI 3.14159

/**< @brief Complex Data Structure */
struct COMPLEX {
    float real;
    float image;

    inline COMPLEX() { }

    inline COMPLEX(float real, float image) {
        this->real = real;
        this->image = image;
    }

    inline COMPLEX operator +(const COMPLEX& complex) {
        return COMPLEX(real + complex.real, image + complex.image);
    }

    inline COMPLEX operator -(const COMPLEX& complex) {
        return COMPLEX(real - complex.real, image - complex.image);
    }

    inline COMPLEX operator *(const COMPLEX& complex) {
        return COMPLEX(
            real * complex.real - image * complex.image, 
            real * complex.image + image * complex.real
        );
    }

    COMPLEX* operator +=(const COMPLEX& complex) {
        real += complex.real;
        image += complex.image;
        return this;
    }

    COMPLEX* operator -=(const COMPLEX& complex) {
        real -= complex.real;
        image -= complex.image;
        return this;
    }
};    

#endif  //__TYPEDEFS_H_
