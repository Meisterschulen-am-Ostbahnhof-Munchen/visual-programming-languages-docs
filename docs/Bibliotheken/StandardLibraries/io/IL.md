# IL

```{index} single: IL
```

![](https://user-images.githubusercontent.com/69573151/210780439-a6842673-058d-48f2-8cb7-135c6a960116.png)

* * * * * * * * * *

## Einleitung
Der IL-Funktionsblock (Input Long Word) ist ein Service Interface Function Block für die Verarbeitung von Long Word-Eingabedaten. Er dient als Schnittstelle zwischen der Steuerungslogik und externen Eingabegeräten oder Ressourcen, die 64-Bit-Datenwerte bereitstellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierungsereignis
- **REQ**: Service-Anfrageereignis

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung
- **CNF**: Bestätigung der angeforderten Service-Operation
- **IND**: Indikation von der Ressource

### **Daten-Eingänge**
- **QI** (BOOL): Event Input Qualifier - Steuert die Ausführung des Service
- **PARAMS** (STRING): Service-Parameter für die Konfiguration

### **Daten-Ausgänge**
- **QO** (BOOL): Event Output Qualifier - Zeigt den Status der Operation an
- **STATUS** (STRING): Service-Statusinformationen
- **IN** (LWORD): Eingabedaten von der Ressource (64-Bit Wert)

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der IL-Block arbeitet als Eingabeservice-Interface für Long Word-Daten. Bei Empfang des INIT-Ereignisses wird der Service initialisiert und die Konfigurationsparameter werden über PARAMS übergeben. Das REQ-Ereignis löst eine Leseoperation aus, bei der Daten von der angeschlossenen Ressource gelesen werden. Der Block unterstützt sowohl angeforderte Lesevorgänge (CNF) als auch spontane Datenaktualisierungen (IND) von der Ressource.

## Technische Besonderheiten
- Verarbeitet 64-Bit Long Word-Datentypen (LWORD)
- Unterstützt sowohl poll-basierte als auch event-basierte Datenabfragen
- Flexible Parameterkonfiguration über STRING-Parameter
- Statusrückmeldung über STATUS-Ausgang

## Zustandsübersicht
Der Block durchläuft folgende Zustände:
1. **Nicht initialisiert**: Vor der INIT-Operation
2. **Initialisiert**: Nach erfolgreicher INIT-Operation, bereit für Datenabfragen
3. **Aktiv**: Während der Datenabfrage oder bei empfangenen Indikationen

## Anwendungsszenarien
- Einlesen von 64-Bit Sensordaten
- Kommunikation mit externen Geräten, die Long Word-Daten liefern
- Datenerfassungssysteme mit hoher Präzision
- Steuerungssysteme, die große Zahlenwerte verarbeiten müssen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Eingabeblöcken wie IB (Byte), IW (Word) oder ID (Double Word) verarbeitet IL die größte Datengröße (64 Bit). Er bietet damit die höchste Präzision für numerische Eingabewerte in der 4diac-IO-Bibliothek.

## Fazit
Der IL-Funktionsblock bietet eine robuste und flexible Schnittstelle für die Verarbeitung von 64-Bit Eingabedaten in IEC 61499-Steuerungssystemen. Seine Unterstützung für verschiedene Betriebsmodi (polling und event-driven) macht ihn vielseitig einsetzbar in verschiedenen industriellen Anwendungen.
