# EliteBoard

```{index} single: EliteBoard
```

<img width="676" height="440" alt="image" src="https://github.com/user-attachments/assets/2d3b5eb6-9266-4eae-bc4e-44fbcf12f6e3" />

* * * * * * * * * *

## Einleitung
Der EliteBoard-Funktionsblock ist ein Service Interface Function Block Type, der als Schnittstelle für die EliteBoard-Hardware dient. Dieser Baustein ermöglicht die Anbindung und Steuerung von bis zu 11 verschiedenen Ports über standardisierte Adapter-Schnittstellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **MAP**: Initialisiert den Mapping-Prozess für die konfigurierten Ports

### **Ereignis-Ausgänge**
- **MAPO**: Signalisiert den erfolgreichen Abschluss des Mapping-Prozesses

### **Daten-Eingänge**
*Keine Daten-Eingänge vorhanden*

### **Daten-Ausgänge**
*Keine Daten-Ausgänge vorhanden*

### **Adapter**
Der Funktionsblock verfügt über 11 Adapter-Schnittstellen (Plugs):
- **PortA** bis **PortK**: Jeweils vom Typ `eclipse4diac::io::eliteboard::PortAdapter`

Diese Adapter ermöglichen die Verbindung mit verschiedenen Port-Schnittstellen der EliteBoard-Hardware.

## Funktionsweise
Beim Empfang des MAP-Ereignisses initialisiert der EliteBoard-Funktionsblock die konfigurierten Port-Adapter. Nach erfolgreicher Initialisierung aller angeschlossenen Ports wird das MAPO-Ereignis ausgelöst. Jeder Port-Adapter (PortA bis PortK) kann individuell für spezifische Ein-/Ausgabe-Funktionen konfiguriert werden.

## Technische Besonderheiten
- Unterstützt bis zu 11 unabhängige Port-Schnittstellen
- Verwendet standardisierte PortAdapter-Schnittstellen
- Einfache Initialisierung über ein einzelnes Ereignis
- Robuste Fehlerbehandlung durch zentralisiertes Mapping

## Zustandsübersicht
1. **Initialzustand**: Wartet auf MAP-Ereignis
2. **Mapping-Zustand**: Initialisiert alle konfigurierten Port-Adapter
3. **Bereit-Zustand**: Alle Ports sind initialisiert, MAPO-Ereignis wird ausgelöst

## Anwendungsszenarien
- Steuerung von EliteBoard-Hardware in industriellen Automatisierungssystemen
- Anbindung multipler Ein-/Ausgabe-Schnittstellen in Embedded-Systemen
- Integration in verteilte Steuerungssysteme nach IEC 61499
- Hardware-nahe Steuerungsaufgaben mit modularer Port-Verwaltung

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen IO-Bausteinen bietet EliteBoard eine strukturierte Verwaltung multipler Ports über standardisierte Adapter-Schnittstellen. Während einfache IO-Bausteine typischerweise direkte Daten-Ein-/Ausgänge verwenden, setzt EliteBoard auf Adapter-basierte Architektur für bessere Modularität und Wiederverwendbarkeit.

## Fazit
Der EliteBoard-Funktionsblock stellt eine flexible und skalierbare Lösung für die Anbindung von EliteBoard-Hardware in 4diac-basierten Steuerungssystemen dar. Durch die Verwendung standardisierter Adapter-Schnittstellen und die Unterstützung multipler Ports ermöglicht er eine modulare und wartbare Systemarchitektur für industrielle Automatisierungsanwendungen.