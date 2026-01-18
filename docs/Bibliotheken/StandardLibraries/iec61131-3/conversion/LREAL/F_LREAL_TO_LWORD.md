# F_LREAL_TO_LWORD

```{index} single: F_LREAL_TO_LWORD
```

<img width="1463" height="214" alt="F_LREAL_TO_LWORD" src="https://github.com/user-attachments/assets/a9ab04bc-b63c-4185-a4b8-dfb4db6ffa50" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LREAL_TO_LWORD` dient der Konvertierung eines LREAL-Wertes (64-Bit Gleitkommazahl) in einen LWORD-Wert (64-Bit vorzeichenlose Ganzzahl). Diese Konvertierung ist insbesondere in Szenarien erforderlich, in denen Gleitkommazahlen in eine binäre Darstellung umgewandelt werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Eingang ausgelöst, wird der Wert am Daten-Eingang `IN` gelesen und konvertiert.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der konvertierte Wert steht am Daten-Ausgang `OUT` zur Verfügung.

### **Daten-Eingänge**
- **IN** (LREAL): Der Eingangswert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (LWORD): Der konvertierte Ausgangswert.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem der LREAL-Wert am Eingang `IN` in einen LWORD-Wert umgewandelt wird. Die Konvertierung erfolgt direkt und ohne zusätzliche Parameter. Bei Auslösung des Ereignisses `REQ` wird der Algorithmus ausgeführt, der den Wert konvertiert und das Ereignis `CNF` ausgibt.

## Technische Besonderheiten
- Die Konvertierung erfolgt mittels der Funktion `LREAL_TO_LWORD`, die im Algorithmus des Funktionsblocks implementiert ist.
- Der Funktionsblock ist einfach und hat keine internen Zustände oder komplexe Logik.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Zustandsübergänge oder interne Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Konvertierung von Gleitkommazahlen in eine binäre Darstellung für die weitere Verarbeitung in anderen Systemen.
- Verwendung in Steuerungssystemen, wo Gleitkommawerte in eine für die Hardware verständliche Form umgewandelt werden müssen.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_REAL_TO_WORD` oder `F_DINT_TO_DWORD` führen ähnliche Konvertierungen durch, jedoch mit anderen Datentypen.
- `F_LREAL_TO_LWORD` ist spezifisch für die Konvertierung von 64-Bit Gleitkommazahlen in 64-Bit vorzeichenlose Ganzzahlen.

## Fazit
Der Funktionsblock `F_LREAL_TO_LWORD` bietet eine einfache und effiziente Möglichkeit, Gleitkommazahlen in eine binäre Darstellung umzuwandeln. Durch seine klare Schnittstelle und direkte Funktionsweise ist er ideal für Anwendungen, die solche Konvertierungen erfordern.
