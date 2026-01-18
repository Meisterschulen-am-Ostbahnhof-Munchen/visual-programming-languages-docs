# AX_DEMUX_4

```{index} single: AX_DEMUX_4
```

<img width="1220" height="274" alt="image" src="https://github.com/user-attachments/assets/b2301b38-e22d-4369-99f4-29de847e9d20" />

* * * * * * * * * *

## 📺 Video

* [2025-02-02 18-21-50 Uebung_006c Funktion E_DEMUX8 und ..._DI_REPEAT](https://www.youtube.com/watch?v=fOSa4_A7-dE)

## Einleitung
Der AX_DEMUX_4 ist ein generischer Demultiplexer-Funktionsblock, der eingehende Daten über einen Adapter-Eingang empfängt und basierend auf einem Indexwert selektiv an einen von vier Ausgangsadaptern weiterleitet. Der Baustein dient zur Verteilung von Datenströmen in verteilten Automatisierungssystemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Setzt den Index K und initiiert den Demultiplex-Vorgang

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der Index-Setzung und erfolgreichen Demultiplex-Operation

### **Daten-Eingänge**
- **K** (UINT): Indexwert zur Auswahl des Zielausgangs (0-3)

### **Daten-Ausgänge**
*Keine direkten Datenausgänge vorhanden*

### **Adapter**
- **IN** (Socket): Unidirektionaler AX-Adapter für den Eingangswert zum Demultiplexen
- **OUT1** (Plug): Unidirektionaler AX-Adapter für Ausgang 1
- **OUT2** (Plug): Unidirektionaler AX-Adapter für Ausgang 2  
- **OUT3** (Plug): Unidirektionaler AX-Adapter für Ausgang 3
- **OUT4** (Plug): Unidirektionaler AX-Adapter für Ausgang 4

## Funktionsweise
Der AX_DEMUX_4 arbeitet als 4-fach-Demultiplexer. Bei Empfang eines REQ-Ereignisses wird der aktuelle Wert des Index K ausgewertet. Basierend auf diesem Indexwert wird der eingehende Datenstrom vom IN-Adapter selektiv an einen der vier OUT-Adapter weitergeleitet. Nach erfolgreicher Verteilung wird das CNF-Ereignis ausgelöst.

## Technische Besonderheiten
- Generischer Funktionsblock mit Typ-Hash-Unterstützung
- Verwendet unidirektionale AX-Adapter für robuste Datenkommunikation
- Index-basierte Selektion mit UINT-Datentyp
- Vier fest konfigurierte Ausgangsadapter

## Zustandsübersicht
Der Funktionsblock besitzt einen einfachen Zustandsautomaten:
1. **Wartezustand**: Bereit für REQ-Ereignis
2. **Verarbeitungszustand**: Auswertung von K und Datenverteilung
3. **Bestätigungszustand**: Auslösung von CNF nach erfolgreicher Operation

## Anwendungsszenarien
- Verteilung von Sensordaten an verschiedene Verarbeitungseinheiten
- Lastverteilung in verteilten Steuerungssystemen
- Selektive Datenweiterleitung basierend auf Prioritäten oder Zielgruppen
- Routing von Kommunikationsdaten in Netzwerkarchitekturen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Multiplexern bietet AX_DEMUX_4 vier feste Ausgänge mit Adapter-basierter Schnittstelle, was eine höhere Flexibilität in verteilten Systemen ermöglicht. Die Verwendung von Standard-AX-Adaptern gewährleistet Kompatibilität mit anderen 4diac-Komponenten.

Vergleich mit [E_DEMUX](../../../../../StandardLibraries/events/E_DEMUX.md)

## Fazit
Der AX_DEMUX_4 ist ein robuster und einfach zu konfigurierender Demultiplexer für industrielle Automatisierungssysteme. Seine Adapter-basierte Architektur ermöglicht flexible Integration in bestehende Steuerungsstrukturen, während die Index-gesteuerte Auswahl eine präzise Datenverteilung gewährleistet.