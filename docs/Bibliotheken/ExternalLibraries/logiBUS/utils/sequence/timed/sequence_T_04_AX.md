# sequence_T_04_AX

```{index} single: sequence_T_04_AX
```

* * * * * * * * * *
## Einleitung
`sequence_T_04_AX` ist eine Variante des `sequence_T_04`, die zusätzlich Adapter (`AX`) für die Ausgänge verwendet. Er steuert eine rein zeitgesteuerte Sequenz mit 4 Ausgabezuständen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **START_S1**: Startet die Sequenz bei State_01.
*   **RESET**: Setzt die Sequenz zurück.

### **Ereignis-Ausgänge**
*   **CNF**: Bestätigung der Ausführung.

### **Daten-Eingänge**
*   **DT_S1_S2**: Zeit für Übergang State_01 -> State_02.
*   **DT_S2_S3**: Zeit für Übergang State_02 -> State_03.
*   **DT_S3_S4**: Zeit für Übergang State_03 -> State_04.
*   **DT_S4_START**: Zeit für Übergang State_04 -> START.

### **Daten-Ausgänge**
*   **STATE_NR** (SINT): Aktuelle Zustandsnummer.

### **Adapter**
*   **DO_S1** (adapter::types::unidirectional::AX): Ausgangsadapter für State_01.
*   **DO_S2** (adapter::types::unidirectional::AX): Ausgangsadapter für State_02.
*   **DO_S3** (adapter::types::unidirectional::AX): Ausgangsadapter für State_03.
*   **DO_S4** (adapter::types::unidirectional::AX): Ausgangsadapter für State_04.
*   **timeOut** (iec61499::events::ATimeOut): Timer-Adapter.

## Funktionsweise
Entspricht `sequence_T_04`, verwendet jedoch Adapter für die Ausgänge.

## Technische Besonderheiten
*   Verwendung von `adapter::types::unidirectional::AX`.

## Zustandsübersicht
Siehe `sequence_T_04`.

## Anwendungsszenarien
Für zeitgesteuerte 4-stufige Sequenzen mit Adapteranbindung.

## Vergleich mit ähnlichen Bausteinen
*   **sequence_T_04**: Standardvariante ohne Adapter.

## Fazit
Adapter-Variante des 4-Schritt-Zeit-Sequenzers.