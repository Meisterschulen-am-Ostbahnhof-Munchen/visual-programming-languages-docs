# ATM_MUX_2


![ATM_MUX_2](./ATM_MUX_2.svg)

* * * * * * * * * *  

## Einleitung  

Der Funktionsblock **ATM_MUX_2** ist ein generischer Multiplexer für zwei ATM-Datenkanäle. Er wählt anhand eines numerischen Index (`K`) einen der beiden Eingangsadapter (`IN1` oder `IN2`) aus und leitet dessen Daten über den Ausgangsadapter (`OUT`) weiter. Der Baustein dient der dynamischen Umschaltung zwischen zwei unidirektionalen Datenquellen und eignet sich für Systeme, die zwischen verschiedenen ATM‑ähnlichen Datenströmen umschalten müssen.

## Schnittstellenstruktur  

### **Ereignis-Eingänge**  

| Name | Typ | Kommentar |
|------|-----|-----------|
| `REQ` | Event | Setzt den Index `K` und löst die Umschaltung aus |

Der `REQ`-Eingang initiiert den Auswahlvorgang. Mit ihm wird der Wert von `K` übernommen und der entsprechende Eingang auf den Ausgang geschaltet.

### **Ereignis-Ausgänge**  

| Name | Typ | Kommentar |
|------|-----|-----------|
| `CNF` | Event | Bestätigt die erfolgte Umschaltung |

Nachdem der Multiplexer die Schaltung durchgeführt hat, wird `CNF` ausgegeben. Anschließend ist der ausgewählte Datenpfad aktiv.

### **Daten-Eingänge**  

| Name | Typ | Kommentar |
|------|-----|-----------|
| `K` | UINT | Index des auszuwählenden Eingangs (0 für `IN1`, 1 für `IN2`) |

Der Wert von `K` bestimmt, welcher der beiden Eingangsadapter durchgeschaltet wird. Der Datentyp `UINT` erlaubt prinzipiell auch größere Werte; im vorliegenden Baustein werden jedoch nur die Werte 0 und 1 verwendet.

### **Daten-Ausgänge**  

Der Funktionsblock besitzt keine eigenständigen Datenausgänge. Die Datenweitergabe erfolgt ausschließlich über den Adapter-Ausgang `OUT`.

### **Adapter**  

| Typ | Name | Richtung | Kommentar |
|-----|------|----------|-----------|
| `adapter::types::unidirectional::ATM` | `OUT` | Plug | Ausgang, der die Daten des ausgewählten Eingangs bereitstellt |
| `adapter::types::unidirectional::ATM` | `IN1` | Socket | Erster Eingang (Index 0) |
| `adapter::types::unidirectional::ATM` | `IN2` | Socket | Zweiter Eingang (Index 1) |

Alle Adapter sind vom gleichen unidirektionalen Typ `ATM`. Der Plug `OUT` verbindet den Baustein mit der nachfolgenden Logik, während die Sockets die Datenquellen darstellen.

## Funktionsweise  

Der `ATM_MUX_2` arbeitet ereignisgesteuert. Ein Signal am `REQ`-Eingang führt folgende Schritte aus:  

1. Der aktuelle Wert des Eingangs `K` wird übernommen.  
2. Ist `K = 0`, wird der Datenpfad von `IN1` nach `OUT` durchgeschaltet.  
3. Ist `K = 1`, wird der Datenpfad von `IN2` nach `OUT` durchgeschaltet.  
4. Nach erfolgreicher Umschaltung wird das Ereignis `CNF` gesendet.  

Die eigentliche Datenweiterleitung erfolgt kontinuierlich (sobald der Pfand aktiv ist) – der Baustein puffert keine Daten, sondern leitet sie direkt vom gewählten Eingang zum Ausgang weiter.

## Technische Besonderheiten  

- **Generischer Baustein**: Der `ATM_MUX_2` ist als generischer FB deklariert (`GenericClassName = 'GEN_ATM_MUX'`). Er kann daher in verschiedenen Ausprägungen (z. B. mit mehr als zwei Eingängen) durch Anpassung der generischen Parameter instanziiert werden.  
- **Unidirektionale Adapter**: Daten fließen nur in eine Richtung (vom Eingang zum Ausgang). Eine Rückkopplung oder bidirektionale Kommunikation ist nicht vorgesehen.  
- **Kein interner Zustand**: Der Baustein besitzt keine Zustandsmaschine mit mehreren Zuständen; nach der Umschaltung bleibt der Pfad solange aktiv, bis ein neuer `REQ`-Impuls einen anderen Index setzt.  
- **Indirekte Datenübergabe**: Daten werden nicht als einfache Variablen, sondern über Adapter ausgetauscht. Dies ermöglicht eine modulare Verbindung gleichartiger Datenschnittstellen.

## Zustandsübersicht  

Da der `ATM_MUX_2` keinen expliziten ECC (Execution Control Chart) besitzt, lässt sich sein Verhalten als einfache Zustandsschleife beschreiben:  

| Zustand | Beschreibung |
|---------|--------------|
| **Bereit (Idle)** | Warten auf ein `REQ`-Ereignis. Der zuletzt eingestellte Pfad bleibt aktiv. |
| **Umschaltung** | Nach Empfang von `REQ` wird der Wert von `K` ausgelesen und der entsprechende Pfad aktiviert. |
| **Bestätigung** | Nach erfolgter Umschaltung wird `CNF` ausgegeben und der Baustein kehrt in den Bereit-Zustand zurück. |

Der Baustein kann sich während der Umschaltung in einem kurzen, undefinierten Moment befinden – typischerweise werden die Daten während der Umschaltung nicht weitergereicht.

## Anwendungsszenarien  

- **Datenquellenauswahl**: Umschalten zwischen zwei Sensoren oder Datenströmen (z. B. A/B‑Test von ATM‑Schnittstellen).  
- **Redundanzumschaltung**: Ersatz eines defekten Datenkanals durch einen zweiten Kanal, gesteuert durch einen Fehlerindikator.  
- **Konfigurierbare Datenpfade**: In Steuerungssystemen kann der Index `K` dynamisch von einer übergeordneten Logik gesetzt werden, um je nach Betriebsmodus unterschiedliche Datenquellen anzubinden.  

## Vergleich mit ähnlichen Bausteinen  

- **ATM_MUX_N (generische Variante)**: Der vorliegende `ATM_MUX_2` ist eine spezielle Instanz mit zwei Eingängen. Ein generischer `ATM_MUX` könnte über einen Parameter `N` die Anzahl der Eingänge festlegen.  
- **Einfache If-else-Logik**: In einer IEC 61499‑Umgebung könnte ein Multiplexer auch durch eine Kombination aus Decision‑FB und mehreren Select‑Bausteinen realisiert werden. Der `ATM_MUX_2` kapselt diese Logik jedoch in einem einzigen, wiederverwendbaren Baustein und reduziert so die Komplexität des Netzwerks.  

## Fazit  

Der `ATM_MUX_2` ist ein schlanker, generischer Multiplexer für zwei unidirektionale ATM‑Datenströme. Er zeichnet sich durch einfache Handhabung (Indexauswahl per Ereignis) und modulare Adapter‑Schnittstellen aus. Aufgrund seiner generischen Natur kann er leicht an unterschiedliche Anzahlen von Eingängen angepasst werden. Der Baustein eignet sich besonders für Anwendungen, bei denen eine schnelle, ereignisgesteuerte Kanalumschaltung erforderlich ist, ohne dass zusätzliche Logik im Netzwerk aufgebaut werden muss.