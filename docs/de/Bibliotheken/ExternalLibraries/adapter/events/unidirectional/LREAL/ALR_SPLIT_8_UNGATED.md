# ALR_SPLIT_8_UNGATED

> ℹ️ **UNGATED-Variante:** Dieser Baustein ist die ungegatete Version von [`ALR_SPLIT_8`](ALR_SPLIT_8.md). Er unterdrückt **keine** unveränderten Wiederholungen – jedes neu berechnete Ergebnis wird bedingungslos weitergegeben, auch ohne Wertänderung. Das ist wichtig für Verbraucher, die eine periodische Kadenz unabhängig von Wertänderung brauchen (z. B. Ableitungs-/Frequenzberechnungen, die sonst nicht gegen Null abklingen). Alle Angaben zu Änderungserkennung/Change-Gating weiter unten auf dieser Seite gelten **nicht** für diesen Baustein.

![ALR_SPLIT_8_UNGATED](./ALR_SPLIT_8_UNGATED.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ALR_SPLIT_8_UNGATED** dient der Aufteilung eines einzelnen ALR-Signals (über einen Socket) auf acht identische ALR-Ausgänge (Plugs). Dieser Baustein ist als generischer FB konzipiert und ermöglicht die Signalverteilung innerhalb einer IEC 61499-basierten Steuerung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine

### **Ereignis-Ausgänge**

Keine

### **Daten-Eingänge**

Keine

### **Daten-Ausgänge**

Keine

### **Adapter**

| Bezeichnung | Typ | Richtung | Beschreibung |
| ------------- | ----- | ---------- | -------------- |
| **IN** | `adapter::types::unidirectional::ALR` | Socket | Eingangssignal, das auf alle Ausgänge weitergeleitet wird |
| **OUT1** | `adapter::types::unidirectional::ALR` | Plug | Ausgang 1 – dupliziertes Signal |
| **OUT2** | `adapter::types::unidirectional::ALR` | Plug | Ausgang 2 – dupliziertes Signal |
| **OUT3** | `adapter::types::unidirectional::ALR` | Plug | Ausgang 3 – dupliziertes Signal |
| **OUT4** | `adapter::types::unidirectional::ALR` | Plug | Ausgang 4 – dupliziertes Signal |
| **OUT5** | `adapter::types::unidirectional::ALR` | Plug | Ausgang 5 – dupliziertes Signal |
| **OUT6** | `adapter::types::unidirectional::ALR` | Plug | Ausgang 6 – dupliziertes Signal |
| **OUT7** | `adapter::types::unidirectional::ALR` | Plug | Ausgang 7 – dupliziertes Signal |
| **OUT8** | `adapter::types::unidirectional::ALR` | Plug | Ausgang 8 – dupliziertes Signal |

## Funktionsweise

Der Baustein leitet das über den Socket **IN** anliegende ALR-Signal unverändert an alle acht Ausgangsadapter **OUT1** bis **OUT8** weiter. Es findet keinerlei Datenverarbeitung oder zeitliche Verzögerung statt – die Signale werden direkt durchgeschliffen. Dadurch können mehrere nachfolgende Bausteine parallel mit dem gleichen Signal versorgt werden.

## Technische Besonderheiten

- **Generischer Typ:** Der FB ist als generischer Baustein (`GenericClassName = 'GEN_ALR_SPLIT'`) implementiert, sodass der zugrundeliegende ALR-Typ bei der Instanziierung spezifiziert werden kann.
- **Reine Signalverteilung:** Keine Zustände, keine Datenkonvertierung und kein eigenes Zeitverhalten – der Baustein arbeitet rein passiv.
- **Adapterbasiert:** Die gesamte Kommunikation erfolgt über Adapter, wodurch eine lose Kopplung und einfache Wiederverwendung gewährleistet wird.

## Zustandsübersicht

Der FB besitzt keine Ereignisse und keinen internen Zustandsautomaten. Die Ausführung erfolgt strikt datenflussgetrieben: Ändert sich das Signal am Eingang, wird es sofort an alle Ausgänge propagiert.

## Anwendungsszenarien

- **Signalsplittung** in Steuerungsarchitekturen, wenn ein ALR-Signal mehrfach benötigt wird (z. B. für parallele Auswertungen oder Redundanz).
- **Verschaltung mehrerer Subsysteme** mit identischen Steuerdaten, ohne mehrfache Signalerzeugung.
- **Testaufbauten** zur gleichzeitigen Stimulation mehrerer Empfänger mit demselben Wert.

## Vergleich mit ähnlichen Bausteinen

Andere Splitter-FBs (z. B. SPLIT_4 oder SPLIT_16) unterscheiden sich lediglich in der Anzahl der Ausgänge. Der ALR_SPLIT_8_UNGATED ist speziell für den ALR-Adaptertyp ausgelegt, während generische Splitter (z. B. ANY_SPLIT) für beliebige Datentypen verwendet werden können. Der vorliegende Baustein bietet eine optimierte, typsichere Lösung für ALR-Verteilanwendungen.

- **[`ALR_SPLIT_8_UNGATED`](ALR_SPLIT_8_UNGATED.md)**: Ungegatete Variante – aktualisiert den Ausgang bei jedem Durchlauf, auch ohne Wertänderung.

- **[`ALR_SPLIT_8`](ALR_SPLIT_8.md)**: Die gegatete Variante – aktualisiert den Ausgang nur bei tatsächlicher Wertänderung.

## Änderungserkennung

Dieser Baustein führt **keine** Änderungserkennung durch. Jedes neu berechnete Ergebnis wird bedingungslos auf den Ausgang geschrieben und das zugehörige Adapter-Event gesendet, unabhängig davon, ob sich der Wert gegenüber dem vorherigen Durchlauf geändert hat.

## Fazit

Der **ALR_SPLIT_8_UNGATED** ist ein einfacher, aber effektiver Funktionsblock zur Vervielfachung eines ALR-Signals auf acht Ausgänge. Seine generische Natur, die adapterbasierte Schnittstelle und die passive Funktionsweise machen ihn zu einer robusten und flexiblen Komponente für IEC 61499-Applikationen.
