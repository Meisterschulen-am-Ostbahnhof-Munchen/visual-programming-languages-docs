# AI_SPLIT_2_UNGATED

> ℹ️ **UNGATED-Variante:** Dieser Baustein ist die ungegatete Version von [`AI_SPLIT_2`](AI_SPLIT_2.md). Er unterdrückt **keine** unveränderten Wiederholungen – jedes neu berechnete Ergebnis wird bedingungslos weitergegeben, auch ohne Wertänderung. Das ist wichtig für Verbraucher, die eine periodische Kadenz unabhängig von Wertänderung brauchen (z. B. Ableitungs-/Frequenzberechnungen, die sonst nicht gegen Null abklingen). Alle Angaben zu Änderungserkennung/Change-Gating weiter unten auf dieser Seite gelten **nicht** für diesen Baustein.

![AI_SPLIT_2_UNGATED](./AI_SPLIT_2_UNGATED.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock AI_SPLIT_2_UNGATED dient dazu, ein analoges Eingangssignal (AI) auf zwei identische analoge Ausgänge zu verteilen. Er ist als generischer Baustein konzipiert und ermöglicht eine flexible Weiterverarbeitung des Signals in zwei unabhängigen Pfaden.

## Schnittstellenstruktur

Der Baustein besitzt keine Ereignis- oder Dateneingänge/-ausgänge im klassischen Sinne, sondern kommuniziert ausschließlich über Adapter-Schnittstellen vom Typ `adapter::types::unidirectional::AI`.

### **Ereignis-Eingänge**

Keine

### **Ereignis-Ausgänge**

Keine

### **Daten-Eingänge**

Keine

### **Daten-Ausgänge**

Keine

### **Adapter**

| Adapter | Typ | Richtung | Beschreibung |
| --------- | ----- | ---------- | -------------- |
| IN | adapter::types::unidirectional::AI | Eingang (Socket) | Nimmt ein analoges Eingangssignal auf. |
| OUT1 | adapter::types::unidirectional::AI | Ausgang (Plug) | Gibt das an IN anliegende Signal unverändert weiter. |
| OUT2 | adapter::types::unidirectional::AI | Ausgang (Plug) | Gibt das an IN anliegende Signal unverändert weiter. |

## Funktionsweise

Der Baustein leitet das über den Socket `IN` empfangene analoge Signal (AI) gleichzeitig an beide Ausgänge (`OUT1` und `OUT2`) weiter. Es erfolgt keine Signalverarbeitung oder -veränderung; die Aufteilung ist rein passiv und sofort wirksam. Die Adapter stellen die notwendige Schnittstellenkompatibilität sicher.

## Technische Besonderheiten

- **Generischer Aufbau**: Der Baustein ist als generischer FB (`GEN_AI_SPLIT`) implementiert und kann mit verschiedenen AI-Adaptern verwendet werden, die dem unidirektionalen AI-Protokoll entsprechen.
- **Keine Zustandslogik**: Es existiert kein ECC (Execution Control Chart), daher ist das Verhalten rein kombinatorisch.
- **Plattformunabhängigkeit**: Der Baustein ist gemäß IEC 61499-2 spezifiziert und in Umgebungen einsetzbar, die das Adapterkonzept unterstützen.

## Zustandsübersicht

Der Baustein besitzt kein internes Zustandsverhalten. Die Ausgänge folgen direkt und ohne Verzögerung dem Eingangssignal.

## Anwendungsszenarien

- **Signalverteilung**: Ein einzelner analoger Sensor (z. B. Drucksensor, Temperaturfühler) soll von zwei unabhängigen Steuerungskomponenten ausgewertet werden.
- **Redundanz**: Aufteilung eines Signals für parallele Überwachungs- und Regelungspfade.
- **Simulation**: Erzeugung eines zweiten identischen Signalkanals für Test- oder Analysezwecke.

## Vergleich mit ähnlichen Bausteinen

- **AI_SPLIT_3**: Erweiterung auf drei Ausgänge.
- **AI_SELECT**: Wählt einen von mehreren Eingängen aus, anstatt zu verteilen.
- **AI_MERGE**: Fasst mehrere AI-Signale zu einem zusammen (z. B. Mittelwert).
  AI_SPLIT_2_UNGATED ist spezialisiert auf die einfache 1-zu-2-Verteilung ohne Logik oder Konfiguration.

- **[`AI_SPLIT_2`](AI_SPLIT_2.md)**: Die gegatete Variante – aktualisiert den Ausgang nur bei tatsächlicher Wertänderung.

## Änderungserkennung

Dieser Baustein führt **keine** Änderungserkennung durch. Jedes neu berechnete Ergebnis wird bedingungslos auf den Ausgang geschrieben und das zugehörige Adapter-Event gesendet, unabhängig davon, ob sich der Wert gegenüber dem vorherigen Durchlauf geändert hat.

## Fazit

AI_SPLIT_2_UNGATED ist ein einfacher, aber nützlicher Baustein zur passiven Aufteilung eines analogen Eingangssignals. Durch den generischen Adapteransatz ist er flexibel einsetzbar und erleichtert die modulare Strukturierung von Applikationen nach IEC 61499.
