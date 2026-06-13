Hier ist die Dokumentation für die Übung `Uebung_171_AX` basierend auf den bereitgestellten Daten.

# Uebung_171_AX: Exercise for ASR_AX_SR


* * * * * * * * * *

## Einleitung
Diese Übung behandelt die Verwendung von Adaptern im Kontext von Set/Reset-Logik (SR-Flip-Flop) innerhalb eines Sub-Applikations-Netzwerks. Der Fokus liegt auf der Konvertierung von diskreten Ereignissen (Tasterklicks) in Adapter-Interaktionen und der Ansteuerung eines SR-Bausteins sowie eines digitalen Ausgangs über Adapter-Schnittstellen.

## Verwendete Funktionsbausteine (FBs)

In dieser Übung werden spezifische Bausteine zur Eingabeverarbeitung, Adapter-Konvertierung und Ausgabesteuerung verwendet.

### Sub-Bausteine:

### DigitalInput_CLK_I1 & DigitalInput_CLK_I2
- **Typ**: `logiBUS::io::DI::logiBUS_IE`
- **Beschreibung**: Diese Bausteine dienen als Schnittstelle zu den physischen Tastern.
- **Parameter**:
    - `QI`: `TRUE` (Baustein ist aktiv)
    - `Input`: `Input_I1` bzw. `Input_I2` (Auswahl des Eingangs)
    - `InputEvent`: `BUTTON_SINGLE_CLICK` (Reagiert auf einfachen Klick)
- **Ereignisausgang**:
    - `IND`: Feuert ein Ereignis, wenn der Taster gedrückt wird.

### ASR_2EVENTS_TO_SR
- **Typ**: `adapter::conversion::unidirectional::ASR_2EVENTS_TO_SR`
- **Beschreibung**: Ein Konverter-Baustein, der zwei separate Ereignisse (Setzen und Rücksetzen) entgegennimmt und diese in eine Adapter-Kommunikation für ein SR-Verhalten übersetzt.
- **Ereigniseingang**:
    - `SET`: Verbunden mit Taster 1.
    - `RESET`: Verbunden mit Taster 2.
- **Adapterausgang**:
    - `ASR_OUT`: Die Adapter-Schnittstelle zur Weitergabe der Befehle.

### ASR_AX_SR_1
- **Typ**: `adapter::events::unidirectional::ASR_AX_SR`
- **Beschreibung**: Dieser Baustein implementiert die SR-Logik (Set/Reset) basierend auf Adapter-Eingaben.
- **Adaptereingang**:
    - `S_R`: Empfängt die Set/Reset-Signale vom Konverter.
- **Adapterausgang**:
    - `Q`: Gibt den aktuellen Zustand weiter.

### DigitalOutput_Q1
- **Typ**: `logiBUS::io::DQ::logiBUS_QXA`
- **Beschreibung**: Dieser Baustein steuert den physischen Ausgang an, nimmt jedoch Adapter-Verbindungen entgegen.
- **Parameter**:
    - `QI`: `TRUE`
    - `Output`: `Output_Q1`
- **Adaptereingang**:
    - `OUT`: Verbunden mit dem Ausgang des SR-Bausteins.

## Programmablauf und Verbindungen

Der Ablauf der Übung gestaltet sich wie folgt:

1.  **Eingabeerfassung**:
    *   Der Baustein `DigitalInput_CLK_I1` überwacht den Eingang `I1`. Bei einem Klick wird das Ereignis `IND` ausgelöst.
    *   Der Baustein `DigitalInput_CLK_I2` überwacht den Eingang `I2`. Bei einem Klick wird das Ereignis `IND` ausgelöst.

2.  **Signalverarbeitung und Konvertierung**:
    *   Das `IND`-Ereignis von `DigitalInput_CLK_I1` ist mit dem Eingang `SET` des Bausteins `ASR_2EVENTS_TO_SR` verbunden.
    *   Das `IND`-Ereignis von `DigitalInput_CLK_I2` ist mit dem Eingang `RESET` des Bausteins `ASR_2EVENTS_TO_SR` verbunden.
    *   Der Baustein `ASR_2EVENTS_TO_SR` wandelt diese Ereignisse in Befehle auf der Adapter-Leitung `ASR_OUT` um.

3.  **Logik und Ausgabe**:
    *   Die Adapter-Verbindung führt von `ASR_2EVENTS_TO_SR.ASR_OUT` zu `ASR_AX_SR_1.S_R`. Hier wird der Zustand gespeichert (Setzen oder Rücksetzen).
    *   Der resultierende Zustand wird über die Adapter-Verbindung `ASR_AX_SR_1.Q` an den Ausgangsbaustein `DigitalOutput_Q1.OUT` weitergegeben.
    *   Dies bewirkt, dass der physische Ausgang `Q1` aktiviert wird, wenn `I1` gedrückt wurde, und deaktiviert wird, wenn `I2` gedrückt wurde.

**Lernziele:**
*   Verständnis des Adapter-Konzepts in IEC 61499 / 4diac.
*   Umwandlung von Event-basierter Logik in Adapter-basierte Logik.
*   Realisierung einer Speicherfunktion (SR) mittels Adapter-Bausteinen.

## Zusammenfassung
Die Übung `Uebung_171_AX` zeigt eine moderne Implementierung einer klassischen Speicherfunktion. Anstatt Signale direkt über Boolesche Verbindungen zu verknüpfen, werden hier Adapter verwendet, um die Kommunikation zwischen Eingabe-Konvertierung, Logik und Ausgabe zu kapseln. Dies reduziert die sichtbare Komplexität der Verbindungen und demonstriert die Flexibilität des Adapter-Konzepts für Standard-Automatisierungsaufgaben wie das Schalten eines Ausgangs über zwei Taster.