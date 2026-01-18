# AE2_SPLIT_MERGE_FORWARD

```{index} single: AE2_SPLIT_MERGE_FORWARD
```

<img width="1208" height="217" alt="image" src="https://github.com/user-attachments/assets/68ee26f9-debb-44fc-8735-e765847cdb6f" />

* * * * * * * * * *

## 📺 Video

* [2025-12-14 20-13-12 Hutschienenmoped Merged Bin aufspielen per ESPTOOL js.](https://www.youtube.com/watch?v=XwtH1p5uw88)
* [Hutschienenmoped flashen mit der Merged Flash](https://www.youtube.com/watch?v=y7wVxIezsHA)

## Einleitung
Der Funktionsblock AE2_SPLIT_MERGE_FORWARD ist ein bidirektionaler Splitter und Merger mit bidirektionaler Weiterleitung. Er dient als universeller Verteiler und Sammler für Ereignisse in 4diac-Systemen und ermöglicht die flexible Verteilung von Ereignissen über verschiedene Schnittstellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **EI**: Eingangsereignis (Input Event)

### **Ereignis-Ausgänge**
- **EO**: Ausgangsereignis (Output Event)

### **Adapter**
- **PLUG**: Bidirektionaler Adapter vom Typ AE2
- **SOCKET**: Bidirektionaler Adapter vom Typ AE2

## Funktionsweise
Der Funktionsblock arbeitet nach folgenden Prinzipien:

1. **Ereignisverteilung**: Jedes am EI-Eingang eingehende Ereignis wird gleichzeitig an beide Adapter (PLUG und SOCKET) weitergeleitet.

2. **Ereigniszusammenführung**: Ereignisse, die über einen der beiden Adapter (PLUG oder SOCKET) eingehen, werden am EO-Ausgang ausgegeben.

3. **Bidirektionale Weiterleitung**: Zusätzlich werden Ereignisse zwischen den beiden Adaptern bidirektional weitergeleitet, sodass PLUG- und SOCKET-Ereignisse untereinander ausgetauscht werden können.

## Technische Besonderheiten
- Verwendet den bidirektionalen AE2-Adapter-Typ
- Ermöglicht parallele Ereignisverteilung
- Bietet vollständige bidirektionale Kommunikation zwischen allen Schnittstellen
- Keine Datenverbindungen - rein ereignisbasiert

## Zustandsübersicht
Der Funktionsblock verfügt über keine internen Zustände und arbeitet rein kombinatorisch. Alle Ereignisverarbeitungen erfolgen sofort bei Eintreffen eines Ereignisses.

## Anwendungsszenarien
- Verteiler für Steuerereignisse in komplexen Automatisierungsnetzwerken
- Schnittstellenadapter zwischen verschiedenen Systemkomponenten
- Ereignis-Routing in modularen Steuerungsarchitekturen
- Bidirektionale Kommunikationsbrücken zwischen Funktionsblöcken

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Splitter-Blöcken bietet AE2_SPLIT_MERGE_FORWARD zusätzlich:
- Bidirektionale Funktionalität
- Adapter-basierte Schnittstellen
- Ereignis-Zusammenführung
- Direkte Kommunikation zwischen Adaptern

## Fazit
Der AE2_SPLIT_MERGE_FORWARD ist ein vielseitiger Funktionsblock für komplexe Ereignisverteilungs- und Sammelaufgaben in 4diac-Systemen. Seine bidirektionale Natur und die Adapter-Schnittstellen machen ihn besonders geeignet für modulare und erweiterbare Automatisierungslösungen.