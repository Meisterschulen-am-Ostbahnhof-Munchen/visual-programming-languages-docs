# sequence_T_05

```{index} single: sequence_T_05
```

<img width="1422" height="375" alt="image" src="https://github.com/user-attachments/assets/36968bc8-cd20-4156-b33e-56e693a8c7d8" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `sequence_T_05` ist ein zeitgesteuerter Sequenzer mit fünf Ausgangszuständen. Er durchläuft eine feste Abfolge von Zuständen (State_01 bis State_05), wobei der Übergang zwischen den einzelnen Zuständen durch einstellbare Zeitverzögerungen gesteuert wird. Der Block ist für Anwendungen konzipiert, in denen Prozessschritte oder Aktionen nacheinander und für eine definierte Dauer aktiviert werden müssen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **`START_S1`**: Startet die Sequenz. Der Block wechselt vom Startzustand (`START` oder `State_00`) in den ersten aktiven Zustand `State_01`. Dieses Ereignis ist mit den fünf Zeitdaten-Eingängen verknüpft.
*   **`RESET`**: Setzt die Sequenz von jedem beliebigen Zustand zurück in den inaktiven Startzustand (`State_00`). Alle Ausgänge werden deaktiviert.

### **Ereignis-Ausgänge**
*   **`CNF`**: Ausführungsbestätigung (Confirmation). Wird bei jedem Zustandswechsel ausgelöst und liefert die neue Zustandsnummer (`STATE_NR`).
*   **`EO_S1`**: Wird beim Eintritt in den Zustand `State_01` ausgelöst und liefert den zugehörigen Datenausgang `DO_S1`.
*   **`EO_S2`**: Wird beim Eintritt in den Zustand `State_02` ausgelöst und liefert den zugehörigen Datenausgang `DO_S2`.
*   **`EO_S3`**: Wird beim Eintritt in den Zustand `State_03` ausgelöst und liefert den zugehörigen Datenausgang `DO_S3`.
*   **`EO_S4`**: Wird beim Eintritt in den Zustand `State_04` ausgelöst und liefert den zugehörigen Datenausgang `DO_S4`.
*   **`EO_S5`**: Wird beim Eintritt in den Zustand `State_05` ausgelöst und liefert den zugehörigen Datenausgang `DO_S5`.

### **Daten-Eingänge**
Alle Zeitdaten-Eingänge sind vom Typ `TIME` und haben den Initialwert `NO_TIME`. Sie definieren die Verweildauer im jeweiligen Zustand, bevor der automatische Übergang zum nächsten Zustand erfolgt.
*   **`DT_S1_S2`**: Verweildauer in `State_01` vor dem Übergang zu `State_02`.
*   **`DT_S2_S3`**: Verweildauer in `State_02` vor dem Übergang zu `State_03`.
*   **`DT_S3_S4`**: Verweildauer in `State_03` vor dem Übergang zu `State_04`.
*   **`DT_S4_S5`**: Verweildauer in `State_04` vor dem Übergang zu `State_05`.
*   **`DT_S5_START`**: Verweildauer in `State_05` vor dem Übergang zurück zum Startzustand `State_00`.

### **Daten-Ausgänge**
*   **`STATE_NR`** (SINT): Gibt die aktuelle Zustandsnummer aus. `0` = `START`/`State_00`, `1` = `State_01`, ..., `5` = `State_05`.
*   **`DO_S1`** (BOOL): Ist `TRUE`, wenn Zustand `State_01` aktiv ist.
*   **`DO_S2`** (BOOL): Ist `TRUE`, wenn Zustand `State_02` aktiv ist.
*   **`DO_S3`** (BOOL): Ist `TRUE`, wenn Zustand `State_03` aktiv ist.
*   **`DO_S4`** (BOOL): Ist `TRUE`, wenn Zustand `State_04` aktiv ist.
*   **`DO_S5`** (BOOL): Ist `TRUE`, wenn Zustand `State_05` aktiv ist.

### **Adapter**
*   **`timeOut`** (Plug, Typ: `iec61499::events::ATimeOut`): Ein Timeout-Adapter, der für die zeitgesteuerten Zustandsübergänge verwendet wird. Der Block startet (`START`) den Timer beim Eintritt in einen aktiven Zustand und stoppt (`STOP`) ihn beim Verlassen.

## Funktionsweise
Der Block arbeitet als Basic-FB mit einem definierten ECC (Execution Control Chart). Die Sequenz wird durch das Ereignis `START_S1` initiiert. Daraufhin durchläuft der Block nacheinander die Zustände `State_01` bis `State_05`. In jedem aktiven Zustand wird der entsprechende Datenausgang (`DO_Sx`) auf `TRUE` gesetzt und ein Timer mit der für diesen Zustand konfigurierten Dauer (`DT_Sx_Sy`) gestartet. Sobald der Timer abläuft (`timeOut.TimeOut`), erfolgt der automatische Übergang zum nächsten Zustand. Beim Zustandswechsel wird der vorherige Ausgang deaktiviert und der neue aktiviert. Nach `State_05` kehrt der Block in den inaktiven Zustand `State_00` zurück. Ein `RESET`-Ereignis unterbricht die Sequenz sofort, deaktiviert alle Ausgänge und bringt den Block in den Zustand `State_00`.

## Technische Besonderheiten
*   **Zustandsbehandlung**: Jeder aktive Zustand (`State_01` bis `State_05`) verfügt über separate Algorithmen für Eintritt (`_E`), Bestätigung (`_C`) und Austritt (`_X`). Dies ermöglicht eine klare Trennung der Logik.
*   **Timer-Integration**: Die Zeitsteuerung ist vollständig in den Adapter `ATimeOut` ausgelagert, was die Wiederverwendbarkeit und Wartbarkeit erhöht.
*   **Konstanten**: Der Block importiert Konstanten aus `logiBUS::utils::sequence::const::sequence` (für Zustandsnummern) und `::NO_TIME` für den Initialwert der Zeitdauern.
*   **Initialzustand**: Der eigentliche inaktive Ruhezustand nach einem Reset oder nach Sequenzende ist `sState_00`. Der `xSTART` ist der initiale ECC-Zustand beim ersten Hochfahren.

## Zustandsübersicht
1.  **`xSTART`**: Initialer ECC-Zustand beim Systemstart.
2.  **`sState_00`**: Inaktiver Ruhezustand. Alle Ausgänge sind `FALSE`. Von hier aus kann die Sequenz mit `START_S1` gestartet werden.
3.  **`sState_01` bis `sState_05`**: Aktive Sequenzzustände. Der jeweilige Ausgang `DO_Sx` ist `TRUE`. Der Übergang zum nächsten Zustand erfolgt zeitgesteuert.
4.  **`sRESET`**: Zwischenzustand, der bei einem `RESET`-Ereignis von jedem aktiven Zustand aus angesprungen wird. Deaktiviert alle Ausgänge und wechselt dann zu `sState_00`.

## Anwendungsszenarien
*   **Steuerung von Batch-Prozessen**: Nacheinander aktivierte Schritte wie Füllen, Erhitzen, Rühren, Kühlen und Entleeren mit einstellbaren Schrittzeiten.
*   **Ablaufsteuerungen in Maschinen**: Zeitgesteuerte Abfolge von Zylinderbewegungen oder Werkzeugwechseln in einer automatisierten Anlage.
*   **Testsequenzen**: Automatisierte Prüfabläufe, bei denen verschiedene Signale nacheinander für eine bestimmte Zeit angelegt und das Ergebnis ausgewertet werden muss.
*   **Beleuchtungssteuerung**: Zeitgesteuerte Choreografien für Werbe- oder Dekorationsbeleuchtung.

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einem einfachen `E_DELAY`- oder `E_SR`-Baustein bietet `sequence_T_05` eine vordefinierte, mehrstufige Sequenzlogik in einem einzigen, konfigurierbaren Block. Gegenüber einer selbst programmierten Sequenz mit mehreren verbundenen Bausteinen vereinfacht er die Applikation erheblich und reduziert die Fehleranfälligkeit. Andere Sequenzer-Bausteine könnten eventuell auf Ereignisse (anstelle von Zeit) für den Übergang reagieren oder eine variable Anzahl von Schritten erlauben.

## Fazit
Der `sequence_T_05` ist ein robustes und einfach zu konfigurierendes Werkzeug für zeitgesteuerte Ablaufsteuerungen mit fester Schrittanzahl. Durch die klare Trennung von Zustandslogik und Zeitsteuerung sowie die umfassenden Bestätigungs- und Rücksetzmechanismen eignet er sich ideal für zuverlässige Automatisierungsaufgaben in industriellen Umgebungen. Die Parametrierung der Schrittzeiten zur Laufzeit ermöglicht eine hohe Flexibilität.