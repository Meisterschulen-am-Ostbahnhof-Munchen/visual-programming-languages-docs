# ALI_DEMUX_4


![ALI_DEMUX_4](./ALI_DEMUX_4.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **ALI_DEMUX_4** ist ein generischer Demultiplexer für das ALI-Protokoll (Agrar-Landwirtschaft-Interface). Er verteilt einen über einen Socket eingehenden ALI‑Wert auf einen von vier Adapter‑Ausgängen, gesteuert durch einen Indexparameter. Der Baustein wird typischerweise in Steuerungsanwendungen der Agrartechnik eingesetzt, um Signale gezielt an unterschiedliche nachgelagerte Komponenten weiterzuleiten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|-------------|
| `REQ` | Setzt den Index `K` und startet die Demultiplexing‑Operation. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|-------------|
| `CNF` | Bestätigung, dass der gewählte Ausgang mit dem Eingangswert versorgt wurde. |

### **Daten-Eingänge**

| Variable | Typ    | Beschreibung |
|----------|--------|-------------|
| `K`      | UINT   | Index des gewünschten Ausgangs (1 bis 4 für OUT1 bis OUT4). Werte außerhalb dieses Bereichs haben kein definiertes Verhalten. |

### **Daten-Ausgänge**

*Keine deklariert.* Die Ausgangsdaten werden über die Adapter‑Schnittstellen transportiert.

### **Adapter**

| Typ | Bezeichnung | Richtung | Beschreibung |
|-----|-------------|----------|-------------|
| Socket | `IN` | Eingang | Ankommende ALI‑Werte (z. B. Messdaten oder Steuerbefehle). |
| Plug | `OUT1` | Ausgang | Erster Ausgang (Index 1). |
| Plug | `OUT2` | Ausgang | Zweiter Ausgang (Index 2). |
| Plug | `OUT3` | Ausgang | Dritter Ausgang (Index 3). |
| Plug | `OUT4` | Ausgang | Vierter Ausgang (Index 4). |

Alle Adapter sind vom Typ `adapter::types::unidirectional::ALI` (uni‑direktional, datenfließend).

## Funktionsweise

1. Im Ruhezustand wartet der FB auf ein `REQ`‑Ereignis.
2. Beim Eintreffen von `REQ` wird der aktuelle Wert des Dateneingangs `K` ausgelesen.
3. Der über den Socket `IN` anliegende ALI‑Adapterwert wird auf den Plug mit der entsprechenden Nummer (`OUT1` … `OUT4`) übertragen.
4. Nach erfolgreicher Übertragung wird das Ereignis `CNF` gesendet, das die Durchführung bestätigt.
5. Der baustein bleibt bereit für den nächsten `REQ`‑Aufruf.

## Technische Besonderheiten

- **Generische Erweiterung:** Der FB ist als generischer Typ deklariert (Attribut `GenericClassName = 'GEN_ALI_DEMUX'`). Mittels Typ‑Hash können spezifischere Varianten für unterschiedliche ALI‑Adapter‑Subtypen erzeugt werden, ohne die grundlegende Demultiplex‑Logik zu verändern.
- **Einfache Indexsteuerung:** Der Index `K` ist als `UINT` ausgeführt und deckt die Werte 1 bis 4 ab. Die Zuordnung erfolgt direkt über die Nummerierung der Plugs.
- **Adapterbasiert:** Die gesamte Datenübertragung erfolgt über ALI‑Adapter, sodass der FB in bestehende ALI‑Kommunikationsumgebungen integriert werden kann.

## Zustandsübersicht

Der ALI_DEMUX_4 besitzt einen impliziten, ereignisgesteuerten Ablauf:

- **IDLE** (Wartezustand): Der FB führt keine Operation durch, es liegt kein `REQ` an.
- **EXEC** (Ausführung): Nach Eingang von `REQ` wird der Demultiplex‑Vorgang gestartet. In diesem Zustand wird der Index ausgewertet und die Adapter‑Weiterleitung durchgeführt.
- **DONE** (Abschluss): Die Übertragung ist abgeschlossen, `CNF` wird ausgegeben. Anschließend kehrt der FB in den IDLE‑Zustand zurück.

Eine detaillierte Zustandsmaschine ist nicht explizit modelliert, da der FB rein ereignisgesteuert arbeitet.

## Anwendungsszenarien

- **Signalverteilung in der Landtechnik:** Ein Sensor liefert über den `IN`‑Adapter einen Messwert (z. B. Bodentemperatur, Feuchte). Je nach Index wird dieser Wert an einen von vier Aktoren oder übergeordneten Steuerungsblöcken weitergeleitet.
- **Rundfunk‑ oder Feldbus‑Selektion:** In einer Maschine mit mehreren parallelen Kommunikationskanälen kann der FB verwendet werden, um ein eingehendes ALI‑Paket gezielt an den richtigen Verarbeitungsbaustein zu routen.
- **Test‑ und Simulationsumgebungen:** Durch Umschalten des Index kann schnell zwischen verschiedenen Ausgabepfaden gewechselt werden, ohne den Datenfluss neu zu verdrahten.

## Vergleich mit ähnlichen Bausteinen

| Kriterium | ALI_DEMUX_4 | Standard‑Demultiplexer (z. B. DEMUX_4) |
|-----------|-------------|----------------------------------------|
| Schnittstelle | Adapter‑basiert (ALI‑Protokoll) | Meist einfache Daten‑E/A (BOOL, INT) |
| Flexibilität | Generischer Typ mit Hash | Fester Datentyp |
| Komplexität | Gering – reine Weiterleitung | Ähnlich, aber ohne Adapter‑Kopplung |
| Einsatzbereich | Speziell für ALI‑fähige Systeme | Allgemeine Steuerungstechnik |

Der ALI_DEMUX_4 ist spezifisch für die ALI‑Adapter‑Schnittstelle optimiert und bietet daher eine nahtlose Integration in ALI‑basierte Applikationen.

## Fazit

Der Funktionsblock **ALI_DEMUX_4** stellt eine einfache und effektive Möglichkeit dar, einen eingehenden ALI‑Signalstrom auf vier Ausgänge zu verteilen. Er zeichnet sich durch seine generische Bauweise, klare Schnittstellen und leichte Bedienbarkeit aus. Dank der Adapter‑Architektur ist er besonders in landwirtschaftlichen Steuerungssystemen mit ALI‑Protokoll einsetzbar und trägt zu einer sauberen Strukturierung des Datenflusses bei.