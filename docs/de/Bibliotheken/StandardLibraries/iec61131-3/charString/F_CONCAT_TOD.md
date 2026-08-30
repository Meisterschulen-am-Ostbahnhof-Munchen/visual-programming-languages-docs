# F_CONCAT_TOD

![F_CONCAT_TOD](F_CONCAT_TOD.svg)

* * * * * * * * * *

## Einleitung

Der `F_CONCAT_TOD` fügt einzelne Zeit-/Datumsbestandteile (`HOUR`, `MINUTE`, `SECOND`, `MILLISECOND`) zu einem zusammengesetzten `TIME_OF_DAY`-Wert zusammen. Er ist die Umkehrung von [F_SPLIT_TOD](F_SPLIT_TOD.md), das denselben `TIME_OF_DAY`-Wert wieder in seine Einzelbestandteile zerlegt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Löst die Zusammenführung aus, trägt `HOUR`, `MINUTE`, `SECOND`, `MILLISECOND`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt den Abschluss, trägt `OUT`.

### **Daten-Eingänge**

- **HOUR** (ANY_INT): Stunde.
- **MINUTE** (ANY_INT): Minute.
- **SECOND** (ANY_INT): Sekunde.
- **MILLISECOND** (ANY_INT): Millisekunde.

### **Daten-Ausgänge**

- **OUT** (`TIME_OF_DAY`): Der aus den Einzelbestandteilen zusammengesetzte Wert.

## Funktionsweise

Bei Eintreffen von `REQ` werden die Eingangswerte `HOUR`, `MINUTE`, `SECOND`, `MILLISECOND` zu einem `TIME_OF_DAY`-Wert kombiniert und über `OUT` ausgegeben. Anschließend wird `CNF` ausgelöst.

## Technische Besonderheiten

- **`ANY_INT`-Eingänge**: Die Zeit-/Datumsbestandteile akzeptieren beliebige Ganzzahltypen, was die Verdrahtung mit unterschiedlich typisierten Quellwerten vereinfacht.
- **Keine Bereichsprüfung dokumentiert**: Der Baustein geht von plausiblen Eingabewerten aus (z. B. `MONTH` 1–12); eine explizite Validierung obliegt dem Aufrufer.

## Zustandsübersicht

Zustandslos: jedes `REQ` führt unmittelbar zur Zusammenführung und zu `CNF`.

## Anwendungsszenarien

- **Aufbau von Zeitstempeln** aus separat erfassten oder berechneten Einzelwerten, z. B. aus Sensordaten, Benutzereingaben oder Kommunikationsprotokollen.
- **Konfigurationsauswertung**: Zusammenführen von in einzelnen Variablen abgelegten Datums-/Zeitangaben zu einem verwendbaren `TIME_OF_DAY`-Wert.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[F_SPLIT_TOD](F_SPLIT_TOD.md)**: die Umkehrrichtung — zerlegt einen `TIME_OF_DAY`-Wert in seine Einzelbestandteile.
- **`F_CONCAT_DATE_TOD`**: kombiniert stattdessen einen bereits fertigen `DATE`- und `TIME_OF_DAY`-Wert zu `DATE_AND_TIME`, statt aus Einzelfeldern.

## Fazit

`F_CONCAT_TOD` liefert eine einfache, direkte Zusammenführung von Zeit-/Datumseinzelwerten zu einem `TIME_OF_DAY`-Wert und ergänzt damit die entsprechende Zerlegungsfunktion [F_SPLIT_TOD](F_SPLIT_TOD.md).
