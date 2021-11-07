
#pragma once

static const int MOTION_REQUEST  = 1;
static const int MOTION_RESPONSE = 2;
static const int LED_ON_REQUEST = 33;
static const int LED_OFF_REQUEST = 44;
static const int LED_RESPONSE = 55;
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
//enum LedLevel
//{
static const int Led_OFF = 0;
static const int Led_ON = 1;
//};
struct LedRequest
{
    static const int NODE_ID_POS = 16;
    static const int MSG_ID_POS = 8;
    static const int MSG_ID_MASK = 0xFF;
    static const int TR_ID_MASK = 0xFF;
    static const int NODE_ID_MASK = 0xFF;
    LedRequest(const int msgId_, const int trId_, const int nodeId_ = 0xAA)
    : value(0)
    {
        value = (nodeId_ << NODE_ID_POS) | (msgId_ << MSG_ID_POS) | trId_;
    }
    int msgId() const
    {
        return (value >> MSG_ID_POS) & MSG_ID_MASK;
    }
    int trId() const
    {
        return (value & TR_ID_MASK);
    }
    int nodeId() const
    {
        return (value >> NODE_ID_POS) & NODE_ID_MASK;
    }
    void setMsgId(const int v)
    {
    }
    void setTrId(const int v)
    {

    }
    int get() const {return value;}

    //LedRequest(const int trId): header(LED_REQUEST,trId), led(Led_OFF){}
    //Header header;
    //int led;
private:
    int value;
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
    void set(const SwitchState s)
    {
       state = s;
    }
};
struct Response
{
    
    Header header;
    int led;
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

