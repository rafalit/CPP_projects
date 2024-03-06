
#include "shape.h"
#include "rectangle.h"
#include "circle.h"
#include <memory>
namespace Shapes {
    enum class ShapeOperation {
        INTERSECTION, SUM, DIFFERENCE
    };

    class ShapeComposite : public Shape{
        std::shared_ptr<Shape> shape1_;
        std::shared_ptr<Shape> shape2_;
        ShapeOperation operation_;

    public:
        ShapeComposite(std::shared_ptr<Shape> shape1, std::shared_ptr<Shape> shape2, ShapeOperation operation) : shape1_(shape1), shape2_(shape2), operation_(operation) {};

        bool isIn(int x, int y) const override{
            switch(operation_) {
                case ShapeOperation::INTERSECTION:
                    return shape1_->isIn(x, y) && shape2_->isIn(x, y);

                case ShapeOperation::DIFFERENCE:
                    return shape1_->isIn(x, y) && !shape2_->isIn(x, y);

                case ShapeOperation::SUM:
                    return shape1_->isIn(x, y) || shape2_->isIn(x, y);

                default:
                    return false;
            }
        }

    };

}