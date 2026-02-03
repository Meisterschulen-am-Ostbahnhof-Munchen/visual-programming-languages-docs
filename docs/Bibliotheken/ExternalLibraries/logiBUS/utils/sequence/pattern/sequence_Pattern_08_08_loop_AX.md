# sequence_Pattern_08_08_loop_AX

[Bild des sequence_Pattern_08_08_loop_AX, falls vorhanden]


![sequence_Pattern_08_08_loop_AX](.././sequence_Pattern_08_08_loop_AX.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **sequence_Pattern_08_08_loop_AX** ist ein Sequenzer (Schrittkette), der ein konfigurierbares "Nockenschaltwerk" mit 8 Zuständen (Schritten) und 8 Ausgängen implementiert. Er ist darauf ausgelegt, zyklisch zu arbeiten (Loop-Verhalten), wobei der Übergang von Schritt 8 zurück zu Schritt 1 erfolgt.

Dieser Baustein ermöglicht die Definition von Bitmustern für jeden der 8 Schritte, die über spezielle Adapter (AX-Schnittstelle) ausgegeben werden. Die Weiterschaltung zwischen den Zuständen kann entweder ereignisgesteuert oder zeitgesteuert erfolgen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*   **START_S1**: Initialisiert die Sequenz und springt direkt in den Zustand 1 (`State_01`). Dieses Ereignis übernimmt auch die parametrisierten Zeitwerte (`DT_...`) und Bitmuster (`P_...`).
*   **S1_S2** bis **S8_S1**: Manuelle Trigger-Ereignisse, um sofort vom aktuellen Zustand in den nächsten zu wechseln (z. B. springt `S1_S2` von Zustand 1 nach 2).
*   **RESET**: Setzt den Baustein aus jedem beliebigen Zustand in den Initialzustand (`START`) zurück und deaktiviert alle Ausgänge.

### **Ereignis-Ausgänge**

*   **CNF**: Bestätigungs-Ereignis (Execution Confirmation). Es wird gefeuert, sobald ein neuer Zustand erreicht wurde und die Ausgänge aktualisiert sind.

### **Daten-Eingänge**

*   **DT_S1_S2** bis **DT_S8_S1** (Typ: `TIME`): Definieren die Verweildauer im jeweiligen Zustand, bevor automatisch in den nächsten geschaltet wird. Standardwert ist `NO_TIME` (kein automatisches Umschalten per Zeit).
*   **P_S1** bis **P_S8** (Typ: `BYTE`): Definieren das Ausgabemuster für den jeweiligen Zustand.
    *   Bit 0 steuert Adapter Q1
    *   Bit 1 steuert Adapter Q2
    *   ...
    *   Bit 7 steuert Adapter Q8

### **Daten-Ausgänge**

*   **STATE_NR** (Typ: `SINT`): Gibt die aktuelle Zustandsnummer aus (0 = START, 1 = State_01, ..., 8 = State_08).

### **Adapter**

*   **Q1** bis **Q8** (Typ: `adapter::types::unidirectional::AX`): Die 8 physikalischen oder logischen Ausgänge. Jeder Adapter erhält ein Daten-Signal (`D1`) und ein Ereignis-Signal (`E1`).
*   **timeOut** (Typ: `iec61499::events::ATimeOut`): Ein interner Adapter zur Handhabung der zeitgesteuerten Übergänge zwischen den Schritten.

## Funktionsweise

Der Baustein arbeitet als endlicher Automat (State Machine) mit einer zyklischen Struktur:

1.  **Initialisierung**: Durch das Ereignis `START_S1` wird die Sequenz gestartet. Dabei werden die konfigurierten Zeitwerte und Bitmuster eingelesen. Der Automat wechselt in **State_01**.
2.  **Zustandslogik**: In jedem Zustand (`State_01` bis `State_08`) wird das entsprechende Byte-Muster (`P_Sn`) zerlegt.
    *   Ist Bit 0 von `P_S1` gesetzt, wird `Q1.D1` auf TRUE gesetzt.
    *   Ist Bit 1 von `P_S1` gesetzt, wird `Q2.D1` auf TRUE gesetzt, usw.
    *   Gleichzeitig wird das Ereignis `E1` an allen Adaptern `Q1` bis `Q8` ausgelöst, um die Änderung zu signalisieren.
3.  **Transitionen**: Der Wechsel zum nächsten Zustand erfolgt, wenn:
    *   Das explizite Ereignis empfangen wird (z. B. `S1_S2`).
    *   ODER die konfigurierte Zeit (`DT_S1_S2`) abgelaufen ist (via `timeOut` Adapter).
4.  **Zyklus**: Nach **State_08** folgt der Übergang zurück zu **State_01** (`S8_S1` oder Zeitablauf), wodurch eine Endlosschleife entsteht.
5.  **Reset**: Das Ereignis `RESET` unterbricht den Ablauf sofort, setzt alle Ausgänge (`Q1` bis `Q8`) auf `FALSE` und setzt die Zustandsnummer auf 0.

## Technische Besonderheiten

*   **AX-Adapter-Nutzung**: Anstelle von klassischen `BOOL`-Ausgängen nutzt dieser FB Adapter vom Typ `AX`. Dies ermöglicht eine flexiblere Anbindung, z.B. an Hardware-Abstraktionsschichten oder komplexe Aktoren, die ein Event-Signal zur Datenübernahme benötigen.
*   **Bit-Mapping**: Die Steuerung der 8 Ausgänge erfolgt effizient über `BYTE`-Variablen. Dies reduziert die Anzahl der notwendigen Eingangspins am Baustein drastisch im Vergleich zu einzelnen Boolschen Eingängen pro Schritt und Ausgang.
*   **Hybride Steuerung**: Der Baustein unterstützt gleichzeitig zeitgesteuerte Abläufe (Timer) und ereignisgesteuerte Abläufe (externe Trigger), was ihn sehr flexibel macht.

## Zustandsübersicht

| Zustands-ID | Name | Beschreibung | Ausgangslogik | Übergang nach |
| :--- | :--- | :--- | :--- | :--- |
| **0** | xSTART | Wartezustand / Reset | Keine | State_01 (bei START_S1) |
| **1** | sState_01 | Schritt 1 | Q1-Q8 gemäß P_S1 | State_02 |
| **2** | sState_02 | Schritt 2 | Q1-Q8 gemäß P_S2 | State_03 |
| **3** | sState_03 | Schritt 3 | Q1-Q8 gemäß P_S3 | State_04 |
| **4** | sState_04 | Schritt 4 | Q1-Q8 gemäß P_S4 | State_05 |
| **5** | sState_05 | Schritt 5 | Q1-Q8 gemäß P_S5 | State_06 |
| **6** | sState_06 | Schritt 6 | Q1-Q8 gemäß P_S6 | State_07 |
| **7** | sState_07 | Schritt 7 | Q1-Q8 gemäß P_S7 | State_08 |
| **8** | sState_08 | Schritt 8 | Q1-Q8 gemäß P_S8 | State_01 (Loop) |
| **-** | sRESET | Reset-Zustand | Q1-Q8 = FALSE | xSTART |

## Anwendungsszenarien

*   **Lauflicht-Steuerungen**: Durch Setzen von `P_S1=1`, `P_S2=2`, `P_S3=4` usw. kann ein einfaches Lauflicht realisiert werden.
*   **Nockenschaltwerke**: Steuerung von mechanischen Abläufen, bei denen mehrere Aktoren (Zylinder, Ventile) in einer festen zeitlichen Reihenfolge aktiviert werden müssen.
*   **Ampelsteuerungen**: Zyklische Abfolge von Rot-Gelb-Grün Phasen.
*   **Reinigungszyklen**: Spülen, Waschen, Trocknen in wiederkehrenden Intervallen.

## Vergleich mit ähnlichen Bausteinen

Im Gegensatz zu linearen Sequenzern (ohne Loop) ist dieser Baustein explizit für wiederkehrende Prozesse konzipiert. Er unterscheidet sich von einfachen Zählern dadurch, dass für jeden Schritt ein individuelles Ausgangsmuster und eine individuelle Zeit definiert werden kann. Die Verwendung von AX-Adaptern unterscheidet ihn von Standard-IEC-61499-Bausteinen, die meist direkte Boolesche Ausgänge verwenden, und prädestiniert ihn für strukturierte, objektorientierte Steuerungsdesigns.

## Fazit

Der **sequence_Pattern_08_08_loop_AX** ist ein leistungsfähiger und kompakter Baustein zur Realisierung komplexer, zyklischer Schrittketten. Durch die Parametrierung über Byte-Muster und Zeitwerte lassen sich vielfältige Steuerungsaufgaben ohne Änderung der internen Logik realisieren. Die integrierte Reset-Funktionalität und die Adapter-Schnittstelle sorgen für eine saubere Integration in moderne 4diac-Anwendungen.