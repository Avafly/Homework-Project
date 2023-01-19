#define LED_SEG_NUM 7
#define NOTE_RANGE 8
#define DISTANCE_MAX 35

// Pitch and its corresponding frequency
#define C4 262
#define D4 294
#define E4 330
#define F4 349
#define G4 392
#define A4 440
#define B4 494

#define C5 523
#define D5 587
#define E5 659
#define F5 698
#define G5 784
#define A5 880
#define B5 988

int range1[NOTE_RANGE] = {C4, D4, E4, F4, G4, A4, B4, 0}; // C4 ~ B4
int range2[NOTE_RANGE] = {C5, D5, E5, F5, G5, A5, B5, 0}; // C5 ~ B5
int fretIntervals[NOTE_RANGE] = {5, 9, 13, 17, 21, 25, 30, 100};

enum RhythmType {
    CONTINUOUS_NOTES,
    DISCRETE_NOTES
};

int ledValue = 1;
int tempoInterval;
RhythmType rhythmType;

// pin assignment
int piezoPin = 11;
int ledGreenPin = 10;
int ledRedPin = 9;
int trigPin1 = 12;
int trigPin2 = 7;
int echoPin1 = A1;
int echoPin2 = A4;
int joystickPinX = A0;
int joystickPinY = A2;
int joystickPinM = 13;
int ledSegPins[LED_SEG_NUM] = {2, 3, 4, 5, 6, 7, 8};

void setup() {
    // switch input
    Serial.begin(9600);
    // joystick
    pinMode(joystickPinM, INPUT_PULLUP);
    // 7-segment led
    for (int i = 0; i < 7; i ++) {
        pinMode(ledSegPins[i], OUTPUT);
    }
    // speaker
    pinMode(piezoPin, OUTPUT);
    // sonar
    pinMode(trigPin1, OUTPUT);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin1, INPUT);
    pinMode(echoPin2, INPUT);
    // leds
    pinMode(ledGreenPin, OUTPUT);
    pinMode(ledRedPin, OUTPUT);
    // default settings
    setTempoInterval(ledValue);
    // rhythmType = DISCRETE_NOTES;
    rhythmType = CONTINUOUS_NOTES;

    // start with displaying default mode
    ledDisplay(ledSegPins, ledValue);
}

void loop() {
    if (digitalRead(joystickPinM) == 0) { // change mode if the middle button of joystick is pressed
        changeMode();
    }
    play();
}

void changeMode() {
    digitalWrite(ledGreenPin, LOW);
    digitalWrite(ledRedPin, LOW);

    while (1) {
        // x-axis: tempoInterval
        int joystickValueX = analogRead(joystickPinX);
        if (joystickValueX < 200) {
            if (ledValue > 1) {
                ledValue --;
            } else {
                ledValue = 3;
            }
        } else if (joystickValueX > 700) {
            if (ledValue < 3) {
                ledValue ++;
            } else {
                ledValue = 1;
            }
        }
        setTempoInterval(ledValue);

        // y-axis: rhythmType
        int flag = 0;
        int joystickValueY = analogRead(joystickPinY);
        if (joystickValueY < 200 || joystickValueY > 700) {
            rhythmType = 1 - rhythmType; // flip rhythmType
            flag = 1;
        }

        ledDisplay(ledSegPins, ledValue); // display rhythmType
        if (flag) {
            digitalWrite(ledRedPin, HIGH);
            delay(200);
            digitalWrite(ledRedPin, LOW);
        }

        delay(800);
        if (digitalRead(joystickPinM) == 0) { // press the middle button of joystick to finish setting
            Serial.print(tempoInterval);
            if (rhythmType == CONTINUOUS_NOTES) {
                Serial.println(" CON_NOTES");
            } else {
                Serial.println(" DIS_NOTES");
            }
            break;
        }
    }
}

void ledDisplay(int* segPins, int value) {
    // LED number profile
    static int segTable[3][LED_SEG_NUM] = {
        {0, 1, 1, 0, 0, 0, 0}, // 1
        {1, 1, 0, 1, 1, 0, 1}, // 2
        {1, 1, 1, 1, 0, 0, 1}  // 3
    };
    // display number accroding to segTable
    for (int i = 0; i < LED_SEG_NUM; i ++) {
        if (segTable[value - 1][i]) {
            digitalWrite(segPins[i], HIGH);
        } else {
            digitalWrite(segPins[i], LOW);
        }
    }
    delay(100);
}

int sampling(int trigPin, int echoPin) { // distance measurement using sonar
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    return pulseIn(echoPin, HIGH) / (29 * 2); // return distance
}

void play() {
    // distance1 is responsible for C4-B4, while distance2 for C5-B5
    double distance1 = sampling(trigPin1, echoPin1);
    double distance2 = sampling(trigPin2, echoPin2);

    double distance;
    int* range;
    if (distance1 < DISTANCE_MAX) { // if distance1 extended the max distance range, then use another sonar
        distance = distance1;
        range = range1;
    } else {
        distance = distance2;
        range = range2;
    }

    digitalWrite(ledGreenPin, HIGH);
    digitalWrite(ledRedPin, HIGH);

    for (int i = 0; i < NOTE_RANGE; i ++) {
        if (distance >= 100 || distance < 2) {
          noTone(piezoPin);
          break;
        }
        if (distance < fretIntervals[i] && starCount < starNum) {
            if (rhythmType == CONTINUOUS_NOTES) {
                tone(piezoPin, range[i]);
            } else {
                tone(piezoPin, range[i], tempoInterval / 2);
            }
            break;
        }
    }

    delay(tempoInterval / 2);
    digitalWrite(ledRedPin, LOW);
    delay(tempoInterval / 2);
}

void setTempoInterval(int value) {
    static int tempoIntervals[3] = {50, 300, 700};
    tempoInterval = tempoIntervals[value - 1];
}