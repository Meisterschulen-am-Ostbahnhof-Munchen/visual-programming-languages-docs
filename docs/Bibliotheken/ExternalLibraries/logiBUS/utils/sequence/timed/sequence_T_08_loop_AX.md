# sequence_T_08_loop_AX

<img width="1129" height="403" alt="image" src="https://github.com/user-attachments/assets/9561f0ed-527a-45c8-81f5-0ecdd43aab2e" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `sequence_T_08_loop_AX` ist ein zeitgesteuerter Sequenzer mit acht Zuständen. Er realisiert eine zyklische Abfolge, bei der jeder Zustand für eine individuell einstellbare Zeitdauer aktiv ist. Der Übergang zum nächsten Zustand erfolgt automatisch nach Ablauf der eingestellten Zeit. Der Block ist für Anwendungen konzipiert, in denen eine feste Reihenfolge von Aktionen (z. B. das Schalten von Ausgängen) in einer Schleife durchlaufen werden muss.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **`START_S1`**: Startet die Sequenz. Beim Empfang dieses Ereignisses springt der Block vom initialen `START`-Zustand in den ersten aktiven Zustand `State_01`. Das Ereignis ist mit allen Zeitdaten-Eingängen verknüpft.
*   **`RESET`**: Setzt die Sequenz zurück. Unabhängig vom aktuellen Zustand führt dieses Ereignis zum sofortigen Übergang in den `RESET`-Zustand und anschließend zurück in den initialen `START`-Zustand.

### **Ereignis-Ausgänge**
*   **`CNF`** (Execution Confirmation): Wird bei jedem Zustandswechsel ausgelöst, um die Ausführung zu bestätigen. Das Ereignis ist mit dem Datenausgang `STATE_NR` verknüpft, der die Nummer des neu aktivierten Zustands liefert.

### **Daten-Eingänge**
Alle Daten-Eingänge sind vom Typ `TIME` und definieren die Verweilzeit für den jeweiligen Zustand vor dem automatischen Übergang. Der Standardinitialwert ist `NO_TIME`.
*   **`DT_S1_S2`**: Verweilzeit in `State_01` vor Übergang zu `State_02`.
*   **`DT_S2_S3`**: Verweilzeit in `State_02` vor Übergang zu `State_03`.
*   **`DT_S3_S4`**: Verweilzeit in `State_03` vor Übergang zu `State_04`.
*   **`DT_S4_S5`**: Verweilzeit in `State_04` vor Übergang zu `State_05`.
*   **`DT_S5_S6`**: Verweilzeit in `State_05` vor Übergang zu `State_06`.
*   **`DT_S6_S7`**: Verweilzeit in `State_06` vor Übergang zu `State_07`.
*   **`DT_S7_S8`**: Verweilzeit in `State_07` vor Übergang zu `State_08`.
*   **`DT_S8_S1`**: Verweilzeit in `State_08` vor Übergang zu `State_01` (Zyklus).

### **Daten-Ausgänge**
*   **`STATE_NR`** (Typ: `SINT`): Gibt die aktuelle Zustandsnummer aus. Die Nummerierung ist wie folgt: `START = 0`, `State_01 = 1`, `State_02 = 2`, ..., `State_08 = 8`.

### **Adapter**
Der Block verwendet neun Adapter-Sockets (`Plugs`):
*   **`DO_S1` bis `DO_S8`** (Typ: `adapter::types::unidirectional::AX`): Unidirektionale Adapter, die den physischen oder logischen Ausgang repräsentieren, der aktiviert wird, wenn der entsprechende Zustand (`State_01` bis `State_08`) aktiv ist.
*   **`timeOut`** (Typ: `iec61499::events::ATimeOut`): Ein Zeitgeber-Adapter, der für die zeitgesteuerten Zustandsübergänge verantwortlich ist. Er wird in jedem aktiven Zustand gestartet und löst bei Zeitablauf das `TimeOut`-Ereignis aus.

## Funktionsweise
Der FB ist als Basic Function Block (BFB) mit einer Execution Control Chart (ECC) implementiert. Die ECC besteht aus einem initialen Zustand (`xSTART`), acht aktiven Zuständen (`sState_01` bis `sState_08`), einem Reset-Zustand (`sRESET`) und den dazugehörigen Übergängen.

1.  **Start**: Bei Empfang des `START_S1`-Ereignis wechselt der FB von `xSTART` in `sState_01`.
2.  **Zustandsaktivierung**: Beim Eintritt in einen aktiven Zustand (z.B. `sState_01`) werden mehrere Aktionen ausgeführt:
    *   Der entsprechende Ausgangsadapter wird über den `E`-Algorithmus (Entry) eingeschaltet (z.B. `DO_S1.D1 := TRUE`).
    *   Der `CNF`-Ausgang wird mit der neuen Zustandsnummer (`STATE_NR`) getriggert.
    *   Die für diesen Zustand konfigurierte Zeit (`DT_Sx_Sy`) wird an den `timeOut`-Adapter übergeben und dieser wird gestartet.
    *   Der Ausgangsadapter des vorherigen Zustands wird über den `X`-Algorithmus (Exit) ausgeschaltet (dies geschieht bereits während des Eintritts in den neuen Zustand).
3.  **Zeitgesteuerter Übergang**: Nach Ablauf der im `timeOut`-Adapter gesetzten Zeit wird das `timeOut.TimeOut`-Ereignis generiert. Dies ist die Bedingung für den Übergang zum nächsten Zustand in der Sequenz (z.B. von `sState_01` zu `sState_02`).
4.  **Zyklus**: Nach dem letzten Zustand (`sState_08`) erfolgt der Übergang zurück zum ersten Zustand (`sState_01`), wodurch eine Endlosschleife entsteht.
5.  **Reset**: Das `RESET`-Ereignis kann von jedem beliebigen Zustand aus ausgelöst werden. Es führt zum Übergang in den `sRESET`-Zustand. Hier werden alle Ausgangsadapter ausgeschaltet, der `timeOut`-Adapter gestoppt und eine Bestätigung mit `STATE_NR = 0` (`START`) gesendet. Anschließend wechselt der FB automatisch zurück in den initialen `xSTART`-Zustand.

## Technische Besonderheiten
*   **Robuste Zustandsbehandlung**: Die `X`-Algorithmen (Exit) werden bereits beim Eintritt in den neuen Zustand ausgeführt, um sicherzustellen, dass der vorherige Ausgang zuverlässig deaktiviert wird, bevor der neue aktiviert wird.
*   **Flexible Zeitsteuerung**: Jede Zustandsdauer ist individuell über die `TIME`-Eingänge konfigurierbar. Der Wert `NO_TIME` kann verwendet werden, um einen sofortigen Übergang zu erzwingen.
*   **Adapter-basierte Ausgänge**: Die Verwendung von unidirektionalen AX-Adaptern für die Ausgänge ermöglicht eine klare Trennung der Schnittstelle und eine einfache Wiederverwendung in verschiedenen Netzwerken.
*   **Externer Zeitgeber**: Die Zeitmessung wird komplett an den spezialisierten `ATimeOut`-Adapter ausgelagert, was den FB logisch schlank hält und die Wartbarkeit erhöht.

## Zustandsübersicht
Die ECC umfasst folgende Zustände:
*   **`xSTART`**: Initialer, inaktiver Wartezustand.
*   **`sState_01` bis `sState_08`**: Aktive Zustände der Sequenz. Jeder aktiviert einen spezifischen Ausgang (`DO_Sx`).
*   **`sRESET`**: Zwischenzustand für den Reset-Vorgang. Deaktiviert alle Ausgänge und bereitet den Rückkehr in `xSTART` vor.

Die Übergangsbedingungen sind:
*   `START_S1`: Von `xSTART` nach `sState_01`.
*   `timeOut.TimeOut`: Zwischen den aktiven Zuständen in sequentieller Reihenfolge (`sState_01` -> `sState_02` -> ... -> `sState_08` -> `sState_01`).
*   `RESET`: Von jedem aktiven Zustand (`sState_01`-`sState_08`) nach `sRESET`.
*   `1` (immer wahr): Von `sRESET` zurück zu `xSTART`.

## Anwendungsszenarien
*   **Steuerung von zyklischen Prozessen**: Automatisierte Abläufe in Verpackungsmaschinen, Waschanlagen oder Beleuchtungssteuerungen, bei denen Aktionen nacheinander für bestimmte Zeiten ausgeführt werden müssen.
*   **Schrittkette**: Als Kern einer Schrittkette (SPS-Programmierung nach DIN EN 61131-3), die durch Zeitvorgaben voranschreitet.
*   **Test- und Prüfstandsautomatisierung**: Automatisches Durchschalten verschiedener Testphasen oder Belastungsprofile mit konfigurierbaren Haltezeiten.

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einem einfachen TON (Timer On-Delay) Baustein bietet dieser Sequenzer eine vordefinierte Zustandsmaschine mit mehreren Ausgängen. Gegenüber einer manuell programmierten Sequenz in Structured Text (ST) oder einer Abfolge von Einzelbausteinen bietet dieser FB eine vorgefertigte, getestete und wiederverwendbare Lösung mit einer klaren, standardisierten Schnittstelle. Bausteine mit ereignisgesteuerten (anstatt zeitgesteuerten) Übergängen wären für andere Anwendungsfälle geeignet.

## Fazit
Der `sequence_T_08_loop_AX` ist ein spezialisierter und robuster Funktionsblock zur Implementierung zeitgesteuerter Zyklen mit acht Schritten. Seine klare Schnittstelle, die Verwendung von Adaptern für Ausgänge und Zeitgeber sowie die integrierte Reset-Funktionalität machen ihn zu einer zuverlässigen und wartungsfreundlichen Komponente für zyklische Automatisierungsaufgaben in 4diac-basierten Steuerungssystemen.
