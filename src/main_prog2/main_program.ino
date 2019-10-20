#include <IRremote.h>
#include <IRremoteInt.h>

// Define remote codes. The IRremote.h decodes the readings as inverse
#define chminus  0b00010101101110 // 657 or 2705 by the irremote.h
#define chplus   0b00110101101111 // 656 or 2704 
#define volminus 0b00110101101010 // 661 or 2709
#define volplus  0b00110101101001 // 662 or 2710
#define onoff    0b00010101110011 // 652 or 2700
#define shutter_signal  2
#define focus_signal    3

// pin definitions                     
uint8_t receiver_pin  = 2;    //  The digital pin that the signal pin of the sensor is connected to
uint8_t focus_pin     = 3;    // set low to focus
uint8_t shutter_pin   = 4;    // for controlling the shutter along with focus pin. Set both pins low.
uint8_t led_pin       = 13;   // status led pin (built-in led)

IRrecv receiver(receiver_pin);  //  Create a new receiver object that would decode signals to key codes
decode_results results;    //  A variable that would be used by receiver to put the key code into


void take_photo(){
  blink_led(2);
  digitalWrite(focus_pin, LOW);
  digitalWrite(shutter_pin, LOW);
  delay(1000);          // set the pins low for 1 second to simulate shutter button press
  digitalWrite(focus_pin, HIGH);
  digitalWrite(shutter_pin, HIGH);
}

void focus(){
  blink_led(3);
  pinMode(focus_pin, OUTPUT);
  digitalWrite(focus_pin, LOW);     // set pin low
  delay(1000);          // set the pin low for 1 second
  digitalWrite(focus_pin, LOW);     // set pin back high again
}

void blink_led(uint8_t amount){
  uint8_t i;
  uint8_t blink_delay = 150; // in ms
  for (i=0;i<amount;i++){
    digitalWrite(led_pin, HIGH);
    delay(blink_delay);
    digitalWrite(led_pin, LOW);
    delay(blink_delay);
  }
}

uint8_t check_remote_signal(){
  uint8_t ret_val = 0;
  if (receiver.decode(&results)) {

    // The IRremote.h library sometimes interprets the signal without the leading character so
    // we have to check if the signal received is either of two values

    // chminus = shutter
    if ((results.value == 657) || (results.value == 2705)) {
      ret_val = shutter_signal;
    }
    // chplus = focus
    if ((results.value == 656) || (results.value == 2704)) {
      ret_val = focus_signal;
    }
    else {
      ret_val = 0;
    }
    results.value = 0;
    receiver.resume();
    return ret_val;
  }
  return 0;
}


void setup() {
  receiver.enableIRIn();        // Enable receiver so that it would start processing infrared signals
  pinMode(focus_pin, INPUT);
  pinMode(shutter_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  
  // startup sequence
  blink_led(4);
  delay(10);
}

void loop() {
  uint8_t remote_signal = 0;
  remote_signal = check_remote_signal();
  if (remote_signal == shutter_signal){
    take_photo();
  }
  if (remote_signal == focus_signal){
    focus();
  }
  else {
    ; // do nothing
  }
  delay(50);    // 50 ms
}
