# QW

```{index} single: QW
```

![](https://user-images.githubusercontent.com/69573151/210781478-8f72e916-a5af-485b-9b70-0cb6ee45204e.png)

* * * * * * * * * *

## Einleitung
Der QW-Funktionsblock ist ein Ausgabeservice-Interface-Baustein für die Ausgabe von Wort-Daten (WORD). Er dient als Schnittstelle zwischen der Steuerungslogik und physikalischen Ausgabegeräten oder Ressourcen und ermöglicht die sichere Übertragung von 16-Bit-Daten an externe Hardware.

![QW](QW.svg)

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
- **OUT** (WORD): Ausgabedaten für die Ressource

### **Daten-Ausgänge**
- **QO** (BOOL): Ereignis-Ausgangsqualifizierer
- **STATUS** (STRING): Service-Statusinformationen

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der QW-Block initialisiert bei Empfang des INIT-Ereignisses die Hardware-Schnittstelle mit den übergebenen PARAMS. Nach erfolgreicher Initialisierung bestätigt er dies mit INITO. Bei einer REQ-Anfrage werden die an OUT anliegenden WORD-Daten an die konfigurierte Ressource ausgegeben. Die Operation wird mit CNF bestätigt, wobei STATUS Informationen über den Erfolg oder Fehler der Operation liefert.

## Technische Besonderheiten
- Verarbeitet 16-Bit WORD-Daten
- String-basierte Parameterkonfiguration über PARAMS
- Statusrückmeldung über STRING-Variable
- Qualifier-Bits (QI/QO) für Ereignissteuerung

## Zustandsübersicht
1. **Nicht initialisiert**: Block wartet auf INIT-Ereignis
2. **Initialisiert**: Block ist betriebsbereit und wartet auf REQ-Ereignisse
3. **Aktiv**: Verarbeitet Ausgabeanfragen und generiert Bestätigungen

## Anwendungsszenarien
- Ansteuerung von digitalen Ausgabemodulen
- Kommunikation mit I/O-Systemen
- Steuerung von Hardware mit 16-Bit-Datenworten
- Integration in verteilte Steuerungssysteme

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu QB (Byte-Ausgabe) verarbeitet QW 16-Bit statt 8-Bit Daten. Gegenüber QD (Double-Word) bietet er eine geringere Datenbreite bei reduziertem Ressourcenbedarf. Die Struktur ähnelt anderen IO-Service-Blöcken, ist jedoch spezifisch auf WORD-Daten ausgelegt.

## Fazit
Der QW-Funktionsblock bietet eine robuste und standardisierte Schnittstelle für die Ausgabe von 16-Bit-Daten an externe Ressourcen. Durch seine klare Ereignissteuerung und Statusrückmeldung eignet er sich ideal für zuverlässige Echtzeit-I/O-Operationen in industriellen Steuerungssystemen.