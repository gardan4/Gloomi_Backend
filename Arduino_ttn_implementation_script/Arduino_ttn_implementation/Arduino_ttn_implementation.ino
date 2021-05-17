#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>
#include <dht11.h>


#define lichtsensor A0
#define DHT11PIN 3
#define pirPin 4   // PIR Out pin 

int redpin = A3; //select the pin for the blauw LED
int bluepin =A1; // select the pin for the  groen LED
int greenpin =A2; // select the pin for the  groen LED

dht11 DHT11;

// LoRaWAN NwkSKey, network session key
static const PROGMEM u1_t NWKSKEY[16] = { 0xE3, 0xC7, 0x72, 0xF1, 0x78, 0xDA, 0x19, 0x8D, 0x86, 0x2A, 0x4F, 0x2E, 0x96, 0x60, 0xCE, 0xC3 };

// LoRaWAN AppSKey, application session key
static const u1_t PROGMEM APPSKEY[16] = { 0x9F, 0xCD, 0x26, 0x79, 0x1E, 0x87, 0x29, 0x37, 0x0C, 0x81, 0xB6, 0x61, 0xD0, 0xF1, 0x63, 0x4B };
//
// LoRaWAN end-device address (DevAddr)
static const u4_t DEVADDR = 0x26011C1C;

// These callbacks are only used in over-the-air activation, so they are
// left empty here (we cannot leave them out completely unless
// DISABLE_JOIN is set in config.h, otherwise the linker will complain).
void os_getArtEui (u1_t* buf) { }
void os_getDevEui (u1_t* buf) { }
void os_getDevKey (u1_t* buf) { }

static uint8_t mydata[5] = {0x00,0x00,0x00,0x00,0x00};
static osjob_t sendjob;

// Schedule TX every this many seconds (might become longer due to duty cycle limitations).
const unsigned TX_INTERVAL = 10;


void Data()
{
  int chk = DHT11.read(DHT11PIN);
  int temp = DHT11.temperature;
  mydata[0] = temp;
  int hum = DHT11.humidity;
  mydata[1] = hum;


  double light = analogRead(lichtsensor);
  int lightlevel = light / 1100 * 100;
  mydata[2] = lightlevel;


  int pirStat = digitalRead(pirPin); 
  if (pirStat == HIGH) {            // if motion detected
    Serial.println("Movement (%): 1");
    mydata[3] = 1;
  } 
  else {
    mydata[3] = 0;
    Serial.println("Movement (%): 0");
  }


  //controlling led
  if (pirStat == HIGH && light <30) { 
    //movement and light so light to 100%
    digitalWrite(redpin,LOW);
    digitalWrite(bluepin,LOW);
    digitalWrite(greenpin,LOW);
  }
  else if (pirStat == LOW && light <30) {
    //no movement but night so lights dimmed to 30%  but at the 
    //moment there is not enough digital pin space so this is not possible
    digitalWrite(redpin,HIGH);
    digitalWrite(bluepin,HIGH);
    digitalWrite(greenpin,HIGH);
  }
  else {
    //day so lights 0%
    digitalWrite(redpin,HIGH);
    digitalWrite(bluepin,HIGH);
    digitalWrite(greenpin,HIGH);
  }
  
  Serial.print("Humidity (%): ");
  Serial.println(hum);

  Serial.print("Temperature (C): ");
  Serial.println(temp);
  
  Serial.print("Lux (0-1100): ");
  Serial.println(light);
  Serial.println();
  
  delay(1000);
}

// Pin mapping
const lmic_pinmap lmic_pins = {
    .nss = 10,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 9,
    .dio = {2, 6, 7}
};

void onEvent (ev_t ev) {
    Serial.print(os_getTime());
    Serial.print(": ");
    switch(ev) {
        case EV_SCAN_TIMEOUT:
            Serial.println(F("EV_SCAN_TIMEOUT"));
            break;
        case EV_BEACON_FOUND:
            Serial.println(F("EV_BEACON_FOUND"));
            break;
        case EV_BEACON_MISSED:
            Serial.println(F("EV_BEACON_MISSED"));
            break;
        case EV_BEACON_TRACKED:
            Serial.println(F("EV_BEACON_TRACKED"));
            break;
        case EV_JOINING:
            Serial.println(F("EV_JOINING"));
            break;
        case EV_JOINED:
            Serial.println(F("EV_JOINED"));
            break;
        case EV_RFU1:
            Serial.println(F("EV_RFU1"));
            break;
        case EV_JOIN_FAILED:
            Serial.println(F("EV_JOIN_FAILED"));
            break;
        case EV_REJOIN_FAILED:
            Serial.println(F("EV_REJOIN_FAILED"));
            break;
        case EV_TXCOMPLETE:
            Serial.println(F("EV_TXCOMPLETE (includes waiting for RX windows)"));
            if (LMIC.txrxFlags & TXRX_ACK)
              Serial.println(F("Received ack"));
            if (LMIC.dataLen) {
              Serial.println(F("Received "));
              Serial.println(LMIC.dataLen);
              Serial.println(F(" bytes of payload"));
              int y = LMIC.dataLen;
              }
            // Schedule next transmission
            os_setTimedCallback(&sendjob, os_getTime()+sec2osticks(TX_INTERVAL), do_send);
            break;
        case EV_LOST_TSYNC:
            Serial.println(F("EV_LOST_TSYNC"));
            break;
        case EV_RESET:
            Serial.println(F("EV_RESET"));
            break;
        case EV_RXCOMPLETE:
            // data received in ping slot
            Serial.println(F("EV_RXCOMPLETE"));
            break;
        case EV_LINK_DEAD:
            Serial.println(F("EV_LINK_DEAD"));
            break;
        case EV_LINK_ALIVE:
            Serial.println(F("EV_LINK_ALIVE"));
            break;
         default:
            Serial.println(F("Unknown event"));
            break;
    }
}

void do_send(osjob_t* j){
    // Check if there is not a current TX/RX job running
    if (LMIC.opmode & OP_TXRXPEND) 
    {
        Serial.println(F("OP_TXRXPEND, not sending"));
    }
    else 
    {
        Data();
        // Prepare upstream data transmission at the next possible time.
        LMIC_setTxData2(1, mydata, sizeof(mydata)-1, 0);
        Serial.println(F("Packet queued"));
        //Serial.println(LMIC.freq);
    }
    // Next TX is scheduled after TX_COMPLETE event.
}

void setup() {
    //leds
    pinMode(redpin, OUTPUT);
    pinMode(bluepin, OUTPUT);
    pinMode(greenpin, OUTPUT);


    Serial.begin(9600);
    Serial.println(F("Starting"));

    LMIC_setClockError(MAX_CLOCK_ERROR * 10 / 100);

    #ifdef VCC_ENABLE
    // For Pinoccio Scout boards
    pinMode(VCC_ENABLE, OUTPUT);
    digitalWrite(VCC_ENABLE, HIGH);
    delay(1000);
    #endif

    // LMIC init
    os_init();
    // Reset the MAC state. Session and pending data transfers will be discarded.
    LMIC_reset();

    // Set static session parameters. Instead of dynamically establishing a session
    // by joining the network, precomputed session parameters are be provided.
    #ifdef PROGMEM
    // On AVR, these values are stored in flash and only copied to RAM
    // once. Copy them to a temporary buffer here, LMIC_setSession will
    // copy them into a buffer of its own again.
    uint8_t appskey[sizeof(APPSKEY)];
    uint8_t nwkskey[sizeof(NWKSKEY)];
    memcpy_P(appskey, APPSKEY, sizeof(APPSKEY));
    memcpy_P(nwkskey, NWKSKEY, sizeof(NWKSKEY));
    LMIC_setSession (0x1, DEVADDR, nwkskey, appskey);
    #else
    // If not running an AVR with PROGMEM, just use the arrays directly
    LMIC_setSession (0x1, DEVADDR, NWKSKEY, APPSKEY);
    #endif

    
    LMIC_setLinkCheckMode(0);

    // TTN uses SF9 for its RX2 window.
    //LMIC.dn2Dr = DR_SF9;

    // Set data rate and transmit power for uplink (note: txpow seems to be ignored by the library)
    LMIC_setDrTxpow(DR_SF7,14);

    // Start job
    do_send(&sendjob);
}

void loop() {
    os_runloop_once();
}
