
#include "Arduino.h"
#include "Components.h"
#include "shared/Messages.h"
#include "Loop.h"

TIME prevLog = 0;
int transactionId = 0;
//int node = 0;
class Nodes
{
public:
	Nodes(){}
	int numOfUnreachedNodes() const
	{
		int retVal{0};
		for (int i = 0; i < maxNumberOfNodes; i++)
		{
			if (not reached[i])
			{
				retVal++;
			}
		}
		return retVal;
	}
	int nextUnreached()
	{
		int retVal = currIdx;
		updateCurrIdx();
		return retVal;
	}
	void wasReached(const int nodeIdx)
	{
		if (nodeIdx < maxNumberOfNodes)
		{
			reached[nodeIdx] = true;
		}
	}
	bool reachable(const int nodeIdx) const
	{
		bool retVal{false};
		if (nodeIdx < maxNumberOfNodes)
		{
			retVal = reached[nodeIdx];
		}
		return retVal;
	}
private:
	void updateCurrIdx()
	{
		int numNodes = maxNumberOfNodes;
		do
		{
			Serial.println(numNodes);
		    currIdx++;
		    if (currIdx >= maxNumberOfNodes) {currIdx = 0;}
		    if (not reached[currIdx]) {numNodes = 0;}
		    else
		    {
		    	numNodes--;
		    }
		}
		while(numNodes);
	}
	bool reached[maxNumberOfNodes]{false};
	int currIdx{0};
};
Nodes nodes;
bool orderOneNode(const int node, const int msgId)
{
    TIME timeSpent = -1;
    transactionId++;
    TIME const listenPeriod = 1000;
    TIME const sendPeriod = 100;
    RadioMode mode(listenPeriod, sendPeriod);
    unsigned int respTrId = 0;
    bool const success = onePingRound(mode, node, transactionId, timeSpent, respTrId, msgId);
    _SERIAL.print("node "); _SERIAL.print(node); _SERIAL.print("transactionId: "); _SERIAL.print(transactionId);
    _SERIAL.print("/");_SERIAL.print(respTrId);
    _SERIAL.print(", success: "); _SERIAL.println(success);
    return success;
}

void listenAliveInd(const int receiver)
{
	radio.openReadingPipe(0, led_server_addresses[receiver]);
	radio.startListening();
	radio.stopListening();
}
void toggleLed(const int node_idx)
{
  Serial.print("toggle led: "); Serial.println(node_idx);
  int& msgId = msgIdTable[node_idx];
  const int nextMsgId = (msgId == LED_ON_REQUEST) ? LED_OFF_REQUEST : LED_ON_REQUEST;
  bool success = orderOneNode(node_idx, nextMsgId);
  if (success)
  {
      msgId = nextMsgId;
  }
}
bool queryNode(const int node_idx)
{
	Serial.print("queryNode: "); Serial.println(node_idx);
	const int msgId = msgIdTable[node_idx];
	return orderOneNode(node_idx, msgId);
}
#ifdef BLUETOOTH_ON
TIME timeStampBluetoothActive{0};
TIME const bluetoothWaitPeriod{10000};
void loop()
{
  String string = "";
  TIME const timeNow = millis();
  if (_BLUETOOTH.available())
  {
	  timeStampBluetoothActive = timeNow;
  }
  while(_BLUETOOTH.available() > 0)
  {
    char const command = ((byte)_BLUETOOTH.read());
    if(command == ':')
    {
      break;
    }
    else
    {
      string += command;
    }
    delay(1);
  }
  if(string == "SC")
  {
	  Serial.println(string);
      String resp = "RESP:";
      for (unsigned node = 0; node < maxNumberOfNodes; node++)
      {
    	  if (nodes.reachable(node))
    	  {
			  char cnt_str_buffer[10] = {0};
			  itoa(node, cnt_str_buffer, 10);
			  resp += cnt_str_buffer;
    	  }
    	  else
    	  {
    		  resp += "N/A";
    	  }
    	  resp += ";";
      }
      _BLUETOOTH.print(resp + "#");
  }
  else if(string =="CL")
  {
  }
  else if (string.substring(0, 3) == "LED")
  {
      Serial.println(string.substring(3));
      int const node = string.substring(3).toInt();
      toggleLed(node);
  }
  else if (timeNow - timeStampBluetoothActive >= bluetoothWaitPeriod)
  {
	  Serial.print(timeNow); Serial.print(" numOfUnreachedNodes: "); Serial.println(nodes.numOfUnreachedNodes());
	  if (nodes.numOfUnreachedNodes())
	  {
		  const int nodeIdx = nodes.nextUnreached();
		  if (queryNode(nodeIdx))
		  {
			  nodes.wasReached(nodeIdx);
		  }
	  }
  }

}
#else
struct Stats
{
  Stats(): rounds(0), attempts(0), ok(0), spent(0) {}
  unsigned int rounds;
  unsigned int attempts;
  unsigned int ok;
  unsigned int nok;
  TIME spent;
};
Stats stats;
const unsigned int MAX_ATTEMPTS = 10;

void loop()
{
	toggleLed(0);
}
#endif
