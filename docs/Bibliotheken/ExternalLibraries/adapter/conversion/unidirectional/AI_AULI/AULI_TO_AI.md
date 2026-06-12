# AULI_TO_AI


![AULI_TO_AI](./AULI_TO_AI.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AULI_TO_AI** ist ein zusammengesetzter Baustein (Composite FB), der einen eingehenden Adapter vom Typ **AULI** (ULINT-basiert) in einen ausgehenden Adapter vom Typ **AI** (INT-basiert) konvertiert. Er dient als Schnittstellenwandler zwischen Komponenten, die unterschiedliche Datentypen für analoge Werte verwenden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Der Baustein selbst besitzt keine direkten Ereignis-Eingänge. Die Ereignissteuerung erfolgt über die angeschlossenen Adapter.

### **Ereignis-Ausgänge**
Auch auf dieser Ebene sind keine dedizierten Ereignis-Ausgänge vorhanden; die Ausgabeereignisse werden über den AI_OUT-Adapter weitergegeben.

### **Daten-Eingänge**
- Keine direkten Dateneingänge auf Blockebene. Die Daten gelangen über den Socket `AULI_IN` in den Baustein.

### **Daten-Ausgänge**
- Keine direkten Datenausgänge auf Blockebene. Die konvertierten Daten werden über den Plug `AI_OUT` ausgegeben.

### **Adapter**

| Name      | Richtung | Typ                                      | Beschreibung                                |
|-----------|----------|------------------------------------------|---------------------------------------------|
| `AULI_IN` | Socket   | `adapter::types::unidirectional::AULI`   | ULINT-Eingangsadapter (analoger Wert)       |
| `AI_OUT`  | Plug     | `adapter::types::unidirectional::AI`     | INT-Ausgangsadapter (konvertierter Wert)    |

## Funktionsweise

Der Baustein verwendet intern den vordefinierten Funktionsblock `F_ULINT_TO_INT` aus der IEC 61131-Bibliothek. Die Funktionsweise ist:

1. Ein Ereignis vom Socket `AULI_IN.E1` triggert die Konvertierung des Datenwerts `AULI_IN.D1` (ULINT) über den internen FB `Convert`.
2. Der FB `Convert` führt die Typumwandlung von `ULINT` nach `INT` aus.
3. Nach erfolgreicher Konvertierung wird das Ausgangsereignis `Convert.CNF` ausgelöst, welches das Ereignis `AI_OUT.E1` aktiviert.
4. Der konvertierte Datenwert (`Convert.OUT`) wird an `AI_OUT.D1` weitergeleitet.

Damit wird eine nahtlose, ereignisgesteuerte Umwandlung von AULI- auf AI-Adapter realisiert.

## Technische Besonderheiten

- **Komposition:** Der Baustein ist als Composite FB realisiert, d.h. er kapselt die Logik in einem übersichtlichen Baustein und nutzt einen standardisierten Konvertierungsbaustein.
- **Unidirektionale Adapter:** Sowohl `AULI_IN` als auch `AI_OUT` sind unidirektionale Adapter, die nur eine Datenflussrichtung unterstützen.
- **Ereignisgesteuert:** Der Konvertierungsprozess startet nur bei einem eingehenden Ereignis, was eine effiziente Verarbeitung ermöglicht.
- **Lizenzhinweis:** Der Baustein unterliegt der Eclipse Public License 2.0.

## Zustandsübersicht

Da der Baustein rein ereignisgesteuert arbeitet und keine internen Zustände speichert, gibt es keine explizite Zustandsmaschine. Er verhält sich wie eine funktionale Transformation: Auf jedes Ereignis am Eingang erfolgt die Konvertierung und ein Ausgangsereignis.

Interner Ablauf (vereinfacht):
- **Idle:** Warten auf Ereignis von `AULI_IN`.
- **Processing:** Konvertierung läuft (instantan, da synchroner FB).
- **Done:** Ausgangsereignis wird gesendet, Rückkehr zu Idle.

## Anwendungsszenarien

- **Systemintegration:** Verbindung von Komponenten, die unterschiedliche Datentypen für analoge Signale verwenden (z.B. ein Sensor liefert ULINT, ein Aktuator erwartet INT).
- **Adapter-Kaskaden:** Erweiterung von Protokollumsetzungen in Automatisierungsprojekten.
- **Datentypanpassung:** Wenn ein Feldbus- oder Gateway-Modul nur ULINT-Werte liefert, das Steuerungssystem jedoch INT benötigt.

## Vergleich mit ähnlichen Bausteinen

| Baustein            | Eingabetyp | Ausgabetyp | Beschreibung                                   |
|---------------------|------------|------------|------------------------------------------------|
| `AULI_TO_AI`        | AULI (ULINT) | AI (INT) | Konvertiert ganze Adapter-Schnittstellen.      |
| `F_ULINT_TO_INT`    | ULINT      | INT        | Nur Datenkonvertierung, keine Adapter.         |
| `AI_TO_AULI` (ggf.) | AI (INT)   | AULI (ULINT) | Umgekehrte Richtung (nicht vorhanden).       |

Der wesentliche Unterschied zu reinen Datenkonvertierungsbausteinen liegt in der Adapter-Ein-/Ausgabe, die eine vollständige Schnittstellenumsetzung ermöglicht.

## Fazit

Der Baustein `AULI_TO_AI` bietet eine elegante und standardisierte Möglichkeit, adapterspezifische Typkonvertierungen zwischen ULINT- und INT-basierten analogen Schnittstellen durchzuführen. Durch die Kapselung der Konvertierungslogik in einem Composite FB wird die Wiederverwendbarkeit und Übersichtlichkeit erhöht. Er eignet sich besonders für modulare Automatisierungsarchitekturen, bei denen unterschiedliche Protokolle oder Datentypen aufeinandertreffen.