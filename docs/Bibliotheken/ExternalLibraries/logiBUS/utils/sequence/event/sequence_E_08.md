# sequence_E_08

<img width="1143" height="415" alt="image" src="https://github.com/user-attachments/assets/4a56f7f9-4f54-4812-883b-f99753f1fbd2" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `sequence_E_08` ist ein Sequenzer mit acht Ausgängen, der durch Ereignisse gesteuert wird. Er realisiert eine lineare Zustandsmaschine mit einem definierten Startzustand und acht aktiven Zuständen. Der Übergang von einem Zustand zum nächsten erfolgt ausschließlich durch das Eintreffen eines spezifischen Ereignisses. Der Baustein eignet sich für Steuerungsaufgaben, bei denen Prozessschritte nacheinander und ereignisgesteuert durchlaufen werden müssen, wie z.B. in Handhabungs- oder Montageabläufen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **START_S1**: Wechselt vom Startzustand (`START`) in den Zustand `State_01`.
*   **S1_S2**: Wechselt von `State_01` nach `State_02`.
*   **S2_S3**: Wechselt von `State_02` nach `State_03`.
*   **S3_S4**: Wechselt von `State_03` nach `State_04`.
*   **S4_S5**: Wechselt von `State_04` nach `State_05`.
*   **S5_S6**: Wechselt von `State_05` nach `State_06`.
*   **S6_S7**: Wechselt von `State_06` nach `State_07`.
*   **S7_S8**: Wechselt von `State_07` nach `State_08`.
*   **S8_START**: Wechselt von `State_08` zurück in den `START`-Zustand (repräsentiert durch `sState_00`).
*   **RESET**: Setzt den Baustein aus *jedem beliebigen Zustand* sofort in den `START`-Zustand zurück.

### **Ereignis-Ausgänge**
*   **CNF**: Ausführungsbestätigung. Wird bei jedem Zustandswechsel ausgelöst und liefert die neue Zustandsnummer (`STATE_NR`).
*   **EO_S1**: Wird beim Eintritt in `State_01` ausgelöst und liefert den Wert von `DO_S1` (TRUE).
*   **EO_S2**: Wird beim Eintritt in `State_02` ausgelöst und liefert den Wert von `DO_S2` (TRUE).
*   **EO_S3**: Wird beim Eintritt in `State_03` ausgelöst und liefert den Wert von `DO_S3` (TRUE).
*   **EO_S4**: Wird beim Eintritt in `State_04` ausgelöst und liefert den Wert von `DO_S4` (TRUE).
*   **EO_S5**: Wird beim Eintritt in `State_05` ausgelöst und liefert den Wert von `DO_S5` (TRUE).
*   **EO_S6**: Wird beim Eintritt in `State_06` ausgelöst und liefert den Wert von `DO_S6` (TRUE).
*   **EO_S7**: Wird beim Eintritt in `State_07` ausgelöst und liefert den Wert von `DO_S7` (TRUE).
*   **EO_S8**: Wird beim Eintritt in `State_08` ausgelöst und liefert den Wert von `DO_S8` (TRUE).

### **Daten-Eingänge**
*   Dieser Funktionsblock besitzt keine Daten-Eingänge.

### **Daten-Ausgänge**
*   **STATE_NR** (SINT): Aktuelle Zustandsnummer. `START` = 0, `State_01` = 1, `State_02` = 2, ..., `State_08` = 8. Die Werte werden aus der Konstanten-Bibliothek `sequence` geladen.
*   **DO_S1** (BOOL): Ist `TRUE`, wenn Zustand `State_01` aktiv ist.
*   **DO_S2** (BOOL): Ist `TRUE`, wenn Zustand `State_02` aktiv ist.
*   **DO_S3** (BOOL): Ist `TRUE`, wenn Zustand `State_03` aktiv ist.
*   **DO_S4** (BOOL): Ist `TRUE`, wenn Zustand `State_04` aktiv ist.
*   **DO_S5** (BOOL): Ist `TRUE`, wenn Zustand `State_05` aktiv ist.
*   **DO_S6** (BOOL): Ist `TRUE`, wenn Zustand `State_06` aktiv ist.
*   **DO_S7** (BOOL): Ist `TRUE`, wenn Zustand `State_07` aktiv ist.
*   **DO_S8** (BOOL): Ist `TRUE`, wenn Zustand `State_08` aktiv ist.

### **Adapter**
*   Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der `sequence_E_08` ist als Basic-FB mit einer ausführlichen Execution Control Chart (ECC) implementiert. Die Logik folgt einer linearen Kette von Zuständen (`sState_01` bis `sState_08`), einem Start-/Ruhezustand (`sState_00`) und einem expliziten Reset-Zustand (`sRESET`).

Bei jedem Zustandswechsel werden drei Aktionen ausgeführt:
1.  **Exit-Aktion des vorherigen Zustands**: Ein `State_XX_X`-Algorithmus setzt den zugehörigen Datenausgang (`DO_Sx`) auf `FALSE`.
2.  **Confirmation-Aktion des neuen Zustands**: Ein `State_XX_C`-Algorithmus setzt die `STATE_NR` und löst das `CNF`-Ereignis aus.
3.  **Entry-Aktion des neuen Zustands**: Ein `State_XX_E`-Algorithmus setzt den zugehörigen Datenausgang (`DO_Sx`) auf `TRUE` und löst das entsprechende `EO_Sx`-Ereignis aus.

Ein `RESET`-Ereignis führt unmittelbar in den `sRESET`-Zustand. Dort werden über Exit-Algorithmen *alle* potenziell aktiven Ausgänge (`DO_S1` bis `DO_S8`) auf `FALSE` gesetzt. Anschließend erfolgt ein automatischer Übergang (Condition=`1`, also immer wahr) in den `sState_00` (START).

## Technische Besonderheiten
*   **Ereignisbasierte Transitionen**: Zustandsübergänge sind strikt an das Eintreffen der definierten Ereignisse gebunden. Es gibt keine zeit- oder datengetriggerten Übergänge.
*   **Expliziter Reset-Pfad**: Der Reset-Vorgang läuft über einen eigenen Zustand (`sRESET`), der sicherstellt, dass alle Ausgänge deaktiviert werden, bevor der Startzustand (`sState_00`) erreicht wird. Dies gewährleistet einen sauberen und definierten Neustart.
*   **Konsistente Schnittstelle**: Die Namensgebung der Ereignisse (z.B. `S1_S2`) macht die erwartete Transition intuitiv verständlich.
*   **Verwendung von Konstanten**: Die Zustandsnummern (`STATE_NR`) werden aus einer zentralen Konstanten-Bibliothek (`sequence`) bezogen, was die Wartbarkeit und Konsistenz verbessert.

## Zustandsübersicht
*   **sState_00**: Start- bzw. Ruhezustand. `STATE_NR` = 0. Alle Ausgänge sind `FALSE`.
*   **sState_01** bis **sState_08**: Aktive Prozesszustände 1 bis 8. Der jeweilige Ausgang `DO_Sx` ist `TRUE`, `STATE_NR` entspricht der Zustandsnummer.
*   **sRESET**: Zwischenzustand während eines Reset-Vorgangs. Setzt alle Ausgänge zurück.
*   **xSTART**: Initialer ECC-Zustand (wird nur einmal beim Start der Anwendung durchlaufen).

## Anwendungsszenarien
*   **Schrittkettensteuerungen**: Steuerung von Maschinen mit klar sequentiellen Arbeitsabläufen, wie Pressen, Schweißanlagen oder Verpackungsmaschinen.
*   **Handhabungsgeräte**: Steuerung eines Roboterarms, der Teile nacheinander greift, transportiert und ablegt.
*   **Teststände**: Automatisierte Abfolge von Test- und Prüfschritten an einem Bauteil.
*   **Batch-Prozesse**: Steuerung von Reaktoren oder Mischbehältern, in denen nacheinander verschiedene Zutaten zugegeben oder Prozessparameter geändert werden müssen.

## Vergleich mit ähnlichen Bausteinen
*   **VS. `E_R_TRIG` / `E_F_TRIG`**: Diese Bausteine detektieren Flanken. `sequence_E_08` nutzt solche Flankendetektoren typischerweise als Quelle für seine Transitionsevents, ist selbst aber eine komplexe Zustandsmaschine.
*   **VS. `E_DELAY`**: Ein reiner Verzögerungsbaustein. `sequence_E_08` kann durch externe Timer und entsprechende Verknüpfung zeitgesteuerte Abläufe realisieren, bietet aber von Haus aus keine integrierte Zeitsteuerung.
*   **VS. `E_SR` (Flip-Flop)**: Ein elementarer Speicherbaustein mit Set/Reset. `sequence_E_08` kann als eine Kette solcher Speicher aufgefasst werden, bei der das Setzen eines Zustands das Zurücksetzen des vorherigen impliziert.
*   **VS. SFC (Sequential Function Chart)**: Die Funktionsweise entspricht im Prinzip einer einfachen SFC-Sequenz. `sequence_E_08` kapselt diese SFC-ähnliche Logik in einem wiederverwendbaren FB.

## Fazit
Der `sequence_E_08` ist ein robustes und gut strukturiertes Werkzeug zur Implementierung ereignisgesteuerter Schrittketten in IEC 61499. Seine klare Schnittstelle und der explizite Reset-Mechanismus machen ihn zuverlässig und einfach in übergeordnete Steuerungen zu integrieren. Er ist ideal für Anwendungen geeignet, bei denen eine feste, lineare Abfolge von Aktionen durch externe Signale (z.B. Endschalter, Benutzerbefehle) vorangetrieben wird. Für zyklische oder komplex verzweigte Abläufe müsste der Baustein erweitert oder ein anderer Ansatz gewählt werden.
