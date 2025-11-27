# AB2_B_TO_BYTE

<img width="1224" height="196" alt="image" src="https://github.com/user-attachments/assets/b8d88980-eb0b-4d26-8400-a6af1b5cbe0b" />

* * * * * * * * * *

## Einleitung
Der AB2_B_TO_BYTE ist ein Composite-Funktionsblock, der zur bidirektionalen Konvertierung zwischen AB2- und BYTE-Datentypen dient. Der Baustein fungiert als Adapter-Konverter und ermöglicht die nahtlose Integration unterschiedlicher Datentypen in Automatisierungssystemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ** (Request to Adapter): Startet die Konvertierungsoperation und fordert die Datenausgabe an

### **Ereignis-Ausgänge**
- **CNF** (Confirmation from Adapter): Signalisiert den erfolgreichen Abschluss der Konvertierungsoperation

### **Daten-Eingänge**
- **OUT** (BYTE): Ausgabedaten, die an den Adapter gesendet werden sollen

### **Daten-Ausgänge**
- **IN** (BYTE): Eingabedaten, die vom Adapter empfangen wurden

### **Adapter**
- **AB2_IN** (adapter::types::bidirectional::AB2): Bidirektionaler AB2-Adapter für die Datentyp-Konvertierung

## Funktionsweise
Der Funktionsblock arbeitet als bidirektionaler Konverter zwischen AB2- und BYTE-Datentypen. Bei Empfang eines REQ-Ereignisses werden die an OUT anliegenden BYTE-Daten über den AB2_IN-Adapter konvertiert. Nach erfolgreicher Konvertierung wird das CNF-Ereignis ausgelöst und die konvertierten Daten an IN ausgegeben.

Die interne Vernetzung zeigt folgende Signalflüsse:
- REQ → AB2_IN.EI1 (Adapter-Eingangsereignis)
- AB2_IN.EO1 → CNF (Adapter-Ausgangsereignis)
- OUT → AB2_IN.DI1 (Adapter-Dateneingang)
- AB2_IN.DO1 → IN (Adapter-Datenausgang)

## Technische Besonderheiten
- Implementiert als Composite-Funktionsblock mit integriertem Adapter
- Unterstützt bidirektionale Datenkonvertierung
- Positionierungsattribute für grafische Darstellung in der Entwicklungsumgebung
- Eingebettet im Package "adapter::conversion::bidirectional"

## Zustandsübersicht
Der Funktionsblock durchläuft folgende Zustände:
1. **Bereit**: Wartet auf REQ-Ereignis
2. **Konvertierung aktiv**: Verarbeitet Daten über AB2-Adapter
3. **Bestätigung**: Sendet CNF bei erfolgreichem Abschluss

## Anwendungsszenarien
- Integration von AB2-Komponenten in BYTE-basierte Steuerungssysteme
- Datentyp-Konvertierung in heterogenen Automatisierungsnetzwerken
- Adapter-Lösungen für Legacy-Systeme mit AB2-Schnittstellen
- Protokollumsetzung zwischen verschiedenen Kommunikationsstandards

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Konvertierungsbausteinen bietet AB2_B_TO_BYTE:
- Bidirektionale Funktionalität in einem einzigen Baustein
- Integrierte Adapter-Schnittstelle für AB2-Typen
- Composite-Architektur mit erweiterter Funktionalität
- Standardisierte Ereignisbehandlung mit REQ/CNF-Paar

## Fazit
Der AB2_B_TO_BYTE Funktionsblock stellt eine robuste Lösung für die bidirektionale Konvertierung zwischen AB2- und BYTE-Datentypen dar. Seine Composite-Architektur mit integriertem Adapter ermöglicht eine einfache Integration in bestehende Automatisierungssysteme und bietet zuverlässige Datentyp-Kompatibilität.
