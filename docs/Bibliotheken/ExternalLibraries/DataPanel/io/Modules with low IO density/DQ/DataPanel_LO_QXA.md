# DataPanel_LO_QXA

```{index} single: DataPanel_LO_QXA
```

<img width="1457" height="251" alt="image" src="https://github.com/user-attachments/assets/418a1c22-0c23-44ee-91d2-bb0a93254c66" />

* * * * * * * * * *

## Einleitung
Der DataPanel_LO_QXA ist ein zusammengesetzter Funktionsblock für die Ausgabe von booleschen Daten in Automatisierungssystemen. Er dient als Schnittstelle für digitale Ausgabefunktionen und ermöglicht die Steuerung von Ausgängen über definierte Service-Parameter.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierungsereignis mit den zugehörigen Daten QI, PARAMS, u8SAMember und Output

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung mit QO und STATUS
- **CNF**: Bestätigung des angeforderten Services mit QO und STATUS

### **Daten-Eingänge**
- **QI** (BOOL): Ereignis-Eingangsqualifizierer
- **PARAMS** (STRING): Service-Parameter
- **u8SAMember** (USINT): Knoten-SA 217..224 mit Initialwert LO::LO_00
- **Output** (DataPanel_LO_DO_S): Identifiziert den Ausgang DigitalOutput_1A..4B mit Initialwert Invalid

### **Daten-Ausgänge**
- **QO** (BOOL): Ereignis-Ausgangsqualifizierer
- **STATUS** (STRING): Service-Status

### **Adapter**
- **OUT**: Unidirektionaler Adapter vom Typ AX für die Ausgabesteuerung

## Funktionsweise
Der Funktionsblock initialisiert sich über das INIT-Ereignis und gibt über INITO den Initialisierungsstatus zurück. Die eigentliche Ausgabesteuerung erfolgt über den Adapter OUT, der mit dem internen QX-Block verbunden ist. Der QX-Block verarbeitet die Eingabedaten und gibt über CNF den Status der Service-Anfrage zurück.

## Technische Besonderheiten
- Verwendet spezifische SA-Member-Adressierung (217-224)
- Unterstützt verschiedene digitale Ausgänge (1A-4B)
- Implementiert Service-Parameter-Übergabe via STRING
- Enthält integrierte Fehlerbehandlung mit Invalid-Initialwert

## Zustandsübersicht
1. **Nicht initialisiert**: Vor INIT-Ereignis
2. **Initialisierung läuft**: Während INIT-Verarbeitung
3. **Bereit**: Nach erfolgreicher INITO-Bestätigung
4. **Aktiv**: Bei Service-Anfragen über Adapter OUT

## Anwendungsszenarien
- Steuerung digitaler Ausgänge in Automatisierungssystemen
- Integration in Prozessleitsysteme mit SA-Adressierung
- Anbindung an übergeordnete Steuerungssysteme via Service-Parameter
- Boolesche Signalausgabe in industriellen Anwendungen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen digitalen Ausgabeblöcken bietet DataPanel_LO_QXA erweiterte Funktionalität durch:
- Parametrierbare Service-Schnittstelle
- SA-Member-basierte Adressierung
- Integrierte Statusrückmeldung
- Adapter-basierte Erweiterbarkeit

## Fazit
Der DataPanel_LO_QXA ist ein leistungsfähiger zusammengesetzter Funktionsblock für die professionelle Steuerung digitaler Ausgänge in industriellen Automatisierungssystemen. Seine modulare Struktur und parametrierbare Schnittstelle machen ihn besonders geeignet für komplexe Anwendungen mit flexiblen Konfigurationsanforderungen.
