# IE

```{index} single: IE
```
## 🎧 Podcast

* [4diac IDE: Dein "Hello World" der Automatisierung – Das Blinking Tutorial Lokal](https://podcasters.spotify.com/pod/show/eclipse-4diac-de/episodes/4diac-IDE-Dein-Hello-World-der-Automatisierung--Das-Blinking-Tutorial-Lokal-e36971r)
* [4diac IDE: Dein Open-Source-Werkzeugkasten für verteilte Industrieautomatisierung nach IEC 61499](https://podcasters.spotify.com/pod/show/eclipse-4diac-de/episodes/4diac-IDE-Dein-Open-Source-Werkzeugkasten-fr-verteilte-Industrieautomatisierung-nach-IEC-61499-e36821e)
* [4diac IDE: Wie der IEC 61499 Standard die Industrieautomatisierung revolutioniert](https://podcasters.spotify.com/pod/show/eclipse-4diac-de/episodes/4diac-IDE-Wie-der-IEC-61499-Standard-die-Industrieautomatisierung-revolutioniert-e36756a)
* [4diac-Präsentation: Zielgruppen, Struktur und Alleinstellungsmerkmal Schärfen](https://podcasters.spotify.com/pod/show/eclipse-4diac-de/episodes/4diac-Prsentation-Zielgruppen--Struktur-und-Alleinstellungsmerkmal-Schrfen-e38ckbo)
* [Den Software-Drachen zähmen: Industrielle Automatisierung und die Zukunft der Produktion](https://podcasters.spotify.com/pod/show/eclipse-4diac-de/episodes/Den-Software-Drachen-zhmen-Industrielle-Automatisierung-und-die-Zukunft-der-Produktion-e372eg1)

## 📺 Video

* [Die große Migration](https://www.youtube.com/watch?v=XcBu7y6ch4E)
* [Die Kunst des Lötens](https://www.youtube.com/watch?v=I6Srdxx6fzU)
* [Die Welt der Normung](https://www.youtube.com/watch?v=9phDmkJVaGM)
* [Löten wie ein Profi](https://www.youtube.com/watch?v=8ulMWcxaB-c)
* [The secret of the field](https://www.youtube.com/watch?v=MmMrEXum4w4)

## Einleitung
Der IE-Funktionsblock (Input Event) ist ein Service-Interface-Funktionsblock für die Verarbeitung von Ereigniseingangsdaten. Er dient als Schnittstelle zwischen der Steuerungslogik und externen Eingabegeräten oder -signalen und ermöglicht die Initialisierung, Abfrage und Indikation von Eingabeereignissen.

![IE](IE.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierung - Initialisiert den Funktionsblock mit Parametern
- **REQ**: Service-Anfrage - Löst eine Abfrage des Eingabezustands aus

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung - Bestätigt die erfolgreiche Initialisierung
- **CNF**: Service-Bestätigung - Bestätigt die verarbeitete Service-Anfrage
- **IND**: Indikation von der Ressource - Signalisiert eingehende Ereignisse von der Hardware

### **Daten-Eingänge**
- **QI** (BOOL): Ereignis-Eingangs-Qualifier - Aktiviert/deaktiviert die Ereignisverarbeitung
- **PARAMS** (STRING): Service-Parameter - Konfigurationsparameter für den Service

### **Daten-Ausgänge**
- **QO** (BOOL): Ereignis-Ausgangs-Qualifier - Status der Ereignisverarbeitung
- **STATUS** (STRING): Service-Status - Rückmeldung über den aktuellen Betriebszustand

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der IE-Funktionsblock arbeitet als bidirektionale Schnittstelle für Eingabeereignisse. Bei der Initialisierung (INIT) werden die Service-Parameter konfiguriert. Über REQ-Ereignisse können gezielte Abfragen des Eingabezustands durchgeführt werden. Gleichzeitig kann der Block asynchron IND-Ereignisse generieren, wenn von der Hardware spontan Eingabeereignisse erkannt werden.

## Technische Besonderheiten
- Unterstützt sowohl poll-basierte (REQ/CNF) als auch interrupt-basierte (IND) Betriebsmodi
- String-basierte Parameter- und Statusübertragung für flexible Konfiguration
- Separate Qualifier für Eingangs- und Ausgangsereignisse (QI/QO)
- Robuste Fehlerbehandlung durch STATUS-Rückmeldungen

## Zustandsübersicht
Der Funktionsblock durchläuft folgende Hauptzustände:
1. **Nicht initialisiert**: Block wartet auf INIT-Ereignis
2. **Initialisiert**: Block ist betriebsbereit und kann REQ- und IND-Ereignisse verarbeiten
3. **Abfrage aktiv**: Verarbeitung einer REQ-Anfrage
4. **Indikation aktiv**: Verarbeitung eines spontanen Eingabeereignisses

## Anwendungsszenarien
- Abfrage von digitalen Eingängen (z.B. Taster, Schalter)
- Überwachung von Sensorsignalen
- Schnittstelle zu externen Eingabegeräten
- Ereignisgesteuerte Steuerungsanwendungen
- Hardware-nahe E/A-Verwaltung in Automatisierungssystemen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren Eingabeblöcken bietet IE erweiterte Funktionalität:
- Gegenüber reinen E/A-Blöcken: Unterstützt sowohl poll- als auch event-basierte Abfragen
- Gegenüber statischen Eingabeblöcken: Dynamische Parametrierung zur Laufzeit
- Erweiterte Statusrückmeldungen für verbesserte Fehlerdiagnose

## Fazit
Der IE-Funktionsblock stellt eine flexible und robuste Lösung für die Behandlung von Eingabeereignissen in 4diac-basierten Steuerungssystemen dar. Seine Fähigkeit, sowohl synchrone Abfragen als auch asynchrone Indikationen zu verarbeiten, macht ihn besonders geeignet für Anwendungen, die sowohl reaktive als auch proaktive Eingabeverarbeitung erfordern.