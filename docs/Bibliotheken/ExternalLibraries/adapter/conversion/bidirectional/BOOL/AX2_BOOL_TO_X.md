# AX2_BOOL_TO_X

<img width="1186" height="196" alt="image" src="https://github.com/user-attachments/assets/ed299069-4248-4942-bdcb-3615f0044660" />

* * * * * * * * * *

## Einleitung
Der Funktionsblock AX2_BOOL_TO_X dient als Composite-Funktionsblock zur Konvertierung von BOOL-Werten in das AX2-Adapterformat. Er ermöglicht die bidirektionale Kommunikation zwischen einfachen BOOL-Daten und dem spezifischen AX2-Adapter-Interface.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Anfrage-Ereignis zur Aktivierung des Adapters
  - Verknüpft mit Datenausgang OUT
  - Y-Position: 46

### **Ereignis-Ausgänge**
- **CNF**: Bestätigungs-Ereignis vom Adapter
  - Verknüpft mit Dateneingang IN
  - Y-Position: 46

### **Daten-Eingänge**
- **OUT**: BOOL-Dateneingang für die Ausgaberichtung
  - Y-Position: 31

### **Daten-Ausgänge**
- **IN**: BOOL-Datenausgang für die Eingaberichtung
  - Empfängt Daten vom Adapter
  - Y-Position: 47

### **Adapter**
- **AX2_OUT**: AX2-Adapter für bidirektionale Kommunikation
  - Adapter-Typ: adapter::types::bidirectional::AX2
  - Position: x=-3900, y=-500

## Funktionsweise
Der Funktionsblock fungiert als Brücke zwischen BOOL-Daten und dem AX2-Adapter. Bei Eintreffen eines REQ-Ereignisses wird der OUT-Wert über den AX2_OUT-Adapter gesendet. Gleichzeitig können über denselben Adapter eingehende Daten empfangen und als IN-Ausgang mit einem CNF-Ereignis bereitgestellt werden.

## Technische Besonderheiten
- Implementiert als Composite-Funktionsblock
- Unterstützt bidirektionale Datenübertragung
- Verwendet spezifische AX2-Adapter-Schnittstelle
- Automatische Ereignis- und Datenweiterleitung zwischen Hauptschnittstelle und Adapter

## Zustandsübersicht
Der Funktionsblock arbeitet zustandslos und leitet Ereignisse und Daten direkt zwischen den Schnittstellen weiter:
- REQ → AX2_OUT.EO1
- AX2_OUT.EI1 → CNF
- OUT → AX2_OUT.DO1
- AX2_OUT.DI1 → IN

## Anwendungsszenarien
- Integration von BOOL-Signalen in AX2-basierte Systeme
- Protokollumsetzung zwischen verschiedenen Automatisierungsebenen
- Bidirektionale Datenaustausch-Szenarien
- Adapter-basierte Systemintegration

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Konvertierungsbausteinen bietet AX2_BOOL_TO_X:
- Bidirektionale Funktionalität
- Integrierte Adapter-Schnittstelle
- Komplette Ereignisbehandlung
- Höhere Abstraktionsebene durch Composite-Design

## Fazit
AX2_BOOL_TO_X ist ein spezialisierter Composite-Funktionsblock, der eine effiziente Brücke zwischen BOOL-Daten und dem AX2-Adapter-Protokoll bildet. Seine bidirektionale Architektur und integrierte Ereignisbehandlung machen ihn ideal für Systeme, die eine nahtlose Integration zwischen verschiedenen Protokollschichten erfordern.
