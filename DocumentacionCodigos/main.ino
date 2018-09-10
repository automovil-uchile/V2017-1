#include <Motor.h>

Motor motorL('left', 6, 7);
Motor motorR('right', 5, 4);

void setup()
{
}

void loop()
{
  motorL.setThrottle(0.25);
  motorR.setThrottle(0.75);
  delay(1000);
}