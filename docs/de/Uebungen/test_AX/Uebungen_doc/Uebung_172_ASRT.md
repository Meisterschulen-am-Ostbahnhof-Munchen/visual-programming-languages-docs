# Uebung_172_ASRT: Exercise for ASRT_AX_T_FF_SR

![Uebung_172_ASRT_network](./Uebung_172_ASRT_network.svg)

* * * * * * * * * *

## Einleitung

Diese Übung zeigt die Anwendung eines SR+Toggle-Flipflops (ASRT) in der 4diac-IDE. Drei Taster an den digitalen Eingängen I1, I2 und I3 steuern das Setzen, Rücksetzen und Umschalten eines Speicherbausteins, dessen Ausgang einen digitalen Ausgang Q1 schaltet. Die Übung ist der direkte Nachfolger von `Uebung_171_ASR` und erweitert das reine SR-Flipflop um einen dritten, umschaltenden Eingang.

## Verwendete Funktionsbausteine (FBs)

### Sub-Bausteine: DigitalInput_CLK_I1, DigitalInput_CLK_I2 und DigitalInput_CLK_I3

- **Typ**: `logiBUS::io::DI::logiBUS_IE`
- **Verwendete interne FBs**: keine (Hardware-Konfigurationsbaustein)
  - **Parameter**:
    - `QI` = TRUE
    - `Input` = `Input_I1`, `Input_I2` bzw. `Input_I3`
    - `InputEvent` = `BUTTON_SINGLE_CLICK`
  - **Ereignisausgang**: `IND` (wird bei Betätigung des Tasters ausgelöst)
  - **Datenausgang**: keine
- **Funktionsweise**: Die Bausteine repräsentieren die digitalen Eingänge der logiBUS-Hardware. Sie detektieren einen einzelnen Tastendruck (Single Click) auf dem entsprechenden Eingangskanal und geben ein Ereignis (`IND`) aus.

### Sub-Baustein: ASRT_3EVENTS_TO_SRT_1

- **Typ**: `adapter::conversion::unidirectional::ASRT_3EVENTS_TO_SRT`
- **Verwendete interne FBs**: keine (Konvertierungsbaustein)
  - **Parameter**: keine
  - **Ereigniseingänge**: `SET`, `RESET`, `TOGGLE`
  - **Adapterausgang**: `ASRT_OUT` (verbindet sich mit einem ASRT-Adapter)
- **Funktionsweise**: Dieser Baustein wandelt drei separate Ereignisse (SET, RESET und TOGGLE) in eine Adapter-Schnittstelle um, die das Ansteuern eines ASRT-Flipflops ermöglicht. Ein eingehendes SET-Ereignis setzt den Ausgangsadapter auf den Set-Zustand, ein RESET-Ereignis auf den Reset-Zustand, ein TOGGLE-Ereignis kehrt den aktuellen Zustand um.

### Sub-Baustein: ASRT_AX_T_FF_SR_1

- **Typ**: `adapter::events::unidirectional::ASRT_AX_T_FF_SR`
- **Verwendete interne FBs**: keine (ASRT-Speicherbaustein)
  - **Parameter**: keine
  - **Adaptereingang**: `S_R_T` (erhält SET/RESET/TOGGLE-Signale vom Konverter)
  - **Datenausgang**: `Q` (boolescher Wert, Zustand des Flipflops)
- **Funktionsweise**: Der Baustein realisiert ein SR+Toggle-Flipflop. Der interne Zustand wird über den Adaptereingang `S_R_T` gesteuert: Ein Set-Signal aktiviert den Ausgang `Q` (TRUE), ein Reset-Signal deaktiviert ihn (FALSE), ein Toggle-Signal kehrt den aktuellen Zustand um. Der Ausgang bleibt bis zum nächsten Signal stabil.

### Sub-Baustein: DigitalOutput_Q1

- **Typ**: `logiBUS::io::DQ::logiBUS_QXA`
- **Verwendete interne FBs**: keine (Hardware-Konfigurationsbaustein)
  - **Parameter**:
    - `QI` = TRUE
    - `Output` = `Output_Q1`
  - **Daten eingang**: `OUT` (erhält den Schaltbefehl vom ASRT)
  - **Ereignisausgang**: keine
- **Funktionsweise**: Der Baustein steuert den digitalen Ausgang Q1 der logiBUS-Hardware. Sobald am Dateneingang `OUT` ein TRUE-Signal anliegt, wird der angeschlossene Aktor (z. B. eine Lampe) eingeschaltet; bei FALSE wird er ausgeschaltet.

## Programmablauf und Verbindungen

Der Ablauf wird durch die Ereignis- und Adapterverbindungen im SubApp-Netzwerk bestimmt:

1. **Eingangsereignisse**:
   - Ein Tastendruck an `Input_I1` löst im Baustein `DigitalInput_CLK_I1` das Ereignis `IND` aus. Dieses wird an den Ereigniseingang `SET` des Konverters `ASRT_3EVENTS_TO_SRT_1` geleitet.
   - Ein Tastendruck an `Input_I2` löst im Baustein `DigitalInput_CLK_I2` das Ereignis `IND` aus. Dieses wird an den Ereigniseingang `RESET` des Konverters geleitet.
   - Ein Tastendruck an `Input_I3` löst im Baustein `DigitalInput_CLK_I3` das Ereignis `IND` aus. Dieses wird an den Ereigniseingang `TOGGLE` des Konverters geleitet.

2. **Adapterverarbeitung**:
   - Der Konverter `ASRT_3EVENTS_TO_SRT_1` setzt den Ausgangsadapter `ASRT_OUT` entsprechend dem letzten eingehenden Ereignis (SET, RESET oder TOGGLE).
   - Der Adapterausgang ist mit dem Adaptereingang `S_R_T` des ASRT-Bausteins `ASRT_AX_T_FF_SR_1` verbunden.

3. **Speicher und Ausgabe**:
   - Der ASRT-Baustein reagiert auf das anliegende Adaptersignal und aktualisiert seinen Ausgang `Q`.
   - Der Ausgang `Q` ist mit dem Dateneingang `OUT` des digitalen Ausgangsbausteins `DigitalOutput_Q1` verbunden. Dadurch wird der physische Ausgang Q1 entsprechend ein- oder ausgeschaltet.

- **Lernziele**: Verständnis der Ereignissteuerung mit drei unabhängigen Eingängen, Umgang mit Adapterbausteinen, kombinierte SR+Toggle-Speicherfunktion, Abgrenzung zum reinen SR-Flipflop aus `Uebung_171_ASR`.
- **Schwierigkeitsgrad**: Mittel
- **Benötigte Vorkenntnisse**: Grundlagen der 4diac-IDE, Umgang mit Ereignis- und Datenverbindungen, logiBUS-Konfiguration, Kenntnis der Übung `Uebung_171_ASR`.
- **Ausführung**: Die Übung kann nach dem Laden und Kompilieren in der 4diac-Runtime ausgeführt werden. Die Eingangskanäle I1, I2 und I3 müssen mit Tastern belegt sein; der Ausgang Q1 steuert einen Aktor (z. B. LED oder Relais).

## Zusammenfassung

Die Übung `Uebung_172_ASRT` demonstriert die Realisierung eines SR+Toggle-Speichers mit drei Tastern als Eingänge und einem digitalen Ausgang. Sie ist der direkte Analog zu `Uebung_171_ASR`, ersetzt aber den ASR-Adapter durch den neuen ASRT-Adapter, der zusätzlich zu Set/Reset auch ein Toggle-Ereignis unterstützt. Der Nutzer lernt, wie drei diskrete Ereignisse über Adapter an einen kombinierten Speicherbaustein weitergegeben und schließlich auf einen physischen Ausgang geschaltet werden.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
