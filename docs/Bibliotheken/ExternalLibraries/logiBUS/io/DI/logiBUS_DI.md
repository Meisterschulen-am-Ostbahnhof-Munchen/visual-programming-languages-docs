# logiBUS_DI

```{index} single: logiBUS_DI
```

* * * * * * * * * *

## Einleitung

Die logiBUS_DI GlobalConstants-Definition stellt eine Sammlung von vordefinierten Konstanten für digitale Eingänge des logiBUS-Systems bereit. Diese Konstanten definieren die Pin-Zuordnungen für verschiedene digitale Eingangskanäle und werden zur Konfiguration von logiBUS-DI-Funktionsblöcken verwendet.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*Keine Ereigniseingänge vorhanden - handelt sich um eine Konstantendefinition*

### **Ereignis-Ausgänge**
*Keine Ereignisausgänge vorhanden - handelt sich um eine Konstantendefinition*

### **Daten-Eingänge**
*Keine Dateneingänge vorhanden - handelt sich um eine Konstantendefinition*

### **Daten-Ausgänge**
*Keine Datenausgänge vorhanden - handelt sich um eine Konstantendefinition*

### **Adapter**
*Keine Adapter vorhanden - handelt sich um eine Konstantendefinition*

## Funktionsweise

Die GlobalConstants-Definition logiBUS_DI stellt strukturierte Konstanten vom Typ `logiBUS_DI_S` bereit, die jeweils einen spezifischen Pin-Wert enthalten:

- **Input_I1** bis **Input_I9**: Definiert die digitalen Eingänge 1 bis 9 mit entsprechenden Pin-Nummern
- **Invalid**: Definiert einen ungültigen Pin mit dem Wert 255

Diese Konstanten werden als Initialisierungswerte für die Konfiguration von digitalen Eingängen im logiBUS-System verwendet.

## Technische Besonderheiten

- **Strukturtyp**: Alle Konstanten verwenden den strukturierten Datentyp `logiBUS_DI_S`
- **Pin-Bereich**: Gültige Pins reichen von 1-9, ungültige Konfiguration wird durch Pin 255 gekennzeichnet
- **Package-Zugehörigkeit**: Die Konstanten sind im Package `logiBUS::io::DI` organisiert
- **Initialisierung**: Alle Konstanten werden bei der Deklaration mit ihren Pin-Werten initialisiert

## Zustandsübersicht

Da es sich um eine reine Konstantendefinition handelt, gibt es keine Zustandsübergänge oder Zustandsautomaten.

## Anwendungsszenarien

- Konfiguration von digitalen Eingangsmodulen in logiBUS-Systemen
- Parametrierung von Funktionsblöcken, die digitale Eingänge verarbeiten
- Typsichere Pin-Zuordnungen in Steuerungsprogrammen
- Fehlerbehandlung durch Verwendung der Invalid-Konstante

## Vergleich mit ähnlichen Bausteinen

Im Gegensatz zu Funktionsblöcken mit aktiver Logik handelt es sich hier um eine reine Konstantendefinition, die:
- Keine aktive Verarbeitung durchführt
- Keine Ereignisse verarbeitet
- Ausschließlich Konfigurationsdaten bereitstellt
- Zur Compile-Zeit ausgewertet wird

## Fazit

Die logiBUS_DI GlobalConstants bieten eine strukturierte und typsichere Methode zur Konfiguration digitaler Eingänge im logiBUS-System. Durch die vordefinierten Konstanten wird die Fehleranfälligkeit bei der Pin-Zuordnung reduziert und die Wartbarkeit der Steuerungsprogramme verbessert.
