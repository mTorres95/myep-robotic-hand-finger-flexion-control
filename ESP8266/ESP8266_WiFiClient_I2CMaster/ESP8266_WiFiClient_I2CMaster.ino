#include <ESP8266WiFi.h>
#include <Wire.h>  //I2C

const char* ssid = "Torres";
const char* password = "miamarti";

const char* host = "192.168.0.11"; // 192.168.0.103
const byte port = 80;

const byte SLA = 0x20; // slave address

void setup()
{
  // Opens serial port, setting data rate in bps (=baud)
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);

  Serial.println("\n==============================");
  Serial.println(" ESP8266_WiFiClient_I2CMaster");
  Serial.println("==============================");
  Serial.printf("Conectando con %s ", ssid);
  Serial.println();
  // ======= CONEXION A WI-FI =======
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("EXITO - Conectado a red WiFi: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP de ESP8266: ");
  Serial.println(WiFi.localIP());
  
  //join i2c bus with SDA=D1 and SCL=D2 of NodeMCU
  Wire.begin(D1,D2);                                  //I2C  (Tools -> Board: NodeMCU 1.0 (ESP-12E Module) para que reconozca D1 y D2)
  
}


void loop()
{
  // Declaramos o instanciamos un cliente que se conectará al Host
  WiFiClient client;

  Serial.printf("\n[Conectando con %s ... ", host);
  // ======= CONEXION AL SERVIDOR =======
  // Intentamos conectarnos
  if (client.connect(host, port))
  {
    Serial.println("Conectado]");

    Serial.println("[Enviando una solicitud]");
    client.print(String("GET /") + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Conexion: close\r\n" +
                 "\r\n"
                );

    Serial.println("[Respuesta:]");
    // Mientras la conexion perdure
    while (client.connected())
    {
      // ======= RECEPCION DE DATOS =======
      // Si existen datos disponibles
      if (client.available())
      {
        String line = client.readStringUntil('\n');
        // I2C
        char * lineToSend = new char [line.length()+1];
        strcpy(lineToSend, line.c_str());
        // lineToSend = lineToSend + '0';
        // if (lineToSend[0] == 'F') {
        if (lineToSend[0] == ':') {
          Serial.println(lineToSend); 
          Wire.beginTransmission(SLA);   // START + SLAVE ADDRESS
          Wire.write(0xBB);              // SLAVE REGISTER
          Wire.write(lineToSend);        // DATA
          Wire.endTransmission();        // STOP
          delay(1000);      
        }
      }
    }
    // (VERIFICAR comentario) Una vez el servidor envia todos los datos requeridos se desconecta y el programa continua
    client.stop();
    Serial.println("\n[Desconectado]");
  }
  else
  {
    Serial.println("Fallo Conexion!]");
    client.stop();
  }
  delay(10000);
}
