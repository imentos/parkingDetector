#define trigPin 3
#define echoPin 2
#define distanceToCar 5
#define distanceIgnore 4
#define alertTimer 10

int alertCount = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

long microsecondsToInches(long microseconds)
{
// According to Parallax's datasheet for the PING))), there are
// 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
// second). This gives the distance travelled by the ping, outbound
// and return, so we divide by 2 to get the distance of the obstacle.
// See: http://www.parallax.com/dl/docs/prod/acc/28015-PI...
return microseconds / 74 / 2;
}

void loop() {
  // put your main code here, to run repeatedly:
  int duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = microsecondsToInches(duration);
  delay(500);
  
  if (distance < distanceIgnore) {
    Serial.println("Ignored");
    return;
  }

  Serial.println(distance);  
  if (distance > distanceToCar) {
    Serial.println("Car moved");

    if (alertCount == 0) {
      Serial.println("***Send Alert");
    }
    if (alertCount++ > alertTimer) {      
      alertCount = 0;
    }    
  } else {
      alertCount = 0;
  }
}
