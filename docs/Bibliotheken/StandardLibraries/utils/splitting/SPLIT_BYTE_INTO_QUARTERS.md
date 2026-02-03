# SPLIT_BYTE_INTO_QUARTERS

## 🎧 Podcast

* [QUARTER](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/QUARTER-e36741d)

---- 
```{index} single: SPLIT_BYTE_INTO_QUARTERS
```

![SPLIT_BYTE_INTO_QUARTERS](https://github.com/user-attachments/assets/9cbf32e0-f8c2-437f-88d3-8e29db1731dd)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `SPLIT_BYTE_INTO_QUARTERS` dient dazu, ein Byte in vier Viertelbytes (Quarter Bytes) aufzuteilen. Diese Funktion ist besonders nützlich, wenn einzelne Teile eines Bytes separat verarbeitet werden müssen, z.B. bei der Dekodierung von Daten oder bei der Bitmanipulation.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Verarbeitung des Eingabebytes. Wird mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert den Abschluss der Verarbeitung und liefert die vier Viertelbytes. Wird mit den Daten-Ausgängen `QUARTER_BYTE_00`, `QUARTER_BYTE_01`, `QUARTER_BYTE_02` und `QUARTER_BYTE_03` verknüpft.

### **Daten-Eingänge**
- `IN` (BYTE): Das Eingabebyte, das in vier Viertelbytes aufgeteilt werden soll.

### **Daten-Ausgänge**
- `QUARTER_BYTE_00` (BYTE): Das erste Viertelbyte (Bits 0-1).
- `QUARTER_BYTE_01` (BYTE): Das zweite Viertelbyte (Bits 2-3).
- `QUARTER_BYTE_02` (BYTE): Das dritte Viertelbyte (Bits 4-5).
- `QUARTER_BYTE_03` (BYTE): Das vierte Viertelbyte (Bits 6-7).

### **Adapter**
Es werden keine Adapter verwendet.

## Funktionsweise
Der Funktionsblock extrahiert die vier Viertelbytes aus dem Eingabebyte `IN` mithilfe von Bitoperationen:
1. Jedes Viertelbyte wird durch eine bitweise UND-Operation mit einer entsprechenden Maske isoliert.
2. Anschließend wird das Ergebnis durch eine Rechtsverschiebung (`SHR`) in die richtige Position gebracht.
3. Die verwendeten Masken und Verschiebungswerte sind in der Konstanten-Datei `quarterconst` definiert.

## Technische Besonderheiten
- Die Bitoperationen sind effizient und schnell, da sie direkt auf Prozessorebene ausgeführt werden.
- Die Verwendung von Konstanten (`quarterconst`) ermöglicht eine flexible Anpassung der Masken und Verschiebungswerte.

## Zustandsübersicht
Der Funktionsblock hat keinen internen Zustand. Die Verarbeitung erfolgt ausschließlich bei Auftreten des `REQ`-Ereignisses.

## Anwendungsszenarien
- Dekodierung von Daten, die in einem Byte gepackt sind.
- Extraktion von einzelnen Steuerbits aus einem Statusbyte.
- Verarbeitung von Daten in Kommunikationsprotokollen, bei denen Informationen in Viertelbytes codiert sind.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Bitmanipulations-Funktionsblöcken bietet `SPLIT_BYTE_INTO_QUARTERS` eine spezialisierte und optimierte Lösung für die Aufteilung eines Bytes in vier Teile.
- Andere Blöcke wie `EXTRACT_BITS` oder `BIT_SLICE` sind allgemeiner, erfordern aber mehr Konfiguration und sind möglicherweise weniger effizient.




## Zugehörige Übungen

* [Uebung_056](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_056.md)

## Fazit
Der `SPLIT_BYTE_INTO_QUARTERS`-Funktionsblock ist eine effiziente und spezialisierte Lösung für die Aufteilung eines Bytes in vier Viertelbytes. Durch die Verwendung von Bitoperationen und Konstanten ist er schnell und flexibel einsetzbar. Ideal für Anwendungen, bei denen Daten in kompakter Form vorliegen und separat verarbeitet werden müssen.