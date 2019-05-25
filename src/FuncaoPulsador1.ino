void FUNCAO_PULSADOR1() {

  String ale;
  String PULSADOR;

  if ( (digitalRead(PULSADOR1) == LOW) && (flag4 == 0) ) {

    if (StatusPulsador1 == LOW) {
      digitalWrite(RELE1, !digitalRead(RELE1));
    }

    if (digitalRead(RELE1)) {
      ledStatus4 = 1;
      gravarStatusPino4(HIGH);
    } else {
      ledStatus4 = 0;
      gravarStatusPino4(LOW);
    }

    ale = ledStatus4;

    if (ledStatus4 == 0) {

      PULSADOR = " \xF0\x9F\x92\xA1 LIGADO VIA PULSADOR \xF0\x9F\x92\xA1";

    }
    if (ledStatus4 == 1) {
      PULSADOR = " \xF0\x9F\x92\xA1 DESLIGADO VIA PULSADOR \xF0\x9F\x92\xA1";
    }

    Serial.println("botão pressionado 1 ");
    bot->sendMessage(chat_id, PULSADOR , "");
    gravarStatusPino4(ledStatus4);
  }


}