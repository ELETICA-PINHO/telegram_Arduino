
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));
  for (int i = 0; i < numNewMessages; i++) {
    chat_id = String(bot->messages[i].chat_id);
    String text = bot->messages[i].text;


    String from_name = bot->messages[i].from_name;
    if (from_name == "") from_name = "Convidado";


    //////////////////////////////RELE1////////////////////////////////////////////////////


    if ((text == "RELE1ON") && (ledStatus4 == 1)) {
      digitalWrite(RELE1, LOW);   // turn the LED on (HIGH is the voltage level)
      ledStatus4 = 0;
      bot->sendMessage(chat_id, " \xF0\x9F\x92\xA1 RELE 1 FOI LIGADO", "");
      gravarStatusPino4(LOW);
    }

    else if ((text == "RELE1ON") && (ledStatus4 == 0)) {
      bot->sendMessage(chat_id, " \xF0\x9F\x92\xA1 RELE 1 JA ESTAVA LIGADO", "");
    }

    if ((text == "RELE1OFF") && (ledStatus4 == 0)) {
      digitalWrite(RELE1, HIGH);    // turn the LED off (LOW is the voltage level)
      ledStatus4 = 1;
      bot->sendMessage(chat_id, " \xF0\x9F\x92\xA1 RELE 1 FOI DESLIGADO", "");
      gravarStatusPino4(HIGH);
    }

    else if ((text == "RELE1OFF") && (ledStatus4 == 1)) {
      bot->sendMessage(chat_id, " \xF0\x9F\x92\xA1 RELE 1 JA ESTAVA DESLIGADO", "");
    }


    if (text == "STATUS1") {

      if (ledStatus4) {

        bot->sendMessage(chat_id, " \xF0\x9F\x92\xA1 RELE 1 ESTA DESLIGADO", "");
      } else {

        bot->sendMessage(chat_id, " \xF0\x9F\x92\xA1 RELE 1 ESTA LIGADO", "");
      }
    }



    if (text == "PUSAR1") {
      digitalWrite(RELE1, LOW);   // turn the LED on (HIGH is the voltage level)
      delay(500);
      digitalWrite(RELE1, HIGH);   // turn the LED on (HIGH is the voltage level)
      bot->sendMessage(chat_id, " \xF0\x9F\x92\xA1 RELE 1 RECEBEU PULSO", "");
    }


    //--------------->>>>>FUNÇÃO RELOGIO NTP DEFINE DEZENA DE HORA<<<<<----------------------------------------------------

    if (text == "HORA") {
      timeClient.begin();
      timeClient.update();
      hora = timeClient.getFormattedTime();
      Serial.println(hora);
      String message = "Hora Atual: " + String(hora) + " \n";
      bot->sendMessage(chat_id, message, "");
    }



    if (text == "ALARME") {


      alarme();

    //  alarme_M_DEC = EEPROM.read(102);
     // alarme_M_DEC = alarme_M_DEC;
      //EEPROM.end();


      if (ativa == 1)
      {

        Serial.printf("TIME LIGA ATIVADO");
        bot->sendMessage(chat_id, " \xE2\x8F\xB0 TIME LIGA ATIVADO" , "");

      }

      if (ativa == 2)
      {
        Serial.printf("TIME DESLIGA ATIVADO");
        bot->sendMessage(chat_id, " \xE2\x8F\xB0 TIME DESLIGA ATIVADO" , "");

      }

      if (ativa == 0)
      {
        Serial.printf("ALARME DESATIVADO");
        bot->sendMessage(chat_id, " \xE2\x8F\xB0 ALARME DESATIVADO");

      }



      String message = "Alarme ajustado: " + String(alarme_H_DEC) + ":" + String(alarme_M_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");

    }




    if (text == "TIMELIGA") {
      EEPROM.begin(512);
      ativa = 1;
      Despertador = 1;
      EEPROM.write(105,Despertador);
      EEPROM.write(104,ativa);
      EEPROM.end();

      String message = " \xE2\x8F\xB0 TIME LIGA: " + String(ativa) + ":" + String(Despertador) + " \n";
      bot->sendMessage(chat_id, message, "");
    }



    if (text == "TIMEDESLIGA") {
      EEPROM.begin(512);
      ativa = 2;
      Despertador = 2;
      EEPROM.write(105,Despertador);
      EEPROM.write(104,ativa);
      EEPROM.end();

      String message = " \xE2\x8F\xB0 TIME DESLIGA: " + String(ativa) + ":" + String(Despertador) + " \n";
      bot->sendMessage(chat_id, message, "");
    }



    if (text == "DESATIVA") {
       EEPROM.begin(512);
      ativa = 0;
      EEPROM.write(104,ativa);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 DESLIGA ALARME: " ":" + String(ativa) + " \n";
      bot->sendMessage(chat_id, message, "");
    }





    if (text == "HORA0") {
       EEPROM.begin(512);
      alarme_H_DEC = 0;
      EEPROM.write(103,alarme_H_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 H:\x30\xE2\x83\xA3 \x30\xE2\x83\xA3 " + String("") + " \n";
      bot->sendMessage(chat_id, message, "");
    }


    if (text == "HORA1") {
       EEPROM.begin(512);
      alarme_H_DEC = 1;
      EEPROM.write(103,alarme_H_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 H: " + String(alarme_H_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");

    }

    if (text == "HORA2") {
       EEPROM.begin(512);
      alarme_H_DEC = 2;
      EEPROM.write(103,alarme_H_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 H: " + String(alarme_H_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }


    if (text == "HORA3") {
       EEPROM.begin(512);
      alarme_H_DEC = 3;
      EEPROM.write(103,alarme_H_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 H: " + String(alarme_H_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }


    if (text == "HORA4") {
       EEPROM.begin(512);
      alarme_H_DEC = 4;
      EEPROM.write(103,alarme_H_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 H: " + String(alarme_H_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }


    if (text == "HORA5") {
       EEPROM.begin(512);
      alarme_H_DEC = 5;
      EEPROM.write(103,alarme_H_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 H: " + String(alarme_H_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }


    if (text == "HORA6") {
       EEPROM.begin(512);
      alarme_H_DEC = 6;
      EEPROM.write(103,alarme_H_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 H: " + String(alarme_H_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }


    if (text == "HORA7") {
       EEPROM.begin(512);
      alarme_H_DEC = 7;
      EEPROM.write(103,alarme_H_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 H: " + String(alarme_H_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }



    if (text == "HORA8") {
       EEPROM.begin(512);
      alarme_H_DEC = 8;
      EEPROM.write(103,alarme_H_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 H: " + String(alarme_H_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }


    if (text == "HORA9") {
       EEPROM.begin(512);
      alarme_H_DEC = 9;
      EEPROM.write(103,alarme_H_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 H: " + String(alarme_H_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }


    if (text == "HORA10") {
       EEPROM.begin(512);
      alarme_H_DEC = 10;
      EEPROM.write(103,alarme_H_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 H" + String(alarme_H_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }



    if (text == "HORA11") {
       EEPROM.begin(512);
      alarme_H_DEC = 11;
      EEPROM.write(103,alarme_H_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 H: " + String(alarme_H_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }


    if (text == "HORA12") {
       EEPROM.begin(512);
      alarme_H_DEC = 12;
      EEPROM.write(103,alarme_H_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 H: " + String(alarme_H_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }


    if (text == "HORA13") {
       EEPROM.begin(512);
      alarme_H_DEC = 13;
      EEPROM.write(103,alarme_H_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 H: " + String(alarme_H_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }



    if (text == "HORA14") {
       EEPROM.begin(512);
      alarme_H_DEC = 14;
      EEPROM.write(103,alarme_H_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 H: " + String(alarme_H_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }


    if (text == "HORA15") {
       EEPROM.begin(512);
      alarme_H_DEC = 15;
      EEPROM.write(103,alarme_H_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 H: " + String(alarme_H_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }



    if (text == "HORA16") {
       EEPROM.begin(512);
      alarme_H_DEC = 16;
      EEPROM.write(103,alarme_H_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 H: " + String(alarme_H_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }


    if (text == "HORA17") {
       EEPROM.begin(512);
      alarme_H_DEC = 17;
      EEPROM.write(103,alarme_H_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 H: " + String(alarme_H_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }


    if (text == "HORA18") {
       EEPROM.begin(512);
      alarme_H_DEC = 18;
      EEPROM.write(103,alarme_H_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 H: " + String(alarme_H_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }



    if (text == "HORA19") {
       EEPROM.begin(512);
      alarme_H_DEC = 19;
      EEPROM.write(103,alarme_H_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 H: " + String(alarme_H_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }



    if (text == "HORA20") {
       EEPROM.begin(512);
      alarme_H_DEC = 20;
      EEPROM.write(103,alarme_H_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 H: " + String(alarme_H_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }


    if (text == "HORA21") {
       EEPROM.begin(512);
      alarme_H_DEC = 21;
      EEPROM.write(103,alarme_H_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 H: " + String(alarme_H_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }


    if (text == "HORA22") {
       EEPROM.begin(512);
      alarme_H_DEC = 22;
      EEPROM.write(103,alarme_H_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 H: " + String(alarme_H_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }


    if (text == "HORA23") {
      EEPROM.begin(512);
      alarme_H_DEC = 23;
      EEPROM.write(103,alarme_H_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 H: " + String(alarme_H_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }


    //--------------->>>>>FUNÇÃO RELOGIO NTP DEFINE DEZENA DE HORA FIM<<<<<----------------------------------------------------




    //--------------->>>>>FUNÇÃO RELOGIO NTP DEFINE DEZENA DE MINUTO<<<<<-------------------------------------------------------


    if (text == "MINUTO0") {
      EEPROM.begin(512);
      alarme_M_DEC = 0;
       EEPROM.write(102,alarme_M_DEC);
      EEPROM.end();

      String message = " \xE2\x8F\xB0 M " + String(alarme_M_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }




    if (text == "MINUTO5") {
      EEPROM.begin(512);
      alarme_M_DEC = 5;
      EEPROM.write(102,alarme_M_DEC);
      EEPROM.end();

      String message = " \xE2\x8F\xB0 M: " + String(alarme_M_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
      
    }



    if (text == "MINUTO10") {
      EEPROM.begin(512);
      alarme_M_DEC = 10;
      EEPROM.write(102,alarme_M_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 M: " + String(alarme_M_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }



    if (text == "MINUTO15") {
      EEPROM.begin(512);
      alarme_M_DEC = 15;
      EEPROM.write(102,alarme_M_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 M: " + String(alarme_M_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }


    if (text == "MINUTO20") {
      EEPROM.begin(512);
      alarme_M_DEC = 20;
      EEPROM.write(102,alarme_M_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 M: " + String(alarme_M_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }




    if (text == "MINUTO25") {
       EEPROM.begin(512);
      alarme_M_DEC = 25;
      EEPROM.write(102,alarme_M_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 M: " + String(alarme_M_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }




    if (text == "MINUTO30") {
       EEPROM.begin(512);
      alarme_M_DEC = 30;
      EEPROM.write(102,alarme_M_DEC);
      EEPROM.end();
      String message = "\xE2\x8F\xB0 M: " + String(alarme_M_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }


    if (text == "MINUTO35") {
       EEPROM.begin(512);
      alarme_M_DEC = 35;
      EEPROM.write(102,alarme_M_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 M: " + String(alarme_M_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }


    if (text == "MINUTO40") {
       EEPROM.begin(512);
      alarme_M_DEC = 40;
      EEPROM.write(102,alarme_M_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 M: " + String(alarme_M_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }


    if (text == "MINUTO45") {
       EEPROM.begin(512);
      alarme_M_DEC = 45;
      EEPROM.write(102,alarme_M_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 M: " + String(alarme_M_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }


    if (text == "MINUTO50") {
       EEPROM.begin(512);
      alarme_M_DEC = 50;
      EEPROM.write(102,alarme_M_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 M: " + String(alarme_M_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }


    if (text == "MINUTO55") {
       EEPROM.begin(512);
      alarme_M_DEC = 55;
      EEPROM.write(102,alarme_M_DEC);
      EEPROM.end();
      String message = " \xE2\x8F\xB0 M: " + String(alarme_M_DEC) + " \n";
      bot->sendMessage(chat_id, message, "");
    }



    //--------------->>>>>FUNÇÃO RELOGIO NTP DEFINE DEZENA DE MINUTO FIM<<<<<--------


    // Cria teclado com as opções de comando
    if (text == "OPCAOHORA") {
      String keyboardJson = "[[\"HORA1\", \"HORA2\"],[\"HORA3\", \"HORA4\"],[\"HORA5\", \"HORA6\"],[\"HORA7\", \"HORA8\"],[\"HORA9\", \"HORA10\"],[\"HORA11\", \"HORA12\"],[\"HORA13\", \"HORA14\"],[\"HORA15\", \"HORA16\"],[\"HORA17\", \"HORA18\"],[\"HORA19\", \"HORA20\"],[\"HORA21\", \"HORA22\"],[\"HORA23\", \"HORA0\"],[\"OPCAOMENU\"],[\"OPCAOTIME\"]]";
      bot->sendMessageWithReplyKeyboard(chat_id, " \xF0\x9F\x95\x90 Opções para Hora \xF0\x9F\x95\x90 ", "", keyboardJson, true);
    }

    if (text == "OPCAOMINUTO") {
      String keyboardJson = "[[\"MINUTO0\", \"MINUTO5\"],[\"MINUTO10\", \"MINUTO15\"],[\"MINUTO20\", \"MINUTO25\"],[\"MINUTO30\", \"MINUTO35\"],[\"MINUTO40\", \"MINUTO45\"],[\"MINUTO50\", \"MINUTO55\"],[\"OPCAOMENU\"],[\"OPCAOTIME\"]]";
      bot->sendMessageWithReplyKeyboard(chat_id, " \xF0\x9F\x95\x90 Opções para Minutos \xF0\x9F\x95\x90 ", "", keyboardJson, true);
    }

    if (text == "OPCAORELES") {
      String keyboardJson = "[[\"RELE1ON\", \"RELE1OFF\"],[\"PUSAR1\"],[\"STATUS1\"],[\"OPCAOMENU\"]]";
      bot->sendMessageWithReplyKeyboard(chat_id, " \xF0\x9F\x94\xA6 Opções para Reles \xF0\x9F\x94\xA6 ", "", keyboardJson, true);
    }

    if (text == "OPCAOTIME") {
      String keyboardJson = "[[\"HORA\", \"ALARME\"],[\"OPCAOMINUTO \", \"OPCAOHORA\"],[\"TIMELIGA \", \"TIMEDESLIGA\"], [\"DESATIVA\"], [\"OPCAOMENU\"]]";
      bot->sendMessageWithReplyKeyboard(chat_id, " \xF0\x9F\x95\x90 Opções para funções Time \xF0\x9F\x95\x90 ", "", keyboardJson, true);
    }

    if (text == "OPCAOMENU") {
      String keyboardJson = "[[\"OPCAOTIME\", \"OPCAORELES\"],[\"OPCAOMENU\"],[\"ELETRICAPINHO\"]]";
      bot->sendMessageWithReplyKeyboard(chat_id, "\xF0\x9F\x92\xBB Opções para Menus \xF0\x9F\x92\xBB ", "", keyboardJson, true);
    }

     if (text == "OPCAO") {
      String keyboardJson = "[[\"ELETRICAPINHO\"],[\"RELE1ON\", \"RELE1OFF\"],[\"PUSAR1\"],[\"STATUS1\"],[\"HORA\", \"ALARME\"],[\"TIMELIGA \", \"TIMEDESLIGA\"], [\"DESATIVA\"],[\"MINUTO0\", \"MINUTO5\"],[\"MINUTO10\", \"MINUTO15\"],[\"MINUTO20\", \"MINUTO25\"],[\"MINUTO30\", \"MINUTO35\"],[\"MINUTO40\", \"MINUTO45\"],[\"MINUTO50\", \"MINUTO55\"],[\"OPCAOMENU\"],[\"HORA1\", \"HORA2\"],[\"HORA3\", \"HORA4\"],[\"HORA5\", \"HORA6\"],[\"HORA7\", \"HORA8\"],[\"HORA9\", \"HORA10\"],[\"HORA11\", \"HORA12\"],[\"HORA13\", \"HORA14\"],[\"HORA15\", \"HORA16\"],[\"HORA17\", \"HORA18\"],[\"HORA19\", \"HORA20\"],[\"HORA21\", \"HORA22\"],[\"HORA23\", \"HORA0\"]]";
      bot->sendMessageWithReplyKeyboard(chat_id, "\xF0\x9F\x92\xBB Opções para Menus \xF0\x9F\x92\xBB ", "", keyboardJson, true);
    }




    if (text == "ELETRICAPINHO") {

      String welcome = from_name;
      welcome += "\n\n bem vindo ao Bot da Eletrica Pinho Sistemas Embarcados PIC,ESP,AVR,ARDUINO.  \xC2\xA9 \xC2\xAE \n\n";
      welcome += "Nosso blog\n";
      welcome += "https://eletricapinho.wordpress.com/ \n\n";
      welcome += "http://eletrica-pinho.blogspot.com.br/ \n\n";
      welcome += "E-mail: eletricapinho@gmail.com\n\n";
      welcome += "Cel: (11) 96875-7762 \n\n";
      welcome += "OPCAOMENU\n";
      bot->sendMessage(chat_id, welcome, "Markdown");

    }

  }

}