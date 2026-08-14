# F_DAY_OF_WEEK

![F_DAY_OF_WEEK](F_DAY_OF_WEEK.svg)

* * * * * * * * * *
## Einleitung

Der `F_DAY_OF_WEEK` ermittelt aus einem Datum (`DATE`) den zugehörigen Wochentag als Zahl. Er ist ein einfacher Funktionsbaustein zur Kalenderberechnung nach IEC 61131-3.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Löst die Berechnung aus, trägt `IN`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt den Abschluss, trägt `OUT`.

### **Daten-Eingänge**

- **IN** (DATE): Das Eingabedatum.

### **Daten-Ausgänge**

- **OUT** (USINT): Der Wochentag (`0` = Sonntag, `1` = Montag, …, `6` = Samstag).

## Funktionsweise

Bei Eintreffen von `REQ` berechnet die Algorithmus-ST-Anweisung `OUT := DAY_OF_WEEK(IN)` den Wochentag von `IN` und gibt ihn über `OUT` aus. Anschließend wird `CNF` ausgelöst.

## Technische Besonderheiten

- **Kodierung `0`–`6`**: Sonntag ist `0`, Samstag ist `6` — diese Kodierung sollte beim Vergleich mit anderen, ggf. Montag-basierten Wochentagskonventionen beachtet werden.

## Zustandsübersicht

Zustandslos: jedes `REQ` führt unmittelbar zur Berechnung und zu `CNF`.

## Anwendungsszenarien

- **Wochentagsabhängige Steuerungslogik**: z. B. unterschiedliche Betriebsprogramme an Werktagen vs. Wochenenden.
- **Anzeige/Protokollierung**: Ausgabe des Wochentags neben einem Datum in Anzeigen oder Log-Einträgen.
- **Terminplanung**: Prüfung, ob ein berechnetes Datum auf einen bestimmten Wochentag fällt.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[F_SPLIT_DATE](F_SPLIT_DATE.md)**: zerlegt ein Datum in Jahr/Monat/Tag, berechnet aber keinen Wochentag.

## Fazit

`F_DAY_OF_WEEK` liefert eine einfache Kalenderberechnung zur Ermittlung des Wochentags aus einem `DATE`-Wert und eignet sich für wochentagsabhängige Steuerungs- und Anzeigelogik.
