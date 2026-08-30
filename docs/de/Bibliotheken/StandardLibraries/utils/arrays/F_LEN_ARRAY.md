# F_LEN_ARRAY

![F_LEN_ARRAY](F_LEN_ARRAY.svg)

* * * * * * * * * *

## Einleitung

Der `F_LEN_ARRAY` ist ein einfacher Funktionsbaustein, der die Länge (Anzahl der Elemente) einer gewählten Dimension eines Arrays beliebigen Typs zurückgibt. Er ergänzt die Standardfunktionen `UPPER_BOUND`/`LOWER_BOUND` um eine direkt nutzbare Längenberechnung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Löst die Berechnung aus, trägt `ARR` und `DIM`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt den Abschluss, trägt `OUT`.

### **Daten-Eingänge**

- **ARR** (ANY_DERIVED): Das Array, dessen Länge ermittelt werden soll.
- **DIM** (ANY_INT, Default `DINT#1`): Die zu betrachtende Array-Dimension (bei mehrdimensionalen Arrays).

### **Daten-Ausgänge**

- **OUT** (ANY_INT): Die Länge der gewählten Dimension, also Anzahl der Elemente.

## Funktionsweise

Der Baustein ist als `SimpleFB` mit einem einzelnen ECC-Zustand implementiert. Bei `REQ` berechnet die Algorithmus-ST-Anweisung `OUT := ADD(SUB(UPPER_BOUND(ARR, DIM), LOWER_BOUND(ARR, DIM)), 1)` — also die obere minus die untere Indexgrenze der gewählten Dimension, plus 1 (da beide Grenzen inklusive sind). Anschließend wird `CNF` ausgelöst.

## Technische Besonderheiten

- **`ANY_DERIVED`-Eingang**: `ARR` akzeptiert Arrays beliebigen Elementtyps und beliebiger Dimensionalität.
- **Dimensionsauswahl über `DIM`**: Bei mehrdimensionalen Arrays kann über `DIM` gezielt die Länge einer bestimmten Dimension abgefragt werden; Standardwert ist die erste Dimension (`DINT#1`).
- **Basiert auf `UPPER_BOUND`/`LOWER_BOUND`**: Der Baustein ist eine direkte Kombination dieser beiden IEC-61131-3-Standardfunktionen und spart deren manuelle Verrechnung.

## Zustandsübersicht

Zustandslos: jedes `REQ` führt unmittelbar zur Berechnung und zu `CNF`.

## Anwendungsszenarien

- **Dynamische Array-Verarbeitung**: Schleifen über ein Array, dessen tatsächliche Größe erst zur Laufzeit (z. B. abhängig vom Aufrufer) bekannt ist.
- **Plausibilitätsprüfung**: Vergleich der tatsächlichen Array-Länge mit einer erwarteten Größe, bevor auf einzelne Elemente zugegriffen wird.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **`UPPER_BOUND`/`LOWER_BOUND`**: die beiden Standardfunktionen, aus denen `F_LEN_ARRAY` seine Berechnung zusammensetzt.

## Fazit

`F_LEN_ARRAY` liefert eine einfache, direkt nutzbare Längenermittlung für Arrays beliebigen Typs und einer wählbaren Dimension, ohne dass `UPPER_BOUND`/`LOWER_BOUND` manuell miteinander verrechnet werden müssen.
