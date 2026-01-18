# F_USINT_TO_BCD_BYTE

```{index} single: F_USINT_TO_BCD_BYTE
```

<img width="1293" height="181" alt="F_USINT_TO_BCD_BYTE" src="https://github.com/user-attachments/assets/80d3e282-af2a-4b59-89db-9d093b6ef103" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_USINT_TO_BCD_BYTE` dient der Konvertierung eines vorzeichenlosen 8-Bit-Integer-Werts (USINT) in ein BCD-kodiertes Byte (BYTE). BCD (Binary Coded Decimal) ist eine Kodierung, bei der jede Dezimalziffer durch vier Bits dargestellt wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Ein vorzeichenloser 8-Bit-Integer-Wert (USINT), der in BCD umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT**: Das Ergebnis der Konvertierung als BCD-kodiertes Byte (BYTE).

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, wenn das Ereignis `REQ` eintritt. Der Algorithmus wandelt den Eingabewert `IN` von USINT in ein BCD-kodiertes Byte um und speichert das Ergebnis in `OUT`. Anschließend wird das Ereignis `CNF` ausgelöst, um den Abschluss der Konvertierung zu signalisieren.

## Technische Besonderheiten
- Der Funktionsblock ist deterministisch und führt keine internen Zustandsänderungen durch.
- Die Konvertierung erfolgt direkt über die Funktion `USINT_TO_BCD_BYTE`.

## Zustandsübersicht
Der Funktionsblock hat keinen internen Zustand. Die Konvertierung wird bei jedem `REQ`-Ereignis neu durchgeführt.

## Anwendungsszenarien
- Anzeigesteuerung für siebensegmentige Displays.
- Kommunikation mit Geräten, die BCD-kodierte Daten erwarten.
- Datenkonvertierung in Steuerungssystemen, die BCD-Format erfordern.

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu generischen Konvertierungsblöcken ist `F_USINT_TO_BCD_BYTE` spezialisiert auf die Umwandlung von USINT zu BCD.
- Andere Blöcke könnten zusätzliche Funktionen wie Fehlerbehandlung oder unterschiedliche Kodierungen bieten, sind aber oft komplexer.

## Fazit
Der Funktionsblock `F_USINT_TO_BCD_BYTE` ist ein effizientes Werkzeug für die spezifische Aufgabe der Konvertierung von USINT zu BCD. Seine Einfachheit und Determinismus machen ihn zu einer zuverlässigen Wahl in Steuerungsanwendungen, die BCD-kodierte Daten erfordern.
