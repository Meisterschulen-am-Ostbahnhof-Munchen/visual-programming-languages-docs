# F_SPLIT_LDT

![F_SPLIT_LDT](F_SPLIT_LDT.svg)

* * * * * * * * * *

## Einleitung

Der `F_SPLIT_LDT` zerlegt einen `LDATE_AND_TIME`-Wert in seine einzelnen Zeit-/Datumsbestandteile (`YEAR`, `MONTH`, `DAY`, `HOUR`, `MINUTE`, `SECOND`, `MILLISECOND`). Er ist die Umkehrung von [F_CONCAT_LDT](F_CONCAT_LDT.md), das dieselben Einzelbestandteile wieder zu einem `LDATE_AND_TIME`-Wert zusammenfügt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Löst die Zerlegung aus, trägt `IN`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt den Abschluss, trägt `YEAR`, `MONTH`, `DAY`, `HOUR`, `MINUTE`, `SECOND`, `MILLISECOND`.

### **Daten-Eingänge**

- **IN** (`LDATE_AND_TIME`): Der zu zerlegende Zeit-/Datumswert.

### **Daten-Ausgänge**

- **YEAR** (UINT): Jahr.
- **MONTH** (USINT): Monat.
- **DAY** (USINT): Tag.
- **HOUR** (USINT): Stunde.
- **MINUTE** (USINT): Minute.
- **SECOND** (USINT): Sekunde.
- **MILLISECOND** (UDINT): Millisekunde.

## Funktionsweise

Bei Eintreffen von `REQ` wird `IN` in seine Einzelbestandteile zerlegt, die über `YEAR`, `MONTH`, `DAY`, `HOUR`, `MINUTE`, `SECOND`, `MILLISECOND` ausgegeben werden. Anschließend wird `CNF` ausgelöst.

## Technische Besonderheiten

- **Feste Ausgabetypen**: Anders als bei [F_CONCAT_LDT](F_CONCAT_LDT.md) (generisch `ANY_INT`) sind die Ausgänge hier auf konkrete, für den jeweiligen Wertebereich passend gewählte Ganzzahltypen festgelegt (z. B. `USINT` für Monat/Tag, deren Wertebereich klein ist).

## Zustandsübersicht

Zustandslos: jedes `REQ` führt unmittelbar zur Zerlegung und zu `CNF`.

## Anwendungsszenarien

- **Anzeige/Weiterverarbeitung einzelner Zeit-/Datumsbestandteile**, z. B. für eine formatierte Anzeige auf einem Panel oder für Berechnungen, die nur einen bestimmten Bestandteil benötigen.
- **Protokollierung**: Aufschlüsselung eines Zeitstempels in seine Einzelwerte für strukturierte Log-Ausgaben.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[F_CONCAT_LDT](F_CONCAT_LDT.md)**: die Umkehrrichtung — fügt Einzelbestandteile zu einem `LDATE_AND_TIME`-Wert zusammen.

## Fazit

`F_SPLIT_LDT` liefert eine einfache, direkte Zerlegung eines `LDATE_AND_TIME`-Werts in seine Einzelbestandteile und ergänzt damit die entsprechende Zusammenführungsfunktion [F_CONCAT_LDT](F_CONCAT_LDT.md).
