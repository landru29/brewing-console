#ifndef __TEMPERATURE__H__
#define __TEMPERATURE__H__


#define TEMPERATURE_PIN 12   // on pin D12 (a 4.7K resistor is necessary)


/**
 * Get a temperature sensor address
 * @return True if an address was found, False if no more address
 */
//bool getAddress();

/**
 * Launch a measure on a sensor
 * @return Temperature in celcius
 */
//float performMeasure();

/**
 * True if at least one sensor was found
 * @return True if found
 */
//bool sensorFound();



class Temperature {
  private:
    byte addr[8] = {0, 0, 0, 0, 0, 0, 0, 0};

  public:
    Temperature(byte* address);
    float performMeasure();

    static int count;
    static Temperature** sensor;
    static void searchSensors();

};

#endif
