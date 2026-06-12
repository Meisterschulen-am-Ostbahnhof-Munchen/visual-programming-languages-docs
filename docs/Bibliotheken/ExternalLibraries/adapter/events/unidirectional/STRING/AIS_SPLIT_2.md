# AIS_SPLIT_2


![AIS_SPLIT_2](./AIS_SPLIT_2.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AIS_SPLIT_2** ist ein generischer Adapter-Baustein, der einen eingehenden unidirektionalen AIS‑Adapter (Application Interface Socket) auf zwei identische, ausgehende AIS‑Adapter aufteilt. Er dient als passiver Splitter ohne eigene Logik oder Ereignisverarbeitung.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Nicht vorhanden.

### **Ereignis-Ausgänge**
Nicht vorhanden.

### **Daten-Eingänge**
Nicht vorhanden.

### **Daten-Ausgänge**
Nicht vorhanden.

### **Adapter**
- **IN** (Socket): Typ `adapter::types::unidirectional::AIS` – Eingangsschnittstelle für den zu verteilenden Adapter.
- **OUT1** (Plug): Typ `adapter::types::unidirectional::AIS` – erster Ausgang, erhält alle Daten/Ereignisse von IN.
- **OUT2** (Plug): Typ `adapter::types::unidirectional::AIS` – zweiter Ausgang, erhält identische Daten/Ereignisse wie OUT1.

## Funktionsweise
Der Baustein leitet den am Socket **IN** anliegenden Adapter unverändert und ohne Verzögerung an beide Plugs **OUT1** und **OUT2** weiter. Jegliche über den AIS‑Adapter definierten Ereignisse und Daten werden parallel auf beide Ausgänge kopiert. Der FB selbst besitzt keine eigene Verarbeitungslogik, Zustände oder Zeitverhalten.

## Technische Besonderheiten
- **Generische Parametrierung**: Der konkrete AIS‑Adapter-Typ wird erst zur Projektierungszeit über das Attribut `eclipse4diac::core::GenericClassName` festgelegt (Standardwert: `'GEN_AIS_SPLIT'`). Dadurch kann der Baustein für verschiedene AIS‑Varianten wiederverwendet werden.
- **Keine Eigenzustände**: Da keine ECC‑Zustandsmaschine oder Data‑/Event‑Ein-/Ausgänge vorhanden sind, ist der FB rein passiv und verhält sich wie eine „Verdrahtungshilfe“.
- **Unidirektional**: Die Adapter sind als unidirektional deklariert – eine Datenflussrichtung von IN zu OUT1/OUT2 ist implizit.

## Zustandsübersicht
Der AIS_SPLIT_2 besitzt keine eigene Zustandsmaschine. Der Betriebszustand wird ausschließlich durch die jeweils angeschlossenen AIS‑Adapter bestimmt.

## Anwendungsszenarien
- **Parallelverarbeitung**: Ein AIS‑Signal soll gleichzeitig von zwei nachfolgenden Funktionsblöcken verarbeitet werden (z. B. Visualisierung und Steuerung).
- **Monitoring**: Abzweigen eines AIS‑Signals zu einer Überwachungsinstanz, ohne das Originalsignal zu beeinflussen.
- **Generische Aufteilung**: Einsatz in Bibliotheken, wo die genaue AIS‑Struktur erst zur Laufzeit oder Konfigurationszeit festgelegt wird.

## Vergleich mit ähnlichen Bausteinen
- **AIS_SPLIT_4**: Bietet vier Ausgänge statt zwei; ansonsten gleiche Funktionsweise.
- **Ereignis‑/Datensplitter**: Andere Splitter arbeiten mit einfachen Events oder Daten (z. B. F_SPLIT), während AIS_SPLIT_2 komplette Adapter‑Schnittstellen aufteilt.
- **AIS_MERGE**: Das Gegenstück, das zwei AIS‑Eingänge zu einem Ausgang zusammenführt.

## Fazit
Der AIS_SPLIT_2 ist ein minimalistischer, generisch einsetzbarer Adapter‑Splitter, der die flexible Verzweigung von AIS‑Schnittstellen in 4diac‑Projekten ermöglicht. Durch die Parametrierung über das GenericClassName‑Attribut kann er ohne Anpassung des Quellcodes für verschiedene AIS‑Typen verwendet werden.