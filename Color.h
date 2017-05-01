#ifndef COLOR_H
#define COLOR_H

#include <vector>

class Color
{
public:
    float getR() const;
    float getG() const;
    float getB() const;
    float getA() const;
    void setR(float specter);
    void setG(float specter);
    void setB(float specter);
    void setA(float specter);
    Color(float r, float g, float b, float a);
    Color();
    bool operator==(const Color& other) const;
    bool operator!=(const Color& other) const;
    static Color Red, Green, Blue, Cyan, Orange, Purple, Yellow, Black, White, Gray, TranslucidBlack;
    void set();
    static void unset();
private:
    static bool equal(const Color& c1, const Color& c2);
    float r, g, b, a;
};

#endif //COLOR_H
