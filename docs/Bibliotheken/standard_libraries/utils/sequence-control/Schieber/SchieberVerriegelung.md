# SchieberVerriegelung

<img width="1313" height="347" alt="image" src="https://github.com/user-attachments/assets/fe5348b3-624e-44a5-8e31-8927d4dd851e" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock "SchieberVerriegelung" dient zur Steuerung und Verriegelung von drei Schiebern (Hauptschieber, linker und rechter Schieber). Er ermöglicht verschiedene Betriebszustände und gewährleistet eine sichere Steuerung der Schieberpositionen basierend auf den Eingangssignalen und Sperrzuständen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `INIT`: Initialisierungsanforderung (mit Daten `QI`)
- `EI1`: Allgemeines Ereignis (mit Daten `DI_LINKS_GESPERRT` und `DI_RECHTS_GESPERRT`)
- `EI_Hauptschieber_Open`: Öffnen des Hauptschiebers
- `EI_Hauptschieber_Close`: Schließen des Hauptschiebers
- `EI_SchieberLinks_Open`: Öffnen des linken Schiebers
- `EI_SchieberLinks_Close`: Schließen des linken Schiebers
- `EI_SchieberRechts_Open`: Öffnen des rechten Schiebers
- `EI_SchieberRechts_Close`: Schließen des rechten Schiebers

### **Ereignis-Ausgänge**
- `INITO`: Initialisierungsbestätigung (mit Daten `QO`)
- `EO_Hauptschieber_Open`: Bestätigung Öffnen Hauptschieber
- `EO_Hauptschieber_Close`: Bestätigung Schließen Hauptschieber
- `EO_SchieberLinks_Open`: Bestätigung Öffnen linker Schieber
- `EO_SchieberLinks_Close`: Bestätigung Schließen linker Schieber
- `EO_SchieberRechts_Open`: Bestätigung Öffnen rechter Schieber
- `EO_SchieberRechts_Close`: Bestätigung Schließen rechter Schieber

### **Daten-Eingänge**
- `QI`: BOOL - Qualifizierer für Initialisierungsereignis
- `DI_LINKS_GESPERRT`: BOOL - Status linker Schieber gesperrt
- `DI_RECHTS_GESPERRT`: BOOL - Status rechter Schieber gesperrt

### **Daten-Ausgänge**
- `QO`: BOOL - Qualifizierer für Ausgangsereignis

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock durchläuft verschiedene Zustände, die die Positionen der Schieber repräsentieren:
- **Initialisierung**: Startzustand und Initialisierung
- **AlleZu**: Alle Schieber geschlossen
- **AlleAuf**: Alle Schieber geöffnet
- **LinksAuf**: Haupt- und linker Schieber geöffnet, rechter geschlossen
- **RechtsAuf**: Haupt- und rechter Schieber geöffnet, linker geschlossen

Übergänge zwischen den Zuständen erfolgen durch entsprechende Ereignisse und unter Berücksichtigung der Sperrzustände.

## Technische Besonderheiten
- Verwendung von Qualifiern (`QI`, `QO`) für Initialisierungsereignisse
- Berücksichtigung von Sperrzuständen (`DI_LINKS_GESPERRT`, `DI_RECHTS_GESPERRT`) bei Zustandsübergängen
- Drei Algorithmen für Initialisierung, Deinitialisierung und Normalbetrieb

## Zustandsübersicht
1. **START**: Initialer Zustand
2. **Init**: Initialisierungszustand
3. **DeInit**: Deinitialisierungszustand
4. **AlleZu**: Alle Schieber geschlossen (Standardzustand nach Init)
5. **AlleAuf**: Alle Schieber geöffnet
6. **LinksAuf**: Haupt- und linker Schieber geöffnet
7. **RechtsAuf**: Haupt- und rechter Schieber geöffnet

## Anwendungsszenarien
- Steuerung von industriellen Schiebersystemen
- Sicherheitskritische Anwendungen mit Verriegelungslogik
- Systeme mit mehreren, voneinander abhängigen Aktoren

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Schiebersteuerungen bietet dieser FB:
- Erweiterte Verriegelungslogik
- Mehrere Betriebszustände
- Berücksichtigung von Sperrzuständen
- Komplexere Zustandsübergänge

## Fazit
Der SchieberVerriegelung-FB bietet eine robuste Lösung für die Steuerung mehrerer voneinander abhängiger Schieber mit integrierter Verriegelungslogik. Durch die verschiedenen Zustände und Übergänge ermöglicht er flexible Anpassungen an unterschiedliche Betriebsszenarien.
