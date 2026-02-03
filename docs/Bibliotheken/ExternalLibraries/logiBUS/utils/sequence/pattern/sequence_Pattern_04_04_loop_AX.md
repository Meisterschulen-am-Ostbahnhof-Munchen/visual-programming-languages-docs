# sequence_Pattern_04_04_loop_AX

![Bild des FB, falls vorhanden](Placeholder_sequence_Pattern_04_04_loop_AX.png)


![sequence_Pattern_04_04_loop_AX](.././sequence_Pattern_04_04_loop_AX.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **sequence_Pattern_04_04_loop_AX** ist ein Sequenzer (Schrittschaltwerk), der eine Abfolge von 4 Zuständen in einer Endlosschleife steuert. Er fungiert ähnlich wie ein elektronisches Nockenschaltwerk. Für jeden der 4 Schritte kann ein spezifisches Ausgabemuster (Pattern) definiert werden, das 4 Ausgänge (Q1 bis Q4) steuert.

Der Baustein nutzt **AX-Adapter** für die Ausgänge und unterstützt sowohl zeitgesteuerte Übergänge (Timeouts) als auch ereignisgesteuerte manuelle Weiterschaltung. Nach dem vierten Schritt springt die Sequenz automatisch oder manuell zurück zum ersten Schritt (Loop-Verhalten).

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*   **START_S1**: Startet die Sequenz und springt direkt in den Zustand 1 (`State_01`). Dabei werden die Konfigurationsdaten (Zeiten und Muster) eingelesen.
*   **S1_S2**: Manueller Auslöser für den Übergang von Schritt 1 zu Schritt 2.
*   **S2_S3**: Manueller Auslöser für den Übergang von Schritt 2 zu Schritt 3.
*   **S3_S4**: Manueller Auslöser für den Übergang von Schritt 3 zu Schritt 4.
*   **S4_S1**: Manueller Auslöser für den Übergang von Schritt 4 zurück zu Schritt 1 (Schleifenschluss).
*   **RESET**: Setzt den Baustein aus jedem Zustand zurück in den Initialzustand (`START`). Alle Ausgänge werden deaktiviert.

### **Ereignis-Ausgänge**

*   **CNF**: Bestätigungsereignis (Execution Confirmation). Wird gefeuert, wenn sich der Zustand ändert oder der Baustein initialisiert wurde.

### **Daten-Eingänge**

*   **DT_S1_S2** (TIME): Verweilzeit in Schritt 1, bevor automatisch zu Schritt 2 gewechselt wird. Standardwert: `NO_TIME` (kein automatischer Wechsel).
*   **DT_S2_S3** (TIME): Verweilzeit in Schritt 2.
*   **DT_S3_S4** (TIME): Verweilzeit in Schritt 3.
*   **DT_S4_S1** (TIME): Verweilzeit in Schritt 4, bevor automatisch zurück zu Schritt 1 gewechselt wird.
*   **P_S1** (BYTE): Ausgabemuster für Schritt 1.
    *   Bit 0 steuert Q1
    *   Bit 1 steuert Q2
    *   Bit 2 steuert Q3
    *   Bit 3 steuert Q4
*   **P_S2** (BYTE): Ausgabemuster für Schritt 2.
*   **P_S3** (BYTE): Ausgabemuster für Schritt 3.
*   **P_S4** (BYTE): Ausgabemuster für Schritt 4.

### **Daten-Ausgänge**

*   **STATE_NR** (SINT): Aktuelle Zustandsnummer (0 = START, 1 = State_01, ..., 4 = State_04).

### **Adapter**

*   **Q1** (`adapter::types::unidirectional::AX`): Ausgang 1 (gesteuert durch Bit 0 der Pattern).
*   **Q2** (`adapter::types::unidirectional::AX`): Ausgang 2 (gesteuert durch Bit 1 der Pattern).
*   **Q3** (`adapter::types::unidirectional::AX`): Ausgang 3 (gesteuert durch Bit 2 der Pattern).
*   **Q4** (`adapter::types::unidirectional::AX`): Ausgang 4 (gesteuert durch Bit 3 der Pattern).
*   **timeOut** (`iec61499::events::ATimeOut`): Interner Adapter zur Verwaltung der Zeitverzögerungen (Timer).

## Funktionsweise

Der Baustein implementiert eine State-Machine (ECC), die zyklisch durch vier aktive Zustände läuft.

1.  **Initialisierung**: Der Baustein startet im Zustand `xSTART`. Durch das Event `START_S1` wechselt er in `sState_01`.
2.  **Zustandsverarbeitung**: In jedem Zustand (`sState_01` bis `sState_04`):
    *   Wird der Timer (`timeOut`) gestoppt und mit der entsprechenden Zeit (`DT_xx`) neu gestartet.
    *   Wird die aktuelle Zustandsnummer (`STATE_NR`) aktualisiert und `CNF` gesendet.
    *   Werden die Ausgänge `Q1` bis `Q4` basierend auf dem korrespondierenden Eingangs-Byte (`P_Sx`) gesetzt. Das Mapping erfolgt bitweise (Bit 0 -> Q1, Bit 1 -> Q2, etc.).
    *   Werden die Events an den Adaptern `Qx` gefeuert (`Qx.E1`), um die Datenänderung zu signalisieren.
3.  **Übergänge (Transitionen)**: Ein Wechsel zum nächsten Schritt erfolgt entweder:
    *   **Automatisch**: Wenn die konfigurierte Zeit (`DT_...`) abgelaufen ist (`timeOut.TimeOut`).
    *   **Manuell**: Wenn das explizite Weiterschalt-Event (z.B. `S1_S2`) eintrifft.
4.  **Schleife**: Nach `sState_04` erfolgt der Übergang zurück zu `sState_01` (Loop), sofern kein Reset ausgelöst wird.
5.  **Reset**: Das `RESET` Event führt jederzeit dazu, dass alle Ausgänge auf `FALSE` gesetzt werden, `STATE_NR` auf 0 geht und der Baustein im `xSTART` Zustand auf einen neuen Startbefehl wartet.

## Technische Besonderheiten

*   **Bit-Mapping**: Die Steuerung der Ausgänge erfolgt effizient über Byte-Muster. Dies ermöglicht es, beliebige Kombinationen der 4 Ausgänge pro Schritt mit einem einzigen Parameter zu definieren.
    *   Beispiel: `P_S1 = 5` (Binär `0000 0101`) aktiviert Q1 und Q3.
*   **AX-Adapter**: Die Verwendung von AX-Adaptern deutet darauf hin, dass dieser Baustein für modulare Systeme konzipiert ist, bei denen die Aktoren über standardisierte Schnittstellen angebunden sind.
*   **Zeit & Event Dualität**: Die Flexibilität, Schritte sowohl zeitgesteuert als auch ereignisgesteuert zu verlassen, erlaubt gemischte Betriebsarten (z.B. Schritt 1 nach Zeit, Schritt 2 wartet auf manuelle Bestätigung).

## Zustandsübersicht

| Zustand | Beschreibung | Ausgangslogik (Q1-Q4) | Nächster Zustand (Auto/Manuell) |
| :--- | :--- | :--- | :--- |
| **xSTART** | Ruhezustand | Inaktiv | sState_01 (via `START_S1`) |
| **sState_01** | Schritt 1 | P_S1 | sState_02 |
| **sState_02** | Schritt 2 | P_S2 | sState_03 |
| **sState_03** | Schritt 3 | P_S3 | sState_04 |
| **sState_04** | Schritt 4 | P_S4 | sState_01 (Loop) |
| **sRESET** | Reset-Logik | Alle FALSE | xSTART |

## Anwendungsszenarien

*   **Lauflicht / Blinker**: Einfache zyklische Lichtsteuerungen.
*   **Nockenschaltwerk-Simulation**: Steuerung von wiederkehrenden Maschinenzyklen (z.B. Greifen, Heben, Verschieben, Senken).
*   **Ampelsteuerungen**: Durch Anpassung der `DT`-Zeiten können einfache Ampelphasen realisiert werden (wobei hier meist 4 Schritte ausreichend sind, z.B. Rot, Rot-Gelb, Grün, Gelb).
*   **Test-Muster-Generator**: Erzeugung von definierten Signalabfolgen zu Testzwecken.

## Vergleich mit ähnlichen Bausteinen

Im Gegensatz zu einfachen Zählern bietet dieser Baustein integrierte Zeitsteuerungen pro Schritt und eine direkte Musterzuweisung. Gegenüber komplexeren Sequenzern (z.B. SFC / Ablaufsprache) ist er kompakter, aber auf genau 4 Schritte und 4 Ausgänge limitiert. Die "Loop"-Variante unterscheidet sich von "Single-Shot"-Sequenzern dadurch, dass sie nicht am Ende stehen bleibt, sondern endlos wiederholt.

## Fazit

Der `sequence_Pattern_04_04_loop_AX` ist ein robuster und flexibler Baustein für kleine, zyklische Steuerungsaufgaben in IEC 61499 Anwendungen. Durch die Kombination aus Zeit- und Ereignissteuerung sowie der direkten Bit-zu-Adapter-Zuweisung eignet er sich hervorragend für repetitive Automatisierungssequenzen.