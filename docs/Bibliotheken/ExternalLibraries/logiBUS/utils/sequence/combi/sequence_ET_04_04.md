# sequence_ET_04_04

```{index} single: sequence_ET_04_04
```

<img width="1369" height="422" alt="image" src="https://github.com/user-attachments/assets/5b5fc7b9-65cb-4c19-b1ee-bad5fd7b2d45" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `sequence_ET_04_04` ist ein Sequenzer mit 8 Ausgängen, der zur Steuerung von Abläufen in der Automatisierungstechnik dient. Er realisiert eine feste Zustandsfolge, wobei die Übergänge zwischen den Zuständen entweder durch ein externes Ereignis oder durch einen einstellbaren Zeitablauf ausgelöst werden können. Der Baustein ist besonders für Anwendungen geeignet, bei denen eine zyklische oder schrittweise Aktivierung von Ausgängen erforderlich ist.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **`EI1`**: Allgemeines Eingangsereignis. Führt im Startzustand (`xSTART`) zu einer Selbsttransition (kein Zustandswechsel).
*   **`START_S1`**: Startet die Sequenz oder springt von den Zuständen 1-3 zurück in Zustand 4 bzw. von den Zuständen 5-8 zurück in den Endzustand (`sState_00`). Löst den Übergang vom Startzustand (`xSTART`) oder vom Endzustand (`sState_00`) in den ersten aktiven Zustand (`sState_01`) aus.
*   **`S4_S5`**: Löst den Übergang vom Zustand 4 (`sState_04`) in den Zustand 5 (`sState_05`) aus. Dies ist der einzige manuelle Übergang in der Sequenz.
*   **`EI_RESET`**: Setzt die Sequenz von jedem beliebigen aktiven Zustand in den Reset-Zustand (`sRESET`) und anschließend in den Endzustand (`sState_00`) zurück.

### **Ereignis-Ausgänge**
*   **`CNF`**: Ausführungsbestätigung (Execution Confirmation). Wird bei jedem Zustandswechsel ausgelöst und liefert die neue Zustandsnummer (`STATE_NR`).
*   **`EO_S1` bis `EO_S8`**: Zustandsereignisse. Werden beim Eintritt in den entsprechenden Zustand (State_01 bis State_08) ausgelöst und liefern den zugehörigen booleschen Datenausgang (`DO_Sx`).
*   **`EO_RESET`**: Wird beim Durchlaufen des Reset-Zustands (`sRESET`) ausgelöst.

### **Daten-Eingänge**
*   **`DT_S1_S2`** (TIME): Zeit für den automatischen Übergang von State_01 zu State_02. Initialwert: `NO_TIME` (deaktiviert).
*   **`DT_S2_S3`** (TIME): Zeit für den automatischen Übergang von State_02 zu State_03. Initialwert: `NO_TIME` (deaktiviert).
*   **`DT_S3_S4`** (TIME): Zeit für den automatischen Übergang von State_03 zu State_04. Initialwert: `NO_TIME` (deaktiviert).
*   **`DT_S5_S6`** (TIME): Zeit für den automatischen Übergang von State_05 zu State_06. Initialwert: `NO_TIME` (deaktiviert).
*   **`DT_S6_S7`** (TIME): Zeit für den automatischen Übergang von State_06 zu State_07. Initialwert: `NO_TIME` (deaktiviert).
*   **`DT_S7_S8`** (TIME): Zeit für den automatischen Übergang von State_07 zu State_08. Initialwert: `NO_TIME` (deaktiviert).
*   **`DT_S8_START`** (TIME): Zeit für den automatischen Übergang von State_08 zurück in den Endzustand (`sState_00`). Initialwert: `NO_TIME` (deaktiviert).

### **Daten-Ausgänge**
*   **`STATE_NR`** (SINT): Aktuelle Zustandsnummer. `0` = START/State_00, `1` = State_01, ..., `8` = State_08.
*   **`DO_S1` bis `DO_S8`** (BOOL): Logische Ausgänge, die anzeigen, ob der entsprechende Zustand aktiv ist. Werden beim Zustandseintritt auf `TRUE` und beim Verlassen auf `FALSE` gesetzt.

### **Adapter**
*   **`timeOut`** (Plug, Typ: `iec61499::events::ATimeOut`): Wird für die Realisierung der zeitgesteuerten Zustandsübergänge verwendet. Der FB startet (`START`) und stoppt (`STOP`) den Timer und setzt die Verzögerungszeit (`DT`).

## Funktionsweise
Der FB arbeitet als Basic Function Block (BFB) mit einem erweiterten endlichen Automaten (ECC). Die Sequenz durchläuft normalerweise die Zustände 1 bis 8 in fester Reihenfolge. Der Übergang von Zustand 4 zu Zustand 5 erfolgt ausschließlich durch das externe Ereignis `S4_S5`. Alle anderen Übergänge (1→2, 2→3, 3→4, 5→6, 6→7, 7→8, 8→Ende) können zeitgesteuert erfolgen, sofern die entsprechende Zeit (`DT_...`) nicht auf `NO_TIME` gesetzt ist.

Jeder aktive Zustand (1-8) setzt seinen zugehörigen booleschen Ausgang (`DO_Sx`) auf `TRUE` und startet ggf. den Timer für den nächsten Übergang. Beim Verlassen des Zustands wird der Ausgang auf `FALSE` zurückgesetzt. Bei jedem Zustandswechsel wird das Bestätigungsereignis `CNF` mit der neuen `STATE_NR` ausgelöst.

Das Ereignis `START_S1` dient nicht nur zum initialen Start, sondern auch zum "Zurückspringen" innerhalb der Sequenz: Von den Zuständen 1-3 springt es zurück in Zustand 4, von den Zuständen 5-8 zurück in den Endzustand (`sState_00`). Ein `EI_RESET` bricht die Sequenz von jedem Punkt aus ab, deaktiviert alle Ausgänge und bringt den FB in den konsistenten Endzustand `sState_00`.

## Technische Besonderheiten
*   **Hybride Triggerung**: Kombination von ereignis- und zeitgesteuerten Zustandsübergängen.
*   **Flexible Zeitsteuerung**: Jeder zeitgesteuerte Übergang kann individuell durch Setzen der `DT_...`-Eingänge konfiguriert oder durch den Wert `NO_TIME` deaktiviert werden.
*   **Sicherer Reset**: Der Reset-Vorgang (`EI_RESET`) stoppt sicher alle laufenden Timer und setzt alle internen Ausgänge zurück.
*   **Zustandsrücksprung**: Das `START_S1`-Ereignis ermöglicht spezifische Rücksprünge in die Sequenz, was komplexe Steuerungsmuster unterstützt.

## Zustandsübersicht
Der ECC umfasst folgende Zustände:
*   **`xSTART`**: Initialer, inaktiver Zustand.
*   **`sState_01` bis `sState_08`**: Aktive Arbeitszustände der Sequenz.
*   **`sState_00`**: Inaktiver Endzustand nach Abschluss der Sequenz.
*   **`sRESET`**: Reset-Zustand, der von allen aktiven Zuständen aus angesprungen werden kann.
*   **`sState_05_RESET`** / **`sState_00_RESET`**: Zwischenzustände für die speziellen Rücksprungaktionen via `START_S1`.

## Anwendungsszenarien
*   **Steuerung von Batch-Prozessen**: Schrittweise Aktivierung von Ventilen, Pumpen oder Heizungen in einem chemischen Prozess.
*   **Verkettete Maschinenabläufe**: Steuerung der einzelnen Schritte in einer Montage- oder Verpackungslinie.
*   **Teststände**: Automatisierte, zyklische Prüfabläufe mit konfigurierbaren Wartezeiten zwischen den Testschritten.
*   **Sicherheitssequenzen**: Geordnetes An- und Abfahren einer Anlage.

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Timern (z.B. `TON`) oder Zählern (z.B. `CTU`) bietet dieser FB eine vordefinierte, komplexe Zustandslogik mit mehreren Ausgängen. Gegenüber generischen Schrittketten-Bausteinen (SFC) ist er weniger flexibel, aber dafür spezifischer, einfacher zu konfigurieren und bietet integrierte Reset- und Sprungfunktionen. Er stellt eine spezialisierte Lösung für 8-stufige Prozesse dar.

## Fazit
Der `sequence_ET_04_04` ist ein robuster und praktischer Sequenzer für Standardautomationsaufgaben mit bis zu acht Schritten. Die Kombination aus Zeit- und Ereignissteuerung sowie die integrierten Sicherheits- und Rücksetzfunktionen machen ihn zu einer zuverlässigen Komponente für sich wiederholende Steuerungsabläufe. Seine Stärke liegt in der klaren Struktur und einfachen Parametrierung der Zustandsübergänge.