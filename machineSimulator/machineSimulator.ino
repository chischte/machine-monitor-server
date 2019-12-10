#include <Debounce.h> // https://github.com/chischte/debounce-library.git
#include <Insomnia.h> // https://github.com/chischte/insomnia-delay-library.git

const byte TOGGLE_PIN = 5;

Debounce stateToggleButton(TOGGLE_PIN);
Insomnia printDelay; //use no brackets for a delay
String countOneUp(String inputString)
{
  String outputString = String((inputString.toInt() + 1));
  return outputString;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(TOGGLE_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("id=1&status=POWER ON&cycr=***&cyct=***");
}

void loop() {
  // put your main code here, to run repeatedly:

  const String machineId = "1";
  static String machineStatus = "stopped";
  static String cyclesReset = "666";
  static String cyclesTotal = "1201556";
  if (stateToggleButton.switchedLow()) {
    if (machineStatus == "running") {
      machineStatus = "stopped";
    } else {
      machineStatus = "running";
    }
    cyclesReset = countOneUp(cyclesReset);
    cyclesTotal = countOneUp(cyclesTotal);
    String logString = "id=" + machineId + "&status=" + machineStatus + "&cycr=" + cyclesReset + "&cyct=" + cyclesTotal;
    Serial.println(logString);
  }

  //if (printDelay.delayTimeUp(3000)) {
  //Serial.println("id=2&status=running&cycr=666&cyct=1234567");
  //cyclesReset = countOneUp(cyclesReset);
  //cyclesTotal = countOneUp(cyclesTotal);
  //}
  
}
