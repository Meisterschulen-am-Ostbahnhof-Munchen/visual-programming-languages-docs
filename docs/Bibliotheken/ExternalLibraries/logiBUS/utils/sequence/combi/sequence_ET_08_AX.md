# sequence_ET_08_AX

* * * * * * * * * *
## Einleitung
`sequence_ET_08_AX` ist eine Variante des `sequence_ET_08`, die zusätzlich Adapter (`AX`) für die Ausgänge verwendet. Er steuert eine Sequenz mit 8 Ausgabezuständen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **START_S1**: Startet die Sequenz bei State_01.
*   **S1_S2** ... **S7_S8**: Manuelle Übergänge zwischen den Zuständen.
*   **S8_START**: Manueller Übergang State_08 -> START.
*   **RESET**: Setzt die Sequenz zurück.

### **Ereignis-Ausgänge**
*   **CNF**: Bestätigung der Ausführung.

### **Daten-Eingänge**
*   **DT_S1_S2** ... **DT_S8_START**: Zeiten für die automatischen Übergänge zwischen den Zuständen.

### **Daten-Ausgänge**
*   **STATE_NR** (SINT): Aktuelle Zustandsnummer.

### **Adapter**
*   **DO_S1** ... **DO_S8** (adapter::types::unidirectional::AX): Ausgangsadapter für State_01 bis State_08.
*   **timeOut** (iec61499::events::ATimeOut): Timer-Adapter.

## Funktionsweise
Entspricht `sequence_ET_08`, verwendet jedoch Adapter für die Ausgänge.

## Technische Besonderheiten
*   Verwendung von `adapter::types::unidirectional::AX`.

## Zustandsübersicht
Siehe `sequence_ET_08`.

## Anwendungsszenarien
Für 8-stufige Sequenzen mit Adapteranbindung.

## Vergleich mit ähnlichen Bausteinen
*   **sequence_ET_08**: Standardvariante ohne Adapter.

## Fazit
Adapter-Variante des 8-Schritt-Sequenzers.
