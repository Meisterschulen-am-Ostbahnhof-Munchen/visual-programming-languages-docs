# sequence_E_04_loop_AX

<img width="1688" height="398" alt="image" src="https://github.com/user-attachments/assets/a7f7d9e9-e985-4624-8ec3-e6d406e4b85b" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `sequence_E_04_loop_AX` ist ein sequenzieller Steuerbaustein, der einen zyklischen Ablauf über vier Zustände realisiert. Die Zustandsübergänge werden ausschließlich durch externe Ereignisse ausgelöst. Jeder aktive Zustand setzt einen spezifischen digitalen Ausgang über einen zugeordneten Adapter. Der Baustein eignet sich für Anwendungen, bei denen ein schrittweiser Prozess mit manueller oder ereignisgesteuerter Fortschaltung benötigt wird, wie z.B. in manuellen Bedienabläufen oder testgesteuerten Sequenzen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **`START_S1`**: Löst den Übergang vom Initialzustand (`START`) in den ersten Arbeitszustand (`State_01`) aus.
*   **`S1_S2`**: Löst den Übergang von `State_01` zu `State_02` aus.
*   **`S2_S3`**: Löst den Übergang von `State_02` zu `State_03` aus.
*   **`S3_S4`**: Löst den Übergang von `State_03` zu `State_04` aus.
*   **`S4_S1`**: Löst den Übergang von `State_04` zurück zu `State_01` aus und schließt damit den Loop.
*   **`RESET`**: Setzt den Baustein aus jedem beliebigen Zustand zurück in den Initialzustand (`START`).

### **Ereignis-Ausgänge**
*   **`CNF`** (Execution Confirmation): Wird bei jedem Zustandswechsel ausgelöst, um die Ausführung zu bestätigen. Wird zusammen mit dem Datenausgang `STATE_NR` gesendet.

### **Daten-Eingänge**
*   Dieser Funktionsblock besitzt keine Daten-Eingänge.

### **Daten-Ausgänge**
*   **`STATE_NR`** (SINT): Gibt die aktuelle Zustandsnummer aus. Die Kodierung lautet: START = 0, State_01 = 1, State_02 = 2, State_03 = 3, State_04 = 4.

### **Adapter**
Der Baustein verfügt über vier Plug-Adapter des Typs `adapter::types::unidirectional::AX` (einfache Ausgabe).
*   **`DO_S1`**: Wird aktiviert, wenn `State_01` aktiv ist. Setzt das Signal `D1` auf `TRUE`.
*   **`DO_S2`**: Wird aktiviert, wenn `State_02` aktiv ist. Setzt das Signal `D1` auf `TRUE`.
*   **`DO_S3`**: Wird aktiviert, wenn `State_03` aktiv ist. Setzt das Signal `D1` auf `TRUE`.
*   **`DO_S4`**: Wird aktiviert, wenn `State_04` aktiv ist. Setzt das Signal `D1` auf `TRUE`.

## Funktionsweise
Der Baustein ist als BasicFB implementiert und folgt einem definierten Zustandsautomaten (ECC). Beim Eintritt in einen Zustand wird der entsprechende Entry-Algorithmus (`_E`) ausgeführt, der den zugehörigen Adapter-Ausgang (`D1`) auf `TRUE` setzt. Gleichzeitig wird der Confirmation-Algorithmus (`_C`) ausgeführt, der die `STATE_NR` setzt und das `CNF`-Ereignis auslöst.

Bei einem Zustandsübergang wird vor dem Verlassen des alten Zustands der entsprechende Exit-Algorithmus (`_X`) ausgeführt, der den zugehörigen Adapter-Ausgang (`D1`) auf `FALSE` zurücksetzt. Ein `RESET`-Ereignis deaktiviert alle potenziell aktiven Adapter-Ausgänge (durch Aufruf aller Exit-Algorithmen), setzt die Zustandsnummer auf 0 und wechselt in den `START`-Zustand.

Die Zustandsfolge ist: `START` -> `State_01` -> `State_02` -> `State_03` -> `State_04` -> (`State_01`). Der Übergang von `State_04` zurück zu `State_01` erfolgt durch das `S4_S1`-Ereignis, wodurch eine zyklische Wiederholung ermöglicht wird.

## Technische Besonderheiten
*   **Ereignisgesteuerte Transitionen:** Jeder Schritt muss explizit durch ein externes Ereignis freigegeben werden. Es gibt keine automatischen oder zeitgesteuerten Übergänge.
*   **Saubere Signalverwaltung:** Durch die Trennung in Entry- (Einschalten) und Exit-Algorithmen (Ausschalten) wird ein klares Schaltverhalten gewährleistet. Ein `RESET` deaktiviert systematisch alle Ausgänge.
*   **Adapter-basierte Ausgänge:** Die Verwendung von standardisierten AX-Adaptern ermöglicht eine einfache und typensichere Kopplung mit nachgelagerten Bausteinen oder Schnittstellen.
*   **Zustandsrückmeldung:** Der aktuelle Zustand wird kontinuierlich über den `STATE_NR`-Ausgang bereitgestellt und bei jedem Wechsel mit einem `CNF`-Ereignis quittiert.

## Zustandsübersicht
1.  **`xSTART`** (Initialzustand): Kein Adapter-Ausgang aktiv. `STATE_NR = 0`. Wartet auf `START_S1`.
2.  **`sState_01`**: Adapter `DO_S1` aktiv. `STATE_NR = 1`. Wartet auf `S1_S2` oder `RESET`.
3.  **`sState_02`**: Adapter `DO_S2` aktiv. `STATE_NR = 2`. Wartet auf `S2_S3` oder `RESET`.
4.  **`sState_03`**: Adapter `DO_S3` aktiv. `STATE_NR = 3`. Wartet auf `S3_S4` oder `RESET`.
5.  **`sState_04`**: Adapter `DO_S4` aktiv. `STATE_NR = 4`. Wartet auf `S4_S1` (Loop) oder `RESET`.
6.  **`sRESET`** (Zwischenzustand): Wird bei `RESET`-Ereignis angesprungen, deaktiviert alle Ausgänge, setzt `STATE_NR` auf 0 und wechselt automatisch (Condition=`1`) zurück zu `xSTART`.

## Anwendungsszenarien
*   **Manuelle Bediensequenzen:** Steuerung einer Maschine, bei der der Operator jeden Schritt manuell über einen Tastendruck freigeben muss (z.B. "Einspannen" -> "Bohren" -> "Fräsen" -> "Entladen").
*   **Test- und Prüfabläufe:** Schrittweise Ausführung von Funktionstests, wobei jeder Testschritt durch das Ergebnis des vorherigen Schritts freigegeben wird (als Ereignis).
*   **Sicherheitskritische Prozesse:** Prozesse, bei denen eine unkontrollierte automatische Fortschaltung unerwünscht ist und jeder Übergang explizit bestätigt werden muss.
*   **Zustandsgesteuerte Signalverteilung:** Verteilen eines Aktivsignals an verschiedene nachgelagerte Komponenten in einer festen, aber extern gesteuerten Reihenfolge.

## Vergleich mit ähnlichen Bausteinen
*   **Im Gegensatz zu `E_CYCLE`- oder `E_DELAY`-Bausteinen** besitzt dieser Sequenzer keine zeitgesteuerten, automatischen Übergänge. Jeder Schritt erfordert ein externes Trigger-Ereignis.
*   **Im Gegensatz zu einem einfachen `E_SR` (Flip-Flop)** oder mehreren `E_SPS`-Bausteinen kapselt dieser FB eine komplette Zustandsmaschine mit vier Zuständen und zyklischem Verhalten in einer einzigen, übersichtlichen Komponente.
*   **Im Gegensatz zu generischen State-Machine-FBs** ist dieser Baustein spezifisch für vier Zustände und die Nutzung von AX-Adaptern optimiert, was die Konfiguration vereinfacht, aber die Flexibilität für andere Zustandsanzahlen einschränkt.

## Fazit
Der `sequence_E_04_loop_AX` ist ein robuster und einfach zu verwendender Sequenzer für Anwendungen, die eine feste, ereignisgesteuerte Folge von vier Zuständen mit zugehörigen binären Ausgängen erfordern. Die klare Trennung von Ein- und Austrittsaktionen sowie der integrierte Reset-Mechanismus sorgen für ein vorhersehbares und sicheres Verhalten. Die Verwendung standardisierter Adapter fördert die Wiederverwendbarkeit und einfache Integration in größere Steuerungsanwendungen. Seine Stärke liegt in der Einfachheit und Eindeutigkeit für den konkreten Anwendungsfall, während für komplexere oder flexiblere Sequenzen andere Bausteine in Betracht gezogen werden sollten.
