# FB_TP_LTIME

![FB_TP_LTIME](FB_TP_LTIME.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `FB_TP_LTIME` ist die `LTIME`-Variante (64-Bit-Zeitdauer, Nanosekunden-Auflösung) des Standard-Timer-Bausteins `FB_TP` (Impuls). Er verhält sich funktional identisch zu `FB_TP`, verwendet für `PT`/`ET` jedoch den Datentyp `LTIME` statt `TIME`.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Startet die Ausführung, verknüpft mit `IN` und `PT`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt die Ausführung, verknüpft mit `Q` und `ET`.

### **Daten-Eingänge**

- **IN** (BOOL): Eingangssignal.
- **PT** (LTIME): Vorgabezeit.

### **Daten-Ausgänge**

- **Q** (BOOL): Ausgangssignal, siehe Funktionsweise.
- **ET** (LTIME): Verstrichene Zeit seit Start der Zeitmessung.

## Funktionsweise

Ein steigender Flankenwechsel von IN löst einen TRUE-Impuls der festen Dauer PT an Q aus, unabhängig davon, wie lange IN TRUE bleibt. Intern hält der Baustein (analog zu `FB_TP`) die internen Hilfsvariablen `MEM` und `StartTime`, um Flankenwechsel von `IN` und den Startzeitpunkt der Zeitmessung zu verfolgen — mit `LTIME`-Auflösung statt `TIME`.

## Technische Besonderheiten

- **`LTIME` statt `TIME`**: Bietet 64-Bit-Auflösung in Nanosekunden statt der 32-Bit-Millisekundenauflösung von `TIME`, relevant für sehr lange oder sehr präzise Zeitmessungen.
- **Funktional identisch zu `FB_TP`**: Gleiches Timing-Verhalten, lediglich der Datentyp von `PT`/`ET` unterscheidet sich.

## Zustandsübersicht

Siehe `FB_TP` — identisches Zustandsverhalten, nur mit `LTIME`-Zeitwerten statt `TIME`.

## Anwendungsszenarien

- **Zeitmessungen mit sehr hoher Präzision oder sehr langer Dauer**, bei denen die Millisekundenauflösung bzw. der Wertebereich von `TIME` nicht ausreicht.
- **Konsistente `LTIME`-Verwendung** in Applikationen, die durchgehend mit `LTIME` statt `TIME` arbeiten, um Datentyp-Konvertierungen zu vermeiden.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **`FB_TP`**: dieselbe Funktion mit `TIME` statt `LTIME`.

## Fazit

`FB_TP_LTIME` liefert dieselbe Impuls-Funktionalität wie `FB_TP`, jedoch mit `LTIME`-Auflösung, und eignet sich für Applikationen, die durchgängig mit hochauflösenden Zeitwerten arbeiten.
