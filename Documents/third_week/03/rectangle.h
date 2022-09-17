#pragma once
#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED
class Rectangle {
public:
    Rectangle(int, int );
    int GetArea() const;
    int GetPerimeter() const;
    int GetWidth() const;
    int GetHeight() const;
private:
    int width_, height_;
};


#endif // RECTANGLE_H_INCLUDED
