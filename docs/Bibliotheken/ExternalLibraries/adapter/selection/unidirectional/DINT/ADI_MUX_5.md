# ADI_MUX_5


![ADI_MUX_5](./ADI_MUX_5.svg)

* * * * * * * * * *

## Einleitung
Der **ADI_MUX_5** ist ein generischer Multiplexer-Funktionsblock, der aus fünf ADI-Adapter-Eingängen (IN1 bis IN5) einen einzelnen ADI-Adapter-Ausgang (OUT) auswählt. Die Auswahl erfolgt ereignisgesteuert über den Parameter `K` (Index). Der Baustein eignet sich besonders für die flexible Umschaltung analoger oder digitaler Signalquellen in Automatisierungsanwendungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ** (Event) – Auslöser zum Setzen des Index `K` und zum Durchschalten des entsprechenden Eingangs auf den Ausgang.

### **Ereignis-Ausgänge**
- **CNF** (Event) – Bestätigung, dass der Auswahlvorgang abgeschlossen ist.

### **Daten-Eingänge**
- **K** (`UINT`, mit *REQ*) – Index des zu selektierenden Eingangs (0 = IN1, 1 = IN2, …, 4 = IN5).

### **Daten-Ausgänge**
- Keine dedizierten Datenausgänge vorhanden; die Ausgangsdaten werden über den Adapter-Ausgang `OUT` übertragen.

### **Adapter**
- **IN1** – ADI-Adapter (Socket) – Eingangssignal 1  
- **IN2** – ADI-Adapter (Socket) – Eingangssignal 2  
- **IN3** – ADI-Adapter (Socket) – Eingangssignal 3  
- **IN4** – ADI-Adapter (Socket) – Eingangssignal 4  
- **IN5** – ADI-Adapter (Socket) – Eingangssignal 5  
- **OUT** – ADI-Adapter (Plug) – Ausgangssignal (entspricht dem selektierten Eingang)

## Funktionsweise
1. Ein Ereignis am Ereigniseingang **REQ** wird empfangen.  
2. Der Wert des Daten-Eingangs **K** wird ausgelesen.  
3. Der Funktionsblock verbindet den entsprechenden ADI-Eingang (IN1 bei K=0, IN2 bei K=1, … IN5 bei K=4) mit dem ADI-Ausgang **OUT**.  
4. Nach erfolgreicher Umschaltung wird das Bestätigungsereignis **CNF** gesendet.

Die Auswahl erfolgt synchron zum REQ-Ereignis; es gibt keine zyklische Abfrage.

## Technische Besonderheiten
- **Generischer Baustein**: Über das Attribut `eclipse4diac::core::GenericClassName` kann der Funktionsblock zu einem spezifischen, typsicheren Multiplexer (z. B. `GEN_ADI_MUX`) abgeleitet werden.  
- **Adapterbasierte Schnittstelle**: Die Verwendung des ADI-Adapter-Typs (unidirektional) ermöglicht die flexible Anbindung unterschiedlicher Signalquellen, ohne die eigentlichen Datentypen festzulegen.  
- **Kompakte Indexlogik**: Der Eingang K ist als `UINT` definiert – Werte außerhalb des gültigen Bereichs (0 … 4) führen zu undefiniertem Verhalten; eine Absicherung sollte in der Anwendung erfolgen.

## Zustandsübersicht
Der Funktionsblock besitzt **keine explizite Zustandsmaschine** (ECC). Er reagiert rein ereignisgesteuert: Jedes REQ-Ereignis löst einen einmaligen Auswahlvorgang aus, nach dessen Abschluss sofort CNF ausgegeben wird. Der interne Zustand entspricht dem zuletzt gesetzten Index **K**.

## Anwendungsszenarien
- **Sensorenumschaltung**: Auswahl zwischen verschiedenen analogen Messwertgebern (z. B. Temperatur, Druck, Füllstand) an einem gemeinsamen Auswertungskanal.  
- **Signalpriorisierung**: Dynamisches Umschalten auf redundante oder alternative Signale bei Ausfall einer Quelle.  
- **Modulare Steuerungen**: Verwendung innerhalb von Bausteinbibliotheken, bei denen die Anzahl der Eingänge durch Generierung variiert werden kann.

## Vergleich mit ähnlichen Bausteinen
- **MUX_2 / MUX_4 (Standard‑IEC‑61499)**: Diese Multiplexer arbeiten mit festen Datentypen (z. B. `ANY`) und haben separate Datenausgänge. Der ADI_MUX_5 hingegen nutzt Adapter und ist auf den ADI‑Typ spezialisiert.  
- **Generic ADI MUX (abgeleitet)**: Durch die generische Basis können Spezialisierungen mit anderer Eingangsanzahl (z. B. ADI_MUX_3, ADI_MUX_8) erzeugt werden, ohne die Logik neu zu implementieren.  
- **Unterschied zu Select‑Bausteinen**: Select-FBs arbeiten meist bitweise oder auf Skalaren; ADI_MUX_5 überträgt komplette Adapterdatenströme.

## Fazit
Der **ADI_MUX_5** ist ein kompakter, generischer Multiplexer für ADI‑Adapter in der 4diac‑IDE. Seine adapterbasierte Schnittstelle und die einfache Indexsteuerung machen ihn zu einem praktischen Werkzeug für die flexible Signalauswahl in Steuerungsanwendungen. Die Möglichkeit der Generierung (GenericClassName) erlaubt eine typsichere Anpassung an konkrete Projekte.