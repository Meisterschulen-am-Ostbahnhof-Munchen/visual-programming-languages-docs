# AUDI_FB_CTD


![AUDI_FB_CTD](./AUDI_FB_CTD.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AUDI_FB_CTD** realisiert einen Abwärtszähler (Down Counter) auf Basis des Datentyps UDINT. Er ist speziell für den Einsatz mit Adapter-Schnittstellen ausgelegt und verwendet die Typen `AX` und `AUDI` zur ereignisgesteuerten Kommunikation. Die eigentliche Zähllogik wird durch einen internen Funktionsblock des Typs `iec61131::counters::FB_CTD_UDINT` ausgeführt.

Dieser Baustein feuert bei jeder Aktualisierung – unabhängig davon, ob der Eingang `CD`, `LD` oder `PV` ausgelöst wurde – ein Ereignis auf dem Ausgangskanal `Q`. Für eine auf Änderungen basierte Auslösung wird der Einsatz eines nachgeschalteten `AX_D_FF`-Filters empfohlen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der Baustein besitzt keine direkten Ereignis-Eingänge. Alle Ereignisse werden über die angeschlossenen **Sockets** (Adapter-Eingänge) zugeführt.

| Socket (Adapter) | Typ   | Beschreibung                              |
|------------------|-------|-------------------------------------------|
| `CD`             | `AX`  | Count-Down-Ereignis (Abwärtszählen)       |
| `LD`             | `AX`  | Load-Ereignis (Laden des Preset-Wertes)   |
| `PV`             | `AUDI`| Preset-Wert-Ereignis (Vorgabewert setzen) |

### **Ereignis-Ausgänge**

| Name | Typ    | Beschreibung                                      |
|------|--------|---------------------------------------------------|
| `CNF`| Event  | Bestätigungsereignis nach jeder Verarbeitung      |

### **Daten-Eingänge**

Die Daten werden über die Sockets als Teil des Adapter-Protokolls übertragen.

| Socket (Adapter) | Daten-Typ | Bedeutung                               |
|------------------|-----------|-----------------------------------------|
| `CD.D1`          | BOOL      | Befehl zum Herunterzählen (TRUE = zählen)|
| `LD.D1`          | BOOL      | Befehl zum Laden des Preset-Wertes      |
| `PV.D1`          | UDINT     | Vorgabewert für den Zähler (Preset)     |

### **Daten-Ausgänge**

Die Ausgangsdaten werden über die Plugs ausgegeben.

| Plug (Adapter) | Daten-Typ | Bedeutung                           |
|----------------|-----------|-------------------------------------|
| `Q.D1`         | BOOL      | Zählerstand = 0 (TRUE wenn erreicht)|
| `CV.D1`        | UDINT     | Aktueller Zählerwert                |

### **Adapter**

| Richtung | Name | Typ   | Beschreibung                             |
|----------|------|-------|------------------------------------------|
| Socket   | `CD` | `AX`  | Ereignisgesteuerter Zählimpuls (abwärts) |
| Socket   | `LD` | `AX`  | Ereignisgesteuertes Laden des Presets    |
| Socket   | `PV` | `AUDI`| Ereignisgesteuerte Vorgabe des Presets   |
| Plug     | `Q`  | `AX`  | Ausgangssignal: Zählerstand = 0          |
| Plug     | `CV` | `AUDI`| Ausgangssignal: aktueller Zählerwert     |

## Funktionsweise

Intern wird ein standardisierter IEC‑61131‑Abwärtszähler (`FB_CTD_UDINT`) verwendet. Die Adapter-Ereignisse `CD.E1`, `LD.E1` und `PV.E1` werden zu einem einzigen `REQ`-Ereignis des internen Bausteins zusammengeführt. Dadurch wird der interne Zähler bei jedem beliebigen äußeren Ereignis neu berechnet.

- **CD (Count Down)**: Liegt das Datensignal `CD.D1 = TRUE` an, wird der aktuelle Zählerwert um 1 verringert. Bei `FALSE` bleibt der Wert unverändert.
- **LD (Load)**: Ist `LD.D1 = TRUE`, wird der Zähler auf den Wert von `PV.D1` gesetzt.
- **PV (Preset Value)**: Das Ereignis aktualisiert den gespeicherten Preset-Wert; ein darauf folgendes `LD`-Ereignis übernimmt diesen.

Nach jeder Berechnung werden die Ausgangsdaten `CV` (aktueller Zählerwert) und `Q` (TRUE wenn `CV = 0`) über die entsprechenden Plugs ausgegeben. Gleichzeitig wird das Bestätigungsereignis `CNF` ausgelöst.

## Technische Besonderheiten

- **Ereignisverhalten**: Bei jedem Eingangsereignis (`CD`, `LD` oder `PV`) wird der Ausgangskanal `Q` bedient. Das bedeutet, dass ein `Q.E1`-Ereignis auch dann gesendet wird, wenn sich der Zählerwert oder der `Q`-Zustand nicht geändert hat. Dies kann zu unnötig vielen Ereignissen in der nachfolgenden Logik führen.
- **Empfehlung zur Filterung**: Soll das Ausgangsereignis nur bei tatsächlicher Zustandsänderung von `Q` ausgelöst werden, ist ein **AX_D_FF** (Flip-Flop) als Filter zwischenzuschalten. Dieser unterdrückt Wiederholungen.
- **Adapterbasierte Anbindung**: Alle Ein- und Ausgänge erfolgen über genormte Adapter (`AX`, `AUDI`). Dies vereinfacht die modulare Verdrahtung und Wiederverwendung in unterschiedlichen Umgebungen.

## Zustandsübersicht

Der Baustein besitzt keine expliziten Zustände. Der interne Zähler arbeitet nach den Regeln eines IEC‑61131‑CTD-Bausteins. Der aktuelle Zählerstand wird durch die Datensignale bestimmt.

## Anwendungsszenarien

- **Ereignisgesteuerte Abwärtszählung**: Einsatz in Automatisierungssystemen, bei denen ein Zählerstand durch äußere Ereignisse dekrementiert wird (z. B. Anzahl verarbeiteter Werkstücke).
- **Modulare Steuerungskomponenten**: Integration in adapterbasierte Architekturen, bei denen standardisierte Schnittstellen den Datenaustausch zwischen verschiedenen Funktionsblöcken erleichtern.
- **Timer‑Nachbildung**: Kombination mit einem Taktgeber, um eine definierte Anzahl von Zyklen zu zählen und bei Erreichen von Null eine Aktion auszulösen.

## Vergleich mit ähnlichen Bausteinen

- **Standard‑CTD** (z. B. `FB_CTD_UDINT`): Besitzt direkte Ein-/Ausgangsvariablen, keine Adapter. Der `AUDI_FB_CTD` hingegen kapselt die Logik und stellt die Signale über Adapter bereit, was eine saubere Trennung von Ereignis- und Datenkanälen ermöglicht.
- **Aufwärtszähler (CTU)**: Im Gegensatz zum `AUDI_FB_CTD` zählt ein CTU aufwärts. Beide können adapterbasiert realisiert werden, sind aber für unterschiedliche Zählrichtungen ausgelegt.
- **Eigenschaft „immer feuern“**: Viele Standardzähler geben nur dann ein Ausgangsereignis, wenn sich der Ausgangszustand ändert. Der `AUDI_FB_CTD` tut dies bei jeder Verarbeitung, was eine Besonderheit darstellt und je nach Anwendung Vor- oder Nachteil sein kann.

## Fazit

Der `AUDI_FB_CTD` ist ein flexibler adaptergestützter Abwärtszähler für UDINT-Werte. Seine Stärke liegt in der modularen Anbindung über standardisierte Schnittstellen. Entwickler sollten jedoch das spezielle Ereignisverhalten (Ausgangsimplus bei jedem Update) beachten und bei Bedarf durch einen Filter korrigieren. Der Baustein eignet sich gut für ereignisgesteuerte Zählaufgaben in heterogenen Steuerungslandschaften.