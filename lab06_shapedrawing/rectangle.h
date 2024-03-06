

#include "shape.h"

namespace Shapes {

    class Rectangle : public Shape {
    private:
        Point diagonal1{0, 0};
        Point diagonal2{0, 0};
    public:
        Rectangle(int xFrom, int yFrom, int xTo, int yTo);
        int x() const;
        int xTo() const;
        int y() const;
        int yTo() const;
        bool isIn(int x, int y) const override;

        /////////////////////////////////



    };

}
