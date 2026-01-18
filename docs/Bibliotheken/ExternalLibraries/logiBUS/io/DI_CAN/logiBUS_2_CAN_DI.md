# logiBUS_2_CAN_DI

```{index} single: logiBUS_2_CAN_DI
```

* * * * * * * * * *

## Einleitung
Die logiBUS_2_CAN_DI GlobalConstants definieren Konstanten für die Konfiguration von digitalen Eingängen (DI) im logiBUS-System über CAN-Bus. Diese Konstanten werden zur Pin-Zuweisung für digitale Eingangskanäle verwendet und stellen eine standardisierte Schnittstelle für die Hardware-Konfiguration bereit.

## Schnittstellenstruktur

### **Konstantendefinitionen**

Die GlobalConstants definieren drei Hauptkonstanten für die digitale Eingangskonfiguration:

- **Input_CI1**: Konfiguration für digitalen Eingangskanal 1
- **Input_CI2**: Konfiguration für digitalen Eingangskanal 2
- **Invalid**: Kennzeichnet einen ungültigen oder nicht konfigurierten Eingang

### **Datentypen**

Alle Konstanten verwenden den strukturierten Datentyp `logiBUS_2_CAN_DI_S`, der folgende Komponente enthält:
- **Pin**: Ganzzahlwert zur Identifikation des physikalischen Eingangspins

## Funktionsweise
Die Konstanten werden zur Laufzeit nicht verändert und dienen ausschließlich der Konfiguration der digitalen Eingänge. Sie definieren die Hardware-Zuordnung zwischen logischen Kanälen und physikalischen Pins im CAN-basierten logiBUS-System.

## Technische Besonderheiten

- **Pin-Zuordnung**: Kanal 1 ist Pin 1, Kanal 2 ist Pin 2 zugeordnet
- **Ungültige Kennung**: Der Wert 255 kennzeichnet einen ungültigen oder nicht verfügbaren Eingang
- **CAN-Integration**: Speziell für CAN-basierte logiBUS-Systeme optimiert
- **Typensicherheit**: Verwendung strukturierter Datentypen für konsistente Konfiguration

## Anwendungsszenarien

- Konfiguration von digitalen Eingängen in logiBUS-Steuerungen
- Hardware-Abstraktion in CAN-basierten Automatisierungssystemen
- Pin-Zuordnung in verteilten E/A-Systemen
- Fehlerbehandlung bei nicht konfigurierten Eingängen

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einfachen numerischen Konstanten bieten diese strukturierten Konstanten:
- Höhere Typsicherheit durch strukturierte Datentypen
- Bessere Wartbarkeit durch zentrale Konfiguration
- Erweiterbarkeit für zusätzliche Parameter
- Kompatibilität mit logiBUS-Systemarchitektur

## Fazit
Die logiBUS_2_CAN_DI GlobalConstants bieten eine robuste und typsichere Lösung für die Konfiguration digitaler Eingänge in CAN-basierten logiBUS-Systemen. Durch die strukturierte Herangehensweise ermöglichen sie eine klare Hardware-Zuordnung und erleichtern die Wartung und Erweiterung von Automatisierungslösungen.