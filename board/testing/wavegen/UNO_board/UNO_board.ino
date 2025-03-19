// Generador de ondas de prueba
//  VARS y CONST del programa
const uint8_t PIN = 3;                // fast-pwm pin
const uint8_t SAMPLESIZE = 64;        // subdiv
const uint8_t SAMPLERATE = 100000;    // uSec
uint8_t signal[SAMPLESIZE];           // sample
uint32_t timerSignal = SAMPLERATE;    // timer

// T = 0.000100sec * 64 = 0.0064sec
// f = 1/T =  156.25 Hz


void setup()
  {
    cli();
    // Config. prescaler
    // Configurar Timer2:
    TCCR2A = 0;                // Limpiar registros de configuración
    TCCR2B = 0;                // Limpiar registros de configuración
    TCNT2  = 0;                // Inicializar contador en 0
  
    // Configuración de modo Fast PWM, 8 bits
    TCCR2A |= (1 << WGM21) | (1 << WGM20);  // Modo 3: Fast PWM
    TCCR2B |= (1 << CS21);                  // Prescaler en 8
  
    // Habilitar la salida PWM en el pin 3 (OC2A)
    TCCR2A |= (1 << COM2A1);                // Modo Clear on Compare Match
  
    // Establecer el valor de comparación (PWM)
    OCR2A = 128; // 50% de ancho de pulso
    
    // Creo que esto era el modo del prescaler en cantidad de bits
    // Mayor cantida bits = Menor frecuencia de PWM (0x01 o 0b00000001 el más rapido)
    TCCR2B = TCCR2B & 0b11111000 | 0x01;

    // Rehabilitar interrupciones
    sei();

    for (uint8_t i = 0; i<SAMPLESIZE; i++)
      {
        signal[i] = 64*sin(2*PI*i/SAMPLESIZE)+64;
      }
  }


uint8_t i=0;
void loop()
  {
    uint32_t time = micros();

    if (time > timerSignal)                 // Comparador para el timer
      {
        analogWrite (PIN, signal[i]);       // Salida
        i++; if (i == SAMPLESIZE) { i=0; }   // Comparador para fin de ciclo
        timerSignal += SAMPLERATE;          // Incremento en el timer
      }
  }
