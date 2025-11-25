# AX_SEL

<img width="1242" height="224" alt="image" src="https://github.com/user-attachments/assets/70f03e26-14b2-40a3-9eff-056402fef00e" />

* * * * * * * * * *
## Einleitung
Der AX_SEL Funktionsblock ist ein binärer Selektor, der zur Auswahl zwischen zwei Eingangswerten dient. Er gehört zur Kategorie der Standard-Selektionsfunktionen gemäß IEC 61131-3 und ermöglicht die flexible Auswahl von Daten basierend auf einem Steuersignal.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*Keine Ereignis-Eingänge vorhanden*

### **Ereignis-Ausgänge**
- **CNF** - Bestätigung des angeforderten Dienstes (Confirmation of Requested Service)

### **Daten-Eingänge**
- **IN0** (ANY) - Selektierbare Eingangsvariable
- **IN1** (ANY) - Selektierbare Eingangsvariable

### **Daten-Ausgänge**
- **OUT** (ANY) - Ausgewählter Eingang

### **Adapter**
- **G** (adapter::types::unidirectional::AX) - Unidirektionaler Adapter für Steuerung

## Funktionsweise
Der AX_SEL Funktionsblock wählt zwischen zwei Eingangswerten (IN0 und IN1) aus und gibt den selektierten Wert am Ausgang OUT aus. Die Auswahl wird über den angeschlossenen Adapter G gesteuert. Bei Aktivierung des CNF-Ereignisses wird der ausgewählte Wert am Ausgang OUT bereitgestellt.

## Technische Besonderheiten
- Verwendet den ANY-Datentyp für maximale Flexibilität bei den Ein- und Ausgängen
- Implementiert als unidirektionaler Adapter für einfache Steuerung
- Unterstützt verschiedene Datentypen durch die Verwendung von ANY

## Zustandsübersicht
Der Funktionsblock besitzt einen einfachen Zustand:
- **Bereit**: Wartet auf Steuersignal vom Adapter G
- Bei Empfang des Steuersignals wird der entsprechende Eingang ausgewählt und das CNF-Ereignis ausgelöst

## Anwendungsszenarien
- Auswahl zwischen zwei verschiedenen Sensoren
- Umschaltung zwischen Betriebsmodi
- Selektion von Datenquellen in Abhängigkeit von Betriebszuständen
- Wechsel zwischen manueller und automatischer Steuerung

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Selektionsbausteinen bietet AX_SEL:
- Größere Flexibilität durch ANY-Datentyp
- Einfache Integration durch unidirektionalen Adapter
- Standardisierte Schnittstelle gemäß IEC 61131-3

Vergleich mit [F_SEL](../../../../../StandardLibraries/iec61131-3/selection/F_SEL.md)

## Fazit
Der AX_SEL Funktionsblock stellt eine einfache und flexible Lösung für binäre Auswahlaufgaben in Steuerungssystemen dar. Durch die Verwendung des ANY-Datentyps und standardisierter Adapter-Schnittstellen ermöglicht er eine vielseitige Anwendung in verschiedenen Automatisierungsprojekten.
