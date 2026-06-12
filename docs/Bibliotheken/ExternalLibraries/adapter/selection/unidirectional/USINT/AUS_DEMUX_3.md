# AUS_DEMUX_3


![AUS_DEMUX_3](./AUS_DEMUX_3.svg)

* * * * * * * * * *  

## Einleitung  

Der Funktionsblock **AUS_DEMUX_3** realisiert einen generischen Demultiplexer für AUS-Signale. Er verteilt einen über einen Socket anliegenden Eingangswert (vom Adaptertyp `AUS`) auf einen von drei über Plugs bereitgestellten Ausgängen. Die Auswahl des aktiven Ausgangs erfolgt über den Index `K`. Die verwendeten Adapter sind unidirektional und ermöglichen eine lose Kopplung zwischen den Komponenten.  

## Schnittstellenstruktur  

### **Ereignis-Eingänge**  

| Name | Typ   | Mit Variablen | Kommentar               |
|------|-------|---------------|-------------------------|
| REQ  | Event | K             | Setzt den Index K       |

### **Ereignis-Ausgänge**  

| Name | Typ   | Kommentar                         |
|------|-------|-----------------------------------|
| CNF  | Event | Bestätigung nach Setzen von K     |

### **Daten-Eingänge**  

| Name | Typ  | Kommentar      |
|------|------|----------------|
| K    | UINT | Auswahlindex (1..3) |

### **Daten-Ausgänge**  

Keine eigenen Datenausgänge; die Ausgabe erfolgt über die Adapter.  

### **Adapter**  

| Name | Typ                                     | Richtung | Kommentar                              |
|------|-----------------------------------------|----------|----------------------------------------|
| IN   | `adapter::types::unidirectional::AUS`   | Socket   | Eingangswert, der demultiplext wird    |
| OUT1 | `adapter::types::unidirectional::AUS`   | Plug     | Erster Ausgangskanal                   |
| OUT2 | `adapter::types::unidirectional::AUS`   | Plug     | Zweiter Ausgangskanal                  |
| OUT3 | `adapter::types::unidirectional::AUS`   | Plug     | Dritter Ausgangskanal                  |

## Funktionsweise  

Der Baustein arbeitet ereignisgesteuert. Ein Ereignis am Eingang `REQ` übernimmt den aktuellen Wert von `K` und leitet den am Socket `IN` anliegenden AUS-Wert an den entsprechenden Plug (`OUT1`, `OUT2` oder `OUT3`) weiter. Nach erfolgreicher Weiterleitung wird das Ereignis `CNF` ausgegeben. Der Wert von `K` bestimmt den Zielkanal:  

- `K = 1` → Weiterleitung an `OUT1`  
- `K = 2` → Weiterleitung an `OUT2`  
- `K = 3` → Weiterleitung an `OUT3`  

Liegt `K` außerhalb des gültigen Bereichs, bleibt der Ausgang unverändert (keine Aktion).  

## Technische Besonderheiten  

- **Generischer Baustein** – Der FB ist als generischer Typ (`GEN_AUS_DEMUX`) ausgeführt und kann bei der Instanziierung für unterschiedliche Kanalzahlen parametrisiert werden.  
- **Adapterbasierte Schnittstelle** – Die Verwendung von Adaptern nach IEC 61499 ermöglicht eine flexible und standardisierte Signalkopplung.  
- **Unidirektionale Datenübertragung** – Die AUS-Adapter arbeiten nur in eine Richtung; das entspricht typischen Anwendungen wie der Ansteuerung von Stellgliedern.  

## Zustandsübersicht  

Der Baustein besitzt keine explizite Zustandsmaschine (ECC). Die Funktionalität ist rein ereignisgesteuert: Jedes `REQ`-Ereignis führt direkt zur Auswahl und Weiterleitung. Damit ist der FB nebenläufig und ohne interne Zustände nutzbar.  

## Anwendungsszenarien  

- **Signalverteilung** – Ein zentraler Sensor- oder Steuerwert soll je nach Auswahl an einen von mehreren Aktoren weitergegeben werden.  
- **Multipoint-Steuerung** – In landwirtschaftlichen Maschinen (z. B. HR Agrartechnik) werden damit verschiedene Segmentventile oder Antriebe aus einem gemeinsamen Signal angesteuert.  
- **Testumgebungen** – Gezieltes Umschalten eines Testsignals auf verschiedene Prüflinge.  

## Vergleich mit ähnlichen Bausteinen  

| Baustein         | Beschreibung                                              | Unterschiede                                           |
|------------------|-----------------------------------------------------------|--------------------------------------------------------|
| **AUS_MUX**      | Multiplexer: wählt einen von mehreren Eingängen aus       | Umgekehrte Datenrichtung, mehrere Eingänge, ein Ausgang |
| **AUS_DEMUX_2**  | Demultiplexer mit zwei Ausgängen                          | Reduzierte Kanalzahl, gleiche Logik                     |
| **AUS_SWITCH**   | Einfacher Schalter (ein/aus)                              | Keine Kanalauswahl, nur Weiterleitung/Abschaltung       |

Der **AUS_DEMUX_3** bietet gezielt drei Ausgänge und eignet sich für Anwendungen, die eine feste Kanalanzahl erfordern.  

## Fazit  

Der **AUS_DEMUX_3** ist ein kompakter, ereignisgesteuerter Demultiplexer für unidirektionale AUS-Signale. Durch die Adaptertechnik und die generische Auslegung lässt er sich flexibel in automatisierungstechnische Systeme nach IEC 61499 integrieren. Besonders in der Landtechnik und bei verteilten Steuerungen ist er ein nützliches Werkzeug zur gezielten Signalverteilung.