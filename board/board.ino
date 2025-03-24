const uint8_t bufferSerial = 32;
uint8_t readSerial[bufferSerial];

 struct channel
  {
    uint8_t PIN;    // Input pin
    uint8_t MODE;   // Mode (osc/logic)
    uint8_t READ;   // 
    uint8_t DELAY;  // Delay (1= 100uSec)
    uint8_t SIZE;
    uint8_t NBYTE;
  };  


uint8_t i=0;

uint16_t ADCread[256];
uint8_t  toSend[512];

uint32_t TIMER = Delay;

void setup()
  {
    Serial.begin(115200);
  }

void serialEvent() // The CLI of board
  {
    if (Serial.available())
      {
        uint8_t readByte = Serial.peek();

        switch (readByte)
          {
            // Delay by sample
            case 'T': Delay = Serial.parseInt(); serial.Print("Sampling time changed to DELAY=");serial.Println(Delay); break;
            
            // Number of samples
            case 'N': Nsamp = Serial.parseInt(); serial.Print("Sampling size changed to SIZE=");serial.Println(Nsamp); break;

            // Number of bytes
            case 'B': Nbyte = Serial.parseInt(); serial.Print("Sampling byte changed to NBYTE=");serial.Println(Nbyte); break;

            // Run
            case 'R': Read = true;  break;
            // stop
            case 'S': Read = false; break;

            
          }
      }
  }

void loop()
  {
    if (Read == true)
      {
        // Read routine
        uint32_t TIME = micros();
        if (TIME > TIMER)
          {
            // Read ADC
            ADCread[i] = analogRead(A0);
            
            // Convert ADC vale to bytes to send
            if (Nbyte>1){ toSend[i*2] = ADCread[i]>>2; toSend[i*2+1] = ADCread[i] & 0b0000000000000011; }
            else { toSend[i] = ADCread[i]>>2; }
            
            // Time functions to generate wave
            i++; if (i > Nsamp) { i=0; }
            TIMER += Delay;
          }
      }
    else
      {
        delay(10); // Do nothing
      }
  }