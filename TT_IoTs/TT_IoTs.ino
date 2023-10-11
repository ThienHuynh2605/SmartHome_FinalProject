#define tivi_khach 17
#define quat_khach 16
#define btn_tivi_khach 34
#define btn_quat_khach_on 35
#define btn_quat_khach_off 32

#define den_ngu 0
#define tivi_ngu 19
#define btn_tivi_ngu 33
#define btn_den_ngu_on 25
#define btn_den_ngu_off 26

#define quat_bep 18
#define cua_bep 5
#define btn_cua_bep 27
#define btn_quat_bep_on 12
#define btn_quat_bep_off 14


#include <Arduino.h>
#include <DHT.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0X27, 16, 2);

// Define for MQ2
#define MQ2_D 4

// Define for DHT11 module
#define DHTPIN 23
DHT dht(DHTPIN, DHT11);  // chọn chân 23 cho cảm biến DHT11

// #define WIFI_SSID "eoh.io"
// #define WIFI_PASSWORD "Eoh@2020"
#define WIFI_SSID "Bong Bi"
#define WIFI_PASSWORD "khongbietmatkhau123"

/* Define the RTDB URL */
#define DATABASE_URL "tt-coso-ungdung-iots-default-rtdb.firebaseio.com"
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;


void setup() {
  Serial.begin(115200);
  dht.begin();

  // Configure for LCD_I2C
  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("L.K:");
  lcd.setCursor(8, 0);
  lcd.print("L.N:");
  lcd.setCursor(0, 1);
  lcd.print("T.Gio:");

  // Connect wifi.....................
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.database_url = DATABASE_URL;
  config.signer.test_mode = true;
  Firebase.reconnectNetwork(true);
  Firebase.begin(&config, &auth);
  Firebase.setDoubleDigits(5);

  pinMode(tivi_khach, OUTPUT);
  pinMode(quat_khach, OUTPUT);
  pinMode(btn_tivi_khach, INPUT);
  pinMode(btn_quat_khach_on, INPUT);
  pinMode(btn_quat_khach_off, INPUT);

  pinMode(den_ngu, OUTPUT);
  pinMode(tivi_ngu, OUTPUT);
  pinMode(btn_tivi_ngu, INPUT);
  pinMode(btn_den_ngu_on, INPUT);
  pinMode(btn_den_ngu_off, INPUT);

  pinMode(quat_bep, OUTPUT);
  pinMode(cua_bep, OUTPUT);
  pinMode(btn_cua_bep, INPUT);
  pinMode(btn_quat_bep_on, INPUT);
  pinMode(btn_quat_bep_off, INPUT);

  pinMode(MQ2_D, INPUT);
}

void loop() {

  int khiGas = digitalRead(MQ2_D);
  float humi = dht.readHumidity();     // Get humidity value from the DHT11 sensor
  float temp = dht.readTemperature();  // Get temperature value from the DHT11 sensor

  // Nut nhan Tivi phong khach
  if (digitalRead(btn_tivi_khach)) {
    delay(1);
    if (digitalRead(btn_tivi_khach)) {
      Serial.printf("Set bool PhongKhach -> TiVi %s\n", Firebase.setBool(fbdo, F("/PhongKhach/TiVi"), !digitalRead(tivi_khach)) ? "ok" : fbdo.errorReason().c_str());
      while (digitalRead(btn_tivi_khach))
        ;
    }
  }

  // Nut nhan bat quat phong khach
  if (digitalRead(btn_quat_khach_on)) {
    delay(1);
    if (digitalRead(btn_quat_khach_on)) {
      Serial.printf("Set bool PhongKhach -> Quat %s\n", Firebase.setBool(fbdo, F("/PhongKhach/Quat"), 1) ? "ok" : fbdo.errorReason().c_str());
      while (digitalRead(btn_quat_khach_on))
        ;
    }
  }

  // Nut nhan tat quat phong khach
  if (digitalRead(btn_quat_khach_off)) {
    delay(1);
    if (digitalRead(btn_quat_khach_off)) {
      Serial.printf("Set bool PhongKhach -> Quat %s\n", Firebase.setBool(fbdo, F("/PhongKhach/Quat"), 0) ? "ok" : fbdo.errorReason().c_str());
      while (digitalRead(btn_quat_khach_off))
        ;
    }
  }

  // Nut nhan Tivi phong ngu
  if (digitalRead(btn_tivi_ngu)) {
    delay(1);
    if (digitalRead(btn_tivi_ngu)) {
      Serial.printf("Set bool PhongNgu -> TiVi %s\n", Firebase.setBool(fbdo, F("/PhongNgu/TiVi"), !digitalRead(tivi_ngu)) ? "ok" : fbdo.errorReason().c_str());
      while (digitalRead(btn_tivi_ngu))
        ;
    }
  }

  // Nut nhan bat den phong ngu
  if (digitalRead(btn_den_ngu_on)) {
    delay(1);
    if (digitalRead(btn_den_ngu_on)) {
      Serial.printf("Set bool PhongNgu -> Den %s\n", Firebase.setBool(fbdo, F("/PhongNgu/Den"), 1) ? "ok" : fbdo.errorReason().c_str());
      while (digitalRead(btn_den_ngu_on))
        ;
    }
  }

  // Nut nhan tat den phong ngu
  if (digitalRead(btn_den_ngu_off)) {
    delay(1);
    if (digitalRead(btn_den_ngu_off)) {
      Serial.printf("Set bool PhongNgu -> Den %s\n", Firebase.setBool(fbdo, F("/PhongNgu/Den"), 0) ? "ok" : fbdo.errorReason().c_str());
      while (digitalRead(btn_den_ngu_off))
        ;
    }
  }

  //  nut nhan cua phong bep
  if (digitalRead(btn_cua_bep)) {
    delay(1);
    if (digitalRead(btn_cua_bep)) {
      Serial.printf("Set bool NhaBep -> CuaBep %s\n", Firebase.setBool(fbdo, F("/NhaBep/CuaBep"), !digitalRead(cua_bep)) ? "ok" : fbdo.errorReason().c_str());
      while (digitalRead(btn_cua_bep))
        ;
    }
  }

  // Nut nhan bat cua phong bep
  if (digitalRead(btn_quat_bep_on)) {
    delay(1);
    if (digitalRead(btn_quat_bep_on)) {
      Serial.printf("Set bool NhaBep -> Quat %s\n", Firebase.setBool(fbdo, F("/NhaBep/Quat"), 1) ? "ok" : fbdo.errorReason().c_str());
      while (digitalRead(btn_quat_bep_on))
        ;
    }
  }

  // Nut nhan tat cua phong bep
  if (digitalRead(btn_quat_bep_off)) {
    delay(1);
    if (digitalRead(btn_quat_bep_off)) {
      Serial.printf("Set bool NhaBep -> Quat %s\n", Firebase.setBool(fbdo, F("/NhaBep/Quat"), 0) ? "ok" : fbdo.errorReason().c_str());
      while (digitalRead(btn_quat_bep_off))
        ;
    }
  }


  // Gui du lieu len firebase
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 5000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

    // Quat phong khach
    bool firebase_quat_khach;
    Serial.printf("Get bool ref PhongKhach -> Quat: %s\n", Firebase.getBool(fbdo, F("/PhongKhach/Quat"), &firebase_quat_khach) ? firebase_quat_khach ? "ON" : "OFF" : fbdo.errorReason().c_str());
    firebase_quat_khach ? digitalWrite(quat_khach, HIGH) : digitalWrite(quat_khach, LOW);

    //Tivi phong khach
    bool firebase_tivi_khach;
    Serial.printf("Get bool ref PhongKhach -> TiVi: %s\n", Firebase.getBool(fbdo, F("/PhongKhach/TiVi"), &firebase_tivi_khach) ? firebase_tivi_khach ? "ON" : "OFF" : fbdo.errorReason().c_str());
    firebase_tivi_khach ? digitalWrite(tivi_khach, HIGH) : digitalWrite(tivi_khach, LOW);

    // Den phong ngu
    bool firebase_den_ngu;
    Serial.printf("Get bool ref PhongNgu -> Den: %s\n", Firebase.getBool(fbdo, F("/PhongNgu/Den"), &firebase_den_ngu) ? firebase_den_ngu ? "ON" : "OFF" : fbdo.errorReason().c_str());
    firebase_den_ngu ? digitalWrite(den_ngu, HIGH) : digitalWrite(den_ngu, LOW);

    // Tivi phong ngu
    bool firebase_tivi_ngu;
    Serial.printf("Get bool ref PhongNgu -> TiVi: %s\n", Firebase.getBool(fbdo, F("/PhongNgu/TiVi"), &firebase_tivi_ngu) ? firebase_tivi_ngu ? "ON" : "OFF" : fbdo.errorReason().c_str());
    firebase_tivi_ngu ? digitalWrite(tivi_ngu, HIGH) : digitalWrite(tivi_ngu, LOW);

    // Quat nha bep
    bool firebase_quat_bep;
    Serial.printf("Get bool ref NhaBep -> Quat: %s\n", Firebase.getBool(fbdo, F("/NhaBep/Quat"), &firebase_quat_bep) ? firebase_quat_bep ? "ON" : "OFF" : fbdo.errorReason().c_str());
    firebase_quat_bep ? digitalWrite(quat_bep, HIGH) : digitalWrite(quat_bep, LOW);

    // Cua nha bep
    bool firebase_cua_bep;
    Serial.printf("Get bool ref NhaBep -> CuaBep: %s\n", Firebase.getBool(fbdo, F("/NhaBep/CuaBep"), &firebase_cua_bep) ? firebase_cua_bep ? "ON" : "OFF" : fbdo.errorReason().c_str());
    firebase_cua_bep ? digitalWrite(cua_bep, HIGH) : digitalWrite(cua_bep, LOW);


    //Check if any reads failed and exit early (to try again).
    if (isnan(humi) || isnan(temp)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
    //Write the DHT11's value on Monitor
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println("ºC ");
    Serial.print("Humidity: ");
    Serial.println(humi);

    // Nhiet do, Do am
    Serial.printf("Set float NhietDo %s\n", Firebase.setFloat(fbdo, F("/NhietDo"), temp) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Set float DoAm %s\n", Firebase.setFloat(fbdo, F("/DoAm"), humi) ? "ok" : fbdo.errorReason().c_str());
    // Khi gas
    Serial.printf("Set bool KhiGas %s\n", Firebase.setBool(fbdo, F("/KhiGas"), !khiGas) ? "ok" : fbdo.errorReason().c_str());

    // Loa phong khach
    if (Firebase.getString(fbdo, F("/PhongKhach/Loa"))) {
      lcd.setCursor(4, 0);
      lcd.print(fbdo.to<const char *>());
    }

    // Loa phong ngu
    if (Firebase.getString(fbdo, F("/PhongNgu/Loa"))) {
      lcd.setCursor(12, 0);
      lcd.print(fbdo.to<const char *>());
    }

    // May thong gio nha bep
    if (Firebase.getString(fbdo, F("/NhaBep/MayThongGio"))) {
      lcd.setCursor(6, 1);
      lcd.print(fbdo.to<const char *>());
    }
  }
}
