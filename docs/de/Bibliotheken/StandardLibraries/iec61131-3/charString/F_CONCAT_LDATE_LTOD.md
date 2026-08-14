# F_CONCAT_LDATE_LTOD

![F_CONCAT_LDATE_LTOD](F_CONCAT_LDATE_LTOD.svg)

* * * * * * * * * *
## Einleitung

Der `F_CONCAT_LDATE_LTOD` verkettet ein Datum (`LDATE`) und eine Tageszeit (`LTIME_OF_DAY`) zu einem kombinierten `LDATE_AND_TIME`-Zeitstempel. Er ist das `L`-präfigierte (64-Bit-Auflösung) Gegenstück zu `F_CONCAT_DATE_TOD`.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Löst die Verkettung aus, trägt `IN1` und `IN2`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt den Abschluss, trägt `OUT`.

### **Daten-Eingänge**

- **IN1** (LDATE): Das Datum.
- **IN2** (LTIME_OF_DAY): Die Tageszeit.

### **Daten-Ausgänge**

- **OUT** (LDATE_AND_TIME): Der kombinierte Datums- und Zeitstempel.

## Funktionsweise

Bei Eintreffen von `REQ` werden `IN1` (Datum) und `IN2` (Tageszeit) zu einem `LDATE_AND_TIME`-Wert kombiniert und über `OUT` ausgegeben. Anschließend wird `CNF` ausgelöst.

## Technische Besonderheiten

- **`L`-Datentypen**: Verwendet die hochauflösenden `LDATE`/`LTIME_OF_DAY`/`LDATE_AND_TIME`-Typen mit Nanosekunden-Auflösung statt der klassischen `DATE`/`TIME_OF_DAY`/`DATE_AND_TIME`-Typen.

## Zustandsübersicht

Zustandslos: jedes `REQ` führt unmittelbar zur Verkettung und zu `CNF`.

## Anwendungsszenarien

- **Kombination separat erfasster hochauflösender Datums- und Zeitinformationen** in Steuerungssystemen, die durchgängig mit `L`-Zeittypen arbeiten.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **`F_CONCAT_DATE_TOD`**: dieselbe Funktion mit den klassischen `DATE`/`TIME_OF_DAY`/`DATE_AND_TIME`-Typen.
- **[F_CONCAT_LDT](F_CONCAT_LDT.md)**: kombiniert stattdessen Einzelfelder (`YEAR`, `MONTH`, … ) statt bereits fertiger `LDATE`/`LTIME_OF_DAY`-Werte.

## Fazit

`F_CONCAT_LDATE_LTOD` liefert die hochauflösende Variante der Datums-/Zeit-Verkettung und eignet sich für Applikationen, die konsequent mit `L`-Zeittypen arbeiten.
