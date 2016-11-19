
#ifndef _MOTOR_H
#define _MOTOR_H

#include "Order.h"

class Motor
{
public:
  Motor(const char* const side, const int e, const int p1, const int p2)
  : my_side(side), enable(e), pole1(p1), pole2(p2), speed(0), logsOn(false) {}
  const char* const my_side;
  const int enable, pole1, pole2;
  int speed;
  bool logsOn;
  virtual void init()
  {
     pinMode(enable, OUTPUT);
     pinMode(pole1, OUTPUT);
     pinMode(pole2, OUTPUT);
     stop();
  }
  virtual void forward(const int s)
  {
    if (logsOn)
    {
#ifdef DEBUGGING
      _SERIAL.print(my_side);
      _SERIAL.print(" forward: ");
      _SERIAL.println(s);
#endif
    }
    move(s, HIGH, LOW);
  }
  virtual void backward(const int s)
  {
      if (logsOn)
      {
#ifdef DEBUGGING
        _SERIAL.print(my_side);
        _SERIAL.print(" backward: ");
        _SERIAL.println(s);
#endif
      }
    move(s, LOW, HIGH);
  }
  void move(const Order& order)
  {
      if (order.getDirection() == Order::stop)
      {
          stop();
      }
      else if (order.getDirection() == Order::forward)
      {
          forward(order.speed);
      }
      else
      {
          backward(order.speed);
      }
  }

  void move(const int s, const int p1, const int p2)
  {
    changeSpeed(s);
    digitalWrite(pole1, p1);
    digitalWrite(pole2, p2);
  }

  virtual void stop()
  {
      if (logsOn)
      {
#ifdef DEBUGGING
        _SERIAL.print(my_side);
        _SERIAL.println(" stop");
#endif
      }
    changeSpeed(0);    
  }
  void changeSpeed(const int s)
  {
     speed = (s < 0) ? (0-s) : s;
     analogWrite(enable, s);
  }
  void loggingOff()
  {
      logsOn = false;
  }
  void loggingOn()
  {
      logsOn = true;
  }
private:
  Motor(Motor& m);
};

#endif
