# sequence_E_08_loop_AX

```{index} single: sequence_E_08_loop_AX
```


![sequence_E_08_loop_AX_ecc](./sequence_E_08_loop_AX_ecc.svg)

* * * * * * * * * *
## Einleitung
`sequence_E_08_loop_AX` ist eine Variante des `sequence_E_08_loop`, die zusätzlich Adapter (`AX`) für die Ausgänge verwendet. Er steuert eine rein ereignisgesteuerte, zyklische Sequenz mit 8 Ausgabezuständen.

![sequence_E_08_loop_AX](sequence_E_08_loop_AX.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **START_S1**: Startet die Sequenz bei State_01.
*   **S1_S2** ... **S7_S8**: Manuelle Übergänge zwischen den Zuständen.
*   **S8_S1**: Übergang State_08 -> State_01 (Loop).
*   **RESET**: Setzt die Sequenz zurück.

### **Ereignis-Ausgänge**
*   **CNF**: Bestätigung der Ausführung.

### **Daten-Eingänge**
*   Keine.

### **Daten-Ausgänge**
*   **STATE_NR** (SINT): Aktuelle Zustandsnummer.

### **Adapter**
*   **DO_S1** ... **DO_S8** (adapter::types::unidirectional::AX): Ausgangsadapter für State_01 bis State_08.

## Funktionsweise
Entspricht `sequence_E_08_loop`, verwendet jedoch Adapter für die Ausgänge.

## Technische Besonderheiten
*   Verwendung von `adapter::types::unidirectional::AX`.

## Zustandsübersicht
Siehe `sequence_E_08_loop`.

## Anwendungsszenarien
Für zyklische ereignisgesteuerte 8-stufige Sequenzen mit Adapteranbindung.

## ⚖️ Vergleich mit ähnlichen Bausteinen
*   **sequence_E_08_loop**: Standardvariante ohne Adapter.






## 🛠️ Zugehörige Übungen

* [Uebung_040_AX](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_040_AX.md)

## Fazit
Adapter-Variante des 8-Schritt-Loop-Ereignis-Sequenzers.