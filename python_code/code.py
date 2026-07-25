import sqlite3 # SQLite veritabanı işlemleri için gerekli modülü içe aktarır.|Imports the module required for SQLite database operations
import serial # Seri port (Arduino vb.) ile iletişim kurmak için pyserial modülünü içe aktarır| Imports the pyserial module to communicate with the serial port (Arduino, etc.)

# TR: DB Browser for SQLite ile oluşturulan veritabanı dosyasına bağlanır
# EN: Connects to the database file created with DB Browser for SQLite
baglan = sqlite3.connect(r"c:\Users\tech\OneDrive\Masaüstü\database.db")

# TR: Veritabanı üzerinde SQL sorguları (INSERT vb.) çalıştırmak için imleç (cursor) oluşturur
# EN: Creates a cursor object to execute SQL queries (INSERT, etc.) on the database
cursor = baglan.cursor()

# TR: COM3 portundan 9600 baud hızıyla seri iletişimi başlatır
# EN: Initializes serial communication on port COM3 at 9600 baud rate
ser = serial.Serial("COM3", 9600, timeout=1)

# TR: Seri porttan sürekli veri okumak için sonsuz döngü başlatır
# EN: Starts an infinite loop to continuously read data from the serial port
while True:
    try: 
        # TR: Porttan gelen satırı okur, UTF-8'e çevirir ve kenar boşluklarını temizler
        # EN: Reads a line from the port, decodes it to UTF-8, and strips whitespace
        veri = ser.readline().decode("utf-8", errors="ignore").strip()

        # TR: Gelen veri "Temperature:" ile başlıyorsa işleme alır
        # EN: Checks if the incoming data starts with "Temperature:"
        if veri.startswith("Temperature:"):

            # TR: Metni ':' karakterinden bölüp değer kısmını ("28\thumidity") alır
            # EN: Splits text by ':' and extracts the value portion ("28\thumidity")
            ham_deger = veri.split(":")[1].strip()
            
            # TR: Yandaki "humidity" gibi kelimeleri atıp sadece ilk elemanı (sayıyı) alır
            # EN: Removes extra words like "humidity" and takes only the first element (the number)
            sayi_str = ham_deger.split()[0] 

            # TR: Metin halindeki sıcaklık bilgisini tam sayıya (integer) dönüştürür
            # EN: Converts the temperature string into an integer
            sicaklik_degeri = int(sayi_str)

            # TR: DB Browser'da açtığın 'dht11' tablosunun 'temperature' sütununa veriyi ekler
            # Note: (sicaklik_degeri,) -> Tek elemanlı Tuple için virgül ŞART / Comma is REQUIRED for single-element Tuple
            # EN: Inserts the value into the 'temperature' column of the 'dht11' table created in DB Browser
            cursor.execute("INSERT INTO dht11 (temperature) VALUES (?)", (sicaklik_degeri,))

            # TR: Veritabanında yapılan değişikliği kalıcı olarak kaydeder
            # EN: Commits and permanently saves the changes to the database
            baglan.commit()

            # TR: Başarıyla kaydedilen değeri terminale yazdırır
            # EN: Prints the successfully saved value to the terminal
            print(f"Temperature saved: {sicaklik_degeri}")
            
    except Exception as e:
        # TR: Okuma veya veritabanı kaydı sırasında oluşabilecek hataları yakalar
        # EN: Catches any exception during reading or database operation
        print("Error:", e)
