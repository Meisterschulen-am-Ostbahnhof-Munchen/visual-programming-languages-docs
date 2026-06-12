# ALR_MUX_2


![ALR_MUX_2](./ALR_MUX_2.svg)

* * * * * * * * * *
## Einleitung

Der **ALR_MUX_2** ist ein generischer Multiplexer-Funktionsblock, der es ermöglicht, zwischen zwei unidirektionalen ALR-Adapter-Eingängen auszuwählen und den gewählten Datenstrom an einen einzelnen ALR-Adapter-Ausgang weiterzuleiten. Die Auswahl erfolgt ereignisgesteuert über einen ganzzahligen Index.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `REQ`    | Startet die Auswahl des Index `K` und leitet die entsprechenden ALR-Daten weiter. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `CNF`    | Bestätigt die erfolgreiche Verarbeitung des `REQ`-Ereignisses. |

### **Daten-Eingänge**

| Variable | Typ   | Beschreibung |
|----------|-------|--------------|
| `K`      | UINT  | Auswahlindex; gültige Werte: `0` (Auswahl von `IN1`) oder `1` (Auswahl von `IN2`). |

### **Daten-Ausgänge**

Keine Daten-Ausgänge vorhanden. Die Ausgabe erfolgt ausschließlich über den Adapter `OUT`.

### **Adapter**

| Rolle  | Bezeichnung | Typ                                        | Beschreibung                               |
|--------|-------------|--------------------------------------------|--------------------------------------------|
| Socket | `IN1`       | `adapter::types::unidirectional::ALR`       | Erster ALR-Eingang (Index `K=0`).          |
| Socket | `IN2`       | `adapter::types::unidirectional::ALR`       | Zweiter ALR-Eingang (Index `K=1`).         |
| Plug   | `OUT`       | `adapter::types::unidirectional::ALR`       | Ausgang, der die Daten des gewählten Eingangs bereitstellt. |

## Funktionsweise

Der Baustein arbeitet nach dem Multiplexer-Prinzip:

1. Ein eingehendes `REQ`-Ereignis löst die Verarbeitung aus.
2. Der Wert von `K` wird ausgewertet:
   -   `K = 0`: Die ALR-Daten von `IN1` werden an den `OUT`-Adapter weitergeleitet.
   -   `K = 1`: Die ALR-Daten von `IN2` werden an den `OUT`-Adapter weitergeleitet.
   -   Andere Werte von `K` sind nicht definiert und können zu undefiniertem Verhalten führen.
3. Nach erfolgreicher Umschaltung wird das `CNF`-Ereignis ausgegeben.

Da es sich um einen generischen Baustein handelt, sind die ALR-Datenstrukturen nicht fest vorgegeben – die genaue Datenzusammensetzung wird durch den verwendeten Adaptertyp bestimmt.

## Technische Besonderheiten

- **Generischer Typ**: Der Baustein wird über das Attribut `GenericClassName` als `'GEN_ALR_MUX'` gekennzeichnet und kann in verschiedenen Instanzen mit unterschiedlichen ALR-Adapter-Bindungen eingesetzt werden.
- **Lizenz**: Der Baustein steht unter der **Eclipse Public License 2.0 (EPL-2.0)**.
- **Adapter-Typ**: Alle Adapter sind vom Typ `adapter::types::unidirectional::ALR`, was eine unidirektionale Kommunikation voraussetzt.
- **Indexbeschränkung**: Es sind nur genau zwei Eingänge (`IN1`, `IN2`) vorhanden; eine Erweiterung auf mehr Kanäle ist nicht vorgesehen.

## Zustandsübersicht

Der Baustein besitzt **keine explizite Zustandsmaschine** (ECC). Die Funktionalität ist rein ereignisgesteuert: Auf jedes `REQ` folgt ein `CNF`. Es existieren keine internen Zustände, die den Ablauf beeinflussen.

## Anwendungsszenarien

- **Landwirtschaftliche Steuerungen**: Auswahl zwischen zwei verschiedenen ALR-basierten Sensoren (z. B. Bodenfeuchte, Temperatur) zur Regelung von Bewässerungssystemen.
- **Aktoransteuerung**: Umschaltung zwischen zwei ALR-Aktoren (z. B. Ventile, Motoren) basierend auf einem Steuerindex.
- **Redundanzschaltung**: Wechsel zwischen primärem und backup-ALR-Pfad bei fehlender Verfügbarkeit.

## Vergleich mit ähnlichen Bausteinen

Im Standard-Funktionsblock-Repertoire existieren Multiplexer wie `MUX_2`, `MUX_4` usw. Diese arbeiten jedoch meist mit direkten Datentypen (BOOL, INT usw.) und nicht mit Adaptern. Der **ALR_MUX_2** ist speziell für ALR-Adapter ausgelegt und ermöglicht die strukturierte Weitergabe komplexer Datenfelder ohne zusätzliche Serialisierung.

## Fazit

Der **ALR_MUX_2** ist ein spezialisierter, generischer Multiplexer für unidirektionale ALR-Adapter. Er bietet eine einfache, ereignisgesteuerte Umschaltung zwischen zwei Eingängen und eignet sich besonders für Anwendungen in der Landwirtschaftstechnik, wo ALR-Datenströme flexibel gelenkt werden müssen. Aufgrund der EPL-2.0-Lizenz kann er frei verwendet und angepasst werden.