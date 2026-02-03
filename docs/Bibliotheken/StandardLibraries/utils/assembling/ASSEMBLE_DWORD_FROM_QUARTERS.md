# ASSEMBLE_DWORD_FROM_QUARTERS

## 🎧 Podcast

* [QUARTER](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/QUARTER-e36741d)

---- 
```{index} single: ASSEMBLE_DWORD_FROM_QUARTERS
```

![ASSEMBLE_DWORD_FROM_QUARTERS](https://github.com/user-attachments/assets/b87a9cb4-49aa-4375-be7f-c4e32422490e)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ASSEMBLE_DWORD_FROM_QUARTERS` kombiniert 16 Quarter-Bytes (je 4 Bit) zu einem DWORD (32 Bit). Dies ist besonders nützlich, wenn Daten in kleineren Einheiten vorliegen und zu einer größeren Einheit zusammengefasst werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Kombination der Quarter-Bytes zu einem DWORD. Wird mit allen 16 Quarter-Bytes verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert die erfolgreiche Kombination der Quarter-Bytes zu einem DWORD.

### **Daten-Eingänge**
- `QUARTER_BYTE_00` bis `QUARTER_BYTE_15`: 16 Eingänge vom Typ `BYTE`, die jeweils ein Quarter-Byte (4 Bit) enthalten.

### **Daten-Ausgänge**
- (Unbenannt): Ein Ausgang vom Typ `DWORD`, der das kombinierte Ergebnis enthält.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock nimmt 16 Quarter-Bytes entgegen und kombiniert sie zu einem 32-Bit-DWORD. Jedes Quarter-Byte wird entsprechend seiner Position im DWORD verschoben und dann mit den anderen verknüpft. Die Verschiebung erfolgt mithilfe von Konstanten (`quarterconst::SHIFT_QUARTER_XX`), die die Position jedes Quarter-Bytes im DWORD definieren.

## Technische Besonderheiten
- Verwendet Bitverschiebungen (`SHL`) und logische ODER-Operationen (`OR`), um die Quarter-Bytes korrekt zu kombinieren.
- Die Konvertierung von `BYTE` zu `DWORD` erfolgt mit `BYTE_TO_DWORD`.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Verarbeitet die Quarter-Bytes und kombiniert sie zu einem DWORD.
3. **Complete**: Sendet das `CNF`-Ereignis und stellt das kombinierte DWORD bereit.

## Anwendungsszenarien
- Datenkomprimierung: Kombination von mehreren kleinen Datenpaketen zu einem größeren.
- Kommunikationsprotokolle: Verarbeitung von Daten, die in kleineren Einheiten übertragen werden.
- Signalverarbeitung: Zusammenfassung von Teilen eines Signals zu einem vollständigen Wert.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Bausteine könnten `BYTE_TO_WORD` oder `WORD_TO_DWORD` sein, die jedoch weniger Flexibilität bieten, da sie nur feste Größen kombinieren.
- `ASSEMBLE_DWORD_FROM_QUARTERS` bietet mehr Kontrolle über die Position jedes einzelnen Bits im resultierenden DWORD.


## Zugehörige Übungen

* [Uebung_060](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_060.md)

## Fazit
Der `ASSEMBLE_DWORD_FROM_QUARTERS`-Funktionsblock ist ein leistungsfähiges Werkzeug zur Kombination von 16 Quarter-Bytes zu einem DWORD. Durch seine flexible und präzise Arbeitsweise eignet er sich ideal für Anwendungen, bei denen Daten in kleineren Einheiten vorliegen und zu einer größeren Einheit zusammengefasst werden müssen.