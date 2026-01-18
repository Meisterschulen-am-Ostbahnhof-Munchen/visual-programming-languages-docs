# LED_COLOURS

```{index} single: LED_COLOURS
```

* * * * * * * * * *
## Einleitung
LED_COLOURS ist eine globale Konstantendefinition, die standardisierte Farbwerte für LED-Anzeigen bereitstellt. Diese Konstanten werden in logiBUS-Systemen zur einheitlichen Steuerung von farbigen LED-Ausgängen verwendet.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*Keine Ereigniseingänge vorhanden*

### **Ereignis-Ausgänge**
*Keine Ereignisausgänge vorhanden*

### **Daten-Eingänge**
*Keine Dateneingänge vorhanden*

### **Daten-Ausgänge**
*Keine Datenausgänge vorhanden*

### **Adapter**
*Keine Adapter vorhanden*

## Funktionsweise
LED_COLOURS definiert eine Sammlung globaler Konstanten vom Typ UINT (16-Bit vorzeichenlose Ganzzahl), die verschiedene LED-Farben repräsentieren. Jede Farbe ist einem festen numerischen Wert zugeordnet:

- LED_RED: 1
- LED_YELLOW: 2
- LED_ORANGE: 3
- LED_GREEN: 4
- LED_BLUE: 5
- LED_WHITE: 6
- LED_MAGENTA: 7
- LED_CYAN: 8

## Technische Besonderheiten
- Alle Konstanten sind vom Typ UINT (16-Bit unsigned integer)
- Wertebereich: 1-8 für die definierten Farben
- Konstanten sind zur Kompilierzeit festgelegt und unveränderlich
- Teil des logiBUS::io::DO_LED Packages

## Zustandsübersicht
*Da es sich um statische Konstanten handelt, existiert kein Zustandsmodell*

## Anwendungsszenarien
- Farbkodierung in Maschinensteuerungen
- Statusanzeigen mit farbigen LEDs
- Vereinheitlichung der Farbsteuerung in verteilten Systemen
- Visualisierung von Betriebszuständen in Industrieanlagen

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu Funktionsblöcken mit dynamischem Verhalten handelt es sich hier um rein statische Konstantendefinitionen. Ähnliche Konstrukte wären:
- ENUM-Datentypen für Farbdefinitionen
- #define-Präprozessoranweisungen in C/C++
- Konstanten-Blöcke in anderen IEC 61131-Sprachen

## Fazit
LED_COLOURS bietet eine standardisierte und wartungsfreundliche Lösung für die Farbsteuerung von LED-Anzeigen in logiBUS-Systemen. Durch die zentrale Definition werden Inkonsistenzen vermieden und die Code-Wiederverwendbarkeit erhöht.