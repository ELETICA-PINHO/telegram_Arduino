
#include <FS.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <EEPROM.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic
#include <NTPClient.h>
#include <WiFiUdp.h>
#define BOT_TOKEN_LENGTH 47
#define PULSADOR1  2
#define RELE1      0

//-----------------------Variaveis Globais------------------------------------------------------------
WiFiUDP ntpUDP;
String hora;
uint8_t hora_DEC;
uint8_t minuto_DEC;
uint8_t alarme_H_DEC;
uint8_t alarme_M_DEC;
uint8_t ativa = 0;
uint8_t Despertador = 0;
//uint8_t Despertador_desliga = 0;
int16_t utc = -3; // horario normal UTC -3:00 Brazil  >> horario de verão UTC -2:00 Brazil  
uint32_t currentMillis = 0;
uint32_t previousMillis = 0;
NTPClient timeClient(ntpUDP, "a.st1.ntp.br", utc * 3600, 60000);


char botToken[BOT_TOKEN_LENGTH] = "";
WiFiClientSecure client;
UniversalTelegramBot *bot;

int Bot_mtbs = 100; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done
bool Start = false;
int ledStatus4 = 0;
int sensorStatus4 = 0;
String chat_id;
char stado;
int flag4 = 0;
int entradas = 0;
uint8_t statusAnt4   =             0;
uint8_t config_salva   =           0;
bool shouldSaveConfig = false;
int StatusPulsador1;
//--------------------------------------Fim Variaveis Globais-------------------------------------------------



//-----------------Prototipo de Funções Auxiliares----------------------------

void saveConfigCallback ();
void readBotTokenFromEeprom();
void writeBotTokenToEeprom();
void gravarStatusPino4();
void lerStatusAnteriorPino();
void handleNewMessages();
void FUNCAO_PULSADOR1();
void alarme_ativa();
void despertador_liga();
void despertador_desliga();
void alarme();

//-----------------------------------------------------------------------------



void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  pinMode(PULSADOR1, INPUT);
  pinMode(RELE1, OUTPUT);
  digitalWrite(RELE1, HIGH);
  
  Serial.println("read bot token");
  readBotTokenFromEeprom(0);
  Serial.println(botToken);
  WiFiManager wifiManager;
  wifiManager.setSaveConfigCallback(saveConfigCallback);
  WiFiManagerParameter custom_bot_id("botid", "Bot Token", botToken, 50);
  wifiManager.addParameter(&custom_bot_id);
  wifiManager.autoConnect("Eletrica Pinho");

  strcpy(botToken, custom_bot_id.getValue());
  if (shouldSaveConfig) {
    writeBotTokenToEeprom(0);
  }

  bot = new UniversalTelegramBot(botToken, client);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  lerStatusAnteriorPino();

bot->sendMessage(chat_id, "Placa foi Reiniciada! ou falta de energia", "");
bot->sendMessage(chat_id, hora , "");

bot->sendMessage(chat_id, "Placa foi Reiniciada! ou falta de energia", "");
bot->sendMessage(chat_id, hora , "");

}



void loop() {

  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot->getUpdates(bot->last_message_received + 1);

    while (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot->getUpdates(bot->last_message_received + 1);
    }

    Bot_lasttime = millis();
  }

  FUNCAO_PULSADOR1();
  alarme();




}




void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

void readBotTokenFromEeprom(int offset) {
  for (int i = offset; i < BOT_TOKEN_LENGTH; i++ ) {
    botToken[i] = EEPROM.read(i);
  }
  EEPROM.commit();
}

void writeBotTokenToEeprom(int offset) {
  for (int i = offset; i < BOT_TOKEN_LENGTH; i++ ) {
    EEPROM.write(i, botToken[i]);
  }
  EEPROM.commit();
}





