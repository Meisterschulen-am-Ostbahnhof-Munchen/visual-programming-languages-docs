# AIS_SPLIT_4


![AIS_SPLIT_4](./AIS_SPLIT_4.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AIS_SPLIT_4** dient dazu, ein eingehendes AIS-Adaptersignal (Typ `adapter::types::unidirectional::AIS`) auf vier separate Ausgänge zu verteilen. Er realisiert eine 1‑zu‑4‑Aufteilung ohne Veränderung der Daten. Der Baustein ist generisch ausgeführt und kann über den generischen Klassennamen an unterschiedliche Signaltypen angepasst werden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine.

### **Ereignis-Ausgänge**
Keine.

### **Daten-Eingänge**
Keine.

### **Daten-Ausgänge**
Keine.

### **Adapter**
- **Socket (Eingang):** `IN` – Typ `adapter::types::unidirectional::AIS`
- **Plugs (Ausgänge):**
  - `OUT1` – Typ `adapter::types::unidirectional::AIS`
  - `OUT2` – Typ `adapter::types::unidirectional::AIS`
  - `OUT3` – Typ `adapter::types::unidirectional::AIS`
  - `OUT4` – Typ `adapter::types::unidirectional::AIS`

## Funktionsweise
Der Baustein leitet das am Socket `IN` anliegende Adaptersignal unverändert an alle vier Ausgangsadapter (`OUT1` … `OUT4`) weiter. Es findet keine Datenmanipulation, Filterung oder Pufferung statt. Jeder Ausgang entspricht exakt dem Eingangssignal. Die Verteilung erfolgt asynchron und ohne Ereignissteuerung – die Adapterschnittstelle übernimmt die Datenweitergabe entsprechend ihrer Kommunikationslogik.

## Technische Besonderheiten
- **Generischer Typ:** Der Baustein ist als generischer Funktionsblock ausgeführt. Über das Attribut `eclipse4diac::core::GenericClassName` (Wert `'GEN_AIS_SPLIT'`) kann der eigentliche Signaltyp zur Erstellungszeit festgelegt werden.
- **Typ-Hash:** Ein Leerstring (`''`) für das Attribut `eclipse4diac::core::TypeHash` weist darauf hin, dass der Baustein bei Bedarf dynamisch konfiguriert wird.
- **Kompaktheit:** Da weder Ereignis- noch Dateneingänge/-ausgänge existieren, ist der Baustein rein adapterbasiert und frei von zeitlichen Abhängigkeiten.

## Zustandsübersicht
Der Baustein besitzt keine Zustandsmaschine – er arbeitet kontinuierlich und zustandslos. Es gibt keine internalen Zustände oder Ereignisse, die geschaltet werden müssten. Die Funktionalität erschöpft sich in der passiven Durchleitung des Adaptersignals.

## Anwendungsszenarien
- **Signalverteilung in Steuerungsarchitekturen:** Ein von einer Quelle (z. B. Sensor) bereitgestelltes AIS-Signal soll mehreren nachgeschalteten Verarbeitungseinheiten oder Anzeigen zur Verfügung gestellt werden.
- **Redundante Datenweitergabe:** In sicherheitskritischen Systemen kann das Eingangssignal an mehrere unabhängige Pfade geleitet werden, ohne es zu duplizieren.
- **Test- und Debugumgebungen:** Ein Signal wird parallel an die eigentliche Logik und an ein Analyse-/Protokolltool geführt.

## Vergleich mit ähnlichen Bausteinen
- **AIS_SPLIT_2 / AIS_SPLIT_8:** Diese Bausteine stellen Varianten mit zwei bzw. acht Ausgängen dar. Die Funktionsweise ist identisch; lediglich die Anzahl der ausgegebenen Adapter unterscheidet sich.
- **Datenbasierte Splitter (z. B. SPLIT_INT):** Im Unterschied zu adapterbasierten Splittern arbeiten datenbasierte Splitter mit konkreten Datentypen (z. B. Ganzzahlen) und benötigen meist Ereignisse zur Auslösung. Der AIS_SPLIT_4 ist reiner Adapter-split und benötigt keine explizite Triggerung.
- **Adapter-Multiplexer (z. B. AIS_MUX):** Ein Multiplexer wählt aus mehreren Eingängen einen aus, während der Splitter einen Eingang auf mehrere Ausgänge verteilt.

## Fazit
Der **AIS_SPLIT_4** ist ein einfacher, aber praktischer Funktionsblock zur zuverlässigen Verteilung eines AIS-Signals auf vier identische Ausgänge. Seine generische Auslegung und die reine Adapterlogik machen ihn flexibel einsetzbar und erfordern keine zusätzliche Ereignissteuerung. Er eignet sich ideal für Anwendungen, in denen ein Signal mehrfach benötigt wird, ohne Datenverarbeitung oder Synchronisation.