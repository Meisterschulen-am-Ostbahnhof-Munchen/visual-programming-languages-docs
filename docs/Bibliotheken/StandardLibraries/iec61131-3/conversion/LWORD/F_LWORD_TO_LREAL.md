# F_LWORD_TO_LREAL

```{index} single: F_LWORD_TO_LREAL
```

<img width="1464" height="211" alt="F_LWORD_TO_LREAL" src="https://github.com/user-attachments/assets/89f93d44-7207-4ef1-ba65-ed61f446770f" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LWORD_TO_LREAL` dient der Konvertierung eines LWORD-Datenwerts (64-Bit Ganzzahl ohne Vorzeichen) in einen LREAL-Datenwert (64-Bit Gleitkommazahl nach IEEE 754). Dieser Baustein ist besonders nützlich in Anwendungen, wo eine direkte Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Bei diesem Ereignis wird der Eingangswert `IN` verarbeitet.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung und gibt den konvertierten Wert `OUT` aus.

### **Daten-Eingänge**
- **IN** (LWORD): Der Eingangswert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (LREAL): Der Ergebniswert der Konvertierung.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses wird der Algorithmus ausgeführt, der den `IN`-Wert vom Typ LWORD in einen LREAL-Wert konvertiert. Das Ergebnis wird über den `OUT`-Ausgang ausgegeben und das `CNF`-Ereignis signalisiert die erfolgreiche Konvertierung.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne zusätzliche Parameter.
- Der Baustein ist für die Verwendung in Echtzeitsystemen optimiert.

## Zustandsübersicht
Der Funktionsblock hat einen einfachen Zustandsautomaten:
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Führt die Konvertierung durch.
3. **Complete**: Sendet das `CNF`-Ereignis mit dem Ergebnis.

## Anwendungsszenarien
- Datenverarbeitung in Steuerungssystemen, wo LWORD-Werte in Gleitkommazahlen umgewandelt werden müssen.
- Integration in größere Funktionsblocknetzwerke, die gemischte Datentypen verarbeiten.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Bausteine wie `F_DWORD_TO_REAL` oder `F_WORD_TO_REAL` bieten Konvertierungen für kleinere Datentypen.
- `F_LWORD_TO_LREAL` ist spezifisch für 64-Bit Konvertierungen optimiert.

## Fazit
Der `F_LWORD_TO_LREAL` Funktionsblock ist ein effizientes Werkzeug zur direkten Konvertierung von 64-Bit Ganzahlen in Gleitkommazahlen. Seine einfache Schnittstelle und zuverlässige Funktionsweise machen ihn ideal für den Einsatz in komplexen Automatisierungslösungen.