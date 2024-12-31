// Define the digital input pins
const int setupPin = 2;
const int setupRacersPin = 3;
const int readyPin = 4;
const int racePin = 5;
const int racer1Participating = 8;
const int racer2Participating = 9;
const int racer3Participating = 10;
const int racer4Participating = 11;

const int inputPins[8] = {
  setupPin, 
  setupRacersPin, 
  readyPin, 
  racePin, 
  racer1Participating, 
  racer2Participating, 
  racer3Participating, 
  racer4Participating};

void setup() {
  delay(1000); // delay to make sure other boards start first
  
  // Initialize the digital input pins
  for (int i = 0; i < 8; i++) {
    pinMode(inputPins[i], INPUT_PULLUP);
  }
  
  // Initialize Serial communication at 115200 baud rate
  Serial.begin(115200);
  // while (!Serial) {
  //   ; // wait for serial port to connect. Needed for native USB port only
  // }
  //Serial.println("HW connected");
}

void loop() {
  // Check if there's a request from the serial
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'R') { // If command is 'R', respond with the input states
      byte inputState = readInputs();
      Serial.write(inputState); // Send the input states as a byte
    }
    Serial.flush();
  }
  
  delay(10); // Small delay to prevent overwhelming the serial buffer
}

/// @brief Function to read the inputs and return a byte representing their states
/// @return byte representing the digital inputs defined above
byte readInputs() {
  byte inputState = 0;
  for (int i = 0; i < 8; i++) {
    if (digitalRead(inputPins[i]) == LOW) {
      inputState |= (1 << i); // Set the corresponding bit if the input is HIGH
    }
  }
  return inputState;
}

