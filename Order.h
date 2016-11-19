
#ifndef _Order_h
#define _Order_h
class Order
{
public:
    static const int FULL_SPEED = 255;
    static const int MEDIUM_SPEED = 150;
    static const int MIN_SPEED = 100;
    enum Direction
    {
        stop = 0,
        forward = 1,
        backward = 2
    };
    Direction getDirection() const
    {
#if 0
        if (speed == 0) {return stop;}
        if (speed > 0) {return forward;}
        return backward;
#endif
        return direction;
    }
    int speed;
    Direction direction;
};

#endif
