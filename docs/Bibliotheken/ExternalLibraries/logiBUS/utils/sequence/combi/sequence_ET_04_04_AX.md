# sequence_ET_04_04_AX

* * * * * * * * * *
## Einleitung
Der Funktionsblock `sequence_ET_04_04_AX` ist die adapterbasierte Variante des `sequence_ET_04_04`. Er realisiert eine 8-stufige Sequenzsteuerung, bei der die Ausgänge über `AX`-Adapter (Ereignis + Daten) statt über einfache BOOL-Variablen angesteuert werden. Die Übergänge können sowohl ereignis- als auch zeitgesteuert erfolgen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **`EI1`**: Allgemeines Eingangsereignis.
*   **`START_S1`**: Startet die Sequenz oder springt innerhalb der Phasen zurück.
*   **`S4_S5`**: Manueller Übergang von Zustand 4 zu 5.
*   **`EI_RESET`**: Globaler Reset der Sequenz.

### **Ereignis-Ausgänge**
*   **`CNF`**: Ausführungsbestätigung mit aktueller `STATE_NR`.
*   *(Hinweis: Die zustandsspezifischen Ereignisse EO_Sx entfallen hier, da sie in den Adaptern enthalten sind)*

### **Daten-Eingänge**
*   **`DT_S1_S2`** bis **`DT_S8_START`** (TIME): Zeitverzögerungen für automatische Übergänge.

### **Daten-Ausgänge**
*   **`STATE_NR`** (SINT): Aktuelle Zustandsnummer (0-8).

### **Adapter**
*   **`DO_S1` bis `DO_S8`** (Plug, Typ: `adapter::types::unidirectional::AX`): Adapter-Ausgänge für die Zustände 1 bis 8. Jedes Betreten oder Verlassen eines Zustands löst das Ereignis `E1` am entsprechenden Adapter aus und setzt `D1` auf `TRUE` bzw. `FALSE`.
*   **`timeOut`** (Plug, Typ: `iec61499::events::ATimeOut`): Schnittstelle zum externen Timer.

## Funktionsweise
Die Logik entspricht exakt dem `sequence_ET_04_04`. Der entscheidende Unterschied liegt in der physikalischen Kapselung der Ausgänge. Während die Standard-Variante separate Event- und Data-Leitungen nutzt, bündelt die `_AX`-Variante diese in Adapter-Verbindungen. Dies reduziert die Komplexität im grafischen Editor bei umfangreichen Verschaltungen.

## Technische Besonderheiten
✔ **Adapter-Ausgänge**: Verwendet `AX`-Adapter für alle 8 Zustände.
✔ **Kombinierte Trigger**: Ereignisse und Zeitabläufe steuern die Kette.
✔ **Zustands-Feedback**: Kontinuierliche Ausgabe der `STATE_NR`.

## Zustandsübersicht
Siehe `sequence_ET_04_04`.

## Vergleich mit ähnlichen Bausteinen
*   **sequence_ET_04_04**: Die Variante mit klassischen BOOL-Ausgängen und EO-Events.

## Fazit
`sequence_ET_04_04_AX` ist die ideale Wahl für komplexe 8-Schritt-Steuerungen in Systemen, die konsequent auf adapterbasierte Kommunikation setzen.
