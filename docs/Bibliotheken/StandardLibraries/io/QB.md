# QB

```{index} single: QB
```

![](https://user-images.githubusercontent.com/69573151/210781164-b9fa5de3-e61e-47b8-b34f-86fa3bd398ff.png)

* * * * * * * * * *
## Einleitung
Der QB-Funktionsblock ist ein Ausgabeservice-Interface für Byte-Ausgabedaten. Er dient als Schnittstelle zwischen der Steuerungslogik und physischen Ausgabegeräten oder Ressourcen und ermöglicht die Ausgabe von Byte-Daten an externe Hardware.

![QB](QB.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierungsereignis
- **REQ**: Service-Anfrageereignis

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung
- **CNF**: Bestätigung der angeforderten Service-Operation

### **Daten-Eingänge**
- **QI** (BOOL): Ereignis-Eingangsqualifizierer
- **PARAMS** (STRING): Service-Parameter für Konfiguration
- **OUT** (BYTE): Ausgabedaten für die Ressource

### **Daten-Ausgänge**
- **QO** (BOOL): Ereignis-Ausgangsqualifizierer
- **STATUS** (STRING): Service-Statusinformationen

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der QB-Block initialisiert sich über das INIT-Ereignis mit den entsprechenden PARAMS. Nach erfolgreicher Initialisierung bestätigt er dies mit INITO. Über das REQ-Ereignis können Byte-Daten (OUT) an die angeschlossene Ressource ausgegeben werden. Die Verarbeitung wird mit dem CNF-Ereignis und Statusinformationen quittiert.

## Technische Besonderheiten
- Spezialisiert auf Byte-Datenausgabe
- Unterstützt parametrierbare Initialisierung
- Liefert detaillierte Statusinformationen über STRING-Ausgang
- Verwendet Qualifizierer (QI/QO) für Ereignissteuerung

## Zustandsübersicht
1. **Nicht initialisiert**: Block wartet auf INIT-Ereignis
2. **Initialisiert**: Block bereit für REQ-Anfragen
3. **Aktiv**: Verarbeitet Ausgabeanfragen
4. **Fehler**: Statusmeldung bei Problemen

## Anwendungsszenarien
- Ansteuerung von digitalen Ausgabemodulen
- Kommunikation mit Byte-basierten Peripheriegeräten
- Integration in IO-Subsysteme
- Steuerung von Hardware mit Byte-Kommandos

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu allgemeineren Ausgabeblöcken ist QB speziell auf Byte-Daten optimiert. Andere Blöcke wie z.B. WORD- oder DWORD-Ausgabeblöcke arbeiten mit größeren Datentypen, während QB die effiziente Verarbeitung von 8-Bit-Daten ermöglicht.

## Fazit
Der QB-Funktionsblock bietet eine robuste und standardisierte Schnittstelle für Byte-Ausgabedaten in industriellen Steuerungssystemen. Durch seine klare Ereignissteuerung und Statusrückmeldungen eignet er sich besonders für zuverlässige IO-Operationen in automatisierten Prozessen.