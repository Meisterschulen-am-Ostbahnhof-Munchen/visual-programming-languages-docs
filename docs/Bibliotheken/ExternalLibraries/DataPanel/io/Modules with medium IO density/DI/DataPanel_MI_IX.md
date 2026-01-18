# DataPanel_MI_IX

```{index} single: DataPanel_MI_IX
```

<img width="1444" height="264" alt="image" src="https://github.com/user-attachments/assets/72a89eba-1aec-4942-99dc-d2ed708c0850" />

* * * * * * * * * *
## Einleitung
Der DataPanel_MI_IX ist ein Dienstschnittstellen-Funktionsblock für boolesche Eingabedaten, der speziell für die Kommunikation mit Digital-Eingängen in Automatisierungssystemen entwickelt wurde. Dieser Baustein ermöglicht die Initialisierung und Abfrage von digitalen Eingangssignalen über standardisierte Service-Schnittstellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierung mit Parametern QI, PARAMS, u8SAMember und Input
- **REQ**: Service-Anfrage mit Parameter QI

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung mit Parametern QO und STATUS
- **CNF**: Bestätigung der angeforderten Service-Operation mit Parametern QO, STATUS und IN
- **IND**: Indikation von der Ressource mit Parametern QO, STATUS und IN

### **Daten-Eingänge**
- **QI**: BOOL - Ereignis-Eingangsqualifizierer
- **PARAMS**: STRING - Service-Parameter
- **u8SAMember**: USINT - Knoten SA 224..239 (Initialwert: MI::MI_00)
- **Input**: DataPanel_MI_DI_S - Identifiziert den Digital-Eingang 5A..8B (Initialwert: DataPanel_MI_DI::Invalid)

### **Daten-Ausgänge**
- **QO**: BOOL - Ereignis-Ausgangsqualifizierer
- **STATUS**: STRING - Service-Status
- **IN**: BOOL - Eingabedaten von der Ressource

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der Funktionsblock initialisiert über das INIT-Ereignis die Kommunikation mit einem spezifischen Digital-Eingang. Nach erfolgreicher Initialisierung können über das REQ-Ereignis Abfragen des Eingangszustands durchgeführt werden. Der Baustein liefert über die Ausgangsereignisse CNF und IND den aktuellen Zustand des Digital-Eingangs sowie Statusinformationen zurück.

## Technische Besonderheiten
- Unterstützt spezifische SA-Member-Adressierung im Bereich 224-239
- Verwendet strukturierte Eingangsidentifikation über den DataPanel_MI_DI_S-Datentyp
- Bietet sowohl anforderungsbasierte (REQ/CNF) als auch indikationsbasierte (IND) Kommunikation
- Initialisierung mit konfigurierbaren Service-Parametern

## Zustandsübersicht
Der Funktionsblock durchläuft folgende Zustände:
1. **Nicht initialisiert**: Vor INIT-Aufruf
2. **Initialisiert**: Nach erfolgreicher INIT/INITO-Sequenz
3. **Bereit**: Kann REQ/CNF-Zyklen verarbeiten
4. **Aktiv**: Verarbeitet eingehende IND-Ereignisse von der Ressource

## Anwendungsszenarien
- Überwachung von Digital-Eingängen in Schaltschränken
- Integration in SPS-Steuerungen für Binärsignal-Erfassung
- Industrieautomation mit spezifischen SA-Adressierungsanforderungen
- Anlagen mit verteilten E/A-Systemen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu generischen Digital-Input-Blöcken bietet DataPanel_MI_IX:
- Spezifische Adressierung für DataPanel-Systeme
- Erweiterte Initialisierungsmöglichkeiten mit Parameter-Strings
- Zusätzliche IND-Funktionalität für ereignisbasierte Kommunikation
- Strukturierte Eingangsidentifikation

## Fazit
Der DataPanel_MI_IX ist ein spezialisierter Funktionsblock für die zuverlässige Erfassung digitaler Eingangssignale in DataPanel-Umgebungen. Durch seine flexible Parametrierung und beide Betriebsmodi (anforderungs- und ereignisbasiert) eignet er sich ideal für anspruchsvolle Automatisierungsanwendungen mit spezifischen Adressierungsanforderungen.
