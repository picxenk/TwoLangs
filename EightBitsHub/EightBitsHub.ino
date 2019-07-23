/*
  8BitsHub
 by PROTOROOM, SeungBum Kim <picxenk@gmail.com>
 */

//#include <SPI.h>
//#include <Ethernet.h>
//#include <EthernetUdp.h> // UDP library from: bjoern@cs.stanford.edu 12/30/2008


/* ========== Network Setup ========== */
// [CHECK] : give a number 1 to 9(switch) for hubID
byte hubID = 1;
byte ipD = 170 + hubID;

/* update mac address from WIZ550io device.
0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED // example
  0x00, 0x08, 0xDC, 0x50, 0xB2, 0xFD // 1
  0x00, 0x08, 0xDC, 0x1D, 0x4F, 0x97 // 2
  0x00, 0x08, 0xDC, 0x50, 0xB2, 0xFF // 3
  0x00, 0x08, 0xDC, 0x50, 0xB2, 0xF9 // 4
  0x00, 0x08, 0xDC, 0x50, 0xB3, 0x00 // 5
  0x00, 0x08, 0xDC, 0x50, 0xB2, 0xFB // 6
  0x00, 0x08, 0xDC, 0x50, 0xB3, 0x01 // 7
  0x00, 0x08, 0xDC, 0x50, 0xB2, 0xFC // 8
  0x00, 0x08, 0xDC, 0x50, 0xB3, 0x02 // 9 
*/

byte hubMacList[][6] = {
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }, 
  { 0x00, 0x08, 0xDC, 0x50, 0xB2, 0xFD }, 
  { 0x00, 0x08, 0xDC, 0x1D, 0x4F, 0x97 }, 
  { 0x00, 0x08, 0xDC, 0x50, 0xB2, 0xFF }, 
  { 0x00, 0x08, 0xDC, 0x50, 0xB2, 0xF9 }, 
  { 0x00, 0x08, 0xDC, 0x50, 0xB3, 0x00 }, 
  { 0x00, 0x08, 0xDC, 0x50, 0xB2, 0xFB }, 
  { 0x00, 0x08, 0xDC, 0x50, 0xB3, 0x01 }, 
  { 0x00, 0x08, 0xDC, 0x50, 0xB2, 0xFC },
  { 0x00, 0x08, 0xDC, 0x50, 0xB3, 0x02 } 
};


//IPAddress ip(192, 168, 1, ipD); // hub ip
//unsigned int localPort = 8888; // hub port
//IPAddress rHostIP(192, 168, 1, 100); // display host ip
//IPAddress rHostIP(192, 168, 0, 2); // display host ip
//unsigned int rHostPort = 6000; // display host port

/* ========== Variables ========== */
// buffers for receiving and sending data
//char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
char  ReplyBuffer[2];
int bits[] = {0, 0, 0, 0, 0, 0, 0, 0};
int ports[] = {A0, A1, A2, A3, A4, A5, 6, 8};
unsigned char v;

boolean isDebugging = false;
boolean isSimulation = false;

//EthernetUDP Udp;


void setup() {
//  Ethernet.begin(hubMacList[hubID], ip);
//  Udp.begin(localPort);

  for (int i=0; i<8; i++) {
    pinMode(ports[i], INPUT);
  }

  
//  if (isDebugging) {
//    Serial.begin(9600);
//  }

  Serial.begin(9600);
  v = 0;

}

void loop() {
//  int heartBeatSize = Udp.parsePacket();
//  if (heartBeatSize > 0) {
//    Serial.println("get heaerbeat");
//    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
//    toggleSimulation();
//  }

  if (isSimulation) {
//    sendRandomSignal();
  } else {

    readNodeBits();
    char signal = packBitsToSignal();
    sendNodeSignal2(signal);

  }


  delay(30);
  showStatusLED();
}


char packBitsToSignal() {
  char sig = B00000000;
  for (int i = 0; i < 8; i++) {
    sig = sig << 1;
    if (bits[i] == 1) {
      sig = sig | B00000001;
    }
  }
  return sig;
}


void readNodeBits() {
  for (int i=0; i<8; i++) {
    if (digitalRead(ports[i]) == HIGH) {
      bits[i] = 1;
    } else {
      bits[i] = 0;
    }
  }
}


void sendNodeSignal(char signal) {
//  Udp.beginPacket(rHostIP, rHostPort);
//  ReplyBuffer[0] = byte(hubID);
//  ReplyBuffer[1] = signal;
//  Udp.write(ReplyBuffer, 2);
//  Udp.endPacket();
//  Serial.println("send signal");
}

void sendNodeSignal2(char signal) {
  Serial.write(signal);
}


void sendRandomSignal() {
  //    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
//  Udp.beginPacket(rHostIP, rHostPort);
//  ReplyBuffer[0] = byte(hubID);
//  ReplyBuffer[1] = v;
//  Udp.write(ReplyBuffer, 2);
//  Udp.endPacket();
//  v++;
}


void toggleSimulation() {
  if (isSimulation) isSimulation = false;
  else isSimulation = true;
}


void showStatusLED() {
  if (isSimulation) digitalWrite(13, HIGH);
  else digitalWrite(13, LOW);
}
