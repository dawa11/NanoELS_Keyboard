#include <Keypad.h>
#include <ps2dev.h>

// PS/2 Pins: Clock an Pin 2, Data an Pin 3
PS2dev keyboard(2, 3);

const byte ROWS = 7; 
const byte COLS = 6; 

// Definition der Pins
byte rowPins[ROWS] = {4, 5, 6, 7, 8, 9, 10}; 
byte colPins[COLS] = {A3, 14, 15, A0, A1, A2}; 

// Tasten-Indizes für die Matrix
char keys[ROWS][COLS] = {
  {'q', 'w', 'e', 'r', 't', 'z'},   //F1, F2, F3, F4, F5, F6
  {'u', 'i', 'o', 'p', 'a', 'R'},   //F7, F8, F9, Enter, ESC, R
  {'Q', 'A', 'Z', 'D', '`', '+'},   //Q, A, Z, D, `, +
  {'C', 'S', 'X', 'W', '~', '-'},   //C, S, X, W, ~, -
  {'s', 'O', 'f', 'h', 'g', 'j'},   //Win, O, Up-Arrow, Left-Arrow, Down Arrow~, Right-Arrow
  {'7', '8', '9', '4', '5', '6'},   //7, 8, 9, 4, 5, 6
  {'1', '2', '3', '0', 'd', 'M'}    //1, 2, 3, 0, Backspace, M
};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  keyboard.keyboard_init();
  Serial.begin(9600);
}

// Zentrale Funktion zum Senden der PS/2 Befehle (Set 2)
void sendPS2(uint16_t scancode, bool pressed) {
  if (pressed) {
    if (scancode > 0xFF) keyboard.write(0xE0); // Extended-Präfix
    keyboard.write(scancode & 0xFF);           // Make-Code
  } else {
    if (scancode > 0xFF) keyboard.write(0xE0); // Extended-Präfix
    keyboard.write(0xF0);                      // Break-Code Präfix
    keyboard.write(scancode & 0xFF);           // Key-Code
  }
}

void loop() {
  // keypad.getKeys() füllt eine interne Liste mit allen Tasten, 
  // deren Status sich geändert hat.
  if (keypad.getKeys()) {
    // Wir nutzen hier 10 als Sicherheit (maximale Anzahl gleichzeitig erkannter Tasten)
    for (int i=0; i<10; i++) { 
      if (keypad.key[i].stateChanged) {
        bool isPressed = (keypad.key[i].kstate == PRESSED || keypad.key[i].kstate == HOLD);
        processKey(keypad.key[i].kchar, isPressed);
      }
    }
  }
}

void processKey(char key, bool pressed) {
  switch (key) {
    // Buchstaben
    case 'A': sendPS2(0x1C, pressed); Serial.println("A"); break;
    case 'W': sendPS2(0x1D, pressed); Serial.println("W"); break;
    case 'S': sendPS2(0x1B, pressed); Serial.println("S"); break;
    case 'D': sendPS2(0x23, pressed); Serial.println("D"); break;
    case 'R': sendPS2(0x2D, pressed); Serial.println("R"); break;
    case 'M': sendPS2(0x3A, pressed); Serial.println("M"); break;
    case 'X': sendPS2(0x22, pressed); Serial.println("X"); break;
    case 'Z': sendPS2(0x1A, pressed); Serial.println("Z"); break;
    case 'C': sendPS2(0x21, pressed); Serial.println("C"); break;
    case 'Q': sendPS2(0x15, pressed); Serial.println("Q"); break;
    case 'O': sendPS2(0x44, pressed); Serial.println("O"); break;

    // F-Tasten
    case 'q': sendPS2(0x05, pressed); Serial.println("F1"); break; // F1
    case 'w': sendPS2(0x06, pressed); Serial.println("F2"); break; // F2
    case 'e': sendPS2(0x04, pressed); Serial.println("F3"); break; // F3
    case 'r': sendPS2(0x0C, pressed); Serial.println("F4"); break; // F4
    case 't': sendPS2(0x03, pressed); Serial.println("F5"); break; // F5
    case 'z': sendPS2(0x0B, pressed); Serial.println("F6"); break; // F6
    case 'u': sendPS2(0x83, pressed); Serial.println("F7"); break; // F7
    case 'i': sendPS2(0x0A, pressed); Serial.println("F8"); break; // F8
    case 'o': sendPS2(0x01, pressed); Serial.println("F9"); break; // F9
    
    // Zahlen (Hauptreihe)
    case '0': sendPS2(0x45, pressed); Serial.println("0"); break;
    case '1': sendPS2(0x16, pressed); Serial.println("1"); break;
    case '2': sendPS2(0x1E, pressed); Serial.println("2"); break;
    case '3': sendPS2(0x26, pressed); Serial.println("3"); break;
    case '4': sendPS2(0x25, pressed); Serial.println("4"); break;
    case '5': sendPS2(0x2E, pressed); Serial.println("5"); break;
    case '6': sendPS2(0x36, pressed); Serial.println("6"); break;
    case '7': sendPS2(0x3D, pressed); Serial.println("7"); break;
    case '8': sendPS2(0x3E, pressed); Serial.println("8"); break;
    case '9': sendPS2(0x46, pressed); Serial.println("9"); break;

    // Sonderzeichen & System
    case '+': sendPS2(0x12, pressed); sendPS2(0x55, pressed); Serial.println("+"); break; // Numpad +
    case '-': sendPS2(0x4E, pressed); Serial.println("-"); break; // Numpad -
    case 'p': sendPS2(0x5A, pressed); Serial.println("Enter"); break; // Enter
    case 'a': sendPS2(0x76, pressed); Serial.println("ESC"); break; // Escape
    case 'd': sendPS2(0x66, pressed); Serial.println("Backspace"); break; // Backspace
    case 's': sendPS2(0x00, pressed); Serial.println("Windows"); break; // Windows Taste
    case '~': sendPS2(0x12, pressed); sendPS2(0x0E, pressed); Serial.println("Tilde"); break; //Tilde
    case '`': sendPS2(0x0E, pressed); Serial.println("Backtick"); break; //Backtick

    // Pfeiltasten (Extended)
    case 'f': sendPS2(0xE075, pressed); Serial.println("Up"); break; // Hoch
    case 'g': sendPS2(0xE072, pressed); Serial.println("Down"); break; // Runter
    case 'h': sendPS2(0xE06B, pressed); Serial.println("Left"); break; // Links
    case 'j': sendPS2(0xE074, pressed); Serial.println("Right"); break; // Rechts
  }
}