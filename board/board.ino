const uint8_t bufferSerial = 32;
uint8_t readSerial[bufferSerial];
uint8_t FRAMES=15;
// struct channel
//  {
    
    uint8_t PIN;    // Input pin
    uint8_t MODE;   // Mode (osc/logic)
    uint8_t READ;   // 
    uint8_t DELAY;  // Delay (1= 100uSec)
    uint8_t SIZE;
    uint8_t NBYTE;
//  };


uint8_t i=0;

uint16_t ADCread[256];
uint8_t  toSend[512];

uint32_t TIMER = DELAY;

void setup()
  {
    Serial.begin(115200);
  }

void serialEvent() // The CLI of board
  {
    if (Serial.available())
      {
        //uint8_t readByte = Serial.peek();
        uint8_t readByte = Serial.read();
        switch (readByte)
          {
            // Run
            case 'R': READ = true; Serial.println("RUN!");  break;
            // stop
            case 'S': READ = false; Serial.println("STOP!"); break;
            
            // Delay by sample
            case 'T': DELAY = Serial.parseInt(); Serial.print("Sampling time changed to DELAY=");Serial.print(DELAY);Serial.println("ms"); break;
            
            // Number of samples
            case 'N': SIZE = Serial.parseInt(); Serial.print("Sampling size changed to SIZE=");Serial.print(SIZE);Serial.println("samples"); break;

            // Number of bytes
            case 'B': NBYTE = Serial.parseInt(); Serial.print("Sampling byte changed to NBYTE=");Serial.print(NBYTE);Serial.println("bytes"); break;

            // Number of frames
            case 'F': FRAMES = Serial.parseInt(); Serial.print("Sampling frames changed to FRAMES=");Serial.print(FRAMES);Serial.println("fps"); break;
            
          }
      }
  }

void loop()
  {
    if (MODE == 1)
      {
        if (READ == true)
          {
            // Read routine
            uint32_t TIME = micros();
            if (TIME > TIMER)
              {
                // Read ADC
                ADCread[i] = analogRead(A0);
                
                // Convert ADC vale to bytes to send
                if (NBYTE>1){ toSend[i*2] = ADCread[i]>>2; toSend[i*2+1] = ADCread[i] & 0b0000000000000011; }
                else { toSend[i] = ADCread[i]>>2; }
                
                // Time functions to generate wave
                i++; if (i > SIZE) { i=0; }
                TIMER += DELAY;
              }
          }
        else if (true)
          {
          
          }
        else
          {
            delay(10); // Do nothing
          }
      }
  }
