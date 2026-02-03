# sequence_ET_05_AX

```{index} single: sequence_ET_05_AX
```

* * * * * * * * * *
## Einleitung
`sequence_ET_05_AX` ist eine Variante des `sequence_ET_05`, die zusätzlich Adapter (`AX`) für die Ausgänge verwendet. Er steuert eine Sequenz mit 5 Ausgabezuständen.

![sequence_ET_05_AX](sequence_ET_05_AX.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **START_S1**: Startet die Sequenz bei State_01.
*   **S1_S2**: Manueller Übergang State_01 -> State_02.
*   **S2_S3**: Manueller Übergang State_02 -> State_03.
*   **S3_S4**: Manueller Übergang State_03 -> State_04.
*   **S4_S5**: Manueller Übergang State_04 -> State_05.
*   **S5_START**: Manueller Übergang State_05 -> START.
*   **RESET**: Setzt die Sequenz zurück.

### **Ereignis-Ausgänge**
*   **CNF**: Bestätigung der Ausführung.

### **Daten-Eingänge**
*   **DT_S1_S2**: Zeit für Übergang State_01 -> State_02.
*   **DT_S2_S3**: Zeit für Übergang State_02 -> State_03.
*   **DT_S3_S4**: Zeit für Übergang State_03 -> State_04.
*   **DT_S4_S5**: Zeit für Übergang State_04 -> State_05.
*   **DT_S5_START**: Zeit für Übergang State_05 -> START.

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
Entspricht `sequence_ET_05`, verwendet jedoch Adapter für die Ausgänge.

## Technische Besonderheiten
*   Verwendung von `adapter::types::unidirectional::AX`.

## Zustandsübersicht
Siehe `sequence_ET_05`.

## Anwendungsszenarien
Für 5-stufige Sequenzen mit Adapteranbindung.

## ⚖️ Vergleich mit ähnlichen Bausteinen
*   **sequence_ET_05**: Standardvariante ohne Adapter.

## Fazit
Adapter-Variante des 5-Schritt-Sequenzers.