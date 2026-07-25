#include <Wire.h>  // TR: I2C haberleşme protokolü için gerekli kütüphane
                   // EN: Required library for I2C communication protocol

#include <hd44780.h>  // TR: LCD ekranlar için ana hd44780 kütüphanesi
                      // EN: Main hd44780 library for LCD displays

#include <hd44780ioClass/hd44780_I2Cexp.h>  // TR: I2C genişletici modüllü LCD sürücüsü
                                            // EN: LCD driver class for I2C expander modules

#include <DHT.h>  // TR: DHT sıcaklık ve nem sensörü kütüphanesi
                  // EN: DHT temperature and humidity sensor library

// DHT Sensör Ayarları / DHT Sensor Settings
#define DHTPIN 2       // TR: Sensörün bağlı olduğu dijital pin (Pin 2)
                       // EN: Digital pin where the sensor is connected (Pin 2)

#define DHTTYPE DHT11  // TR: Sensör tipini DHT11 olarak tanımlar
                       // EN: Defines the sensor type as DHT11

// TR: DHT sensör nesnesini verilen pin ve tipe göre oluşturur
// EN: Creates the DHT sensor object with specified pin and type
DHT dht(DHTPIN, DHTTYPE);

// TR: LCD nesnesini tanımlar (hd44780 adresi otomatik olarak tespit eder)
// EN: Defines the LCD object (hd44780 auto-detects the I2C address)
hd44780_I2Cexp lcd;

const int LCD_COLS = 16;  // TR: LCD ekranın sütun sayısı (16 karakter)
                          // EN: Number of columns on the LCD (16 characters)

const int LCD_ROWS = 2;   // TR: LCD ekranın satır sayısı (2 satır)
                          // EN: Number of rows on the LCD (2 rows)

void setup() {
  // TR: Seri haberleşmeyi 9600 baud hızıyla başlatır
  // EN: Initializes serial communication at 9600 baud rate
  Serial.begin(9600);
  
  // TR: DHT sensörünü veri okumak için başlatır
  // EN: Initializes the DHT sensor for reading data
  dht.begin();

  // TR: LCD'yi belirtilen boyutlarda başlatır ve bağlantı durumunu saklar
  // EN: Initializes the LCD with defined size and stores the connection status
  int status = lcd.begin(LCD_COLS, LCD_ROWS);

  // TR: 0 dışında bir değer dönerse bağlantı hatası var demektir
  // EN: If a value other than 0 is returned, it indicates a connection error
  if (status) { 
    // TR: Hata durumunda Arduino üzerindeki dahili LED'i yakıp söndürür (sistemi kilitler)
    // EN: Blinks the built-in LED on Arduino in case of a fatal error (halts execution)
    hd44780::fatalError(status); 
  }
}

void loop() {
  // TR: Sensörden sıcaklık değerini Celsius olarak okur
  // EN: Reads the temperature value from sensor in Celsius
  int sicaklik = dht.readTemperature();

  // TR: Sensörden nem değerini yüzde olarak okur
  // EN: Reads the humidity value from sensor as percentage
  int nem = dht.readHumidity();

  // TR: Okunan değerlerin sayı olup olmadığını kontrol et (isnan = is not a number)
  // EN: Checks if the read values are valid numbers (isnan = is not a number)
  if (isnan(sicaklik) || isnan(nem)) {
    // TR: Sensör okuma hatasını seri porta bildirir
    // EN: Reports sensor read error to the serial port
    Serial.println("DHT sensorunden veri okunamadi!");

    // TR: LCD ekranı temizler
    // EN: Clears the LCD screen
    lcd.clear();

    // TR: İmleci ilk satırın ilk karakterine konumlandırır (Satır 0, Sütun 0)
    // EN: Sets the cursor to the first row, first column (Row 0, Column 0)
    lcd.setCursor(0, 0);

    // TR: LCD ekrana hata mesajı yazdırır
    // EN: Prints error message on the LCD screen
    lcd.print("Sensor ERROR!");
  } else {
    // TR: Python kodunun okuyabileceği seri port metin formatını oluşturur
    // EN: Formats the serial output string to be parsed by Python
    String veri = "Temperature: " + String(sicaklik) + "\t humidity: %" + String(nem);

    // TR: Veriyi seri porta gönderir (Python bu satırı seri porttan yakalayacak)
    // EN: Sends data to serial port (Python will capture this line from serial)
    Serial.println(veri);

    // TR: LCD ekranı önceki içerikten temizler
    // EN: Clears previous content from the LCD screen
    lcd.clear();

    // TR: İmleci ilk satırın başına getirir
    // EN: Sets cursor to the beginning of the first line
    lcd.setCursor(0, 0);

    // TR: İlk satıra "Temperature: " başlığını yazar
    // EN: Prints "Temperature: " header on the first line
    lcd.print("Temperature: ");

    // TR: İmleci ikinci satırın başına getirir (Satır 1, Sütun 0)
    // EN: Sets cursor to the beginning of the second line (Row 1, Column 0)
    lcd.setCursor(0, 1);

    // TR: İkinci satıra sıcaklık değerini yazar
    // EN: Prints the temperature value on the second line
    lcd.print(sicaklik);

    // TR: Sıcaklık değerinin yanına " C" birimini ekler
    // EN: Appends " C" unit next to the temperature value
    lcd.print(" C");
  }

  // TR: DHT11 sensörünün kararlı okuma yapabilmesi için 2 saniye bekler
  // EN: Delays for 2 seconds to allow the DHT11 sensor to read stably
  delay(2000); 
}
