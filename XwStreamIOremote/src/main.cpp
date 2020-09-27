/*
 * https://www.arduino.cc/en/Reference/KeyboardModifiers
 * http://kodi.wiki/view/keyboard_controls
 *
 */

#include <Arduino.h>
#include <Keyboard.h>
#include <IRremote.h>

int RECV_PIN = 4;
int VCC_PIN = 2;

IRrecv irrecv(RECV_PIN);
decode_results results;

char lastCode = 0x00;
int keyRepeatDelay = 300;

void setup()
{
  pinMode(VCC_PIN, OUTPUT);
  digitalWrite(VCC_PIN, HIGH);
  delay(200);

  Serial.begin(9600);
  irrecv.enableIRIn();

  Keyboard.begin();

/*
  for (int i=1; i<255; i++)
  {

    Keyboard.write(i);
    delay(100);
  }*/
}

void press(String help, char key, bool write = false)
{
  lastCode = key;

  if (help == "REPEAT")
    keyRepeatDelay = 50;
  else
    keyRepeatDelay = 300;

  Serial.println(help);
  //Serial.println(key);
  if (write == true)
    Keyboard.write(key);
  else
  {
    Keyboard.write(key);
    //Keyboard.releaseAll();
  }
}

void loop()
{
  if (irrecv.decode(&results))
  {
    Serial.println(results.value);

    switch(results.value)
    {
      case 4294967295: //LG
        press("REPEAT", lastCode);
        break;
      case 551493345: //LG
        press("FULLSCREEN", '\\');
        break;
      case 551486205: //LG
        press("UP", KEY_UP_ARROW);
        break;
      case 551518845: //LG
        press("DOWN", KEY_DOWN_ARROW);
        break;
      case 551510175: //LG
        press("RIGHT", KEY_RIGHT_ARROW);
        break;
      case 551542815: //LG
        press("LEFT", KEY_LEFT_ARROW);
        break;
      case 551489775: //LG
          press("ON", 's');
        break;
      case 551494365: //LG
          press("ENTER", KEY_RETURN);
        break;
      case 551490795: //LG
      case 551541285: //LG
          press("BACK", KEY_BACKSPACE);
        break;
      case 551501505: //LG
          press("HOME", KEY_HOME);
        break;
      case 551514510: //LG
          press("FASTFORWARD", 'f');
        break;
      case 551507370: //LG
          press("INFO", 'i');
        break;
      case 551489010: //LG
          press("PLAY", 'p');
        break;
      case 551547150: //LG
          press("REWIND", 'r');
        break;
      case 551525475: //LG
          press("SUBTITLES", 't');
        break;
      case 551521650: //LG
          press("STOP", 'x');
        break;
      case 551548170: //LG
          press("ZOOM", 'z');
        break;
      case 551509410: //LG
          press("PAUSE", ' ');
        break;
      case 551522415: //LG
          press("MUTE", KEY_F8);
        break;
      case 551502015: //LG
          press("VOLUMEUP", '=');
        break;
      case 551534655: //LG
          press("VOLUMEDOWN", '/');
        break;
      case 551485695: //LG
          press("PAGEUP", KEY_PAGE_UP);
        break;
      case 551518335: //LG
          press("PAGEDOWN", KEY_PAGE_DOWN);
        break;
    }

    irrecv.resume();
  }

  delay(keyRepeatDelay);
}
