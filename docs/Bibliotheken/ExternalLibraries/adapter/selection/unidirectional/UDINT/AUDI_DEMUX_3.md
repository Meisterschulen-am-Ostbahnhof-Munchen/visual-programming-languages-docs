# AUDI_DEMUX_3


![AUDI_DEMUX_3](./AUDI_DEMUX_3.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AUDI_DEMUX_3** ist ein generischer Demultiplexer für den unidirektionalen Adaptertyp `AUDI`. Er verteilt ein eingehendes Adapter-Signal auf einen von drei möglichen Ausgängen, basierend auf einem über den Dateneingang `K` vorgegebenen Index. Der Baustein wird durch ein Ereignis an `REQ` gesteuert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Datentyp | Beschreibung                                   |
|------|----------|-----------------------------------------------|
| REQ  | Event    | Steuersignal: Übernahme des Index `K` und Ausführung der Demultiplex-Funktion |

### **Ereignis-Ausgänge**

| Name | Datentyp | Beschreibung                                      |
|------|----------|--------------------------------------------------|
| CNF  | Event    | Bestätigung nach erfolgter Demultiplex-Operation |

### **Daten-Eingänge**

| Name | Datentyp | Beschreibung                                                  |
|------|----------|--------------------------------------------------------------|
| K    | UINT     | Index (1, 2 oder 3) des gewünschten Ausgangskanals. Werte außerhalb dieses Bereichs führen zu keinem validen Durchschalten. |

### **Daten-Ausgänge**

Keine eigenständigen Datenausgänge vorhanden. Die Ausgabe erfolgt ausschließlich über die folgenden Adapter.

### **Adapter**

| Typ   | Name | Richtung | Beschreibung                                              |
|-------|------|----------|----------------------------------------------------------|
| Sockel | IN   | Eingang  | Unidirektionaler AUDI-Adapter, der das zu multiplexende Signal bereitstellt |
| Plug  | OUT1 | Ausgang  | Erster unidirektionaler AUDI-Ausgang (K=1)               |
| Plug  | OUT2 | Ausgang  | Zweiter unidirektionaler AUDI-Ausgang (K=2)              |
| Plug  | OUT3 | Ausgang  | Dritter unidirektionaler AUDI-Ausgang (K=3)              |

## Funktionsweise

1. **Initialzustand:** Alle Adapterausgänge sind inaktiv (keine Signalweitergabe).
2. **Ereignis REQ:** Der Baustein liest den aktuellen Wert des Dateneingangs `K`.
3. **Demultiplex:** Je nach Wert von `K` wird das eingehende `IN`-Signal auf den entsprechenden Adapterausgang durchgeschaltet:
   - `K = 1` → `OUT1` erhält das Signal von `IN`
   - `K = 2` → `OUT2` erhält das Signal von `IN`
   - `K = 3` → `OUT3` erhält das Signal von `IN`
4. **Bestätigung:** Nach dem Durchschalten wird das Ereignis `CNF` ausgelöst.
5. **Nebenbemerkung:** Nicht ausgewählte Ausgänge bleiben im inaktiven Zustand. Der Wert von `K` zur Zeit des `REQ`-Ereignisses ist entscheidend.

## Technische Besonderheiten

- Der Baustein ist als generischer Funktionsblock (`GenericClassName = 'GEN_AUDI_DEMUX'`) implementiert, bleibt aber auf drei Ausgänge festgelegt.
- Es existiert keine Zustandsmaschine – der FB arbeitet ereignisgesteuert und zustandslos.
- Die Adapter sind unidirektional (`adapter::types::unidirectional::AUDI`), d.h. die Kommunikation erfolgt nur in eine Richtung.
- Die Eingabe von `K` wird nicht auf Gültigkeit überwacht. Werte größer als 3 oder gleich 0 führen zu keiner Durchschaltung (Ausgänge bleiben inaktiv). Es wird dennoch `CNF` ausgelöst.

## Zustandsübersicht

Der Baustein besitzt keine expliziten Zustände. Er verhält sich wie eine Kombinatorik: Auf jedes `REQ`-Ereignis folgt direkt eine Durchschalte-Operation und ein `CNF`.

## Anwendungsszenarien

- **Verteilung von Audiosignalen:** Weitergabe eines Audio-Streams an eine von drei Zielkomponenten (z.B. Lautsprecher, Aufnahmegerät, Analyse-Modul).
- **Kanalwahl in Messsystemen:** Umschalten eines Sensorsignals auf einen von drei Datenpfaden.
- **Adapter-Routing:** Innerhalb einer IEC 61499-basierten Steuerung können mit diesem Baustein flexible Signalwege auf Basis einer Indexauswahl realisiert werden.

## Vergleich mit ähnlichen Bausteinen

- **AUDI_MUX_3** (Multiplexer): Führt die umgekehrte Funktion aus – wählt einen von drei Eingängen und gibt ihn auf einen Ausgang.
- **AUDI_DEMUX_2**, **AUDI_DEMUX_4**: Varianten mit zwei bzw. vier Ausgängen. Der vorliegende Baustein ist für exakt drei Kanäle ausgelegt.
- **Generic DEMUX**: Ein allgemeiner Demultiplexer mit parametrierbarer Kanalzahl (sofern verfügbar) wäre flexibler, benötigt aber mehr Konfiguration. `AUDI_DEMUX_3` ist statisch und daher einfacher zu verwenden.

## Fazit

Der `AUDI_DEMUX_3` ist ein einfacher, aber effektiver Baustein zur kanalbasierten Weiterleitung eines unidirektionalen Adaptersignals. Seine klare Schnittstelle und die ereignisgesteuerte Arbeitsweise machen ihn zu einer zuverlässigen Komponente in IEC 61499-Anwendungen, die eine Signalverteilung an genau drei Ausgänge erfordern.