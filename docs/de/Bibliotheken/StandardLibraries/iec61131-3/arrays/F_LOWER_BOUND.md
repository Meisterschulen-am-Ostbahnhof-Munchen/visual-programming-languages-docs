# F_LOWER_BOUND

![F_LOWER_BOUND](F_LOWER_BOUND.svg)

* * * * * * * * * *
## Einleitung

Der `F_LOWER_BOUND` liefert die untere Indexgrenze einer gewählten Dimension eines Arrays beliebigen Typs. Zusammen mit [F_UPPER_BOUND](F_UPPER_BOUND.md) bildet er die Grundlage für generische, größenunabhängige Array-Verarbeitung — z. B. wird `F_LEN_ARRAY` (siehe `utils::arrays`) aus beiden Grenzen berechnet.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Löst die Abfrage aus, trägt `ARR` und `DIM`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt den Abschluss, trägt `OUT`.

### **Daten-Eingänge**

- **ARR** (ANY_DERIVED): Das Array, dessen Indexgrenze ermittelt werden soll.
- **DIM** (ANY_INT, Default `UDINT#1`): Die zu betrachtende Array-Dimension, 1-basiert.

### **Daten-Ausgänge**

- **OUT** (ANY_INT): Der niedrigsten Index der gewählten Dimension.

## Funktionsweise

Bei Eintreffen von `REQ` ermittelt der Baustein die untere Indexgrenze der über `DIM` gewählten Dimension von `ARR` und gibt sie über `OUT` aus. Anschließend wird `CNF` ausgelöst.

## Technische Besonderheiten

- **`ANY_DERIVED`-Eingang**: `ARR` akzeptiert Arrays beliebigen Elementtyps und beliebiger Dimensionalität.
- **1-basierte Dimensionsauswahl**: `DIM = 1` bezeichnet die erste Dimension; bei mehrdimensionalen Arrays lässt sich so gezielt eine bestimmte Dimension abfragen.
- **Nicht zwingend `0`/größer-`0`**: IEC-61131-3-Arrays können mit beliebigen Indexgrenzen deklariert werden (auch negativ oder nicht bei `0` beginnend) — `F_LOWER_BOUND` liefert die tatsächlich deklarierte Grenze, keine Annahme über deren Wert.

## Zustandsübersicht

Zustandslos: jedes `REQ` führt unmittelbar zur Abfrage und zu `CNF`.

## Anwendungsszenarien

- **Generische Array-Verarbeitung**: Schleifen, die unabhängig von der tatsächlich deklarierten Größe/den Indexgrenzen eines Arrays über dessen Elemente iterieren.
- **Baustein für Längenberechnung**: `F_LEN_ARRAY` (`utils::arrays`) kombiniert `F_LOWER_BOUND` mit `F_UPPER_BOUND`, um die Elementanzahl einer Dimension zu berechnen.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[F_UPPER_BOUND](F_UPPER_BOUND.md)**: die jeweils andere Indexgrenze derselben Dimension.
- **`F_LEN_ARRAY`** (`utils::arrays`): berechnet aus `F_LOWER_BOUND` und `F_UPPER_BOUND` die Elementanzahl.

## Fazit

`F_LOWER_BOUND` liefert die untere Indexgrenze einer Array-Dimension und ist ein grundlegender Baustein für generische, größenunabhängige Array-Verarbeitung in IEC-61131-3-Applikationen.
