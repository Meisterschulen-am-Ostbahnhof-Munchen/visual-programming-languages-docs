# FB_TOF_LTIME

![FB_TOF_LTIME](FB_TOF_LTIME.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `FB_TOF_LTIME` ist die `LTIME`-Variante (64-Bit-Zeitdauer, Nanosekunden-Auflösung) des Standard-Timer-Bausteins `FB_TOF` (Ausschaltverzögerung). Er verhält sich funktional identisch zu `FB_TOF`, verwendet für `PT`/`ET` jedoch den Datentyp `LTIME` statt `TIME`.

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

Q wird sofort TRUE, wenn IN auf TRUE wechselt. Wechselt IN auf FALSE, bleibt Q noch für die Dauer PT TRUE, bevor es auf FALSE zurückfällt. Intern hält der Baustein (analog zu `FB_TOF`) die internen Hilfsvariablen `MEM` und `StartTime`, um Flankenwechsel von `IN` und den Startzeitpunkt der Zeitmessung zu verfolgen — mit `LTIME`-Auflösung statt `TIME`.

## Technische Besonderheiten

- **`LTIME` statt `TIME`**: Bietet 64-Bit-Auflösung in Nanosekunden statt der 32-Bit-Millisekundenauflösung von `TIME`, relevant für sehr lange oder sehr präzise Zeitmessungen.
- **Funktional identisch zu `FB_TOF`**: Gleiches Timing-Verhalten, lediglich der Datentyp von `PT`/`ET` unterscheidet sich.

## Zustandsübersicht

Siehe `FB_TOF` — identisches Zustandsverhalten, nur mit `LTIME`-Zeitwerten statt `TIME`.

## Anwendungsszenarien

- **Zeitmessungen mit sehr hoher Präzision oder sehr langer Dauer**, bei denen die Millisekundenauflösung bzw. der Wertebereich von `TIME` nicht ausreicht.
- **Konsistente `LTIME`-Verwendung** in Applikationen, die durchgehend mit `LTIME` statt `TIME` arbeiten, um Datentyp-Konvertierungen zu vermeiden.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **`FB_TOF`**: dieselbe Funktion mit `TIME` statt `LTIME`.

## Fazit

`FB_TOF_LTIME` liefert dieselbe Ausschaltverzögerung-Funktionalität wie `FB_TOF`, jedoch mit `LTIME`-Auflösung, und eignet sich für Applikationen, die durchgängig mit hochauflösenden Zeitwerten arbeiten.
