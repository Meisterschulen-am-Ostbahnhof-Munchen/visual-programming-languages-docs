# F_CONCAT_LTOD

![F_CONCAT_LTOD](F_CONCAT_LTOD.svg)

* * * * * * * * * *
## Einleitung

Der `F_CONCAT_LTOD` fügt einzelne Zeit-/Datumsbestandteile (`HOUR`, `MINUTE`, `SECOND`, `MILLISECOND`) zu einem zusammengesetzten `LTIME_OF_DAY`-Wert zusammen. Er ist die Umkehrung von [F_SPLIT_LTOD](F_SPLIT_LTOD.md), das denselben `LTIME_OF_DAY`-Wert wieder in seine Einzelbestandteile zerlegt.

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

- **OUT** (`LTIME_OF_DAY`): Der aus den Einzelbestandteilen zusammengesetzte Wert.

## Funktionsweise

Bei Eintreffen von `REQ` werden die Eingangswerte `HOUR`, `MINUTE`, `SECOND`, `MILLISECOND` zu einem `LTIME_OF_DAY`-Wert kombiniert und über `OUT` ausgegeben. Anschließend wird `CNF` ausgelöst.

## Technische Besonderheiten

- **`ANY_INT`-Eingänge**: Die Zeit-/Datumsbestandteile akzeptieren beliebige Ganzzahltypen, was die Verdrahtung mit unterschiedlich typisierten Quellwerten vereinfacht.
- **Keine Bereichsprüfung dokumentiert**: Der Baustein geht von plausiblen Eingabewerten aus (z. B. `MONTH` 1–12); eine explizite Validierung obliegt dem Aufrufer.

## Zustandsübersicht

Zustandslos: jedes `REQ` führt unmittelbar zur Zusammenführung und zu `CNF`.

## Anwendungsszenarien

- **Aufbau von Zeitstempeln** aus separat erfassten oder berechneten Einzelwerten, z. B. aus Sensordaten, Benutzereingaben oder Kommunikationsprotokollen.
- **Konfigurationsauswertung**: Zusammenführen von in einzelnen Variablen abgelegten Datums-/Zeitangaben zu einem verwendbaren `LTIME_OF_DAY`-Wert.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[F_SPLIT_LTOD](F_SPLIT_LTOD.md)**: die Umkehrrichtung — zerlegt einen `LTIME_OF_DAY`-Wert in seine Einzelbestandteile.
- **`F_CONCAT_DATE_TOD`**: kombiniert stattdessen einen bereits fertigen `DATE`- und `TIME_OF_DAY`-Wert zu `DATE_AND_TIME`, statt aus Einzelfeldern.

## Fazit

`F_CONCAT_LTOD` liefert eine einfache, direkte Zusammenführung von Zeit-/Datumseinzelwerten zu einem `LTIME_OF_DAY`-Wert und ergänzt damit die entsprechende Zerlegungsfunktion [F_SPLIT_LTOD](F_SPLIT_LTOD.md).
