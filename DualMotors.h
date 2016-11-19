
#ifndef _DUAL_MOTORS_H
#define _DUAL_MOTORS_H

#include "Motor.h"
#include "MotorControlOrders.h"
struct DualMotors
{
    static const int MINIMUM_SPEED_THRESHOLD = 20;
    static const int STEPLESS_SPEED_THRESHOLD = 35;
    static const int FULL_SPEED_THRESHOLD = 60;
   DualMotors(Motor& l, Motor& r)
   : left(l), right(r)
   {}
   void init()
   {
     left.init();
     right.init();
   }
   void go(MotorControlOrders& orders)
   {
       left.move(orders.left);
       right.move(orders.right);
   }

   void go(const int forward_wise, const int left_wise)
   {
       if (left_wise >= MINIMUM_SPEED_THRESHOLD)
       {
          goLeft(left_wise);
       }
       else if (left_wise <= -MINIMUM_SPEED_THRESHOLD && forward_wise <= MINIMUM_SPEED_THRESHOLD && forward_wise > -MINIMUM_SPEED_THRESHOLD)
       {

          goRight(0-left_wise);
       }
       else
       {
        if (forward_wise >= 0)
        {
           goForward(forward_wise,left_wise);
        }
        else
        {
           goBackward(forward_wise,left_wise);
        }
       }

   }
   void getSpeed(int& speedLeft, int& speedRight, const int tilt)
   {
       if (tilt >= FULL_SPEED_THRESHOLD)
       {
           speedLeft = speedRight = Order::FULL_SPEED;
       }
       else if (tilt >= STEPLESS_SPEED_THRESHOLD)
       {

           const float ratio = (float) (tilt - STEPLESS_SPEED_THRESHOLD) / (float) (FULL_SPEED_THRESHOLD - STEPLESS_SPEED_THRESHOLD);
           const int additionalSpeed = ((Order::FULL_SPEED - Order::MEDIUM_SPEED) * ratio);
           const int higherSpeed = Order::MEDIUM_SPEED + additionalSpeed;
           speedLeft = speedRight = higherSpeed;
       }
       else if (tilt >= MINIMUM_SPEED_THRESHOLD)
       {
           speedLeft = speedRight = Order::MIN_SPEED;
       }
   }

   void goForward(const int forward_wise, const int left_wise)
   {
       int speedLeft = 0;
       int speedRight = 0;
       getSpeed(speedLeft, speedRight, forward_wise);
       left.forward(speedLeft);
       right.forward(speedRight);
   }
   void goBackward(const int forward_wise, const int left_wise)
   {
       int speed = 0;
       if (forward_wise <= -MINIMUM_SPEED_THRESHOLD)
       {
         getSpeed(speed, speed, 0-forward_wise);
       }
       left.backward(speed);
       right.backward(speed);
   }
   void goLeft(const int left_wise)
   {
       int speed = 0;
       getSpeed(speed, speed, left_wise);
       left.backward(speed);
       right.forward(speed);
   }
   void goRight(const int left_wise)
   {
       int speed = 0;
       getSpeed(speed, speed, left_wise);
       left.forward(speed);
       right.backward(speed);
   }

   void forward(const int speed)
   {
      left.forward(speed);
      right.forward(speed);
   }
   void stop()
   {
      left.stop();
      right.stop();
   }
   Motor& left;
   Motor& right;
};

#endif
