# ADD_4

```{index} single: ADD_4
```

![ADD_4](https://user-images.githubusercontent.com/116869307/214143055-ad68b786-ea59-490e-9e7b-c43c007e0ae7.png)

* * * * * * * * * *

## Einleitung
Der **ADD_4** ist ein leistungsfähiger Funktionsbaustein zur Summation von vier Werten, entwickelt unter EPL-2.0 Lizenz. Als Teil der GEN_ADD-Klasse bietet Version 1.0 eine typsichere Implementierung gemäß IEC 61131-3 Standard.

![ADD_4](ADD_4.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Berechnungsanforderung (mit vier Eingabewerten)

### **Ereignis-Ausgänge**
- `CNF`: Berechnungsbestätigung (mit Summenergebnis)

### **Daten-Eingänge**
- `IN1` (ANY_MAGNITUDE): Erster Summand
- `IN2` (ANY_MAGNITUDE): Zweiter Summand
- `IN3` (ANY_MAGNITUDE): Dritter Summand
- `IN4` (ANY_MAGNITUDE): Vierter Summand

### **Daten-Ausgänge**
- `OUT` (ANY_MAGNITUDE): Ergebnis der Addition (IN1+IN2+IN3+IN4)

## Funktionale Merkmale

1. **Berechnungsauslösung**:
   - Einzelnes `REQ`-Ereignis verarbeitet alle vier Eingänge
   - Parallele Werterfassung

2. **Typhandling**:
   - Automatische Typkonvertierung bei gemischten Eingängen
   - Ergebnis im "größten" Eingangstyp

3. **Berechnungsreihenfolge**:
   - Mathematisch assoziativ (IN1+(IN2+(IN3+IN4)))
   - Garantierte reproduzierbare Ergebnisse

## Technische Spezifikationen

✔ **Vier-Eingang-Addition** in einer Operation
✔ **Volle ANY_MAGNITUDE-Unterstützung**
✔ **Optimierte Berechnungsperformance**
✔ **Deterministisches Verhalten**

## Unterstützte Datentypen

| Kategorie      | Beispiele               |
|----------------|-------------------------|
| Ganzzahlen     | INT, DINT, UDINT       |
| Fließkomma     | REAL, LREAL            |
| Zeitwerte      | TIME, LTIME            |
| Spezialtypen   | DATE_AND_TIME          |

## Anwendungsszenarien

- **Energiemonitoring**: Summierung von Verbrauchern
- **Produktionskontrolle**: Mengenerfassung mehrerer Linien
- **Messdatenanalyse**: Aggregation von Sensorwerten
- **Robotersteuerung**: Mehrdimensionale Positionsberechnung

## Vergleich mit anderen Addierern

| Baustein | Eingänge | Vorteile |
|----------|----------|----------|
| ADD_2    | 2        | Einfachste Variante |
| ADD_3    | 3        | Kompromiss |
| ADD_4    | 4        | Höchste Integration |

## Fehlermanagement

- **Typkonflikte**: Ergebnis 0 bei Inkompatibilität
- **Überlauf**: Wrap-around je nach Datentyp
- **Statusrückmeldung**: Über begleitende Logik

## Fazit

Der ADD_4-Baustein bietet maximale Effizienz für Summationsaufgaben:

- Kompakte Vierfach-Berechnung
- Breiteste Typunterstützung
- Optimierte Performance

Ideal für komplexe Steuerungsanwendungen mit multiplen zu aggregierenden Werten. Die generische Implementierung als GEN_ADD ermöglicht höchste Flexibilität bei typsicherer Ausführung.