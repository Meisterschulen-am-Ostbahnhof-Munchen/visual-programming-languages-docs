# sequence_E_04

<img width="1649" height="413" alt="image" src="https://github.com/user-attachments/assets/acbf2b37-87d0-40cc-a3a4-8871d3001c20" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `sequence_E_04` ist ein Sequenzer, der eine lineare Abfolge von vier Zuständen (State_01 bis State_04) mit einem definierten Startzustand (START) und einem Endzustand (State_00) realisiert. Der Übergang zwischen den einzelnen Zuständen erfolgt ausschließlich durch externe Ereignisse. Der Baustein ist für Steuerungsaufgaben konzipiert, bei denen eine schrittweise, ereignisgesteuerte Abarbeitung erforderlich ist, wie z.B. in einfachen Prozess- oder Montageabläufen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **START_S1**: Wechselt vom Zustand START oder State_00 in den Zustand State_01.
*   **S1_S2**: Wechselt vom Zustand State_01 in den Zustand State_02.
*   **S2_S3**: Wechselt vom Zustand State_02 in den Zustand State_03.
*   **S3_S4**: Wechselt vom Zustand State_03 in den Zustand State_04.
*   **S4_START**: Wechselt vom Zustand State_04 in den Zustand State_00.
*   **RESET**: Setzt den Baustein von jedem beliebigen Zustand (State_01 bis State_04) in den Zustand State_00 zurück.

### **Ereignis-Ausgänge**
*   **CNF**: Bestätigungsereignis, das bei jedem Zustandswechsel ausgelöst wird. Es liefert die aktuelle Zustandsnummer über `STATE_NR`.
*   **EO_S1**: Wird beim Eintritt in den Zustand State_01 ausgelöst und liefert den Wert von `DO_S1` (TRUE).
*   **EO_S2**: Wird beim Eintritt in den Zustand State_02 ausgelöst und liefert den Wert von `DO_S2` (TRUE).
*   **EO_S3**: Wird beim Eintritt in den Zustand State_03 ausgelöst und liefert den Wert von `DO_S3` (TRUE).
*   **EO_S4**: Wird beim Eintritt in den Zustand State_04 ausgelöst und liefert den Wert von `DO_S4` (TRUE).

### **Daten-Eingänge**
*   Keine vorhanden.

### **Daten-Ausgänge**
*   **STATE_NR** (SINT): Gibt die Nummer des aktuellen Zustands aus. Die Kodierung lautet: START = 0, State_01 = 1, State_02 = 2, State_03 = 3, State_04 = 4.
*   **DO_S1** (BOOL): Ist TRUE, wenn der Zustand State_01 aktiv ist.
*   **DO_S2** (BOOL): Ist TRUE, wenn der Zustand State_02 aktiv ist.
*   **DO_S3** (BOOL): Ist TRUE, wenn der Zustand State_03 aktiv ist.
*   **DO_S4** (BOOL): Ist TRUE, wenn der Zustand State_04 aktiv ist.

### **Adapter**
*   Keine vorhanden.

## Funktionsweise
Der `sequence_E_04` ist als Basic Function Block (BFB) implementiert und besitzt eine Execution Control Chart (ECC). Die ECC definiert die Zustände und die ereignisgesteuerten Übergänge zwischen ihnen. Bei jedem Zustandswechsel werden spezifische Algorithmen ausgeführt:
1.  **Exit-Algorithmus (X)**: Wird beim Verlassen eines Zustands ausgeführt, um den zugehörigen Datenausgang (`DO_Sx`) auf FALSE zu setzen.
2.  **Entry-Algorithmus (E)**: Wird beim Betreten eines Zustands ausgeführt, um den zugehörigen Datenausgang (`DO_Sx`) auf TRUE zu setzen und das entsprechende Ereignis (`EO_Sx`) auszulösen.
3.  **Confirmation-Algorithmus (C)**: Wird in jedem Zustand (außer RESET) ausgeführt, um die Zustandsnummer `STATE_NR` zu aktualisieren und das Bestätigungsereignis `CNF` auszulösen.

Ein `RESET`-Ereignis führt alle notwendigen Exit-Algorithmen der aktiven Zustände aus und wechselt über einen Zwischenzustand (`sRESET`) in den Endzustand `State_00`.

## Technische Besonderheiten
*   **Ereignisbasierte Transition**: Zustandswechsel sind ausschließlich durch externe Ereignisse möglich. Es gibt keine zeit- oder datengesteuerten Übergänge.
*   **Explizite Zustandskodierung**: Die Zustandsnummern sind als Konstanten aus der Bibliothek `sequence` definiert, was die Wiederverwendung und Lesbarkeit des Codes verbessert.
*   **Sauberer Reset**: Der Reset-Vorgang deaktiviert alle aktiven Ausgänge, bevor der Endzustand erreicht wird, um ein klares und definiertes Systemverhalten zu gewährleisten.
*   **Initialzustand**: Der FB startet im Zustand `xSTART`. Der erste Übergang in die operative Sequenz erfolgt durch das Ereignis `START_S1`.

## Zustandsübersicht
1.  **xSTART**: Initialer Ruhezustand.
2.  **sState_01**: Erster aktiver Schritt. `DO_S1` = TRUE.
3.  **sState_02**: Zweiter aktiver Schritt. `DO_S2` = TRUE.
4.  **sState_03**: Dritter aktiver Schritt. `DO_S3` = TRUE.
5.  **sState_04**: Vierter aktiver Schritt. `DO_S4` = TRUE.
6.  **sState_00**: Finaler Ruhezustand nach Abschluss der Sequenz. Alle `DO_Sx` = FALSE.
7.  **sRESET**: Zwischenzustand während eines Reset-Vorgangs. Führt die Deaktivierung aller Ausgänge durch.

## Anwendungsszenarien
*   **Schrittkettensteuerungen**: Steuerung von Maschinen oder Anlagen, die einen festen, schrittweisen Arbeitsablauf haben (z.B. Pick-and-Place, Füllanlagen).
*   **Taktung von Prozessen**: Synchronisation von Teilprozessen, bei denen jeder Schritt manuell oder durch ein Sensorsignal freigegeben wird.
*   **Manuelle Bedienabläufe**: Umsetzung von geführten Bediensequenzen, bei denen der Operator jeden Schritt bestätigen muss.

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu einem `E_CYCLE`- oder `E_DELAY`-Baustein bietet `sequence_E_04` keine zeitgesteuerten, sondern rein ereignisgesteuerte Übergänge. Im Vergleich zu einem generischen `E_SR` (Flip-Flop) oder einer Kombination aus `E_D_FF` (D-Flip-Flop) realisiert dieser FB eine vordefinierte Zustandsmaschine mit mehreren Schritten und einer klaren Reset-Logik. Er ist spezialisierter und strukturierter als eine ad-hoc Implementierung mit mehreren Einzelbausteinen.

## Fazit
Der `sequence_E_04` ist ein robuster und einfach zu verwendender Sequenzer für IEC 61499. Seine klare, ereignisgesteuerte Schnittstelle und die explizite Zustandsverwaltung machen ihn ideal für Anwendungen, bei denen ein deterministischer, schrittweiser Ablauf erforderlich ist. Die integrierte Reset-Funktionalität und die Zustandsrückmeldung über `CNF` und `STATE_NR` unterstützen eine sichere und gut überwachbare Integration in übergeordnete Steuerungen.
