# ALI_SPLIT_8


![ALI_SPLIT_8](./ALI_SPLIT_8.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein `ALI_SPLIT_8` dient als generischer Splitter für das **Agricultural Light Interface (ALI)**. Er verteilt ein eingehendes ALI-Signal unverändert auf acht parallele Ausgänge. Dadurch können mehrere nachfolgende Verbraucher oder Steuerungen mit dem gleichen Signal versorgt werden, ohne die Signalintegrität zu beeinträchtigen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine Ereignis-Eingänge vorhanden.

### **Ereignis-Ausgänge**
Keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**
Keine Daten-Eingänge vorhanden.

### **Daten-Ausgänge**
Keine Daten-Ausgänge vorhanden.

### **Adapter**
- **Socket (Eingang):**  
  `IN` – vom Typ `adapter::types::unidirectional::ALI`  
  Nimmt das eingehende ALI-Signal auf.

- **Plugs (Ausgänge):**  
  `OUT1` … `OUT8` – jeweils vom Typ `adapter::types::unidirectional::ALI`  
  Stellen die acht identischen Kopien des Eingangssignals bereit.

## Funktionsweise
Der Baustein leitet das am Socket `IN` anliegende ALI-Signal unverändert und ohne Verzögerung an alle acht Plugs (`OUT1` … `OUT8`) weiter. Da es sich um eine reine Signalverteilung handelt, findet keine Bearbeitung, Pufferung oder Statusänderung statt. Sämtliche Ereignisse und Daten, die über den ALI-Adapter transportiert werden, werden auf jeden Ausgang repliziert.

## Technische Besonderheiten
- **Generischer Baustein:** Der FB ist als generischer Typ (`GEN_ALI_SPLIT`) definiert und kann in verschiedenen Kontexten des ALI-Ökosystems eingesetzt werden.
- **Kein ECC:** Es existiert kein Ausführungszustandsautomat (ECC); die Verteilung erfolgt rein kombinatorisch.
- **Unidirektional:** Der Adaptertyp ist unidirektional – das Signal fließt nur vom Socket zu den Plugs, eine Rückkopplung ist nicht vorgesehen.
- **Skalierbarkeit:** Durch den modularen Aufbau können ähnliche Splitter für andere Ausgangszahlen (z.B. `ALI_SPLIT_2`) abgeleitet werden.

## Zustandsübersicht
Der Baustein besitzt keine internen Zustände oder sequentielle Logik. Die Signalverteilung arbeitet kontinuierlich und ohne Verzögerung.

## Anwendungsszenarien
- **Verteilschaltungen:** Ein ALI-Signal (z.B. von einem Steuergerät) muss gleichzeitig an mehrere Aktoren oder Sensoren weitergegeben werden.
- **Redundanz:** Parallele Ansteuerung baugleicher Komponenten, ohne separate Signalquellen vorzusehen.
- **Busstrukturen:** Aufbau von sternförmigen ALI-Netzwerken mit einem zentralen Splitter.

## Vergleich mit ähnlichen Bausteinen
Andere Splitter-Bausteine wie `ALI_SPLIT_2`, `ALI_SPLIT_4` oder `ALI_SPLIT_N` unterscheiden sich lediglich in der Anzahl der Ausgänge. Der `ALI_SPLIT_8` bietet die maximale Verteilung in der Standardfamilie. Im Gegensatz zu einem Multiplexer (`ALI_MUX`) oder einer Weiche (`ALI_SWITCH`) wird hier **jeder Ausgang mit dem gleichen Signal** versorgt – es findet keine Auswahl oder Umschaltung statt.

## Fazit
Der `ALI_SPLIT_8` ist ein einfacher, aber essenzieller Baustein zur Vervielfältigung von ALI-Signalen. Durch seine generische Definition und den Verzicht auf Zustandslogik eignet er sich besonders für robuste, latenzarme Verteilungen in der landwirtschaftlichen Automatisierungstechnik.