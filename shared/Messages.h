
#pragma once

static const int MOTION_REQUEST  = 1;
static const int MOTION_RESPONSE = 2;
static const int LED_REQUEST = 3;
static const int LED_RESPONSE = 4;
static const int TILT_REQUEST = 5;
static const int TILT_RESPONSE = 6;
static const int SWITCH_REQUEST = 7;
static const int PING_REQUEST = 8;
static const int PING_RESPONSE = 9;

typedef unsigned long TIME;
/*static const TIME NO_MOTION = 0;*/
struct Header
{
    explicit Header(const int mId, const int trId): msgId(mId), transactionId(trId)
    {}
    int msgId;
    int transactionId;
};
enum LedLevel
{
    Led_OFF = 0,
    Led_LOW = 1,
    Led_MEDIUM = 2,
    Led_HIGH = 3
};
struct LedRequest
{
    LedRequest(): header(0,0){}
    LedRequest(const int trId): header(LED_REQUEST,trId), led(Led_OFF){}
    Header header;
    LedLevel led;
};

struct TiltValues
{
    double pitch;
    double roll;
};

struct TiltRequest
{
    TiltRequest(const int msgId): header(msgId,0), button(0) {}
    Header header;
    TiltValues tilt;
    int button;
};
struct SwitchRequest
{
    enum SwitchState
    {
       SWITCH_ON = 0,
       SWITCH_OFF = 1
    };
    SwitchRequest(const int msgId): header(msgId,0), state(SWITCH_OFF) {}
    Header header;
    SwitchState state;
    void set(const int s)
    {
       state = (s == 0) ? SWITCH_ON : SWITCH_OFF;
    }
};
struct Response
{
    
    Header header;
    LedLevel led;
    bool motion;
    Response(const int msgId, const int tId): header(msgId, tId), led(Led_OFF), motion(false)
    {
    }
};
struct Ping
{
   Ping(const int i, const int t): header(i, t) {}
   Header header;
};

