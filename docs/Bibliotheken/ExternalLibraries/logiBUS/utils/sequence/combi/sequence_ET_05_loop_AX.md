# sequence_ET_05_loop_AX

```{index} single: sequence_ET_05_loop_AX
```

* * * * * * * * * *
## Einleitung
`sequence_ET_05_loop_AX` ist eine Variante des `sequence_ET_05_loop`, die zusätzlich Adapter (`AX`) für die Ausgänge verwendet. Er steuert eine zyklische Sequenz mit 5 Ausgabezuständen.

![sequence_ET_05_loop_AX](sequence_ET_05_loop_AX.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **START_S1**: Startet die Sequenz bei State_01.
*   **S1_S2**: Manueller Übergang State_01 -> State_02.
*   **S2_S3**: Manueller Übergang State_02 -> State_03.
*   **S3_S4**: Manueller Übergang State_03 -> State_04.
*   **S4_S5**: Manueller Übergang State_04 -> State_05.
*   **S5_S1**: Manueller Übergang State_05 -> State_01 (Loop).
*   **RESET**: Setzt die Sequenz zurück.

### **Ereignis-Ausgänge**
*   **CNF**: Bestätigung der Ausführung.

### **Daten-Eingänge**
*   **DT_S1_S2**: Zeit für Übergang State_01 -> State_02.
*   **DT_S2_S3**: Zeit für Übergang State_02 -> State_03.
*   **DT_S3_S4**: Zeit für Übergang State_03 -> State_04.
*   **DT_S4_S5**: Zeit für Übergang State_04 -> State_05.
*   **DT_S5_S1**: Zeit für Übergang State_05 -> State_01.

### **Daten-Ausgänge**
*   **STATE_NR** (SINT): Aktuelle Zustandsnummer.

### **Adapter**
*   **DO_S1** (adapter::types::unidirectional::AX): Ausgangsadapter für State_01.
*   **DO_S2** (adapter::types::unidirectional::AX): Ausgangsadapter für State_02.
*   **DO_S3** (adapter::types::unidirectional::AX): Ausgangsadapter für State_03.
*   **DO_S4** (adapter::types::unidirectional::AX): Ausgangsadapter für State_04.
*   **DO_S5** (adapter::types::unidirectional::AX): Ausgangsadapter für State_05.
*   **timeOut** (iec61499::events::ATimeOut): Timer-Adapter.

## Funktionsweise
Entspricht `sequence_ET_05_loop`, verwendet jedoch Adapter für die Ausgänge.

## Technische Besonderheiten
*   Verwendung von `adapter::types::unidirectional::AX`.

## Zustandsübersicht
Siehe `sequence_ET_05_loop`.

## Anwendungsszenarien
Für zyklische 5-stufige Prozesse, die über Adapter gesteuert werden sollen.

## Vergleich mit ähnlichen Bausteinen
*   **sequence_ET_05_loop**: Standardvariante ohne Adapter.

## Fazit
Adapter-Variante des 5-Schritt-Loop-Sequenzers.