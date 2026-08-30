# FB_TON_LTIME

![FB_TON_LTIME](FB_TON_LTIME.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `FB_TON_LTIME` ist die `LTIME`-Variante (64-Bit-Zeitdauer, Nanosekunden-Auflösung) des Standard-Timer-Bausteins `FB_TON` (Einschaltverzögerung). Er verhält sich funktional identisch zu `FB_TON`, verwendet für `PT`/`ET` jedoch den Datentyp `LTIME` statt `TIME`.

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

Q wird erst TRUE, wenn IN seit PT ununterbrochen TRUE war. Fällt IN vor Ablauf von PT zurück auf FALSE, bleibt Q FALSE. Intern hält der Baustein (analog zu `FB_TON`) die internen Hilfsvariablen `MEM` und `StartTime`, um Flankenwechsel von `IN` und den Startzeitpunkt der Zeitmessung zu verfolgen — mit `LTIME`-Auflösung statt `TIME`.

## Technische Besonderheiten

- **`LTIME` statt `TIME`**: Bietet 64-Bit-Auflösung in Nanosekunden statt der 32-Bit-Millisekundenauflösung von `TIME`, relevant für sehr lange oder sehr präzise Zeitmessungen.
- **Funktional identisch zu `FB_TON`**: Gleiches Timing-Verhalten, lediglich der Datentyp von `PT`/`ET` unterscheidet sich.

## Zustandsübersicht

Siehe `FB_TON` — identisches Zustandsverhalten, nur mit `LTIME`-Zeitwerten statt `TIME`.

## Anwendungsszenarien

- **Zeitmessungen mit sehr hoher Präzision oder sehr langer Dauer**, bei denen die Millisekundenauflösung bzw. der Wertebereich von `TIME` nicht ausreicht.
- **Konsistente `LTIME`-Verwendung** in Applikationen, die durchgehend mit `LTIME` statt `TIME` arbeiten, um Datentyp-Konvertierungen zu vermeiden.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **`FB_TON`**: dieselbe Funktion mit `TIME` statt `LTIME`.

## Fazit

`FB_TON_LTIME` liefert dieselbe Einschaltverzögerung-Funktionalität wie `FB_TON`, jedoch mit `LTIME`-Auflösung, und eignet sich für Applikationen, die durchgängig mit hochauflösenden Zeitwerten arbeiten.
