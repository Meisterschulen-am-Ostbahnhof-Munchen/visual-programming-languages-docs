# AB_DEMUX_3


![AB_DEMUX_3](./AB_DEMUX_3.svg)

* * * * * * * * * *
## Einleitung
Der **AB_DEMUX_3** ist ein generischer Demultiplexer für den Adaptertyp `unidirectional::AB`. Er leitet einen am Socket **IN** anliegenden Wert abhängig vom Index **K** auf einen der drei Adapter-Plugs **OUT1**, **OUT2** oder **OUT3** weiter. Der Baustein wird über das Ereignis **REQ** gesteuert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| **REQ** | Setzt den Index **K** und triggert die Demultiplexung. (Mit **K** verknüpft) |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| **CNF** | Bestätigt die erfolgreiche Einstellung des Index **K**. |

### **Daten-Eingänge**

| Variable | Typ   | Beschreibung |
|----------|-------|--------------|
| **K**    | UINT  | Index des Zielausgangs (1 = OUT1, 2 = OUT2, 3 = OUT3). |

### **Daten-Ausgänge**
Keine Datenausgänge vorhanden – die Ausgabe erfolgt über die Adapter-Plugs.

### **Adapter**

| Adapter   | Richtung        | Typ                          | Beschreibung |
|-----------|-----------------|------------------------------|--------------|
| **IN**    | Socket (Eingang)| `adapter::types::unidirectional::AB` | Eingangswert, der demultiplext wird. |
| **OUT1**  | Plug (Ausgang)  | `adapter::types::unidirectional::AB` | Erster Ausgang (Index 1). |
| **OUT2**  | Plug (Ausgang)  | `adapter::types::unidirectional::AB` | Zweiter Ausgang (Index 2). |
| **OUT3**  | Plug (Ausgang)  | `adapter::types::unidirectional::AB` | Dritter Ausgang (Index 3). |

## Funktionsweise
Der Baustein wartet auf das Ereignis **REQ**. Sobald dieses eintritt, wird der Wert von **K** ausgewertet:
- Bei **K = 1** wird der am Socket **IN** anliegende Wert auf den Plug **OUT1** übertragen.
- Bei **K = 2** erfolgt die Übertragung auf **OUT2**.
- Bei **K = 3** erfolgt die Übertragung auf **OUT3**.

Für alle anderen Werte von **K** bleibt der Zustand der Ausgänge unverändert (keine Ausgabe). Nach Abschluss der Operation wird das Ereignis **CNF** gesendet.

Der Datenfluss erfolgt bidirektional über die Adapter, jedoch wird nur die Richtung vom Socket zu den Plugs gesteuert.

## Technische Besonderheiten
- **Generischer Baustein**: Der FB ist als generische Klasse (`GenericClassName = 'GEN_AB_DEMUX'`) definiert. Die konkrete Datentypanpassung erfolgt bei der Instanziierung durch das Entwicklungssystem.
- **Adaptertyp**: Alle Adapter sind vom Typ `unidirectional::AB`, was eine einfache, aber feste Kopplung an diesen Bidirektionalschnittstellentyp voraussetzt.
- **Indexbereich**: Der Eingang **K** ist als `UINT` deklariert; nur die Werte 1, 2 und 3 führen zu einer Weiterleitung. Andere Werte bleiben ohne Wirkung.
- **Ereignisgesteuert**: Die Demultiplexung erfolgt nur auf das **REQ**-Ereignis hin – es gibt kein automatisches Durchschleifen oder zyklisches Verhalten.

## Zustandsübersicht
Der FB besitzt keine explizite Zustandsmaschine (ECC). Die Funktionalität wird rein ereignisgesteuert umgesetzt: Nach einem **REQ** wird synchron die Zuordnung vorgenommen und **CNF** ausgegeben. Es gibt keine internen Zustände oder Verzögerungen.

## Anwendungsszenarien
- **Datenwege-Umschaltung**: Ein von einer übergeordneten Steuerung gelieferter AB-Datenwert soll abhängig von einem Index an verschiedene Verbraucher (z. B. Aktoren, Subsysteme) weitergeleitet werden.
- **Selektive Aktivierung**: In der Prozessautomatisierung kann derselbe Sensorwert (adapterbasiert) je nach Betriebsmodus an unterschiedliche Auswertebausteine geschaltet werden.
- **Test- und Simulationsumgebungen**: Gezielte Umleitung von Datenströmen zu Testzwecken.

## Vergleich mit ähnlichen Bausteinen
- **AB_MUX**: Der Multiplexer führt mehrere Adaptereingänge auf einen Ausgang zusammen – die Umkehrfunktion.
- **AB_DEMUX_N**: Varianten mit mehr oder weniger Ausgängen (z. B. `AB_DEMUX_2`, `AB_DEMUX_4`). Der vorliegende FB ist auf drei Ausgänge spezialisiert.
- **Manuelle Umschaltung**: Alternativ könnte die Umschaltung über bedingte Zuweisungen in einem skriptbasierten FB realisiert werden – der **AB_DEMUX_3** bietet jedoch eine kompakte und standardisierte Lösung.

## Fazit
Der **AB_DEMUX_3** ist ein einfacher, aber effektiver Baustein zur Demultiplexierung von AB-Adapterdaten. Er kapselt die Indexauswahl sauber in einem wiederverwendbaren FB und eignet sich besonders für Systeme, die eine flexible, ereignisgesteuerte Datenweiterleitung erfordern. Die generische Natur erlaubt zudem eine einfache Anpassung an verschiedene Datentypen der AB-Schnittstelle.