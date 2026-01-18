# F_USINT_TO_ULINT

```{index} single: F_USINT_TO_ULINT
```

<img width="1466" height="214" alt="F_USINT_TO_ULINT" src="https://github.com/user-attachments/assets/93d99220-51d0-4f22-9315-b8380b7daeae" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_USINT_TO_ULINT` dient der Konvertierung eines `USINT`-Wertes (8-Bit unsigned integer) in einen `ULINT`-Wert (64-Bit unsigned integer). Diese Konvertierung ist nützlich, wenn Daten zwischen Systemen mit unterschiedlichen Wortbreiten ausgetauscht oder verarbeitet werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Ausführung der Konvertierung. Dieser Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert den Abschluss der Konvertierung. Dieser Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- `IN` (USINT): Der Eingangswert, der konvertiert werden soll.

### **Daten-Ausgänge**
- `OUT` (ULINT): Der konvertierte Ausgangswert.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt eine direkte Konvertierung des Eingangswertes `IN` vom Typ `USINT` in den Ausgangswert `OUT` vom Typ `ULINT` durch. Die Konvertierung erfolgt ohne Datenverlust, da der Wertebereich von `USINT` (0 bis 255) vollständig in `ULINT` (0 bis 2^64-1) abgebildet werden kann.

## Technische Besonderheiten
- Die Konvertierung erfolgt in einem einzigen Algorithmus (`REQ`), der bei Auslösung des `REQ`-Ereignisses ausgeführt wird.
- Der Algorithmus ist in ST (Structured Text) implementiert und besteht aus einer einfachen Zuweisung: `OUT := IN;`.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Datenkonvertierung in Steuerungssystemen, die unterschiedliche Wortbreiten verwenden.
- Integration von Peripheriegeräten, die Daten in unterschiedlichen Formaten liefern.
- Allgemeine Typkonvertierung in IEC 61131-3-basierten Programmen.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_SINT_TO_LINT` oder `F_UINT_TO_UDINT` führen ähnliche Konvertierungen durch, jedoch zwischen anderen Datentypen.
- `F_USINT_TO_ULINT` ist spezifisch für die Konvertierung von 8-Bit zu 64-Bit unsigned integers optimiert.

## Fazit
Der Funktionsblock `F_USINT_TO_ULINT` bietet eine einfache und effiziente Möglichkeit, Werte vom Typ `USINT` in `ULINT` zu konvertieren. Durch seine klare Schnittstelle und direkte Funktionsweise ist er ideal für Anwendungen, die eine Typkonvertierung ohne zusätzliche Logik erfordern.
