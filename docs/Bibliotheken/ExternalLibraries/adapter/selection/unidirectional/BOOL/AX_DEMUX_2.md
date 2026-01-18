# AX_DEMUX_2

```{index} single: AX_DEMUX_2
```

<img width="1220" height="220" alt="image" src="https://github.com/user-attachments/assets/843be5c8-1e18-4cc5-81d1-922180394ad4" />

* * * * * * * * * *

## 📺 Video

* [2025-02-02 18-21-50 Uebung_006c Funktion E_DEMUX8 und ..._DI_REPEAT](https://www.youtube.com/watch?v=fOSa4_A7-dE)

## Einleitung
Der AX_DEMUX_2 ist ein generischer Demultiplexer-Funktionsblock, der Eingangssignale auf Basis eines Indexwerts auf verschiedene Ausgangskanäle verteilt. Der Baustein dient zur gezielten Weiterleitung von Datenströmen in verteilten Automatisierungssystemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Setzt den Index K und initiiert den Demultiplex-Vorgang

### **Ereignis-Ausgänge**
- **CNF**: Bestätigt die erfolgreiche Setzung des Index K

### **Daten-Eingänge**
- **K** (UINT): Indexwert zur Steuerung der Ausgangsauswahl

### **Daten-Ausgänge**
- Keine direkten Datenausgänge vorhanden

### **Adapter**
- **IN** (Socket): Eingangsadapter für den zu demultiplexierenden Wert (unidirektionaler AX-Typ)
- **OUT1** (Plug): Erster Ausgangsadapter (unidirektionaler AX-Typ)
- **OUT2** (Plug): Zweiter Ausgangsadapter (unidirektionaler AX-Typ)

## Funktionsweise
Der AX_DEMUX_2 empfängt über den IN-Adapter Eingangsdaten und leitet diese basierend auf dem Indexwert K selektiv an einen der beiden Ausgangsadapter OUT1 oder OUT2 weiter. Bei Aktivierung des REQ-Ereignisses wird der Index K gesetzt und der Demultiplex-Vorgang durchgeführt. Das CNF-Ereignis signalisiert den erfolgreichen Abschluss der Operation.

## Technische Besonderheiten
- Generische Implementierung für flexible Wiederverwendung
- Verwendung unidirektionaler AX-Adapter für klare Signalflussrichtung
- UINT-Datentyp für Indexsteuerung ermöglicht erweiterbare Ausgangsauswahl
- Eclipse 4diac kompatibel gemäß IEC 61499-2 Standard

## Zustandsübersicht
Der Funktionsblock arbeitet zustandslos und reagiert ausschließlich auf eingehende REQ-Ereignisse. Jeder REQ-Impuls führt zu einer sofortigen Verarbeitung und Auslösung des CNF-Bestätigungssignals.

## Anwendungsszenarien
- Verteilen von Sensordaten auf verschiedene Verarbeitungspfade
- Selektive Aktivierung von Aktoren in Mehrkanalsystemen
- Routing von Steuerbefehlen in modularen Anlagen
- Lastverteilung in parallelen Verarbeitungsketten

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Schaltern oder Multiplexern bietet der AX_DEMUX_2 eine spezialisierte Demultiplex-Funktionalität mit Adapter-basierter Schnittstelle. Die Verwendung standardisierter AX-Adapter gewährleistit Kompatibilität innerhalb des 4diac-Ökosystems.

Vergleich mit [E_DEMUX](../../../../../StandardLibraries/events/E_DEMUX.md)

## Fazit
Der AX_DEMUX_2 stellt einen effizienten und standardkonformen Baustein für die Datenverteilung in IEC 61499-basierten Automatisierungssystemen dar. Seine generische Natur und Adapter-basierte Architektur machen ihn zu einer flexiblen Lösung für verschiedene Demultiplex-Anwendungen.