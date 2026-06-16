# AS_SPLIT_6


![AS_SPLIT_6](./AS_SPLIT_6.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **AS_SPLIT_6** dient der Aufteilung eines einzelnen eingehenden AS-Adapter-Signals auf sechs separate AS-Adapter-Ausgänge. Er ist als generischer Baustein realisiert und kann mit unterschiedlichen unidirektionalen AS-Adapter-Typen (z. B. Sensor- oder Aktor-Adaptern) verwendet werden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
– Keine –

### **Ereignis-Ausgänge**
– Keine –

### **Daten-Eingänge**
– Keine –

### **Daten-Ausgänge**
– Keine –

### **Adapter**

| Richtung | Name | Typ |
|----------|------|-----|
| SOCKET   | IN   | unidirectional::AS (generisch) |
| PLUG     | OUT1 | unidirectional::AS (generisch) |
| PLUG     | OUT2 | unidirectional::AS (generisch) |
| PLUG     | OUT3 | unidirectional::AS (generisch) |
| PLUG     | OUT4 | unidirectional::AS (generisch) |
| PLUG     | OUT5 | unidirectional::AS (generisch) |
| PLUG     | OUT6 | unidirectional::AS (generisch) |

## Funktionsweise
Der Baustein leitet alle am SOCKET **IN** anliegenden Adapter-Signale unverändert an alle sechs PLUGs (**OUT1** bis **OUT6**) weiter. Es findet keine Datenverarbeitung oder -umwandlung statt – die Verteilung erfolgt rein strukturell. Somit verhalten sich alle Ausgänge identisch zum Eingang.

## Technische Besonderheiten
- **Generischer Baustein:** Der konkrete AS-Adapter-Typ wird erst bei der Instanziierung festgelegt (z. B. durch die Angabe eines GenericClassNamens wie `'GEN_AS_SPLIT'`). Dadurch ist der Baustein für verschiedene Protokolle oder Datenstrukturen einsetzbar.
- **Keine Zustandslogik:** Der Baustein besitzt keine Zustandsmaschine, keine Algorithmen und keine Ereignisse – er arbeitet rein passiv und sofortig.
- **Unidirektional:** Die Adapter sind vom Typ `unidirectional::AS`, d. h. die Daten fließen nur vom Eingang zu den Ausgängen.

## Zustandsübersicht
Der Baustein verfügt über keine Eckwert-Zustandsautomatik (ECC), da keine sequentiellen Abläufe oder Verarbeitungsschritte definiert sind. Die Signalverteilung erfolgt statisch und kontinuierlich.

## Anwendungsszenarien
- **Signalvervielfältigung:** Ein einzelner Sensor-Adapter (z. B. Temperaturmessung) wird mehreren Verarbeitungseinheiten zur Verfügung gestellt.
- **Datenbus-Kopplung:** Ein gemeinsames Signal wird an sechs parallele Steuerungsmodule oder Anzeigen weitergegeben.
- **Prototyping und Test:** Vereinfachte Erzeugung mehrerer identischer Schnittstellen aus einer Quelle.

## Vergleich mit ähnlichen Bausteinen
- **AS_SPLIT_2 / AS_SPLIT_4** – Identische Funktionalität, jedoch mit nur zwei bzw. vier Ausgängen. Der vorliegende Baustein eignet sich für Anwendungen mit genau sechs Zielen.
- **AS_MERGE_...** – Führt mehrere Adapter-Eingänge zu einem Ausgang zusammen – gegensätzliche Aufgabe.
- **Manuelle Verdrahtung** – Könnte über mehrere Adapter-Kopplungen realisiert werden, erhöht jedoch den Konfigurationsaufwand.

## Fazit
Der **AS_SPLIT_6** ist ein einfacher, aber effektiver generischer Funktionsbaustein zur Aufteilung eines unidirektionalen AS-Signals auf sechs separate Ausgänge. Durch seine generische Natur kann er flexibel in verschiedenen Automatisierungsumgebungen eingesetzt werden, wo eine schnelle und übersichtliche Signalvervielfältigung erforderlich ist.