# F_SPLIT_TOD

![F_SPLIT_TOD](F_SPLIT_TOD.svg)

* * * * * * * * * *
## Einleitung

Der `F_SPLIT_TOD` zerlegt einen `TIME_OF_DAY`-Wert in seine einzelnen Zeit-/Datumsbestandteile (`HOUR`, `MINUTE`, `SECOND`, `MILLISECOND`). Er ist die Umkehrung von [F_CONCAT_TOD](F_CONCAT_TOD.md), das dieselben Einzelbestandteile wieder zu einem `TIME_OF_DAY`-Wert zusammenfügt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Löst die Zerlegung aus, trägt `IN`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt den Abschluss, trägt `HOUR`, `MINUTE`, `SECOND`, `MILLISECOND`.

### **Daten-Eingänge**

- **IN** (`TIME_OF_DAY`): Der zu zerlegende Zeit-/Datumswert.

### **Daten-Ausgänge**

- **HOUR** (USINT): Stunde.
- **MINUTE** (USINT): Minute.
- **SECOND** (USINT): Sekunde.
- **MILLISECOND** (UINT): Millisekunde.

## Funktionsweise

Bei Eintreffen von `REQ` wird `IN` in seine Einzelbestandteile zerlegt, die über `HOUR`, `MINUTE`, `SECOND`, `MILLISECOND` ausgegeben werden. Anschließend wird `CNF` ausgelöst.

## Technische Besonderheiten

- **Feste Ausgabetypen**: Anders als bei [F_CONCAT_TOD](F_CONCAT_TOD.md) (generisch `ANY_INT`) sind die Ausgänge hier auf konkrete, für den jeweiligen Wertebereich passend gewählte Ganzzahltypen festgelegt (z. B. `USINT` für Monat/Tag, deren Wertebereich klein ist).

## Zustandsübersicht

Zustandslos: jedes `REQ` führt unmittelbar zur Zerlegung und zu `CNF`.

## Anwendungsszenarien

- **Anzeige/Weiterverarbeitung einzelner Zeit-/Datumsbestandteile**, z. B. für eine formatierte Anzeige auf einem Panel oder für Berechnungen, die nur einen bestimmten Bestandteil benötigen.
- **Protokollierung**: Aufschlüsselung eines Zeitstempels in seine Einzelwerte für strukturierte Log-Ausgaben.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[F_CONCAT_TOD](F_CONCAT_TOD.md)**: die Umkehrrichtung — fügt Einzelbestandteile zu einem `TIME_OF_DAY`-Wert zusammen.

## Fazit

`F_SPLIT_TOD` liefert eine einfache, direkte Zerlegung eines `TIME_OF_DAY`-Werts in seine Einzelbestandteile und ergänzt damit die entsprechende Zusammenführungsfunktion [F_CONCAT_TOD](F_CONCAT_TOD.md).
