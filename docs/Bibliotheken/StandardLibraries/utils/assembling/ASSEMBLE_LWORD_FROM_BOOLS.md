# ASSEMBLE_LWORD_FROM_BOOLS

```{index} single: ASSEMBLE_LWORD_FROM_BOOLS
```

![ASSEMBLE_LWORD_FROM_BOOLS](https://github.com/user-attachments/assets/9df93a68-feb4-4868-8fbd-9aecbaab21a2)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ASSEMBLE_LWORD_FROM_BOOLS` kombiniert 64 einzelne BOOL-Werte zu einem einzigen LWORD-Datentyp. Dies ist besonders nützlich, wenn mehrere binäre Zustände in einer kompakten Form verarbeitet oder übertragen werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Kombination der 64 BOOL-Eingänge zu einem LWORD.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert die erfolgreiche Kombination der BOOL-Werte zu einem LWORD.

### **Daten-Eingänge**
64 BOOL-Eingänge (`BIT_00` bis `BIT_63`), die jeweils ein Bit im resultierenden LWORD repräsentieren.

### **Daten-Ausgänge**
- Ein LWORD, das aus den 64 BOOL-Eingängen zusammengesetzt wird.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock weist jedes der 64 Bits des LWORD-Ausgangs einem entsprechenden BOOL-Eingang zu. Bei Auslösung des `REQ`-Ereignisses werden alle BOOL-Eingänge gelesen und in das LWORD eingefügt. Das `CNF`-Ereignis signalisiert den Abschluss dieses Vorgangs.

## Technische Besonderheiten
- Verarbeitet 64 BOOL-Eingänge parallel.
- Direkte Bit-Zuordnung ohne zusätzliche Berechnungen.
- Effiziente Implementierung durch direkte Zuweisung der Bits.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Kombiniert die BOOL-Werte zu einem LWORD.
3. **Complete**: Sendet das `CNF`-Ereignis und gibt das kombinierte LWORD aus.

## Anwendungsszenarien
- Komprimierung mehrerer binärer Signale für die Übertragung.
- Verarbeitung von Bitmasken in Steuerungsanwendungen.
- Effiziente Speicherung von binären Zuständen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Ähnlich zu `BOOL_TO_*`-Funktionsblöcken, aber für 64 Bits optimiert.
- Bietet mehr Flexibilität als fest codierte Bit-Operationen.

## Fazit
Der `ASSEMBLE_LWORD_FROM_BOOLS`-Funktionsblock ist ein effizientes Werkzeug zur Kombination mehrerer BOOL-Werte in einen einzigen LWORD-Datentyp, ideal für Anwendungen mit hoher Bit-Dichte.