# F_LEFT

```{index} single: F_LEFT
```

<img width="1279" height="207" alt="F_LEFT" src="https://github.com/user-attachments/assets/a5684213-fe32-44e3-a3b3-69bfaefab215" />

* * * * * * * * * *

## Einleitung
Der Funktionsblock `F_LEFT` extrahiert die linken `L` Zeichen aus der Eingabezeichenkette `IN`. Er ist Teil der Standard-Character- und String-Funktionen gemäß IEC 61131-3.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Extraktion der Zeichenkette. Wird mit den Daten-Eingängen `IN` und `L` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigt die erfolgreiche Extraktion. Wird mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (`ANY_STRING`): Die Eingabezeichenkette, aus der die linken Zeichen extrahiert werden sollen.
- **L** (`ANY_INT`): Die Anzahl der Zeichen, die von links extrahiert werden sollen.

### **Daten-Ausgänge**
- **OUT** (`ANY_STRING`): Die extrahierte Teilzeichenkette, bestehend aus den linken `L` Zeichen von `IN`.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Bei Auslösung des Ereignisses `REQ` extrahiert der Funktionsblock die ersten `L` Zeichen aus der Eingabezeichenkette `IN` und gibt das Ergebnis über `OUT` aus. Das Ereignis `CNF` signalisiert die erfolgreiche Ausführung.

## Technische Besonderheiten
- Unterstützt alle String-Typen (`ANY_STRING`).
- `L` muss ein gültiger Integer-Wert sein. Ist `L` größer als die Länge von `IN`, wird die gesamte Zeichenkette zurückgegeben.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Verarbeitet die Eingabe und extrahiert die Zeichen.
3. **Completed**: Sendet `CNF` mit dem Ergebnis.

## Anwendungsszenarien
- Extraktion von Präfixen aus Zeichenketten.
- Verkürzung von Strings für spezifische Anforderungen.

## Vergleich mit ähnlichen Bausteinen
- **F_RIGHT**: Extrahiert Zeichen von rechts.
- **F_MID**: Extrahiert Zeichen aus der Mitte einer Zeichenkette.

## Fazit
`F_LEFT` ist ein einfacher und effizienter Funktionsblock zur Extraktion von Teilzeichenketten aus dem Anfang eines Strings. Seine Verwendung ist intuitiv und erfüllt die Anforderungen gemäß IEC 61131-3.