# ALI_MUX_3


![ALI_MUX_3](./ALI_MUX_3.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ALI_MUX_3** ist ein generischer Multiplexer für ALI-Datenströme. Er wählt aus drei unidirektionalen ALI-Eingängen (IN1, IN2, IN3) einen aus und gibt diesen über den ALI-Ausgang (OUT) weiter. Die Auswahl erfolgt über den Index K, der über den Ereigniseingang REQ gesetzt wird. Der Baustein wird als generischer FB bereitgestellt und kann in Eclipse 4diac verwendet werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Setzt den Index K und startet die Multiplexer-Funktion. Wird mit dem Daten-Eingang K verwendet (With). |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF  | Event | Bestätigt, dass der Index K gesetzt und der Ausgang aktualisiert wurde. |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| K    | UINT | Auswahlindex für den Multiplexer. Gültige Werte: 0 (IN1), 1 (IN2), 2 (IN3). |

### **Daten-Ausgänge**

*Keine direkten Datenausgänge vorhanden.* Die Ausgabe erfolgt über den Adapter-Ausgang.

### **Adapter**

| Typ | Name | Richtung | Kommentar |
|-----|------|----------|-----------|
| **adapter::types::unidirectional::ALI** | IN1 | Socket | Erster Eingang (wird bei K = 0 durchgeschaltet) |
| **adapter::types::unidirectional::ALI** | IN2 | Socket | Zweiter Eingang (wird bei K = 1 durchgeschaltet) |
| **adapter::types::unidirectional::ALI** | IN3 | Socket | Dritter Eingang (wird bei K = 2 durchgeschaltet) |
| **adapter::types::unidirectional::ALI** | OUT | Plug | Ausgang, der den ausgewählten Eingang weitergibt |

## Funktionsweise

Der FB arbeitet ereignisgesteuert. Ein gültiges Ereignis am Eingang REQ löst folgende Schritte aus:
1. Der aktuelle Wert des Daten-Eingangs K wird gelesen.
2. Abhängig von K wird einer der drei Socket-Adapter (IN1 für K=0, IN2 für K=1, IN3 für K=2) auf den Plug-Adapter OUT geschaltet.
3. Nach erfolgter Durchschaltung wird der Ereignisausgang CNF ausgegeben.

Der Baustein ist unidirektional – Daten fließen nur von den Eingängen zum Ausgang. Der Index K muss vor dem REQ-Ereignis anliegen, da er mit dem Ereignis verbunden ist (With).

## Technische Besonderheiten

- **Generischer Funktionsblock:** Der FB ist als generischer Typ (GenericClassName `GEN_ALI_MUX`) deklariert und kann mit unterschiedlichen Implementierungen oder Instanzen versehen werden.
- **Adapter-basiert:** Alle Ein- und Ausgänge verwenden den gleichen Adaptertyp (`adapter::types::unidirectional::ALI`). Dies ermöglicht eine flexible und typensichere Verbindung mit anderen ALI-Komponenten.
- **TypHash:** Der FB enthält ein Attribut `eclipse4diac::core::TypeHash`, das zur Laufzeit für eindeutige Typidentifikation genutzt werden kann.
- **Nur ein Ereigniseingang:** Die gesamte Steuerlogik erfolgt über das einzige Ereignis REQ. Es gibt keine getrennten Ereignisse für jeden Eingang oder für das Setzen des Index.

## Zustandsübersicht

Der FB besitzt keinen expliziten Zustandsautomaten (ECC) in der XML-Definition. Das Verhalten ist ereignisgesteuert und folgt einem einfachen Ablauf:

| Zustand | Beschreibung |
|---------|--------------|
| **Idle** | Warten auf ein REQ-Ereignis. |
| **Processing** | Nach REQ: Auswahl des Eingangs basierend auf K, Durchschaltung auf OUT. |
| **Done** | Ausgabe von CNF, Rückkehr zu Idle. |

Da kein detaillierter ECC vorliegt, wird die Implementierung als deterministischer, nicht-blockierender Algorithmus angenommen.

## Anwendungsszenarien

- **Sensorauswahl:** In der Agrartechnik (Hinweis aus den Metadaten) können verschiedene Sensoren (z.B. Temperatur, Feuchte, Drehzahl) über ALI-Schnittstellen angeschlossen sein. Der Multiplexer wählt den jeweils benötigten Sensorwert aus.
- **Konfigurationsumschaltung:** In Maschinensteuerungen kann der FB verwendet werden, um zwischen mehreren vorkonfigurierten ALI-Datenpfaden umzuschalten.
- **Redundanz:** Falls einer der Eingänge ausfällt, kann der Multiplexer auf einen anderen umschalten, um den Betrieb aufrechtzuerhalten.

## Vergleich mit ähnlichen Bausteinen

- **ALI_MUX_2:** Ein Multiplexer mit nur zwei Eingängen. ALI_MUX_3 bietet eine zusätzliche Auswahlmöglichkeit (Index 0–2).
- **Standard-MUX (z.B. IEC 61499 MUX):** Ein allgemeiner Multiplexer arbeitet typischerweise mit einfachen Datentypen (INT, REAL) und Ereignissen. ALI_MUX_3 ist speziell für den ALI-Adaptertyp ausgelegt.
- **ALI_SELECT:** Ein Baustein, der durch ein boolesches Signal zwischen zwei ALI-Quellen wählt. ALI_MUX_3 erlaubt die Auswahl aus drei Quellen mittels eines UINT-Index.

## Fazit

Der **ALI_MUX_3** ist ein kompakter und flexibler Multiplexer für drei unidirektionale ALI-Datenströme. Er eignet sich besonders für Anwendungen, in denen mehrere ALI-Quellen über einen Index ausgewählt werden müssen. Die generische Definition erleichtert die Anpassung an spezifische Implementierungen, und die reine Adapter-Schnittstelle sorgt für eine saubere, typisierte Kommunikation. Der Baustein ist ein grundlegendes Element in ALI-basierten Steuerungssystemen.