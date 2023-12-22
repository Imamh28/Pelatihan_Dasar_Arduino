#define TRIG_PIN 9  // Pin trigger sensor ultrasonik
#define ECHO_PIN 10 // Pin echo sensor ultrasonik
#define SERVO_PIN 6 // Pin servo motor

#define MAX_DISTANCE 200 // Jarak maksimal yang dapat diukur oleh sensor ultrasonik (dalam centimeter)

Servo myservo;  // Objek untuk mengontrol servo motor

void setup() {
  Serial.begin(9600);
  myservo.attach(SERVO_PIN);
}

void loop() {
  long duration, distance;
  
  // Mengirim sinyal ultrasonik
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Menerima waktu tempuh sinyal ultrasonik
  duration = pulseIn(ECHO_PIN, HIGH);
  
  // Menghitung jarak berdasarkan waktu tempuh
  distance = (duration * 0.0343) / 2;
  
  if (distance > 0 && distance < MAX_DISTANCE) {
    Serial.print("Jarak: ");
    Serial.print(distance);
    Serial.println(" cm");
    
    // Map nilai jarak menjadi sudut untuk servo motor (misalnya, 0 derajat hingga 180 derajat)
    int angle = map(distance, 2, 50, 0, 180);
    
    // Batasi sudut agar tidak melebihi batas tertentu
    angle = constrain(angle, 0, 180);
    
    // Menggerakkan servo motor sesuai dengan sudut yang dihitung
    myservo.write(angle);
    
    delay(100); // Delay untuk memberikan waktu servo motor bergerak
  } else {
    Serial.println("Tidak dapat mendeteksi objek.");
  }
  
  delay(500); // Delay sebelum melakukan pengukuran berikutnya
}
