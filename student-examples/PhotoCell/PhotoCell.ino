/*
 * This exaple demonstrates varying the brightness of an LED 
 * depending on the reading from an LDR (simple photocell)
 */

int led_pin = 6, ldr_pin = 1;
bool read_complete, is_reading;

void setup() {
  pinMode(led_pin, OUTPUT);

  ADCSRA = bit(ADEN); // enable ADC
  ADCSRA |= bit(ADPS0) | bit(ADPS1) | bit(ADPS2); // set the prescalar to 128
  ADCSRA |= bit(ADIE); // enable interrupt for ADC
  ADMUX = bit(REFS0); // set the reference voltage to Vcc
  read_complete = false;
  is_reading = false;
}

void loop() {
  if (!is_reading)
  {
    ADMUX |= ldr_pin; // set the analog pin to read from
    ADCSRA |= bit(ADSC); // start conversion
    is_reading = true;
  }

  if (read_complete)
  {
    analogWrite(led_pin, ADC * 255.0 / 1023.0); // setting the brightness of the LED depending on the reading of the LDR
    is_reading = false;
    read_complete = false;
    delay(50);
  }

}

ISR(ADC_vect)
{
  read_complete = true;
}

