#include "shape.h"

namespace Shapes {
    class Circle : public Shape {
        Point center{0, 0};
        int radius_;
    public:
        int x() const;
        int y() const;
        int getRadius() const;
        Circle(int xCenter, int yCenter, int radius);

        bool isIn(int x, int y) const override;
    };
}