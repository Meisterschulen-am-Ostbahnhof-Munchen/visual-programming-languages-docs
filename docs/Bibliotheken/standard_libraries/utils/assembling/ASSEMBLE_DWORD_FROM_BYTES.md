# ASSEMBLE_DWORD_FROM_BYTES

![ASSEMBLE_DWORD_FROM_BYTES](https://github.com/user-attachments/assets/818dd9ca-040d-43e5-a631-b8206ec1ed5d)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ASSEMBLE_DWORD_FROM_BYTES` kombiniert vier BYTE-Werte zu einem einzigen DWORD-Wert. Dies ist besonders nützlich, wenn Daten aus mehreren Quellen zusammengeführt werden müssen, um sie als eine einzige Einheit zu verarbeiten oder zu speichern.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Kombination der BYTE-Werte zu einem DWORD. Wird mit den Daten-Eingängen `BYTE_00`, `BYTE_01`, `BYTE_02` und `BYTE_03` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die erfolgreiche Kombination der BYTE-Werte zu einem DWORD. Der kombinierte DWORD-Wert ist am Daten-Ausgang verfügbar.

### **Daten-Eingänge**
- **BYTE_00**: Erstes Byte des zu kombinierenden DWORD.
- **BYTE_01**: Zweites Byte des zu kombinierenden DWORD.
- **BYTE_02**: Drittes Byte des zu kombinierenden DWORD.
- **BYTE_03**: Viertes Byte des zu kombinierenden DWORD.

### **Daten-Ausgänge**
- **(unnamed)**: Der kombinierte DWORD-Wert, der aus den vier Eingabe-Bytes erstellt wurde.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock nimmt vier BYTE-Werte entgegen und kombiniert sie zu einem einzigen DWORD-Wert. Die Kombination erfolgt durch direkte Zuweisung der einzelnen Bytes zu den entsprechenden Positionen im DWORD:
- `BYTE_00` wird dem niedrigstwertigen Byte (B0) des DWORD zugewiesen.
- `BYTE_01` wird dem nächsten Byte (B1) zugewiesen.
- `BYTE_02` wird dem nächsten Byte (B2) zugewiesen.
- `BYTE_03` wird dem höchstwertigen Byte (B3) zugewiesen.

## Technische Besonderheiten
- Der Funktionsblock ist in der ST (Structured Text) Sprache implementiert.
- Die Zuweisung der Bytes erfolgt direkt über die `%B0` bis `%B3` Syntax, die auf die einzelnen Bytes des DWORD zugreift.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Bei Empfang von `REQ` werden die Eingabe-Bytes kombiniert und der DWORD-Wert berechnet.
3. **Completed**: Sendet das `CNF`-Ereignis mit dem kombinierten DWORD-Wert.

## Anwendungsszenarien
- Kombination von Daten aus mehreren Sensoren oder Quellen zu einem einzigen Wert.
- Vorverarbeitung von Daten für die Übertragung oder Speicherung.
- Verwendung in Protokollimplementierungen, wo Daten in Bytes segmentiert und später wieder zusammengesetzt werden müssen.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke könnten einzelne Bytes zu anderen Datentypen (z.B. WORD) kombinieren.
- Im Gegensatz zu manuellen Kombinationen in ST-Code bietet dieser Block eine vordefinierte und wiederverwendbare Lösung.

## Fazit
Der `ASSEMBLE_DWORD_FROM_BYTES`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, vier BYTE-Werte zu einem DWORD zu kombinieren. Seine klare Schnittstelle und direkte Implementierung machen ihn zu einem nützlichen Werkzeug in verschiedenen Anwendungsfällen.
