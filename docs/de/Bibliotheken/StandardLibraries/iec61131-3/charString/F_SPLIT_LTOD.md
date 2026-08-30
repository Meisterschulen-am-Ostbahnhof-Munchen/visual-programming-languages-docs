# F_SPLIT_LTOD

![F_SPLIT_LTOD](F_SPLIT_LTOD.svg)

* * * * * * * * * *

## Einleitung

Der `F_SPLIT_LTOD` zerlegt einen `LTIME_OF_DAY`-Wert in seine einzelnen Zeit-/Datumsbestandteile (`HOUR`, `MINUTE`, `SECOND`, `MILLISECOND`). Er ist die Umkehrung von [F_CONCAT_LTOD](F_CONCAT_LTOD.md), das dieselben Einzelbestandteile wieder zu einem `LTIME_OF_DAY`-Wert zusammenfügt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Löst die Zerlegung aus, trägt `IN`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt den Abschluss, trägt `HOUR`, `MINUTE`, `SECOND`, `MILLISECOND`.

### **Daten-Eingänge**

- **IN** (`LTIME_OF_DAY`): Der zu zerlegende Zeit-/Datumswert.

### **Daten-Ausgänge**

- **HOUR** (USINT): Stunde.
- **MINUTE** (USINT): Minute.
- **SECOND** (USINT): Sekunde.
- **MILLISECOND** (UDINT): Millisekunde.

## Funktionsweise

Bei Eintreffen von `REQ` wird `IN` in seine Einzelbestandteile zerlegt, die über `HOUR`, `MINUTE`, `SECOND`, `MILLISECOND` ausgegeben werden. Anschließend wird `CNF` ausgelöst.

## Technische Besonderheiten

- **Feste Ausgabetypen**: Anders als bei [F_CONCAT_LTOD](F_CONCAT_LTOD.md) (generisch `ANY_INT`) sind die Ausgänge hier auf konkrete, für den jeweiligen Wertebereich passend gewählte Ganzzahltypen festgelegt (z. B. `USINT` für Monat/Tag, deren Wertebereich klein ist).

## Zustandsübersicht

Zustandslos: jedes `REQ` führt unmittelbar zur Zerlegung und zu `CNF`.

## Anwendungsszenarien

- **Anzeige/Weiterverarbeitung einzelner Zeit-/Datumsbestandteile**, z. B. für eine formatierte Anzeige auf einem Panel oder für Berechnungen, die nur einen bestimmten Bestandteil benötigen.
- **Protokollierung**: Aufschlüsselung eines Zeitstempels in seine Einzelwerte für strukturierte Log-Ausgaben.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[F_CONCAT_LTOD](F_CONCAT_LTOD.md)**: die Umkehrrichtung — fügt Einzelbestandteile zu einem `LTIME_OF_DAY`-Wert zusammen.

## Fazit

`F_SPLIT_LTOD` liefert eine einfache, direkte Zerlegung eines `LTIME_OF_DAY`-Werts in seine Einzelbestandteile und ergänzt damit die entsprechende Zusammenführungsfunktion [F_CONCAT_LTOD](F_CONCAT_LTOD.md).
