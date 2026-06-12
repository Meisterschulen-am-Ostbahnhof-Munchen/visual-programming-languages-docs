# AW_SPLIT_4


![AW_SPLIT_4](./AW_SPLIT_4.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AW_SPLIT_4` verteilt einen eingehenden AW-Adapter (unidirektional) auf vier identische AW-Ausgangsadapter. Der Baustein ist generisch ausgelegt und kann mit unterschiedlichen AW-Typen verwendet werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine.

### **Ereignis-Ausgänge**
Keine.

### **Daten-Eingänge**
Keine (die Datenübertragung erfolgt ausschließlich über den Adapter‑Socket).

### **Daten-Ausgänge**
Keine (die Ausgabe erfolgt ausschließlich über die Adapter‑Plugs).

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AW` | `IN` | Socket | Eingang für den zu verteilenden AW‑Datenstrom |
| `adapter::types::unidirectional::AW` | `OUT1` | Plug | Erster Ausgang (Kopie des Eingangs) |
| `adapter::types::unidirectional::AW` | `OUT2` | Plug | Zweiter Ausgang |
| `adapter::types::unidirectional::AW` | `OUT3` | Plug | Dritter Ausgang |
| `adapter::types::unidirectional::AW` | `OUT4` | Plug | Vierter Ausgang |

## Funktionsweise

Der Baustein agiert als passiver Verteiler: Jeder über den Socket `IN` ankommende Wert (bzw. jedes Datenpaket) wird unverändert an alle vier Plugs `OUT1` bis `OUT4` weitergeleitet. Es findet keine Verarbeitung, Pufferung oder zeitliche Synchronisation statt. Der gesamte Datenfluss ist ereignislos und rein adapterbasiert.

## Technische Besonderheiten

- **Generischer Baustein**: Der FB ist mit dem generischen Namen `GEN_AW_SPLIT` deklariert. Das ermöglicht eine späte Bindung an konkrete AW‑Adapter-Typen (z. B. `AT_AW`, `CT_AW` etc.) zur Compile‑ oder Konfigurationszeit.
- **Unidirektionale Kommunikation**: Die verwendeten Adapter sind vom Typ `unidirectional::AW`, d. h. die Daten fließen nur in eine Richtung. Es gibt keine Rückkanäle oder Bestätigungen.
- **Keine Eigendynamik**: Der FB besitzt keine Ereignisse, Zustände oder zeitabhängige Logik. Er ist rein kombinatorisch.

## Zustandsübersicht

Nicht anwendbar – der FB enthält keine Zustandsmaschine (ECC) und arbeitet durchgehend datengetrieben.

## Anwendungsszenarien

- Verteilung eines einzelnen Sensor‑ oder Aktor‑Signalpfads auf mehrere parallele Auswertungen.
- Aufbereitung einer Datenquelle für unterschiedliche Verbraucher in einer Steuerungsanwendung.
- Erzeugung von Test‑ oder Simulationspunkten durch Vervielfachung eines AW‑Datenstroms.

## Vergleich mit ähnlichen Bausteinen

Im Gegensatz zu daten‑ oder ereignisbasierten Split‑Bausteinen (z. B. `SPLIT`, `F_SPLIT`) arbeitet `AW_SPLIT_4` ausschließlich auf Adapterebene. Der Vorteil liegt in der losen Kopplung und der Wiederverwendbarkeit über verschiedene AW‑Typen hinweg. Nachteil: Es können nur AW‑Daten verteilt werden, nicht etwa Ereignisse oder allgemeine Werte.

## Fazit

Der Baustein `AW_SPLIT_4` ist ein einfacher, generischer Verteiler für unidirektionale AW‑Adapter. Er eignet sich ideal, um ein einzelnes AW‑Signal auf bis zu vier Ausgänge aufzuteilen, und fügt sich dank seiner generischen Natur flexibel in unterschiedliche IEC 61499‑Anwendungen ein.