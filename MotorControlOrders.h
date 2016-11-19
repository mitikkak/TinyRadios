
#ifndef _MotorControlOrders_h
#define _MotorControlOrders_h

#include "Order.h"

class MotorControlOrders
{
public:
    const float completelyTurning;
    Order left;
    Order right;
#if 0
    MotorControlOrders(const int forward, const int leftward)
    {

        const int fwd_index = getForwardIndex(forward);
        const int lwd_index = getLeftwardIndex(leftward);
        left.speed = left_speeds[fwd_index][lwd_index];
        right.speed = right_speeds[fwd_index][lwd_index];
    }
#endif
    MotorControlOrders(int forward, int leftward)
    : completelyTurning(10000.0)
    {
        forward = toLimits(forward);
        leftward = toLimits(leftward);
        float const turningRatio = decideDirections(forward, leftward, left.direction, right.direction);
        if (!turningRatio)
        {
            const unsigned int speedVolForward = getVolume(forward);
            left.speed = right.speed = ((float) speedVolForward / 50.0) * Order::FULL_SPEED;
        }
        else if (turningRatio == completelyTurning)
        {
            const unsigned int speedVolLeftward = getVolume(leftward);
            right.speed = left.speed = ((float) speedVolLeftward / 50.0) * Order::FULL_SPEED;
        }
        else
        {
            const unsigned int speedVolForward = getVolume(forward);
            //const unsigned int speedVolLeftward = getVolume(leftward);
            Order& higher = (leftward >= 0) ? right : left;
            Order& lower = (&higher == &left) ? right : left;

            higher.speed = ((float) speedVolForward / 50.0) * Order::FULL_SPEED;
            //const int maxLowerSpeed = higher.speed - 50;
            lower.speed = (int) ((float) higher.speed * turningRatio);
            lower.speed = (lower.speed < Order::MIN_SPEED) ? Order::MIN_SPEED : lower.speed;
        }
    }
    unsigned int getVolume(const int tilt)
    {
        return (tilt < 0) ? (0-tilt) : tilt;
    }
    float getVolume(const float tilt) const
    {
        return (tilt < 0) ? (0-tilt) : tilt;
    }

    float decideDirections(const float forward, const float leftward, Order::Direction& leftDirection, Order::Direction& rightDirection) const
    {
        float turningRatio = 0;
        if (forward <= -20)
        {
            leftDirection = Order::backward;
            rightDirection = Order::backward;
            if ((leftward > 20) || (leftward < -20))
            {
                turningRatio = (20 / getVolume(leftward));
            }
        }
        else if (forward >= 20)
        {
            leftDirection = Order::forward;
            rightDirection = Order::forward;
            if ((leftward >= 20) || (leftward <= -20))
            {
                turningRatio = (20 / getVolume(leftward));
            }
        }
        else if (leftward >= 20)
        {
            leftDirection = Order::backward;
            rightDirection = Order::forward;
            turningRatio = completelyTurning;
        }
        else if (leftward <= -20)
        {
            leftDirection = Order::forward;
            rightDirection = Order::backward;
            turningRatio = completelyTurning;
        }
        else
        {
            leftDirection = Order::stop;
            rightDirection = Order::stop;
        }
        return turningRatio;
    }

    int toLimits(int tilt)
    {
        tilt = (tilt < -50) ? -50 : tilt;
        tilt = tilt > 50 ? 50 : tilt;
        return tilt;
    }

    int getForwardIndex(const int forward) const
    {
        const int step = 50;
        const int initial = 50;
        for (int candidate = initial, i = 0; i < MAX_FWD_ENTRIES; i++, candidate -= step)
        {
            if (forward >= candidate) return i;
        }
        return MAX_FWD_ENTRIES-1;
    }
    int getLeftwardIndex(const int leftward) const
    {
        const int step = 50;
        const int initial = 50;
        for (int candidate = initial, i = 0; i < MAX_LFT_ENTRIES; i++, candidate -= step)
        {
            if (leftward >= candidate) return i;
        }
        return MAX_LFT_ENTRIES-1;
    }
private:
    static const int MAX_FWD_ENTRIES = 3;
    static const int MAX_LFT_ENTRIES = 3;
    static const int left_speeds[MAX_FWD_ENTRIES][MAX_LFT_ENTRIES];
    static const int right_speeds[MAX_FWD_ENTRIES][MAX_LFT_ENTRIES];

};

#endif
