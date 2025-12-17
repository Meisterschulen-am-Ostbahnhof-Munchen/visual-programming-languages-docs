# logiBUS_DO

* * * * * * * * * *

## Einleitung
Die logiBUS_DO GlobalConstants definieren eine Sammlung von Konstanten für die Konfiguration von digitalen Ausgängen (DO - Digital Output) im logiBUS-System. Diese Konstanten werden zur Pin-Zuweisung für digitale Ausgangskanäle verwendet und stellen eine standardisierte Schnittstelle für die Hardware-Konfiguration bereit.

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
Die logiBUS_DO GlobalConstants definieren strukturierte Konstanten vom Typ `logiBUS_DO_S`, die jeweils einen spezifischen Pin-Wert für digitale Ausgänge enthalten. Die Konstanten `Output_Q1` bis `Output_Q10` repräsentieren die verfügbaren Ausgangskanäle mit den entsprechenden Pin-Nummern 1 bis 10. Die Konstante `Invalid` mit dem Pin-Wert 255 dient als Kennzeichnung für ungültige oder nicht konfigurierte Ausgänge.

## Technische Besonderheiten
- **Konstantentyp**: Alle Konstanten sind vom strukturierten Datentyp `logiBUS_DO_S`
- **Pin-Zuordnung**: Klare Zuordnung von Ausgangsnamen zu physikalischen Pin-Nummern
- **Invalid-Kennzeichnung**: Spezielle Konstante mit Pin-Wert 255 für Fehlerbehandlung
- **Package-Struktur**: Organisiert im Package `logiBUS::io::DQ`

## Zustandsübersicht
Da es sich um Konstanten handelt, sind keine Zustandsübergänge vorhanden. Die Werte sind statisch und unveränderlich während der Laufzeit.

## Anwendungsszenarien
- Hardware-Konfiguration von logiBUS-Systemen
- Pin-Zuweisung in Funktionsblöcken für digitale Ausgänge
- Fehlerbehandlung bei ungültigen Ausgangskonfigurationen
- Standardisierung von Ausgangsbezeichnungen in Steuerungsanwendungen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Konstantendefinitionen bietet logiBUS_DO eine spezifische Struktur für digitale Ausgänge mit klarer Pin-Zuordnung und einer definierten Invalid-Konstante für robuste Fehlerbehandlung.

## Fazit
Die logiBUS_DO GlobalConstants bieten eine standardisierte und wartungsfreundliche Lösung für die Konfiguration digitaler Ausgänge in logiBUS-Systemen. Durch die strukturierte Definition der Ausgangskanäle und die bereitgestellte Invalid-Konstante wird eine zuverlässige und fehlertolerante Hardware-Konfiguration ermöglicht.