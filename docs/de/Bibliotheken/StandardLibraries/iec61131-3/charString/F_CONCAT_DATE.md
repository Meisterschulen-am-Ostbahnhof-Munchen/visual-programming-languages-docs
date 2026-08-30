# F_CONCAT_DATE

![F_CONCAT_DATE](F_CONCAT_DATE.svg)

* * * * * * * * * *

## Einleitung

Der `F_CONCAT_DATE` fügt einzelne Zeit-/Datumsbestandteile (`YEAR`, `MONTH`, `DAY`) zu einem zusammengesetzten `DATE`-Wert zusammen. Er ist die Umkehrung von [F_SPLIT_DATE](F_SPLIT_DATE.md), das denselben `DATE`-Wert wieder in seine Einzelbestandteile zerlegt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Löst die Zusammenführung aus, trägt `YEAR`, `MONTH`, `DAY`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt den Abschluss, trägt `OUT`.

### **Daten-Eingänge**

- **YEAR** (ANY_INT): Jahr.
- **MONTH** (ANY_INT): Monat.
- **DAY** (ANY_INT): Tag.

### **Daten-Ausgänge**

- **OUT** (`DATE`): Der aus den Einzelbestandteilen zusammengesetzte Wert.

## Funktionsweise

Bei Eintreffen von `REQ` werden die Eingangswerte `YEAR`, `MONTH`, `DAY` zu einem `DATE`-Wert kombiniert und über `OUT` ausgegeben. Anschließend wird `CNF` ausgelöst.

## Technische Besonderheiten

- **`ANY_INT`-Eingänge**: Die Zeit-/Datumsbestandteile akzeptieren beliebige Ganzzahltypen, was die Verdrahtung mit unterschiedlich typisierten Quellwerten vereinfacht.
- **Keine Bereichsprüfung dokumentiert**: Der Baustein geht von plausiblen Eingabewerten aus (z. B. `MONTH` 1–12); eine explizite Validierung obliegt dem Aufrufer.

## Zustandsübersicht

Zustandslos: jedes `REQ` führt unmittelbar zur Zusammenführung und zu `CNF`.

## Anwendungsszenarien

- **Aufbau von Zeitstempeln** aus separat erfassten oder berechneten Einzelwerten, z. B. aus Sensordaten, Benutzereingaben oder Kommunikationsprotokollen.
- **Konfigurationsauswertung**: Zusammenführen von in einzelnen Variablen abgelegten Datums-/Zeitangaben zu einem verwendbaren `DATE`-Wert.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[F_SPLIT_DATE](F_SPLIT_DATE.md)**: die Umkehrrichtung — zerlegt einen `DATE`-Wert in seine Einzelbestandteile.
- **`F_CONCAT_DATE_TOD`**: kombiniert stattdessen einen bereits fertigen `DATE`- und `TIME_OF_DAY`-Wert zu `DATE_AND_TIME`, statt aus Einzelfeldern.

## Fazit

`F_CONCAT_DATE` liefert eine einfache, direkte Zusammenführung von Zeit-/Datumseinzelwerten zu einem `DATE`-Wert und ergänzt damit die entsprechende Zerlegungsfunktion [F_SPLIT_DATE](F_SPLIT_DATE.md).
