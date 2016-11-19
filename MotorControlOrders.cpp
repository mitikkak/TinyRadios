
#include "MotorControlOrders.h"
#include "Order.h"

const int MotorControlOrders::left_speeds[MAX_FWD_ENTRIES][MAX_LFT_ENTRIES] =
{ {Order::MIN_SPEED,Order::FULL_SPEED, Order::FULL_SPEED},
  {-Order::FULL_SPEED,0,Order::FULL_SPEED},
  {-Order::MIN_SPEED,-Order::FULL_SPEED,-Order::FULL_SPEED}
};
const int MotorControlOrders::right_speeds[MAX_FWD_ENTRIES][MAX_LFT_ENTRIES] =
{ {Order::FULL_SPEED,Order::FULL_SPEED, Order::MIN_SPEED},
  {Order::FULL_SPEED,0,-Order::FULL_SPEED},
  {-Order::FULL_SPEED,-Order::FULL_SPEED,-Order::MIN_SPEED}
};
