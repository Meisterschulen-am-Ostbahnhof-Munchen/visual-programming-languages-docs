# FB_CTUD_DINT

```{index} single: FB_CTUD_DINT
```

<img width="1418" height="340" alt="FB_CTUD_DINT" src="https://github.com/user-attachments/assets/9e2492b2-42d8-4fe5-a22a-8cf85b070cef" />

* * * * * * * * * *
## Einleitung
Der FB_CTUD_DINT ist ein Funktionsblock, der als Aufwärts-/Abwärtszähler (Up Down Counter) mit DINT-Zählwert fungiert. Er ermöglicht das Zählen in beide Richtungen sowie das Zurücksetzen und Laden eines vordefinierten Wertes. Der Zähler ist besonders für Steuerungsanwendungen geeignet, bei denen eine flexible Zählfunktion benötigt wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung (triggert die Zähloperation)

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung (wird nach Abschluss der Zähloperation ausgelöst)

### **Daten-Eingänge**
- **CU** (BOOL): Zählt hoch (Count up)
- **CD** (BOOL): Zählt runter (Count down)
- **R** (BOOL): Setzt den Zähler zurück (Reset)
- **LD** (BOOL): Lädt den Preset-Wert (Load)
- **PV** (DINT): Preset-Wert (Preset value)

### **Daten-Ausgänge**
- **QU** (BOOL): Signalisiert, ob der Zählwert den Preset-Wert erreicht oder überschritten hat (Output up)
- **QD** (BOOL): Signalisiert, ob der Zählwert 0 erreicht oder unterschritten hat (Output down)
- **CV** (DINT): Aktueller Zählwert (Count value)

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt folgende Operationen aus, wenn das REQ-Ereignis eintritt:
1. **Reset (R)**: Setzt den Zählwert (CV) auf 0, wenn R aktiv ist.
2. **Load (LD)**: Lädt den Preset-Wert (PV) in den Zählwert (CV), wenn LD aktiv ist.
3. **Zählen (CU/CD)**:
   - Wenn CU aktiv ist und der Zählwert nicht den Maximalwert (2147483647) erreicht hat, wird der Zählwert um 1 erhöht.
   - Wenn CD aktiv ist und der Zählwert nicht den Minimalwert (-2147483648) erreicht hat, wird der Zählwert um 1 verringert.
4. **Ausgänge setzen**:
   - QU wird auf TRUE gesetzt, wenn der Zählwert den Preset-Wert erreicht oder überschreitet.
   - QD wird auf TRUE gesetzt, wenn der Zählwert 0 erreicht oder unterschreitet.

## Technische Besonderheiten
- Der Zählwert (CV) ist vom Typ DINT (32-Bit Ganzzahl mit Vorzeichen), was einen großen Zählbereich ermöglicht.
- Der Funktionsblock verhindert ein Überlaufen des Zählwerts durch Prüfung der Grenzwerte.
- Gleichzeitiges Aktivieren von CU und CD führt zu keiner Änderung des Zählwerts.

## Zustandsübersicht
Der Funktionsblock hat keinen internen Zustand im Sinne eines Zustandsautomaten. Die Logik wird bei jedem REQ-Ereignis neu ausgeführt.

## Anwendungsszenarien
- Produktionszählung (z.B. Stückzählung auf einem Fließband)
- Positionserfassung (z.B. in linearen Achsen)
- Ereigniszählung mit Möglichkeit zur Richtungsumkehr

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu einfachen Zählern (z.B. CTU oder CTD) bietet dieser Baustein beide Zählrichtungen in einem Block.
- Gegenüber Zählern mit kleinerem Datentyp (z.B. INT) bietet der DINT-Typ einen größeren Zählbereich.

## Fazit
Der FB_CTUD_DINT ist ein vielseitiger Zählbaustein für Anwendungen, die bidirektionale Zählfunktionen mit großem Zählbereich erfordern. Durch die integrierten Reset- und Load-Funktionen sowie die Statusausgänge QU und QD eignet er sich besonders für komplexe Steuerungsaufgaben.
