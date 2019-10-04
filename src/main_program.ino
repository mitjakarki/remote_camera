#include <IRremote.h>
#include <IRremoteInt.h>

// Define remote codes. The IRremote.h decodes the readings as inverse
#define chminus  0b00010101101110 // 657 or 2705 by the irremote.h
#define chplus   0b00110101101111 // 656 or 2704 
#define volminus 0b00110101101010 // 661 or 2709
#define volplus  0b00110101101001 // 662 or 2710
#define onoff    0b00010101110011 // 652 or 2700

// pin definitions                     
uint8_t receiver_pin  = 2;    //  The digital pin that the signal pin of the sensor is connected to
uint8_t focus_pin     = 3;    // set low to focus
uint8_t shutter_pin   = 4;    // for controlling the shutter along with focus pin. Set both pins low.
uint8_t led_pin       = 13;    // status led pin

IRrecv receiver(receiver_pin);  //  Create a new receiver object that would decode signals to key codes
decode_results results;    //  A variable that would be used by receiver to put the key code into


void take_photo(){
  blink_led(2);
  pinMode(focus_pin, OUTPUT);    // set pins low
  pinMode(shutter_pin, OUTPUT);
  digitalWrite(focus_pin, LOW);
  digitalWrite(shutter_pin, LOW);
  delay(1500);          // set the pins low for 1,5 seconds
  pinMode(focus_pin, INPUT);    // set the pins as input again to float them
  pinMode(shutter_pin, INPUT);
}

void focus(){
  blink_led(3);
  pinMode(focus_pin, OUTPUT);    // set pin low
  digitalWrite(focus_pin, LOW);
  delay(1500);          // set the pin low for 1,5 seconds
  pinMode(focus_pin, INPUT);    // set the pin as input again to float them
}

void blink_led(uint8_t amount){
  uint8_t i;
  uint8_t blink_delay = 100; // in ms
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
    // chminus
    if ((results.value == 657) || (results.value == 2705)) {
      ret_val = 2;
    }
    // chplus
    if ((results.value == 656) || (results.value == 2704)) {
      ret_val = 1;
    }
    results.value = 0;
    receiver.resume();
    return ret_val;
  }
  
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
  if (remote_signal == 2){
    take_photo();
  }
  if (remote_signal == 1){
    focus();
  }
}
