# SPLIT_MI_DO_S_Dual_SA


![SPLIT_MI_DO_S_Dual_SA](./SPLIT_MI_DO_S_Dual_SA.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsbaustein **SPLIT_MI_DO_S_Dual_SA** dient dazu, einen einzelnen Datenpanel-Eingang vom Typ `DataPanel_MI_DO_S_Dual_SA` in zwei separate Ausgänge vom Typ `DataPanel_MI_DO_S_Single_SA` aufzuteilen. Dabei werden die in der dualen Struktur enthaltenen Antriebsinformationen für eine Vorwärts-/Rückwärtsbewegung (bzw. oben/unten, rechts/links, im/gegen Uhrzeigersinn) auf zwei unabhängige Ausgänge verteilt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Ereignis | Beschreibung |
|----------|--------------|
| REQ      | Dienstanforderung: Der Baustein verarbeitet den aktuellen Wert des Dateneingangs IN. |

### **Ereignis-Ausgänge**
| Ereignis | Beschreibung |
|----------|--------------|
| CNF      | Bestätigung der durchgeführten Verarbeitung. Wird nach der Ausführung des Algo–rithmus gesendet. |

### **Daten-Eingänge**
| Name | Typ | Beschreibung |
|------|-----|--------------|
| IN   | `DataPanel::io::MI::DQ::DataPanel_MI_DO_S_Dual_SA` | Dualer Eingang, der sowohl Vorwärts- (UP) als auch Rückwärts- (DOWN) Informationen trägt. |

### **Daten-Ausgänge**
| Name  | Typ | Beschreibung |
|-------|-----|--------------|
| UP    | `DataPanel::io::MI::DQ::DataPanel_MI_DO_S_Single_SA` | Ausgang für die Vorwärts-, Aufwärts-, Rechts- oder Rechtsdrehrichtung. |
| DOWN  | `DataPanel::io::MI::DQ::DataPanel_MI_DO_S_Single_SA` | Ausgang für die Rückwärts-, Abwärts-, Links- oder Linksdrehrichtung. |

### **Adapter**
Keine.

## Funktionsweise
Der Baustein wird durch das Ereignis **REQ** aktiviert. Im zugehörigen Algorithmus werden folgende Zuweisungen durchgeführt:

- Der gemeinsame Steuerwert `u8SAMember` der dualen Struktur wird unverändert an beide Ausgänge (`UP.u8SAMember` und `DOWN.u8SAMember`) weitergegeben.
- Die Richtungsinformationen werden getrennt: Der Ausgang `UP.Port` erhält den Wert des Feldes `IN.Up`, und der Ausgang `DOWN.Port` den Wert des Feldes `IN.Down`.
- Nach Ausführung des Algorithmus wird das Bestätigungsereignis **CNF** gesendet.

## Technische Besonderheiten
- Der Baustein ist als einfacher Funktionsbaustein (SimpleFB) realisiert, d. h. die Logik wird innerhalb eines einzigen Algorithmus ohne Zustandsmaschine ausgeführt.
- Die verwendeten Datentypen stammen aus dem Paket `DataPanel::io::MI::DQ`. Sie sind als implizite Importe im Baustein deklariert.
- Die Ausgangsdaten sind zum Zeitpunkt des **CNF**-Ereignisses gültig.

## Zustandsübersicht
Der Baustein besitzt nur einen einzigen EC-Zustand **REQ**, in dem der Algorithmus ausgeführt und anschließend das Ausgangsereignis **CNF** gesetzt wird. Es gibt keine weiteren Zustände oder Verzweigungen.

## Anwendungsszenarien
- Aufteilung eines kombinierten Antriebssignals für einen bidirektionalen Motor in zwei separate Steuerleitungen (z. B. für Drehrichtungssteuerung).
- Trennung von Vorwärts- und Rückwärtssignalen in einer Maschinensteuerung, wenn nachgelagerte Bausteine getrennte Eingänge für jede Bewegungsrichtung erwarten.
- Vorbereitung von Daten für zwei unabhängige Aktoren, die mit demselben Betriebsmodus (z. B. Leistungsstufe) arbeiten, aber unterschiedliche Richtungen ansteuern.

## Vergleich mit ähnlichen Bausteinen
Ein möglicher alternativer Ansatz wäre die Verwendung eines allgemeinen Splitter-Bausteins, der beliebige Verbunddatentypen auftrennt. **SPLIT_MI_DO_S_Dual_SA** ist jedoch speziell auf die genannten Datentypen zugeschnitten und übernimmt direkt die korrekte Zuordnung der Richtungsfelder, was die Fehleranfälligkeit reduziert und die Lesbarkeit des Steuerungscodes erhöht.

## Fazit
**SPLIT_MI_DO_S_Dual_SA** bietet eine einfache und zuverlässige Möglichkeit, einen dualen Datenpanel-Steuerbefehl in zwei separate Ausgänge für die entgegengesetzten Bewegungsrichtungen aufzuteilen. Durch die klar definierte Schnittstelle und die direkte Verarbeitung aus einem Ereignisaufruf eignet er sich besonders für den Einsatz in modularen Steuerungssystemen, bei denen eine saubere Trennung der Richtungssignale erforderlich ist.