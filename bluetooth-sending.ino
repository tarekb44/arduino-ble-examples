#include <SPI.h>
#include <Adafruit_BLE.h>
#include <Adafruit_BluefruitLE_SPI.h>
#include <Adafruit_BluefruitLE_UART.h>

// Common settings
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"
#define MODE_LED_BEHAVIOUR          "MODE"

// CREATE THE BLUEFRUIT LE OBJECT
Adafruit_BluefruitLE_UART ble(BLUEFRUIT_HWSERIAL_NAME, BLUEFRUIT_UART_MODE_PIN);

void setup(void)
{
  Serial.begin(115200);
  Serial.println(F("Adafruit Bluefruit UART Example"));
  Serial.println(F("------------------------------------------------"));

  // Initialise the module
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    Serial.println(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  if ( FACTORYRESET_ENABLE )
  {
    /* Perform a factory reset to make sure everything is in a known state */
    Serial.println(F("Performing a factory reset: "));
    if ( ! ble.factoryReset() ){
      Serial.println(F("Couldn't factory reset"));
    }
  }

  // Set module to DATA mode
  Serial.println( F("Switching to DATA mode!") );
  ble.setMode(BLUEFRUIT_MODE_DATA);

  // Optional: set the transmit power, good for saving battery
  ble.txPower(4);  // Check the datasheet for the value to use

  // Optional: change the device name
  ble.echo(false);
  ble.println("AT+GAPDEVNAME=Bluefruit UART");
  ble.readline();
  Serial.println(ble.buffer);
}

void loop()
{
  // Send a message to the Bluefruit LE app
  ble.print("Hello from Arduino!");

  // Wait a bit before sending again
  delay(1000);
}
