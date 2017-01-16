#include <IRremote.h>

int IRpin = 3;
IRrecv irrecv(IRpin);
decode_results results;
int type;
unsigned int data;


void setup()
{
 Serial.begin(9600);
 irrecv.enableIRIn();
}


void loop() {
 if (irrecv.decode(&results)) {
   type = checkEncodingType(&results);
   data = results.value;
   sendSerial(&results);
   irrecv.resume(); // Receive the next value
 }
} 


int checkEncodingType(decode_results *results) {
  int type;
  switch (results->decode_type) {
    case UNKNOWN:      type = 0;       break ;
    case NEC:          type = 1;       break ;
    case JVC:          type = 2;       break ;
    default:           type = -1;
  }
  return type;
}

void sendSerial(decode_results *results) {
  Serial.print(type);
  Serial.print("-");
  Serial.println(results->value, HEX);
}

void printSerial(decode_results *results) {
  Serial.println("-----------------------");  
  Serial.print("type - data : ");
  Serial.print(type);
  Serial.print(" - 0x");
  Serial.println(results->value, HEX);
}
