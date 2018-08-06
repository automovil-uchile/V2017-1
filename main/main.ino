#include <Motor.h>

Motor motorL('left', 6, 7);

void setup()
{
}

void loop()
{
  motorL.setThrottle(0.01);
  delay(1000);
}
