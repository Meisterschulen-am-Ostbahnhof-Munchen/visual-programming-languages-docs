# AUI_SPLIT_6_UNGATED

> ℹ️ **UNGATED-Variante:** Dieser Baustein ist die ungegatete Version von [`AUI_SPLIT_6`](AUI_SPLIT_6.md). Er unterdrückt **keine** unveränderten Wiederholungen – jedes neu berechnete Ergebnis wird bedingungslos weitergegeben, auch ohne Wertänderung. Das ist wichtig für Verbraucher, die eine periodische Kadenz unabhängig von Wertänderung brauchen (z. B. Ableitungs-/Frequenzberechnungen, die sonst nicht gegen Null abklingen). Alle Angaben zu Änderungserkennung/Change-Gating weiter unten auf dieser Seite gelten **nicht** für diesen Baustein.

![AUI_SPLIT_6_UNGATED](./AUI_SPLIT_6_UNGATED.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AUI_SPLIT_6_UNGATED** dient dazu, einen eingehenden **AUI-Adapter** (Application Universal Interface) auf sechs ausgehende AUI-Adapter aufzuteilen. Er ist als generischer Baustein konzipiert, der in der Lage ist, das eingehende AUI-Signal ohne Datenverarbeitung oder Logik auf alle sechs Ausgänge zu verteilen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine Ereignis-Eingänge vorhanden.

### **Ereignis-Ausgänge**

Keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**

Keine Daten-Eingänge vorhanden.

### **Daten-Ausgänge**

Keine Daten-Ausgänge vorhanden.

### **Adapter**

Der Baustein verwendet ausschließlich Adapter für die Kommunikation:

| Richtung | Name | Typ | Beschreibung |
| ---------- | ------ | ----- | -------------- |
| Eingang | **IN** | `adapter::types::unidirectional::AUI` | Eingehender AUI-Adapter, der aufgeteilt wird. |
| Ausgang | **OUT1** | `adapter::types::unidirectional::AUI` | Erster ausgehender AUI-Adapter. |
| Ausgang | **OUT2** | `adapter::types::unidirectional::AUI` | Zweiter ausgehender AUI-Adapter. |
| Ausgang | **OUT3** | `adapter::types::unidirectional::AUI` | Dritter ausgehender AUI-Adapter. |
| Ausgang | **OUT4** | `adapter::types::unidirectional::AUI` | Vierter ausgehender AUI-Adapter. |
| Ausgang | **OUT5** | `adapter::types::unidirectional::AUI` | Fünfter ausgehender AUI-Adapter. |
| Ausgang | **OUT6** | `adapter::types::unidirectional::AUI` | Sechster ausgehender AUI-Adapter. |

## Funktionsweise

Der Baustein leitet das am Adapter-Eingang **IN** ankommende AUI-Signal ohne jede Verzögerung oder Verarbeitung an alle sechs Adapter-Ausgänge (**OUT1** bis **OUT6**) weiter. Es findet keine Datenmanipulation statt – der Baustein wirkt als reiner Verteiler (Splitter) für AUI-Signale.

## Technische Besonderheiten

- Der Baustein ist als **generischer Funktionsblock** deklariert: Das Attribut `eclipse4diac::core::GenericClassName` ist auf `'GEN_AUI_SPLIT'` gesetzt.
- Es erfolgt keine Zustandsverwaltung oder Ereignislogik – der Baustein ist rein kombinatorisch.
- Die Ausgänge sind voneinander unabhängig; ein Fehler an einem Ausgang beeinflusst die anderen nicht.
- Durch die Verwendung von AUI-Adaptern ist der Baustein für eine unidirektionale Signalweitergabe optimiert.

## Zustandsübersicht

Der Baustein besitzt **keine Zustände**. Er arbeitet kontinuierlich und ohne interne Zustandsmaschine. Das Eingangssignal wird sofort und ständig auf alle Ausgänge gespiegelt.

## Anwendungsszenarien

- **Signalverteilung in der Steuerungstechnik**: Wenn ein AUI-Signal (z.B. ein Messwert oder Steuerbefehl) an mehrere Verbraucher weitergegeben werden muss.
- **Redundanz oder Parallelverarbeitung**: Verteilung eines Signals an mehrere identische nachgelagerte Funktionseinheiten.
- **Test- und Simulationsaufbauten**: Aufteilung eines AUI-Signals für gleichzeitige Überwachung und Verarbeitung.

## Vergleich mit ähnlichen Bausteinen

- **AUI_SPLIT_2 / AUI_SPLIT_4**: Diese Bausteine teilen ein Signal auf zwei bzw. vier Ausgänge auf. **AUI_SPLIT_6_UNGATED** bietet die größte Anzahl (6) an Ausgängen und deckt damit Anwendungen mit vielen parallelen Zielen ab.
- **AUI_MERGE_***: Im Gegensatz zu Splittern fassen Merge-Bausteine mehrere AUI-Signale zu einem zusammen.

- **[`AUI_SPLIT_6`](AUI_SPLIT_6.md)**: Die gegatete Variante – aktualisiert den Ausgang nur bei tatsächlicher Wertänderung.

## Änderungserkennung

Dieser Baustein führt **keine** Änderungserkennung durch. Jedes neu berechnete Ergebnis wird bedingungslos auf den Ausgang geschrieben und das zugehörige Adapter-Event gesendet, unabhängig davon, ob sich der Wert gegenüber dem vorherigen Durchlauf geändert hat.

## Fazit

Der **AUI_SPLIT_6_UNGATED** ist ein einfacher, aber effektiver Verteilerbaustein für AUI-Signale. Er ermöglicht die sternförmige Weiterleitung eines Eingangssignals an bis zu sechs unabhängige Ausgänge. Aufgrund seiner generischen Natur und fehlenden Logik eignet er sich hervorragend für flexible und erweiterbare Automatisierungslösungen.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
