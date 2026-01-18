# sequence_ET_05_loop

```{index} single: sequence_ET_05_loop
```

<img width="1683" height="398" alt="image" src="https://github.com/user-attachments/assets/caae5b56-a31e-4867-ae04-0be4eeb193b6" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `sequence_ET_05_loop` implementiert eine zyklische Sequenz mit fünf Zuständen. Der Übergang zwischen den einzelnen Zuständen kann entweder durch ein externes Ereignis oder nach Ablauf einer einstellbaren Zeit erfolgen. Der Baustein ist für Anwendungen konzipiert, bei denen ein Prozess schrittweise durchlaufen und dabei verschiedene Aktionen in einer festen Reihenfolge ausgelöst werden müssen, wie beispielsweise in Verpackungsmaschinen, Montageprozessen oder Waschprogrammen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **`START_S1`**: Startet die Sequenz und führt den Übergang vom Startzustand (`START`) in den ersten Zustand (`State_01`). Überträgt die Zeitwerte für alle zeitgesteuerten Übergänge.
*   **`S1_S2`**: Löst den Übergang von `State_01` nach `State_02` aus.
*   **`S2_S3`**: Löst den Übergang von `State_02` nach `State_03` aus.
*   **`S3_S4`**: Löst den Übergang von `State_03` nach `State_04` aus.
*   **`S4_S5`**: Löst den Übergang von `State_04` nach `State_05` aus.
*   **`S5_S1`**: Löst den Übergang von `State_05` zurück in `State_01` aus (Zyklus).
*   **`RESET`**: Setzt die Sequenz von jedem beliebigen Zustand zurück in den Startzustand (`START`).

### **Ereignis-Ausgänge**
*   **`CNF`**: Bestätigungsereignis, das bei jedem Zustandswechsel ausgelöst wird. Überträgt die aktuelle Zustandsnummer (`STATE_NR`).
*   **`EO_S1`**: Wird beim Eintritt in `State_01` ausgelöst. Überträgt den Ausgangswert `DO_S1`.
*   **`EO_S2`**: Wird beim Eintritt in `State_02` ausgelöst. Überträgt den Ausgangswert `DO_S2`.
*   **`EO_S3`**: Wird beim Eintritt in `State_03` ausgelöst. Überträgt den Ausgangswert `DO_S3`.
*   **`EO_S4`**: Wird beim Eintritt in `State_04` ausgelöst. Überträgt den Ausgangswert `DO_S4`.
*   **`EO_S5`**: Wird beim Eintritt in `State_05` ausgelöst. Überträgt den Ausgangswert `DO_S5`.

### **Daten-Eingänge**
*   **`DT_S1_S2`** (Typ: `TIME`, Initialwert: `NO_TIME`): Zeit für den automatischen Übergang von `State_01` nach `State_02`. Bei `NO_TIME` ist der zeitgesteuerte Übergang deaktiviert.
*   **`DT_S2_S3`** (Typ: `TIME`, Initialwert: `NO_TIME`): Zeit für den automatischen Übergang von `State_02` nach `State_03`.
*   **`DT_S3_S4`** (Typ: `TIME`, Initialwert: `NO_TIME`): Zeit für den automatischen Übergang von `State_03` nach `State_04`.
*   **`DT_S4_S5`** (Typ: `TIME`, Initialwert: `NO_TIME`): Zeit für den automatischen Übergang von `State_04` nach `State_05`.
*   **`DT_S5_S1`** (Typ: `TIME`, Initialwert: `NO_TIME`): Zeit für den automatischen Übergang von `State_05` nach `State_01`.

### **Daten-Ausgänge**
*   **`STATE_NR`** (Typ: `SINT`): Gibt die Nummer des aktuellen Zustands aus (START = 0, State_01 = 1, ..., State_05 = 5).
*   **`DO_S1`** (Typ: `BOOL`): Ist `TRUE`, wenn `State_01` aktiv ist.
*   **`DO_S2`** (Typ: `BOOL`): Ist `TRUE`, wenn `State_02` aktiv ist.
*   **`DO_S3`** (Typ: `BOOL`): Ist `TRUE`, wenn `State_03` aktiv ist.
*   **`DO_S4`** (Typ: `BOOL`): Ist `TRUE`, wenn `State_04` aktiv ist.
*   **`DO_S5`** (Typ: `BOOL`): Ist `TRUE`, wenn `State_05` aktiv ist.

### **Adapter**
*   **`timeOut`** (Typ: `ATimeOut`): Ein gesteckter Adapter zur Realisierung der zeitgesteuerten Zustandsübergänge. Der FB nutzt dessen Schnittstellen `START`, `STOP` und `DT` (Zeitwert) sowie das Ereignis `TimeOut`.

## Funktionsweise
Der FB ist als Basic-FB mit einer Execution Control Chart (ECC) implementiert. Die Sequenz beginnt im Zustand `xSTART`. Mit dem Ereignis `START_S1` wird der erste Zustand `sState_01` aktiviert. Bei jedem Zustandseintritt werden folgende Aktionen ausgeführt:
1.  Der Timer-Adapter wird gestoppt (`timeOut.STOP`).
2.  Der Ausgang des vorherigen Zustands wird zurückgesetzt (z.B. `State_05_X` für `DO_S5`).
3.  Die Zustandsnummer `STATE_NR` wird aktualisiert und der Timer für den nächsten Übergang konfiguriert (z.B. `State_01_C`).
4.  Der Ausgang des neuen Zustands wird gesetzt (z.B. `State_01_E` für `DO_S1`).
5.  Der Timer-Adapter wird mit der für diesen Übergang konfigurierten Zeit gestartet (`timeOut.START`).

Ein Zustandswechsel kann nun auf zwei Arten erfolgen:
*   **Ereignisgesteuert:** Durch das entsprechende Eingangsereignis (z.B. `S1_S2`).
*   **Zeitgesteuert:** Durch das `TimeOut`-Ereignis des Adapters, sofern die Zeit (`DT_...`) nicht auf `NO_TIME` gesetzt ist.

Die Sequenz durchläuft die Zustände 1 bis 5 und springt dann von `State_05` wieder zurück zu `State_01`, wodurch ein endloser Zyklus entsteht. Das Ereignis `RESET` führt unabhängig vom aktuellen Zustand in den Reset-Zustand `sRESET`, von wo aus die Sequenz automatisch in den `xSTART`-Zustand zurückkehrt.

## Technische Besonderheiten
*   **Hybride Triggerung:** Jeder Zustandsübergang kann individuell entweder ereignis- oder zeitgesteuert konfiguriert werden. Dies ermöglicht maximale Flexibilität innerhalb einer festen Sequenz.
*   **Sichere Zustandsausgänge:** Die booleschen Ausgänge (`DO_Sx`) werden beim Verlassen eines Zustands explizit über einen Exit-Algorithmus (`State_XX_X`) zurückgesetzt. Dies verhindert ein unbeabsichtigtes Beibehalten des `TRUE`-Signals.
*   **Explizite Timer-Steuerung:** Der Timer wird bei jedem Zustandswechsel neu gestartet und gestoppt, was eine präzise und deterministische Zeitsteuerung gewährleistet.
*   **Konstanten:** Der FB verwendet definierte Konstanten (`sequence::State_XX`, `NO_TIME`) aus importierten Bibliotheken, was die Wartbarkeit und Lesbarkeit des Codes erhöht.

## Zustandsübersicht
Die ECC besteht aus sieben Zuständen:
1.  **`xSTART`**: Inaktiver Anfangszustand.
2.  **`sState_01`** bis **`sState_05`**: Die fünf aktiven Sequenzzustände.
3.  **`sRESET`**: Zwischenzustand, der beim Reset alle Ausgänge zurücksetzt und die Bestätigung für den `xSTART`-Zustand sendet.

## Anwendungsszenarien
*   **Steuerung von Zyklischen Prozessen:** Automatische Bearbeitungsmaschinen (z.B. Drehmaschinen mit mehreren Werkzeugen), bei denen jeder Schritt eine bestimmte Zeit dauert oder durch ein Sensorereignis abgeschlossen wird.
*   **Batch-Prozesse:** Chargenweise Abarbeitung in der Lebensmittel- oder Pharmaindustrie, wo Mischen, Erhitzen und Abfüllen nacheinander erfolgen.
*   **Sicherheitssequenzen:** Überwachte Start- oder Stoppprozeduren, bei denen jeder Schritt manuell freigegeben (`EVENT`) oder nach einer Wartezeit (`TIME`) automatisch weiterläuft.
*   **Teststände:** Automatisierte Prüfabläufe, bei denen nacheinander verschiedene Messungen oder Funktionstests durchgeführt werden.

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Timer-Bausteinen oder selbsthaltenden Relaiskaskaden bietet `sequence_ET_05_loop` eine vordefinierte, zyklische Struktur mit integrierter Zeit- und Ereignissteuerung. Gegenüber einer Programmierung mit einzelnen Blöcken (z.B. `E_SR`, `E_DELAY`) reduziert er den Verdrahtungsaufwand und erhöht die Übersichtlichkeit. Andere Sequenzer-FBs haben möglicherweise eine variable Anzahl von Schritten oder andere Übergangslogiken (nur Zeit ODER nur Ereignis). Dieser FB zeichnet sich durch die kombinierte `EVENT`/`TIME`-Triggerung pro Schritt aus.

## Fazit
Der `sequence_ET_05_loop` ist ein robust und klar strukturierter Funktionsblock zur Implementierung von zyklischen 5-Schritt-Sequenzen. Die Kombination aus ereignis- und zeitgesteuerten Übergängen macht ihn äußerst flexibel für eine Vielzahl von Automatisierungsaufgaben. Die explizite Steuerung der Ausgänge und des Timers sorgt für ein deterministisches und zuverlässiges Verhalten. Er ist ideal geeignet, um wiederkehrende Prozessabläufe mit fester Schrittanzahl effizient und übersichtlich in einer IEC 61499-basierten Steuerung abzubilden.
