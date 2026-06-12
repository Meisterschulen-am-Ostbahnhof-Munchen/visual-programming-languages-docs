# ALI_SPLIT_7


![ALI_SPLIT_7](./ALI_SPLIT_7.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **ALI_SPLIT_7** ist ein generischer Splitter, der einen eingehenden ALI-Adapter (Socket `IN`) auf sieben ausgehende ALI-Adapter (Plugs `OUT1`…`OUT7`) verteilt. Er dient zur 1:7-Verteilung von Daten und Ereignissen innerhalb eines unidirektionalen ALI-Kommunikationspfades.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine.

### **Ereignis-Ausgänge**
Keine.

### **Daten-Eingänge**
Keine.

### **Daten-Ausgänge**
Keine.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-------------------|-------------|
| Socket (Eingang) | `IN` | `adapter::types::unidirectional::ALI` | Eingangsadapter, dessen Daten und Ereignisse verteilt werden. |
| Plug (Ausgang) | `OUT1` | `adapter::types::unidirectional::ALI` | Erster Ausgangsadapter. |
| Plug (Ausgang) | `OUT2` | `adapter::types::unidirectional::ALI` | Zweiter Ausgangsadapter. |
| Plug (Ausgang) | `OUT3` | `adapter::types::unidirectional::ALI` | Dritter Ausgangsadapter. |
| Plug (Ausgang) | `OUT4` | `adapter::types::unidirectional::ALI` | Vierter Ausgangsadapter. |
| Plug (Ausgang) | `OUT5` | `adapter::types::unidirectional::ALI` | Fünfter Ausgangsadapter. |
| Plug (Ausgang) | `OUT6` | `adapter::types::unidirectional::ALI` | Sechster Ausgangsadapter. |
| Plug (Ausgang) | `OUT7` | `adapter::types::unidirectional::ALI` | Siebter Ausgangsadapter. |

## Funktionsweise
Der Baustein leitet sämtliche über den Socket `IN` eingehenden ALI-Signale (sowohl Daten als auch Ereignisse) unverändert an alle sieben Ausgangsadapter `OUT1`…`OUT7` weiter. Somit entsteht eine strenge 1:7-Parallelverteilung ohne Verzögerung oder Pufferung. Der FB verhält sich rein kombinatorisch; es findet keine Verarbeitung oder Filterung der Inhalte statt.

## Technische Besonderheiten
- **Generischer Typ**: Der FB ist als generischer Baustein deklariert (`GenericClassName = 'GEN_ALI_SPLIT'`). Dadurch kann er für unterschiedliche ALI-Adapter-Varianten verwendet werden, sofern diese das gleiche Schnittstellenprotokoll (unidirektionale Adapter) unterstützen.
- **Keine Zustände**: Der Baustein besitzt keine Zustandsmaschine (ECC) und speichert keinerlei Daten. Jeder Durchlauf ist deterministisch und nebenwirkungsfrei.
- **Flexible Verteilung**: Durch die feste Anzahl von sieben Ausgängen eignet sich der FB speziell für Anwendungen, die eine Aufteilung auf genau sieben Pfade erfordern.

## Zustandsübersicht
Der FB verfügt über **keine expliziten Zustände**. Seine Funktionalität ist rein passiv und datenflussgetrieben.

## Anwendungsszenarien
- **Parallele Signalverteilung**: Ein von einem übergeordneten Steuermodul gesendeter ALI-Datenstrom soll gleichzeitig an mehrere nachgelagerte Module (z. B. Aktoren, Visualisierungen oder Protokollierungen) weitergegeben werden.
- **Redundanz oder Lastverteilung**: Mehrere identische Verarbeitungseinheiten erhalten dieselben ALI-Eingangsdaten und arbeiten unabhängig voneinander.
- **Adapter‑Konvertierung**: In Kombination mit spezialisierten ALI‑Adaptern kann der Splitter dazu dienen, einen Datenpfad auf unterschiedliche Logik‑ oder Hardware‑Schnittstellen zu vervielfachen.

## Vergleich mit ähnlichen Bausteinen
- **ALI_SPLIT_2 / ALI_SPLIT_4**: Diese Bausteine bieten Aufteilungen auf zwei bzw. vier Ausgänge. `ALI_SPLIT_7` ist die Erweiterung auf sieben Ausgänge für spezifische Anforderungen.
- **ALI_MERGE**: Das Gegenstück, das mehrere ALI‑Eingänge zu einem Ausgang zusammenführt. Ein Splitter wie `ALI_SPLIT_7` arbeitet in umgekehrter Richtung (Fan‑Out).

## Fazit
Der **ALI_SPLIT_7** ist ein spezialisierter, generischer Funktionsbaustein zur sauberen und verlustfreien 1:7‑Verteilung von unidirektionalen ALI‑Signalen. Durch seine einfache Struktur, die fehlende Zustandslogik und die generische Auslegung eignet er sich ideal für modulare Steuerungsarchitekturen, bei denen ein Signal parallel an mehrere Empfänger weitergeleitet werden muss.