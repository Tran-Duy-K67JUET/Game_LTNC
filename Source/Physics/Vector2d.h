#ifndef Vector2D_H
#define Vector2D_H

#include <iostream>

class Vector2D {
public:
    float X, Y;
    Vector2D(float x = 0, float y = 0): X(x), Y(y) {
    }

    inline Vector2D operator + (const Vector2D &other) const {
        return Vector2D(X + other.X, Y + other.Y);
    }

    inline Vector2D operator - (const Vector2D &other) const {
        return Vector2D(X - other.X, Y - other.Y);
    }

    inline Vector2D operator * (const float scl) const {
        return Vector2D(X * scl, Y * scl);
    }

    void Log(std::string msg = "" ) {
        std::cout << msg << "(X Y) = (" << X << " " << Y << ")" << std::endl;
    }
};
#endif // Vector2D_H
