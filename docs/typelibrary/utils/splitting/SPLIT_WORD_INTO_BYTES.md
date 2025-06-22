# SPLIT_WORD_INTO_BYTES

![SPLIT_WORD_INTO_BYTES](https://github.com/user-attachments/assets/5c99635d-3f7d-4266-a108-12d075d58313)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `SPLIT_WORD_INTO_BYTES` dient dazu, ein 16-Bit-Wort (WORD) in seine beiden 8-Bit-Bytes aufzuteilen. Dies ist besonders nützlich, wenn mit Daten gearbeitet wird, die als WORD übertragen werden, aber byteweise verarbeitet werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Wird dieser Ereigniseingang ausgelöst, beginnt die Verarbeitung des Eingangswerts `IN`.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die erfolgreiche Beendigung der Verarbeitung. Dieses Ereignis wird zusammen mit den beiden ausgegebenen Bytes `BYTE_00` und `BYTE_01` ausgelöst.

### **Daten-Eingänge**
- **IN**: Das 16-Bit-Wort (WORD), das in zwei Bytes aufgeteilt werden soll.

### **Daten-Ausgänge**
- **BYTE_00**: Das niederwertige Byte (Bit 0 bis 7) des Eingangsworts `IN`.
- **BYTE_01**: Das höherwertige Byte (Bit 8 bis 15) des Eingangsworts `IN`.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock extrahiert die beiden Bytes aus dem Eingangswort `IN` und gibt sie über die Ausgänge `BYTE_00` (niederwertiges Byte) und `BYTE_01` (höherwertiges Byte) aus. Die Extraktion erfolgt durch direkte Zugriffe auf die Bytes des WORD-Datentyps (`IN.%B0` für das niederwertige Byte und `IN.%B1` für das höherwertige Byte).

## Technische Besonderheiten
- Der Funktionsblock ist in der Programmiersprache ST (Structured Text) implementiert.
- Die Verarbeitung erfolgt synchron mit dem Auslösen des `REQ`-Ereignisses.
- Die Ausgabe der Bytes erfolgt zusammen mit dem `CNF`-Ereignis.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das `REQ`-Ereignis.
2. **Verarbeitungszustand**: Bei Auslösung von `REQ` werden die Bytes extrahiert.
3. **Ausgabe-Zustand**: Die extrahierten Bytes werden mit dem `CNF`-Ereignis ausgegeben, und der Block kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- **Datenkommunikation**: Bei der Verarbeitung von Netzwerkdaten, die als WORD übertragen werden, aber byteweise interpretiert werden müssen.
- **Hardwarenahe Programmierung**: Bei der Arbeit mit Registerinhalten, die als WORD gelesen werden, aber einzelne Bytes enthalten.
- **Datenkonvertierung**: Bei der Umwandlung von WORD-Daten in zwei separate BYTE-Daten für weitere Verarbeitungsschritte.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Extraktionsfunktionen bietet `SPLIT_WORD_INTO_BYTES` eine spezialisierte und optimierte Lösung für die Aufteilung von WORD-Daten in Bytes.
- Andere Bausteine könnten zusätzliche Funktionen wie die Behandlung von Vorzeichen oder die Extraktion von Bits bieten, sind aber für diese spezielle Aufgabe weniger effizient.

## Fazit
Der `SPLIT_WORD_INTO_BYTES`-Funktionsblock ist ein einfacher, aber effektiver Baustein für die Aufteilung von 16-Bit-Wörtern in ihre einzelnen Bytes. Seine klare Schnittstelle und effiziente Implementierung machen ihn ideal für Anwendungen, bei denen diese Funktionalität benötigt wird.
