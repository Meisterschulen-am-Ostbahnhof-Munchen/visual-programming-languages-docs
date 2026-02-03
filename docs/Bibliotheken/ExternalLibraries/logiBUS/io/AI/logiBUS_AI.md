# logiBUS_AI

```{index} single: logiBUS_AI
```

* * * * * * * * * *
## Einleitung
Die logiBUS_AI GlobalConstants definieren eine Sammlung von Konstanten für die Konfiguration von analogen Eingängen im logiBUS-System. Diese Konstanten werden zur einfachen und einheitlichen Referenzierung der analogen Eingangskanäle verwendet.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*Keine Ereignis-Eingänge vorhanden*

### **Ereignis-Ausgänge**
*Keine Ereignis-Ausgänge vorhanden*

### **Daten-Eingänge**
*Keine Daten-Eingänge vorhanden*

### **Daten-Ausgänge**
*Keine Daten-Ausgänge vorhanden*

### **Adapter**
*Keine Adapter vorhanden*

## Funktionsweise
Die logiBUS_AI GlobalConstants stellen vordefinierte Konstanten vom Typ `logiBUS_AI_S` bereit, die jeweils einen spezifischen analogen Eingangskanal repräsentieren. Jede Konstante enthält eine Pin-Nummer, die den physikalischen Eingangskanal identifiziert.

## Technische Besonderheiten
- **Konstantentyp**: Alle Konstanten sind vom strukturierten Datentyp `logiBUS_AI_S`
- **Pin-Zuordnung**: Die Konstanten `AnalogInput_I1` bis `AnalogInput_I9` entsprechen den analogen Eingängen 1 bis 9
- **Ungültige Referenz**: Die Konstante `Invalid` mit Pin-Wert 255 dient als Marker für ungültige oder nicht vorhandene Eingänge
- **Initialisierung**: Alle Konstanten werden bei der Deklaration mit ihren entsprechenden Pin-Werten initialisiert

## Zustandsübersicht
Da es sich um Konstanten handelt, haben diese keine Zustandsänderungen. Die Werte sind während der gesamten Laufzeit unveränderlich.

## Anwendungsszenarien
- Konfiguration von analogen Eingängen in logiBUS-Systemen
- Parametrierung von Funktionsblöcken, die analoge Eingänge benötigen
- Typsichere Referenzierung von analogen Kanälen in der Programmierung
- Fehlerbehandlung durch Verwendung der Invalid-Konstante

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu Funktionsblöcken mit dynamischem Verhalten bieten GlobalConstants:
- Keine Laufzeitberechnungen
- Keine Ereignisbehandlung
- Konstanten statt variabler Werte
- Direkte Initialisierung bei der Deklaration

## Fazit
Die logiBUS_AI GlobalConstants bieten eine effiziente und typsichere Methode zur Referenzierung analoger Eingänge im logiBUS-System. Durch die vordefinierten Konstanten wird die Programmierung vereinfacht und die Fehleranfälligkeit bei der Kanalkonfiguration reduziert.