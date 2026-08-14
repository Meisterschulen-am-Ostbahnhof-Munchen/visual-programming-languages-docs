# F_SPLIT_DATE

![F_SPLIT_DATE](F_SPLIT_DATE.svg)

* * * * * * * * * *
## Einleitung

Der `F_SPLIT_DATE` zerlegt einen `DATE`-Wert in seine einzelnen Zeit-/Datumsbestandteile (`YEAR`, `MONTH`, `DAY`). Er ist die Umkehrung von [F_CONCAT_DATE](F_CONCAT_DATE.md), das dieselben Einzelbestandteile wieder zu einem `DATE`-Wert zusammenfügt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Löst die Zerlegung aus, trägt `IN`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt den Abschluss, trägt `YEAR`, `MONTH`, `DAY`.

### **Daten-Eingänge**

- **IN** (`DATE`): Der zu zerlegende Zeit-/Datumswert.

### **Daten-Ausgänge**

- **YEAR** (UINT): Jahr.
- **MONTH** (USINT): Monat.
- **DAY** (USINT): Tag.

## Funktionsweise

Bei Eintreffen von `REQ` wird `IN` in seine Einzelbestandteile zerlegt, die über `YEAR`, `MONTH`, `DAY` ausgegeben werden. Anschließend wird `CNF` ausgelöst.

## Technische Besonderheiten

- **Feste Ausgabetypen**: Anders als bei [F_CONCAT_DATE](F_CONCAT_DATE.md) (generisch `ANY_INT`) sind die Ausgänge hier auf konkrete, für den jeweiligen Wertebereich passend gewählte Ganzzahltypen festgelegt (z. B. `USINT` für Monat/Tag, deren Wertebereich klein ist).

## Zustandsübersicht

Zustandslos: jedes `REQ` führt unmittelbar zur Zerlegung und zu `CNF`.

## Anwendungsszenarien

- **Anzeige/Weiterverarbeitung einzelner Zeit-/Datumsbestandteile**, z. B. für eine formatierte Anzeige auf einem Panel oder für Berechnungen, die nur einen bestimmten Bestandteil benötigen.
- **Protokollierung**: Aufschlüsselung eines Zeitstempels in seine Einzelwerte für strukturierte Log-Ausgaben.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[F_CONCAT_DATE](F_CONCAT_DATE.md)**: die Umkehrrichtung — fügt Einzelbestandteile zu einem `DATE`-Wert zusammen.

## Fazit

`F_SPLIT_DATE` liefert eine einfache, direkte Zerlegung eines `DATE`-Werts in seine Einzelbestandteile und ergänzt damit die entsprechende Zusammenführungsfunktion [F_CONCAT_DATE](F_CONCAT_DATE.md).
