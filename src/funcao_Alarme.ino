void alarme() {


  if (ativa == 1 ) {
    if (Despertador == 1) {
      despertador_liga();
    }
  }


  if (ativa == 2 ) {
    if (Despertador == 2) {
      despertador_desliga();
    }
  }

}

void despertador_liga() {
  hora_DEC = timeClient.getHours();
  minuto_DEC = timeClient.getMinutes();

  if (hora_DEC == alarme_H_DEC && minuto_DEC == alarme_M_DEC )
  {

    hora_DEC = timeClient.getHours();
    minuto_DEC = timeClient.getMinutes();
    hora = timeClient.getFormattedTime();
    digitalWrite(RELE1, LOW);
    bot->sendMessage(chat_id, "DESPERTADOR LIGA", "");
    bot->sendMessage(chat_id, hora , "");

  }

}


void despertador_desliga() {

  hora_DEC = timeClient.getHours();
  minuto_DEC = timeClient.getMinutes();

  if (hora_DEC == alarme_H_DEC && minuto_DEC == alarme_M_DEC )
  {

    hora_DEC = timeClient.getHours();
    minuto_DEC = timeClient.getMinutes();
    hora = timeClient.getFormattedTime();
    digitalWrite(RELE1, HIGH);
    Serial.println("ALOALO ALO ");
    bot->sendMessage(chat_id, "DESPERTADOR DESLIGA", "");
    bot->sendMessage(chat_id, hora , "");
  }

}