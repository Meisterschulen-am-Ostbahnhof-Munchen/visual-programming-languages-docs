# E_RESTART

```{index} single: E_RESTART
```

![IEC 61499 Service Interface Symbol](https://user-images.githubusercontent.com/113907528/204901925-d33114a6-a86a-4a53-854d-a3f499fc8802.png)

* * * * * * * * * *

## Einleitung
Der **E_RESTART** ist ein spezieller Service-Interface-Funktionsbaustein nach IEC 61499 (Annex A), zur Steuerung von Neustartsequenzen in verteilten Automatisierungssystemen. Der Baustein dient als Schnittstelle zwischen Ressourcen und übergeordneten Steuerungen.

## Schnittstellenstruktur

### **Ereignis-Ausgänge**
- `COLD`: Signalisiert einen Kaltstart (vollständiger Reset)
- `WARM`: Kennzeichnet einen Warmstart (partieller Reset)
- `STOP`: Informiert über anstehenden Stopp-Befehl

### **Service-Schnittstellen**
- Links: E_RESTART (FB-Schnittstelle)
- Rechts: RESOURCE (Geräteschnittstelle)

## Funktionsweise

1. **Kaltstart-Sequenz**:
   - Bei externem `start`-Kommando an die Ressource
   - Auslösung des `COLD`-Ereignisses

2. **Warmstart-Sequenz**:
   - Bei `restart`-Befehl der Ressource
   - Generierung des `WARM`-Ereignisses

3. **Stopp-Sequenz**:
   - Bei Empfang des `stop`-Signals
   - Ausgabe des `STOP`-Ereignisses

## Service-Sequenzen (XML-Spezifikation)

1. **cold_restart**:
   - `start` → `COLD` (Vollständige Reinitialisierung)

2. **warm_restart**:
   - `restart` → `WARM` (Zustandserhaltender Neustart)

3. **stopping**:
   - `stop` → `STOP` (Geordnetes Herunterfahren)

## Technische Besonderheiten

✔ **Standardisierte Neustart-Steuerung** nach IEC 61499 Annex A
✔ **Drei Betriebsmodi** (Cold/Warm/Stop)
✔ **Ressourcenübergreifende** Konsistenz
✔ **EPL-2.0 Open-Source** Implementierung

## Anwendungsszenarien

- **Feldgeräte-Steuerung**: Geordnete Reinitialisierung
- **Systemrecovery**: Automatische Neustartroutinen
- **Energiemanagement**: Geplantes Herunterfahren
- **Sicherheitskritische Systeme**: Zustandsgesicherte Restarts

## Vergleich mit ähnlichen Bausteinen

| Feature        | E_RESTART | E_CYCLE | E_DELAY |
|---------------|-----------|---------|---------|
| Zweck         | Systemsteuerung | Zeitsteuerung | Ereignisverzögerung |
| Ereignistyp   | Steuerbefehle | Periodisch | Einmalig |
| Standard      | Annex A   | Core     | Core     |

## Fazit

Der E_RESTART-Baustein bietet eine normkonforme Lösung für kritische Systemsteuerungsaufgaben:

- Standardisiertes Neustart-Management
- Trennung von Kalt-/Warmstart-Logik
- Zuverlässige Signalweiterleitung

Ermöglicht besonders die Entwicklung von robusten, fehlertoleranten Steuerungssystemen. Die klare Service-Schnittstelle nach IEC 61499 Annex A gewährleistet Interoperabilität über verschiedene Geräteplattformen hinweg.