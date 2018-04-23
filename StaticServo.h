#include <Servo.h>

#define SERVO_MIN 0
#define SERVO_MAX 180

class StaticServo {
  public:
    void begin(uint8_t Pin, uint8_t Min, uint8_t Max, float Home , bool gotoHome = false) {
      if (Min < SERVO_MIN) Min = SERVO_MIN;
      else if (Min > SERVO_MAX) Min = SERVO_MAX;
      
      if (Max < SERVO_MIN) Max = SERVO_MIN;
      else if (Max > SERVO_MAX) Max = SERVO_MAX;
      
      _servo.min = Min;
      _servo.toMax = Max - Min;
      _servo.pin = Pin;
      _servo.home = Home;

      _servo.object.attach(Pin);

      if (gotoHome) home();
      else _position = _servo.home;
    }

    void home() {
      setServo(_servo.home);
    }

    void moveTo(float Position) {
      setServo(Position);
    }

    void move(float incrementPosition) {
      setServo(incrementPosition + _position);
    }

    float getCurrent() {
      return _position;
    }

    uint8_t getCurrentEuler() {
      return (_position * _servo.toMax) + _servo.min;
    }

    uint8_t getMin(){
      return _servo.min;
    }

    uint8_t getMax(){
      return _servo.min + _servo.toMax;
    }

  protected:
    void setServo(float Position) {
      if (Position < 0) Position = 0;
      if (Position > 1) Position = 1;

      _servo.object.write((_servo.toMax * Position) + _servo.min);
      _position = Position;
    }

    struct _servo {
      uint8_t pin, min, toMax;
      float home;
      Servo object;
    } _servo;

    float _position;
};

