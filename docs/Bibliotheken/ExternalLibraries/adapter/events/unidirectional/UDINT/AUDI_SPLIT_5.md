# AUDI_SPLIT_5


![AUDI_SPLIT_5](./AUDI_SPLIT_5.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AUDI_SPLIT_5** dient dazu, ein einzelnes eingehendes AUDI‑Signal auf fünf identische AUDI‑Ausgänge zu verteilen. Er ist als generischer Adapterbaustein konzipiert und erlaubt eine flexible Weiterverarbeitung des Signals in mehreren Pfaden.

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

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| **Socket** | `IN` | `adapter::types::unidirectional::AUDI` | Eingehendes AUDI‑Signal |
| **Plug** | `OUT1` | `adapter::types::unidirectional::AUDI` | Erster Ausgang |
| **Plug** | `OUT2` | `adapter::types::unidirectional::AUDI` | Zweiter Ausgang |
| **Plug** | `OUT3` | `adapter::types::unidirectional::AUDI` | Dritter Ausgang |
| **Plug** | `OUT4` | `adapter::types::unidirectional::AUDI` | Vierter Ausgang |
| **Plug** | `OUT5` | `adapter::types::unidirectional::AUDI` | Fünfter Ausgang |

## Funktionsweise

Der Baustein leitet das am Socket `IN` anliegende AUDI‑Signal unverändert und gleichzeitig an alle fünf Plugs `OUT1` bis `OUT5` weiter. Es erfolgt keine Signalverarbeitung, Wandlung oder Pufferung – die Verteilung erfolgt auf reiner Adapterebene, sobald eine Verbindung zu den Ausgängen besteht.

## Technische Besonderheiten

- **Generischer Baustein**: Der FB ist als generischer Typ (`GEN_AUDI_SPLIT`) realisiert. Er kann über entsprechende Mechanismen der Laufzeitumgebung für verschiedene Datentypen instantiiert werden, solange diese dem unidirektionalen AUDI‑Adapterprotokoll entsprechen.
- **Keine Zustandslogik**: Der Baustein enthält keine Ereignis‑ oder Datenverarbeitung und keinen internen Zustandsautomaten.
- **Einfache und performante Signalverteilung**: Aufgrund seiner reinen Adapterstruktur eignet er sich besonders für Szenarien, in denen ein Signal ohne Latenz vervielfältigt werden muss.

## Zustandsübersicht

Der Baustein besitzt keinen expliziten Zustandsautomaten. Das Verhalten ist deterministisch: Solange der Baustein in Betrieb ist, wird jedes an `IN` ankommende Signal sofort an alle Ausgänge weitergegeben.

## Anwendungsszenarien

- **Verteilen von Steuersignalen** in einer industriellen Automatisierung, z. B. ein Start‑/Stop‑Befehl, der mehrere gleichartige Module erreichen soll.
- **Vervielfältigung eines Messwerts** für parallele Auswertungen oder Visualisierungen.
- **Aufbau von Redundanzpfaden**, indem dasselbe Signal mehrfach genutzt wird.

## Vergleich mit ähnlichen Bausteinen

Im Gegensatz zu Bausteinen wie `AUDI_MERGE_5` (zusammenführen mehrerer Signale) oder `AUDI_SPLIT_2` (nur zwei Ausgänge) bietet `AUDI_SPLIT_5` eine spezifische Aufteilung auf genau fünf Ausgänge. Generische Split‑Bausteine für andere Anzahlen (z. B. `AUDI_SPLIT_N`) existieren oft als Template, während dieser FB eine feste, aber häufig benötigte Konfiguration abdeckt.

## Fazit

`AUDI_SPLIT_5` ist ein einfacher und effizienter Adapterbaustein zur Signalverteilung. Seine generische Auslegung und das Fehlen von Ereignis‑/Datenlogik machen ihn leichtgewichtig und vielseitig einsetzbar. Er eignet sich ideal für alle Anwendungen, in denen ein AUDI‑Signal auf fünf parallele Pfade aufgeteilt werden muss.