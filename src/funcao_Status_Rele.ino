void lerStatusAnteriorPino() {

  statusAnt4 = EEPROM.read(100);
  ledStatus4 = statusAnt4;

  if (statusAnt4 > 1) {
    statusAnt4 = 0;                //Provavelmente é a primeira leitura da EEPROM, passando o valor padrão para o pino.
    EEPROM.write(100, statusAnt4);
  }
  digitalWrite(RELE1, statusAnt4);

  alarme_M_DEC = EEPROM.read(102);
  alarme_M_DEC = alarme_M_DEC;

  alarme_H_DEC = EEPROM.read(103);
  alarme_H_DEC = alarme_H_DEC;


  ativa = EEPROM.read(104);
  ativa = ativa;

  Despertador = EEPROM.read(105);
  Despertador = Despertador;

  
EEPROM.end();


bot->sendMessage(chat_id, "Placa foi Reiniciada! ou falta de energia", "");
bot->sendMessage(chat_id, hora , "");










}//lerStatusAnteriorPino


void gravarStatusPino4(uint8_t statusPino4) {
  EEPROM.begin(512);
  EEPROM.write(100, statusPino4);
  EEPROM.end();
}