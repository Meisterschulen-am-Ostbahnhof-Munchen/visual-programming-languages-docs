# sequence_T_08_AX

```{index} single: sequence_T_08_AX
```

* * * * * * * * * *
## Einleitung
`sequence_T_08_AX` ist eine Variante des `sequence_T_08`, die zusätzlich Adapter (`AX`) für die Ausgänge verwendet. Er steuert eine rein zeitgesteuerte Sequenz mit 8 Ausgabezuständen.

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
*   **DT_S4_S5**: Zeit für Übergang State_04 -> State_05.
*   **DT_S5_S6**: Zeit für Übergang State_05 -> State_06.
*   **DT_S6_S7**: Zeit für Übergang State_06 -> State_07.
*   **DT_S7_S8**: Zeit für Übergang State_07 -> State_08.
*   **DT_S8_START**: Zeit für Übergang State_08 -> START.

### **Daten-Ausgänge**
*   **STATE_NR** (SINT): Aktuelle Zustandsnummer.

### **Adapter**
*   **DO_S1** ... **DO_S8** (adapter::types::unidirectional::AX): Ausgangsadapter für State_01 bis State_08.
*   **timeOut** (iec61499::events::ATimeOut): Timer-Adapter.

## Funktionsweise
Entspricht `sequence_T_08`, verwendet jedoch Adapter für die Ausgänge.

## Technische Besonderheiten
*   Verwendung von `adapter::types::unidirectional::AX`.

## Zustandsübersicht
Siehe `sequence_T_08`.

## Anwendungsszenarien
Für zeitgesteuerte 8-stufige Sequenzen mit Adapteranbindung.

## Vergleich mit ähnlichen Bausteinen
*   **sequence_T_08**: Standardvariante ohne Adapter.

## Fazit
Adapter-Variante des 8-Schritt-Zeit-Sequenzers.