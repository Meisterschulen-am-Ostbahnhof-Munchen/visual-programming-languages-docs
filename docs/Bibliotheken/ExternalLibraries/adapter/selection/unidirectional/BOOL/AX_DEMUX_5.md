# AX_DEMUX_5

```{index} single: AX_DEMUX_5
```

<img width="1220" height="301" alt="image" src="https://github.com/user-attachments/assets/8dd714c2-442d-4dc9-8935-4adc6eee0cd4" />

* * * * * * * * * *
## 📺 Video

* [2025-02-02 18-21-50 Uebung_006c Funktion E_DEMUX8 und ..._DI_REPEAT](https://www.youtube.com/watch?v=fOSa4_A7-dE)

## Einleitung
Der AX_DEMUX_5 ist ein generischer Demultiplexer-Funktionsblock, der eingehende AX-Signale auf einen von fünf Ausgängen verteilt. Der Baustein dient zur gezielten Weiterleitung von Datenströmen basierend auf einem Indexwert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Setzt den Index K und initiiert den Demultiplex-Vorgang

### **Ereignis-Ausgänge**
- **CNF**: Bestätigt die erfolgreiche Setzung des Index K

### **Daten-Eingänge**
- **K** (UINT): Indexwert zur Auswahl des gewünschten Ausgangs

### **Daten-Ausgänge**
*Keine direkten Datenausgänge vorhanden*

### **Adapter**

**Sockets:**
- **IN**: AX-Eingangsadapter für den zu demultiplexierenden Wert

**Plugs:**
- **OUT1**: AX-Ausgangsadapter 1
- **OUT2**: AX-Ausgangsadapter 2  
- **OUT3**: AX-Ausgangsadapter 3
- **OUT4**: AX-Ausgangsadapter 4
- **OUT5**: AX-Ausgangsadapter 5

## Funktionsweise
Der AX_DEMUX_5 verteilt eingehende AX-Signale über den IN-Adapter selektiv auf einen der fünf OUT-Adapter. Der Index K bestimmt, welcher Ausgang aktiviert wird. Bei Eintreffen des REQ-Ereignisses wird der aktuelle K-Wert ausgewertet und der entsprechende Ausgangskanal für die Datenweiterleitung konfiguriert. Das CNF-Ereignis signalisiert den Abschluss dieser Operation.

## Technische Besonderheiten
- Generischer Funktionsblock mit Typ-Hash-Funktionalität
- Verwendet unidirektionale AX-Adapter für Ein- und Ausgänge
- Unterstützt fünf unabhängige Ausgangskanäle
- Index-basierte Auswahl mit UINT-Datentyp

## Zustandsübersicht
Der Funktionsblock arbeitet zustandslos - jeder REQ-Impuls führt zu einer sofortigen Verarbeitung und Ausgabe des CNF-Signals nach erfolgter Konfiguration.

## Anwendungsszenarien
- Verteilung von Steuersignalen in Automatisierungssystemen
- Selektion von Aktorik-Kanälen in mechanischen Systemen
- Routing von Datenströmen in verteilten Steuerungsarchitekturen
- Multiplexer/Demultiplexer-Schaltungen in industriellen Anwendungen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren Demultiplexern bietet AX_DEMUX_5 fünf Ausgangskanäle und ist speziell für AX-Adapter optimiert. Die generische Implementierung ermöglicht flexible Wiederverwendung in verschiedenen Kontexten.

Vergleich mit [E_DEMUX](../../../../../StandardLibraries/events/E_DEMUX.md)

## Fazit
Der AX_DEMUX_5 ist ein effizienter und flexibler Demultiplexer für AX-basierte Kommunikationssysteme, der durch seine fünf Ausgangskanäle und einfache Index-Steuerung vielfältige Anwendungsmöglichkeiten in industriellen Automatisierungslösungen bietet.