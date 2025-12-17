# ASSEMBLE_WORD_FROM_QUARTERS

![ASSEMBLE_WORD_FROM_QUARTERS](https://github.com/user-attachments/assets/6677028d-5ee1-4e7f-80d6-df3177ab9181)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ASSEMBLE_WORD_FROM_QUARTERS` kombiniert 8 Quarter-Bytes zu einem WORD. Dies ist besonders nützlich, wenn Daten in kleineren Einheiten vorliegen und zu einer größeren Einheit zusammengefügt werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Verarbeitung und kombiniert die 8 Quarter-Bytes zu einem WORD.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert die erfolgreiche Kombination der Quarter-Bytes zu einem WORD.

### **Daten-Eingänge**
- `QUARTER_BYTE_00` bis `QUARTER_BYTE_07` (Typ: `BYTE`): Die 8 Quarter-Bytes, die zu einem WORD kombiniert werden.

### **Daten-Ausgänge**
- `OUT` (Typ: `WORD`): Das resultierende WORD, das aus den 8 Quarter-Bytes zusammengesetzt wurde.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock nimmt 8 Quarter-Bytes entgegen und kombiniert sie zu einem WORD. Jedes Quarter-Byte wird an eine bestimmte Position im WORD verschoben und mit logischen OR-Operationen zusammengefügt. Die genauen Verschiebungen werden durch Konstanten (`quarterconst::SHIFT_QUARTER_00` bis `quarterconst::SHIFT_QUARTER_07`) definiert.

## Technische Besonderheiten
- Verwendet bitweise Operationen (SHL und OR) zur Kombination der Bytes.
- Die Verschiebungspositionen sind durch Konstanten definiert, was eine flexible Anpassung ermöglicht.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Kombiniert die Quarter-Bytes zu einem WORD.
3. **Complete**: Sendet das `CNF`-Ereignis mit dem resultierenden WORD.

## Anwendungsszenarien
- Datenkomprimierung: Kombination von kleineren Dateneinheiten zu größeren.
- Kommunikationsprotokolle: Zusammensetzung von Datenpaketen aus einzelnen Bytes.
- Signalverarbeitung: Kombination von Signalabschnitten zu einem Gesamtsignal.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Bausteine könnten `BYTE_TO_WORD` oder `SHL` sein, jedoch bietet `ASSEMBLE_WORD_FROM_QUARTERS` eine spezialisierte Funktion zur Kombination von 8 Quarter-Bytes zu einem WORD.
- Im Gegensatz zu generischen Kombinationsbausteinen ist dieser Funktionsblock auf die spezifische Anforderung der Quarter-Byte-Kombination optimiert.

## Fazit
Der `ASSEMBLE_WORD_FROM_QUARTERS`-Funktionsblock ist ein effizientes Werkzeug zur Kombination von 8 Quarter-Bytes zu einem WORD. Durch die Verwendung von bitweisen Operationen und definierten Verschiebungspositionen bietet er eine zuverlässige und flexible Lösung für diese spezifische Aufgabe.
