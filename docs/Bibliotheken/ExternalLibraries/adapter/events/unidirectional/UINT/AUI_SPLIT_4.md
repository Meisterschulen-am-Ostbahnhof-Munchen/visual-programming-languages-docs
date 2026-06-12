# AUI_SPLIT_4


![AUI_SPLIT_4](./AUI_SPLIT_4.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AUI_SPLIT_4** dient als generischer Verteiler für AUI-Signale. Er nimmt einen einzelnen AUI-Eingang (Socket) entgegen und leitet ihn auf vier separate AUI-Ausgänge (Plugs) weiter. Dieser Baustein wird typischerweise in der Automatisierungstechnik eingesetzt, wenn ein unidirektionales Signal mehrfach parallel benötigt wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine vorhanden.

### **Ereignis-Ausgänge**

Keine vorhanden.

### **Daten-Eingänge**

Keine vorhanden.

### **Daten-Ausgänge**

Keine vorhanden.

### **Adapter**

| Richtung | Name   | Typ                        | Beschreibung                               |
|----------|--------|----------------------------|--------------------------------------------|
| Socket   | `IN`   | `adapter::types::unidirectional::AUI` | Eingangssignal (AUI)                       |
| Plug     | `OUT1` | `adapter::types::unidirectional::AUI` | Erster Ausgang (identisch zu IN)           |
| Plug     | `OUT2` | `adapter::types::unidirectional::AUI` | Zweiter Ausgang (identisch zu IN)          |
| Plug     | `OUT3` | `adapter::types::unidirectional::AUI` | Dritter Ausgang (identisch zu IN)          |
| Plug     | `OUT4` | `adapter::types::unidirectional::AUI` | Vierter Ausgang (identisch zu IN)          |

## Funktionsweise

Der Baustein führt keine Datenmanipulation durch. Er stellt eine passive Verteilereinheit dar: Sobald über den Adapter `IN` ein Signal anliegt, wird dieses ohne Verzögerung oder Änderung an alle vier Ausgangsadapter `OUT1`–`OUT4` weitergegeben. Die Signalrichtung ist unidirektional vom Socket zu den Plugs.

## Technische Besonderheiten

- **Generischer Typ:** Der FB ist als generischer Baustein deklariert (`GenericClassName = 'GEN_AUI_SPLIT'`). Er kann somit mit verschiedenen Ausprägungen des AUI-Adaptertyps verwendet werden.
- **Keine Zustände:** Da keine Ereignisse oder Algorithmen vorhanden sind, besitzt der Baustein keinen internen Zustandsautomaten.
- **Lizenz:** Der Quellcode ist unter der **Eclipse Public License 2.0** verfügbar.

## Zustandsübersicht

Der Baustein hat keine Ereignis-Eingänge oder -Ausgänge und führt keinen Algorithmus aus. Es existiert kein expliziter Zustandsautomat. Der Baustein verhält sich wie eine reine Signalverteilung (Drahtverbindung).

## Anwendungsszenarien

- **Signalkaskadierung:** Ein Sensorsignal (z. B. AUI-basiertes Taktsignal) muss an mehrere Aktoren verteilt werden.
- **Testumgebungen:** Ein Testsignal soll parallel zu mehreren Prüflingen geführt werden.
- **Redundanz:** Ein Signal wird auf mehrere parallele Pfade aufgeteilt, um Ausfallsicherheit zu gewährleisten.
- **Bus-Erweiterung:** Als passiver Splitter in einem AUI-Kommunikationssystem.

## Vergleich mit ähnlichen Bausteinen

- **AUI_SPLIT_2** – Teilt einen Eingang auf zwei Ausgänge (analoges Prinzip, geringere Anzahl).
- **AUI_MERGE** – Fasst mehrere AUI-Eingänge zu einem Ausgang zusammen (Gegenstück).
- **AUI_SELECT** – Wählt mit einem Steuersignal einen von mehreren Eingängen aus (mit Auswahlfunktion).
- Im Gegensatz zu diesen Bausteinen bietet `AUI_SPLIT_4` eine reine 1:4-Verteilung ohne Selektionslogik oder Zusammenführung.

## Fazit

Der Funktionsblock **AUI_SPLIT_4** ist ein einfacher, aber nützlicher Baustein zur passiven Vervielfältigung von AUI-Signalen. Seine generische Natur und die klare Schnittstelle machen ihn zu einem flexiblen Werkzeug in der Automatisierungsentwicklung, insbesondere wenn mehrere gleichartige Empfänger mit demselben Signal versorgt werden müssen.