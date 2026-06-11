# AX_TO_AUS


![AX_TO_AUS](./AX_TO_AUS.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AX_TO_AUS** ist ein Composite-Baustein, der einen booleschen Eingangsadapter (Typ `AX`) in einen ganzzahligen Ausgangsadapter (Typ `AUS`) konvertiert. Er dient als Brücke zwischen Komponenten, die mit unterschiedlichen Datentypen arbeiten, und ermöglicht eine nahtlose Integration in Steuerungsanwendungen nach IEC 61499.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der Baustein besitzt keine direkten Ereignis-Eingänge, jedoch wird über den eingehenden Adapter `AX_IN` das Ereignis `E1` bereitgestellt. Dieses löst die Konvertierung aus.

### **Ereignis-Ausgänge**

Auch hier gibt es keine direkten Ereignis-Ausgänge. Der ausgehende Adapter `AUS_OUT` stellt das Ereignis `E1` zur Verfügung, das nach erfolgreicher Konvertierung getriggert wird.

### **Daten-Eingänge**

Die Daten werden über den Adapter `AX_IN` als boolescher Wert (`D1` vom Typ `BOOL`) entgegengenommen.

### **Daten-Ausgänge**

Der konvertierte Wert wird über den Adapter `AUS_OUT` als vorzeichenloser 8‑Bit‑Ganzzahl (`D1` vom Typ `USINT`) ausgegeben.

### **Adapter**

| Richtung | Name     | Typ                           | Beschreibung                |
|----------|----------|-------------------------------|-----------------------------|
| Socket   | `AX_IN`  | `adapter::types::unidirectional::AX` | Boolescher Eingangsadapter |
| Plug     | `AUS_OUT`| `adapter::types::unidirectional::AUS` | USINT‑Ausgangsadapter      |

## Funktionsweise

Intern verwendet der Baustein den vordefinierten Konvertierungsbaustein `iec61131::conversion::F_BOOL_TO_USINT`. Der Ablauf ist wie folgt:

1. Ein eingehendes Ereignis am Adapter `AX_IN.E1` triggert den internen Baustein über dessen Eingang `REQ`.
2. Der boolesche Wert von `AX_IN.D1` wird an den Eingang `IN` des internen Bausteins weitergeleitet.
3. Der interne Baustein konvertiert den `BOOL`-Wert in einen `USINT`-Wert (`false` → 0, `true` → 1) und legt ihn an seinem Ausgang `OUT` an.
4. Das Bestätigungsereignis `CNF` des internen Bausteins wird an den Adapterausgang `AUS_OUT.E1` weitergeleitet.
5. Der konvertierte Wert vom Ausgang `OUT` wird an den Datenausgang `AUS_OUT.D1` übergeben.

## Technische Besonderheiten

- **Composite-Baustein**: Der FB kapselt die Konvertierungslogik und stellt eine saubere, wiederverwendbare Schnittstelle über Adapter bereit.
- **Plug/Socket‑Kopplung**: Der Baustein verwendet das Adapter‑Pattern (Socket für Eingang, Plug für Ausgang), was eine flexible Verbindung in einer IEC‑61499‑Applikation ermöglicht.
- **Abhängigkeit**: Er importiert den Baustein `iec61131::conversion::F_BOOL_TO_USINT`, der Teil der IEC‑61131‑Konvertierungsbibliothek ist.

## Zustandsübersicht

Der Baustein besitzt keine eigene Zustandsmaschine. Die gesamte Funktionalität wird durch den internen `F_BOOL_TO_USINT`-Baustein realisiert, der ereignisgesteuert arbeitet und keine internen Zustände speichert.

## Anwendungsszenarien

- **Signalanpassung**: Wenn ein Sensor oder ein boolescher Adapter (z. B. Schalter, Grenztaster) an eine Komponente angeschlossen werden soll, die einen ganzzahligen Adapter erwartet.
- **Protokollumsetzung**: In heterogenen Systemen, in denen unterschiedliche Datenformate verwendet werden, kann dieser Baustein als einfacher Konverter dienen.
- **Test- und Simulationsumgebungen**: Um boolesche Werte in numerische Werte umzuwandeln, die von Analysewerkzeugen leichter verarbeitet werden können.

## Vergleich mit ähnlichen Bausteinen

Es existieren zahlreiche Konvertierungsbausteine in der IEC‑61499‑Bibliothek, z. B. `F_BOOL_TO_INT`, `F_BOOL_TO_WORD` oder `F_BOOL_TO_BYTE`. Der Unterschied zu `AX_TO_AUS` liegt in der Adapter‑Schnittstelle: Dieser Baustein kapselt die Konvertierung nicht nur auf Datenebene, sondern auch auf Ereignisebene in einem kompakten Adapter‑Paar. Andere Bausteine arbeiten meist mit einfachen Ein‑/Ausgangsdaten und erfordern zusätzliche Verdrahtung von Ereignissen.

## Fazit

Der Funktionsblock **AX_TO_AUS** ist ein praktischer Helfer, um boolesche Adapter‑Signale in das USINT‑Format zu wandeln. Durch den Einsatz von Adaptern fügt er sich nahtlos in die ereignisgesteuerte Architektur nach IEC 61499 ein und reduziert den Verdrahtungsaufwand erheblich. Er eignet sich besonders für Anwendungen, bei denen eine saubere Trennung zwischen boolescher und numerischer Domäne gewünscht ist.