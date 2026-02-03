# E_TRAIN

```{index} single: E_TRAIN
```

<img width="1139" height="202" alt="E_TRAIN" src="https://user-images.githubusercontent.com/116869307/214142742-8ce9523e-eb2b-416c-afe8-109fb601dd20.png">

* * * * * * * * * *

## Einleitung
Der `E_TRAIN` (Event Train) ist ein Funktionsbaustein nach IEC 61499, der eine endliche Folge von Ereignissen ("Ereigniszug") mit einem festen Zeitabstand generiert. Nach dem Start werden `N` Ereignisse im Abstand von `DT` erzeugt.

![E_TRAIN](E_TRAIN.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge:**
- **START**: Startet die Generierung der Ereignisfolge.
    - **Verbundene Daten**: `DT`, `N`
- **STOP**: Stoppt die laufende Generierung der Ereignisfolge vorzeitig.

### **Ereignis-Ausgänge:**
- **EO (Event Output)**: Das Ausgangsereignis, das periodisch ausgelöst wird.
    - **Verbundene Daten**: `CV`

### **Daten-Eingänge:**
- **DT (Delay Time)**: Die Zeitdauer, die zwischen den einzelnen `EO`-Ereignissen vergeht (Datentyp: `TIME`).
- **N**: Die Gesamtzahl der zu generierenden Ereignisse (Datentyp: `UINT`).

### **Daten-Ausgänge:**
- **CV (Current Value)**: Der Zählerstand, der den Index des gerade ausgelösten Ereignisses angibt (0 bis N-1) (Datentyp: `UINT`).

## Funktionsweise
1.  **Start der Sequenz**: Ein `START`-Ereignis löst den Baustein aus. Ein interner Zähler wird zurückgesetzt, und die Parameter `N` (Anzahl) und `DT` (Zeitabstand) werden übernommen. Der Timer für das erste Ereignis wird gestartet.
2.  **Ereignis-Generierung**:
    - Nach Ablauf der Zeit `DT` wird das erste `EO`-Ereignis ausgelöst. Der `CV`-Ausgang hat dabei den Wert `0`.
    - Unmittelbar danach wird der Timer für das nächste Ereignis neu gestartet.
    - Nach einer weiteren Zeitspanne `DT` wird das nächste `EO`-Ereignis mit `CV=1` ausgelöst.
3.  **Ende der Sequenz**: Dieser Zyklus wiederholt sich, bis `N` Ereignisse generiert wurden. Nachdem das letzte Ereignis (mit `CV = N-1`) ausgelöst wurde, stoppt der Baustein automatisch.
4.  **Stopp**: Ein `STOP`-Ereignis kann die Sequenz jederzeit vorzeitig abbrechen.

## Technische Besonderheiten
- **Puls-Generator**: Erzeugt eine feste Anzahl von Impulsen mit konstantem Abstand.
- **Interner Zähler**: Der Baustein verwendet intern einen `E_CTU`-Zähler, um die Anzahl der bereits generierten Ereignisse zu verfolgen.
- **Sequenz-Zähler**: Der `CV`-Ausgang liefert wertvolle Information darüber, an welcher Stelle der Sequenz man sich gerade befindet.

## Anwendungsszenarien
- **Schrittmotor-Ansteuerung**: Generieren einer exakten Anzahl von Schritten (`N`) mit einer definierten Geschwindigkeit (bestimmt durch `DT`).
- **Dosierprozesse**: Auslösen von `N` Dosiervorgängen im Abstand von `DT`.
- **Testsequenzen**: Senden einer definierten Anzahl von Test-Triggern an ein zu prüfendes Gerät.

## ⚖️ Vergleich mit ähnlichen Bausteinen

| Merkmal       | E_TRAIN | E_CYCLE | E_TABLE |
|--------------|-----------|---------|-----------|
| Ereignisabstand | Fix (`DT`) | Fix (`DT`) | Variabel (Array `DT`) |
| Ereignisanzahl | Endlich (`N`) | Unendlich | Endlich (`N`) |
| Zähler-Ausgang (`CV`) | Ja | Nein | Ja |






## 🛠️ Zugehörige Übungen

* [Uebung_035a2](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_035a2.md)
* [Uebung_035a2_AX](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_035a2_AX.md)
* [Uebung_091](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_091.md)

## Fazit
Der `E_TRAIN`-Baustein ist ideal für Anwendungen, die eine feste Anzahl von Ereignissen in einem konstanten Zeitintervall benötigen. Er kombiniert die Funktionalität eines Taktgebers (`E_CYCLE`) mit einem Zähler, um eine kontrollierte, endliche Impulsfolge zu erzeugen. Der `CV`-Ausgang bietet dabei eine nützliche Rückmeldung über den Fortschritt der Sequenz.