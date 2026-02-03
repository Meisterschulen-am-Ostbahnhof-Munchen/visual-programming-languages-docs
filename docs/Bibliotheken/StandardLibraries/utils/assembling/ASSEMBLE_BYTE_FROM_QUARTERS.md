# ASSEMBLE_BYTE_FROM_QUARTERS

## 🎧 Podcast

* [QUARTER](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/QUARTER-e36741d)

---- 
```{index} single: ASSEMBLE_BYTE_FROM_QUARTERS
```

![ASSEMBLE_BYTE_FROM_QUARTERS](https://github.com/user-attachments/assets/0c4e652e-a741-472a-b8d9-d7721c16cc9a)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ASSEMBLE_BYTE_FROM_QUARTERS` kombiniert vier einzelne Quarter-Bytes zu einem vollständigen Byte. Dies ist besonders nützlich in Szenarien, wo Daten in Teilen übertragen oder verarbeitet werden müssen und anschließend wieder zusammengesetzt werden sollen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Kombination der Quarter-Bytes zu einem Byte. Wird mit den vier Quarter-Bytes (`QUARTER_BYTE_00` bis `QUARTER_BYTE_03`) verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert die erfolgreiche Zusammenführung der Quarter-Bytes zu einem Byte.

### **Daten-Eingänge**
- `QUARTER_BYTE_00`: Erstes Quarter-Byte (niedrigstwertige Bits).
- `QUARTER_BYTE_01`: Zweites Quarter-Byte.
- `QUARTER_BYTE_02`: Drittes Quarter-Byte.
- `QUARTER_BYTE_03`: Viertes Quarter-Byte (höchstwertige Bits).

### **Daten-Ausgänge**
- `BYTE`: Das zusammengesetzte Byte als Ergebnis der Kombination der vier Quarter-Bytes.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock nimmt vier Quarter-Bytes entgegen und kombiniert sie zu einem vollständigen Byte. Dabei werden die einzelnen Quarter-Bytes mittels Bit-Shift-Operationen (`SHL`) an die richtige Position im resultierenden Byte verschoben und durch logische ODER-Verknüpfungen (`OR`) zusammengefügt. Die genauen Verschiebungen werden durch Konstanten (`quarterconst::SHIFT_QUARTER_00` bis `quarterconst::SHIFT_QUARTER_03`) definiert.

## Technische Besonderheiten
- Verwendet Bit-Shift-Operationen (`SHL`) und logische ODER-Verknüpfungen (`OR`) zur Kombination der Quarter-Bytes.
- Die Verschiebungspositionen sind als Konstanten definiert, was eine flexible Anpassung ermöglicht.

## Zustandsübersicht
1. **Initialisierung**: Der Funktionsblock wird initialisiert und wartet auf das `REQ`-Ereignis.
2. **Verarbeitung**: Bei Empfang von `REQ` werden die vier Quarter-Bytes verarbeitet und zum resultierenden Byte kombiniert.
3. **Bestätigung**: Nach erfolgreicher Kombination wird das `CNF`-Ereignis ausgelöst und das resultierende Byte ausgegeben.

## Anwendungsszenarien
- **Datenkommunikation**: Kombination von in Teilen übertragenen Daten zu einem vollständigen Byte.
- **Datenverarbeitung**: Verarbeitung von Daten, die in kleineren Einheiten vorliegen, aber als Ganzes benötigt werden.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Bit-Manipulations-Funktionsblöcken bietet `ASSEMBLE_BYTE_FROM_QUARTERS` eine spezialisierte und optimierte Lösung für die Kombination von Quarter-Bytes.
- Andere Blöcke könnten ähnliche Funktionalität bieten, sind jedoch oft weniger spezifisch und erfordern mehr Konfiguration.


## Zugehörige Übungen

* [Uebung_056](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_056.md)

## Fazit
Der `ASSEMBLE_BYTE_FROM_QUARTERS`-Funktionsblock ist eine effiziente und spezialisierte Lösung für die Kombination von vier Quarter-Bytes zu einem vollständigen Byte. Durch die Verwendung von Bit-Shift- und logischen Operationen bietet er eine performante und flexible Möglichkeit zur Datenverarbeitung in entsprechenden Anwendungsszenarien.