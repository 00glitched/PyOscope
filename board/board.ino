uint8_t FRAMES=15; uint16_t DELAYFRAMES=15;

//         -1 bitshift   5fps    6fps   7fps
//                      10fps   12fps  15fps
//         +1 bitshift  20fps   25fps  30fps
//         +2 bitshift  40fps   50fps  60fps
uint32_t delays_frames[3]={1000000,800000,666666}; uint8_t n=0; uint8_t k=0;

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

uint32_t TIMERANALOG = DELAY;
uint32_t TIMERFRAMES = DELAYFRAMES;

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
            if (TIME > TIMERANALOG)
              {
                // Read ADC
                ADCread[i] = analogRead(A0);
                
                // Convert ADC vale to bytes to send
                if (NBYTE>1)
                  {
                    toSend[i*2] = ADCread[i]>>2; toSend[i*2+1] = ADCread[i] & 0b0000000000000011; // two-bytes
                  }
                else { toSend[i] = ADCread[i]>>2; } // one-byte
                
                // Time functions to generate wave
                i++; if (i > SIZE) { i=0; }
                TIMERANALOG += DELAY;
              }
            if (TIME > TIMERFRAMES)
              {
                // frames-per-second with bitshift
                TIMERFRAMES += delays_frames[k] >> n;
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
