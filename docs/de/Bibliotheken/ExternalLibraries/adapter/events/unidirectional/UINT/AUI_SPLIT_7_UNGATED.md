# AUI_SPLIT_7_UNGATED

> ℹ️ **UNGATED-Variante:** Dieser Baustein ist die ungegatete Version von [`AUI_SPLIT_7`](AUI_SPLIT_7.md). Er unterdrückt **keine** unveränderten Wiederholungen – jedes neu berechnete Ergebnis wird bedingungslos weitergegeben, auch ohne Wertänderung. Das ist wichtig für Verbraucher, die eine periodische Kadenz unabhängig von Wertänderung brauchen (z. B. Ableitungs-/Frequenzberechnungen, die sonst nicht gegen Null abklingen). Alle Angaben zu Änderungserkennung/Change-Gating weiter unten auf dieser Seite gelten **nicht** für diesen Baustein.

![AUI_SPLIT_7_UNGATED](./AUI_SPLIT_7_UNGATED.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AUI_SPLIT_7_UNGATED` dient dazu, ein eingehendes AUI‑Signal (Application User Interface) auf bis zu sieben identische Ausgänge zu verteilen. Er ist als generischer Baustein konzipiert und arbeitet ausschließlich über Adapter‑Schnittstellen – ohne Ereignis‑ oder Daten‑Ein‑/Ausgänge im klassischen Sinne. Dadurch eignet er sich besonders für reine Signalverteilungen in adapterbasierten Architekturen.

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

| Typ | Richtung | Name |
| --- | -------- | ---- |
| Socket (adapter::types::unidirectional::AUI) | Eingang | IN |
| Plug (adapter::types::unidirectional::AUI) | Ausgang | OUT1 |
| Plug (adapter::types::unidirectional::AUI) | Ausgang | OUT2 |
| Plug (adapter::types::unidirectional::AUI) | Ausgang | OUT3 |
| Plug (adapter::types::unidirectional::AUI) | Ausgang | OUT4 |
| Plug (adapter::types::unidirectional::AUI) | Ausgang | OUT5 |
| Plug (adapter::types::unidirectional::AUI) | Ausgang | OUT6 |
| Plug (adapter::types::unidirectional::AUI) | Ausgang | OUT7 |

## Funktionsweise

Der Baustein stellt eine 1‑zu‑7‑Verteilerlogik für AUI‑Adapter dar. Das über den Socket `IN` eingehende Signal wird ohne weitere Verarbeitung oder logische Bedingungen auf alle sieben Plugs (`OUT1` … `OUT7`) repliziert. Die Weiterleitung geschieht rein passiv: jedes empfangene Signal wird an jedem Ausgang gleichzeitig bereitgestellt.

## Technische Besonderheiten

- **Reiner Adapter‑Baustein**: Der FB enthält weder Ereignis‑ noch Daten‑Ein‑/Ausgänge – die gesamte Kommunikation erfolgt über die AUI‑Adapter.
- **Unidirektional**: Die Adapter sind vom Typ `unidirectional`, d. h. die Daten fließen nur vom Eingang (Socket) zu den Ausgängen (Plugs).
- **Generischer Typ**: Der FB ist als generischer Baustein (`GenericClassName = 'GEN_AUI_SPLIT'`) implementiert und kann für verschiedene AUI‑Untertypen wiederverwendet werden.
- **Keine Zustandslogik**: Aufgrund der reinen Verteilungsfunktion besitzt der Baustein keinen internen Zustandsautomaten – er arbeitet kontinuierlich und ohne Verzögerung.

## Zustandsübersicht

Es existiert keine Zustandsmaschine. Der Baustein ist rein datenflussgesteuert und besitzt nur einen statischen Betriebszustand.

## Anwendungsszenarien

- **Signalverteilung in der Feldautomatisierung**: Ein von einer zentralen Steuerung kommendes AUI‑Signal (z. B. Sensordaten oder Steuerbefehle) wird an mehrere parallele Aktoren oder Anzeigeeinheiten weitergeleitet.
- **Test‑ und Simulationsumgebungen**: Einsatz als Splitter, um ein Eingangssignal gleichzeitig auf mehrere Simulations‑ oder Diagnoseeinheiten zu geben.
- **Modulare Systeme**: In adapterbasierten Architekturen (z. B. nach IEC 61499) wird der Baustein genutzt, um eine einzige Schnittstelle auf mehrere nachgelagerte Funktionsblöcke aufzuteilen.

## Vergleich mit ähnlichen Bausteinen

- **AUI_SPLIT_2, AUI_SPLIT_4** – Bausteine mit gleicher Funktionsweise, jedoch auf 2 bzw. 4 Ausgänge reduziert. Der `AUI_SPLIT_7_UNGATED` bietet die größte Anzahl an Ausgängen und deckt damit umfangreichere Verteilungsanforderungen ab.
- **AUI_MERGE** – das Gegenstück, das mehrere AUI‑Eingänge zu einem Ausgang zusammenführt. Im Gegensatz dazu ist der `SPLIT` rein passiv und aggregiert keine Daten.

- **[`AUI_SPLIT_7`](AUI_SPLIT_7.md)**: Die gegatete Variante – aktualisiert den Ausgang nur bei tatsächlicher Wertänderung.

## Änderungserkennung

Dieser Baustein führt **keine** Änderungserkennung durch. Jedes neu berechnete Ergebnis wird bedingungslos auf den Ausgang geschrieben und das zugehörige Adapter-Event gesendet, unabhängig davon, ob sich der Wert gegenüber dem vorherigen Durchlauf geändert hat.

## Fazit

Der `AUI_SPLIT_7_UNGATED` ist ein einfacher, aber essenzieller Funktionsblock zur unidirektionalen Signalverteilung in adapterbasierten Steuerungssystemen. Dank seines generischen Designs und der klaren 1‑zu‑N‑Struktur lässt er sich flexibel in beliebige AUI‑basierte Architekturen integrieren. Für Anwendungen, die eine breite Parallelverteilung ohne Nebenwirkungen erfordern, stellt er eine robuste und wartungsfreundliche Lösung dar.
