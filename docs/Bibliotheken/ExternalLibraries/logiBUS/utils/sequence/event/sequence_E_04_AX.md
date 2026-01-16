# sequence_E_04_AX

* * * * * * * * * *
## Einleitung
Der `sequence_E_04_AX` ist eine Variante des `sequence_E_04`, die zusätzlich Adapter (`AX`) für die Ausgänge verwendet. Er steuert eine rein ereignisgesteuerte Sequenz mit 4 Ausgabezuständen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **START_S1**: Startet die Sequenz bei State_01.
*   **S1_S2**: Übergang State_01 -> State_02.
*   **S2_S3**: Übergang State_02 -> State_03.
*   **S3_S4**: Übergang State_03 -> State_04.
*   **S4_START**: Übergang State_04 -> START.
*   **RESET**: Setzt die Sequenz zurück.

### **Ereignis-Ausgänge**
*   **CNF**: Bestätigung der Ausführung.

### **Daten-Eingänge**
*   Keine.

### **Daten-Ausgänge**
*   **STATE_NR** (SINT): Aktuelle Zustandsnummer.

### **Adapter**
*   **DO_S1** (adapter::types::unidirectional::AX): Ausgangsadapter für State_01.
*   **DO_S2** (adapter::types::unidirectional::AX): Ausgangsadapter für State_02.
*   **DO_S3** (adapter::types::unidirectional::AX): Ausgangsadapter für State_03.
*   **DO_S4** (adapter::types::unidirectional::AX): Ausgangsadapter für State_04.

## Funktionsweise
Entspricht `sequence_E_04`, verwendet jedoch Adapter für die Ausgänge.

## Technische Besonderheiten
*   Verwendung von `adapter::types::unidirectional::AX`.

## Zustandsübersicht
Siehe `sequence_E_04`.

## Anwendungsszenarien
Für ereignisgesteuerte Sequenzen, die über Adapter gesteuert werden.

## Vergleich mit ähnlichen Bausteinen
*   **sequence_E_04**: Standardvariante ohne Adapter.

## Fazit
Adapter-Variante des 4-Schritt-Ereignis-Sequenzers.