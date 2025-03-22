
void setup()
	{
    analogReference(DEFAULT);
		Serial.begin (115200);
	}

uint8_t imax=5;
void loop()
	{
    int16_t ANALOG=0;
    ANALOG = analogRead(A1);
    
		Serial.println(ANALOG);
	}
