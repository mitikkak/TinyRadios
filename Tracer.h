
struct Tracer
{
  const char* name;
  unsigned int timeouts, num_of_msg, wrong_message, right_message, failed_writes, tr_id_ok, motion, led;
  Tracer(const char* n)
  : name(n), timeouts(0), num_of_msg(0), wrong_message(0), right_message(0), failed_writes(0), tr_id_ok(0), motion(0), led()
  {}
  void log(const long timeNow) const
  {
	Serial.print(name);
	Serial.print(F(", time:"));
        Serial.print(timeNow);
        Serial.print(F(", msgs: "));
        Serial.print(num_of_msg);
        Serial.print(F(", failed writes: "));
        Serial.print(failed_writes);
        Serial.print(F(", timeouts: "));
        Serial.print(timeouts);    
        Serial.print(F(", wrong: "));
        Serial.print(wrong_message);
        Serial.print(F(", right: "));
        Serial.print(right_message);
        Serial.print(F(", tr_id_ok: "));
        Serial.print(tr_id_ok);
        Serial.print(F(", since: "));
        Serial.print(since);
        Serial.print(F(", action: "));
        Serial.println(action);    
  }
};
