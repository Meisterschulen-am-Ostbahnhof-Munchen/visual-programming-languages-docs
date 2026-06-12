# AI_FB_CTD


![AI_FB_CTD](./AI_FB_CTD.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AI_FB_CTD** ist ein nach IEC 61499-2 standardisierter Abwärtszähler (**Down Counter**) für Integer-Werte. Er nutzt durchgängig Adapter-Schnittstellen (AX, AI), um Ereignisse und Daten zu transportieren. Der Baustein ist als Wrapper um den klassischen IEC 61131-FB `FB_CTD` realisiert und ermöglicht eine modulare, adapterbasierte Verbindung in 4diac-IDE-Netzwerken. Jedes eingehende Ereignis über die Zählersteuerungen (CD, LD, PV) führt zur Aktualisierung des internen Zählers und löst ein Ausgangsereignis aus.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Der FB besitzt keine direkten, separaten Ereignis-Eingänge. Die erforderlichen Ereignisse werden über die **Socket-Adapter** (CD, LD, PV) bereitgestellt – jedes dieser Module führt ein Ereignis (E1) mit sich, das die Zählerlogik triggert.

| Socket | Ereignis (im Adapter) | Beschreibung                 |
|--------|-----------------------|------------------------------|
| CD     | E1                    | Zählereignis (Abwärtszähler) |
| LD     | E1                    | Ladeereignis (Setzen auf PV) |
| PV     | E1                    | Vorgabeaktualisierung        |

### **Ereignis-Ausgänge**
| Name | Typ    | Beschreibung                                              |
|------|--------|-----------------------------------------------------------|
| CNF  | Event  | Bestätigungsereignis nach jeder Zähleraktualisierung (CD, LD, PV) |

Zusätzlich werden die Ausgangsereignisse auch über die **Plug-Adapter** Q und CV (jeweils E1) weitergegeben.

### **Daten-Eingänge**
Es gibt keine direkten Daten-Eingänge. Alle Datenwerte werden über die Socket-Adapter übertragen:
- **CD** liefert den Abwärtszählimpuls (D1) – logischer Wert, der den Zähler dekrementiert.
- **LD** liefert das Ladesignal (D1) – logischer Wert, der den Zähler auf den aktuellen PV-Wert setzt.
- **PV** liefert den Vorgabewert (D1) – Integer, der als neuer Zählerstand geladen wird.

### **Daten-Ausgänge**
Es gibt keine direkten Daten-Ausgänge. Die Ausgangsdaten werden über die Plug-Adapter bereitgestellt:
- **Q** liefert den Zählerstatus (D1) – BOOL, TRUE wenn Zählerstand ≤ 0.
- **CV** liefert den aktuellen Zählerstand (D1) – INT.

### **Adapter**
| Bezeichnung | Richtung | Typ                               | Beschreibung                                         |
|-------------|----------|-----------------------------------|------------------------------------------------------|
| CD          | Socket   | `adapter::types::unidirectional::AX` | Zählereingang (Ereignis + Daten) für Abwärtszählen   |
| LD          | Socket   | `adapter::types::unidirectional::AX` | Ladeeingang (Ereignis + Daten) zum Setzen auf PV     |
| PV          | Socket   | `adapter::types::unidirectional::AI` | Vorgabeeingang (Ereignis + Daten) für den Preset-Wert|
| Q           | Plug     | `adapter::types::unidirectional::AX` | Ausgangssignal (Ereignis + Daten) – Zähler ≤ 0       |
| CV          | Plug     | `adapter::types::unidirectional::AI` | Ausgangszählerwert (Ereignis + aktueller Zählerstand)|

## Funktionsweise

Der Baustein enthält intern einen `iec61131::counters::FB_CTD`, der die eigentliche Zähllogik implementiert. Die Funktion ist wie folgt:

1. Ein Ereignis an **CD** (über `CD.E1`) oder **LD** (`LD.E1`) oder **PV** (`PV.E1`) triggert den internen FB über seinen `REQ`-Ereigniseingang.
2. Der interne FB wertet die zugehörigen Daten aus:
   - Bei einem **CD**-Ereignis wird der Zähler um 1 dekrementiert (wenn das zugehörige Datum TRUE ist).
   - Bei einem **LD**-Ereignis wird der Zähler auf den aktuellen Wert von **PV** gesetzt (wenn das Ladedatum TRUE ist).
   - Bei einem **PV**-Ereignis wird der Vorgabewert intern aktualisiert (der Zähler bleibt unverändert).
3. Nach der Verarbeitung erzeugt der interne FB sein `CNF`-Ereignis. Dieses wird auf die externen Ausgänge verteilt:
   - `CNF` (direkter Event-Ausgang)
   - `Q.E1` (Ereignis des Plug-Adapters Q)
   - `CV.E1` (Ereignis des Plug-Adapters CV)
4. Zeitgleich werden die Daten:
   - `FB_CTD.Q` (BOOL) → `Q.D1`
   - `FB_CTD.CV` (INT) → `CV.D1`
   übertragen.

Hinweis: Das Ausgangsereignis wird **bei jeder Aktualisierung** (also bei CD, LD oder PV) ausgelöst. Eine reine Wertänderung ohne Ereignis (On-Change) ist nicht implementiert.

## Technische Besonderheiten

- **Lizenz und Herkunft**: Der Baustein steht unter der **Eclipse Public License 2.0** (EPL 2.0). Er wurde als Lehrmaterial für die Meisterschulen am Ostbahnhof entwickelt.
- **Adapter-basierte Kommunikation**: Anders als klassische FB-Schnittstellen werden alle Ein- und Ausgänge über Adapter (AX, AI) realisiert. Dies ermöglicht eine flexible, hierarchische Verdrahtung und Wiederverwendung in komplexen Steuerungsarchitekturen.
- **On-Change-Filter**: Der Baustein feuert das Ausgangsereignis bei **jedem** Eingangsereignis, unabhängig von einer tatsächlichen Wertänderung. Soll eine Änderungsdetektion erfolgen, wird der Einsatz eines **AX_D_FF** (Differentiator-Flipflop) als Vorfilter empfohlen (siehe auch Copyright-Hinweis in der XML).
- **Interner FB**: Die Zähllogik basiert auf dem Standardbaustein `FB_CTD` aus IEC 61131 (adaptiert für 4diac). Dadurch ist das Verhalten deterministisch und kompatibel zu SPS-Programmen.

## Zustandsübersicht

Der Baustein besitzt keinen expliziten Zustandsautomaten. Die einzige innere Variable ist der **aktuelle Zählerwert** (Integer). Dieser wird durch die Ereignisse verändert:

- Initialwert: 0 (oder durch LD auf PV gesetzt)
- CD-Ereignis: Zähler = Zähler - 1 (wenn zugehöriges Datum TRUE, sonst keine Änderung)
- LD-Ereignis: Zähler = PV (wenn Ladedatum TRUE)
- PV-Ereignis: PV-Wert wird intern gespeichert, Zähler bleibt unverändert.

Eine grafische Zustandsmaschine ist daher nicht erforderlich.

## Anwendungsszenarien

- **Bestandszähler**: Dekrementierung eines Lagerbestands bei Entnahme (CD), Neusetzen über LD nach Auffüllung.
- **Ereigniszähler mit Grenzwert**: Zählen von Ereignissen bis zum Erreichen von 0, dann Auslösen eines Signals (Q).
- **Zeit-/Impulssteuerung**: Verwendung als Pulszähler in Verbindung mit einem Taktgeber (CD) und Vorgabe der gewünschten Anzahl (PV).
- **Adapter-Integration**: In modularen Steuerungssystemen, bei denen Ereignisse und Daten über standardisierte Adapter-Schnittstellen gekapselt werden sollen.

## Vergleich mit ähnlichen Bausteinen

| Baustein        | Zählrichtung | Schnittstellen       | Besonderheit                                      |
|-----------------|--------------|----------------------|---------------------------------------------------|
| **AI_FB_CTD**   | Abwärts      | Nur Adapter (AX, AI) | Ausgang bei jeder Aktualisierung                  |
| **AI_FB_CTU**   | Aufwärts     | Nur Adapter (AX, AI) | Aufwärtszähler, analoge Struktur                  |
| **FB_CTD** (Standard) | Abwärts | Direkte Events/Daten | Klassischer Variablenanschluss, ohne Adapter      |
| **FB_CTUD**     | Beide        | Direkt               | Kombinierter Auf-/Abwärtszähler, erweiterte Logik |

Der **AI_FB_CTD** hebt sich durch die konsequente Adapter-Nutzung hervor, was ihn ideal für hierarchische und wiederverwendbare Steuerungsmodelle macht. Im Unterschied zum Standard-FB_CTD entfallen separate Daten- und Eventeingänge – alles wird über die Adapter geführt.

## Fazit

Der `AI_FB_CTD` ist ein flexibler, adapterbasierter Abwärtszähler für Integer-Werte, der die bewährte Zähllogik aus IEC 61131 in eine moderne, modulare Schnittstellenlandschaft überführt. Er eignet sich hervorragend für den Einsatz in verteilten Steuerungssystemen nach IEC 61499, bei denen Kapselung und Wiederverwendbarkeit im Vordergrund stehen. Die einfache Handhabung (drei Eingangsereignisse, zwei Ausgangsadapter) und die klare Dokumentation machen ihn zu einem soliden Grundbaustein für Zähleranwendungen. Empfohlen wird bei Bedarf an Änderungsdetektion die Vorschaltung eines `AX_D_FF`.