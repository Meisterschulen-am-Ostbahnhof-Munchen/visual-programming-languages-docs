# F_WSTRING_AS_USINT

```{index} single: F_WSTRING_AS_USINT
```

<img width="1492" height="214" alt="F_WSTRING_AS_USINT" src="https://github.com/user-attachments/assets/8e64c350-6c28-45b7-9597-276c03f37b6b" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WSTRING_AS_USINT` dient der Konvertierung eines WSTRING-Wertes in einen USINT-Wert. Er ist Teil des Pakets `iec61131::conversion` und ermöglicht die einfache Umwandlung von breiten Zeichenketten in vorzeichenlose 8-Bit-Ganzzahlen.

![F_WSTRING_AS_USINT](F_WSTRING_AS_USINT.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung der Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (WSTRING): Die Eingabezeichenkette, die in einen USINT-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (USINT): Der Ergebniswert der Konvertierung als vorzeichenlose 8-Bit-Ganzzahl.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, wenn das Ereignis `REQ` ausgelöst wird. Die Konvertierung erfolgt mittels der Funktion `WSTRING_AS_USINT`, die den WSTRING-Eingabewert in einen USINT-Wert umwandelt. Nach Abschluss der Konvertierung wird das Ereignis `CNF` ausgelöst, und der Ergebniswert steht am Ausgang `OUT` zur Verfügung.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne zusätzliche Parameter.
- Der Funktionsblock ist für die Verwendung in IEC 61499-konformen Umgebungen optimiert.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Führt die Konvertierung durch.
3. **Done**: Sendet das `CNF`-Ereignis und stellt das Ergebnis bereit.

## Anwendungsszenarien
- Konvertierung von Zeichenketten in numerische Werte für Steuerungsanwendungen.
- Verwendung in Systemen, die Zeichenketten als Eingabe verwenden, aber numerische Verarbeitung erfordern.

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu generischen Konvertierungsbausteinen ist `F_WSTRING_AS_USINT` spezialisiert auf die Umwandlung von WSTRING zu USINT.
- Andere Bausteine könnten zusätzliche Parameter oder Fehlerbehandlung bieten, dieser Baustein ist jedoch auf Einfachheit und Effizienz ausgelegt.

## Fazit
Der `F_WSTRING_AS_USINT`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, WSTRING-Werte in USINT-Werte umzuwandeln. Seine klare Schnittstelle und direkte Funktionsweise machen ihn ideal für Anwendungen, die schnelle und unkomplizierte Konvertierungen benötigen.