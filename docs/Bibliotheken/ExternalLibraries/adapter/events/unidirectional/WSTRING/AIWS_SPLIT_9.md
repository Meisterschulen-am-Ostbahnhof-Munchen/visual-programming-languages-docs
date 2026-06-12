# AIWS_SPLIT_9


![AIWS_SPLIT_9](./AIWS_SPLIT_9.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `AIWS_SPLIT_9` dient der Aufteilung eines eingehenden `AIWS`-Adapter-Signals in neun separate, identisch typisierte Ausgänge. Er wird als generischer Baustein (generic FB) bereitgestellt und ermöglicht die Verteilung eines einzelnen Adapter-Datenstroms an mehrere nachfolgende Funktionseinheiten. Der Block ist unidirektional ausgelegt und benötigt keine Ereignis- oder Dateneingänge, da die Datenübertragung ausschließlich über die Adapter-Schnittstellen erfolgt.

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

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| **Socket** | `IN` | `adapter::types::unidirectional::AIWS` | Eingehendes AIWS-Signal, das auf die neun Ausgänge verteilt wird. |
| **Plug** | `OUT1` | `adapter::types::unidirectional::AIWS` | Erster ausgehender AIWS-Ausgang. |
| **Plug** | `OUT2` | `adapter::types::unidirectional::AIWS` | Zweiter ausgehender AIWS-Ausgang. |
| **Plug** | `OUT3` | `adapter::types::unidirectional::AIWS` | Dritter ausgehender AIWS-Ausgang. |
| **Plug** | `OUT4` | `adapter::types::unidirectional::AIWS` | Vierter ausgehender AIWS-Ausgang. |
| **Plug** | `OUT5` | `adapter::types::unidirectional::AIWS` | Fünfter ausgehender AIWS-Ausgang. |
| **Plug** | `OUT6` | `adapter::types::unidirectional::AIWS` | Sechster ausgehender AIWS-Ausgang. |
| **Plug** | `OUT7` | `adapter::types::unidirectional::AIWS` | Siebter ausgehender AIWS-Ausgang. |
| **Plug** | `OUT8` | `adapter::types::unidirectional::AIWS` | Achter ausgehender AIWS-Ausgang. |
| **Plug** | `OUT9` | `adapter::types::unidirectional::AIWS` | Neunter ausgehender AIWS-Ausgang. |

## Funktionsweise

Der Baustein nimmt am Socket `IN` ein AIWS-Adapter-Signal entgegen und leitet dieses unverändert an alle neun Plugs `OUT1` bis `OUT9` weiter. Es findet keine Datenverarbeitung, Umwandlung oder Verzögerung statt – es handelt sich um eine reine Signalvervielfachung (Fan-Out). Die interne Logik ist als generischer Funktionsblock realisiert, der zur Laufzeit durch die Angabe eines generischen Klassennamens (`eclipse4diac::core::GenericClassName`) parametrisiert werden kann.

## Technische Besonderheiten

- **Generischer Funktionsblock**: Der Baustein ist als generischer `GEN_AIWS_SPLIT` gekennzeichnet. Dadurch kann er in verschiedenen Kontexten wiederverwendet werden, indem der konkrete Adapter-Typ zur Entwurfszeit festgelegt wird.  
- **Unidirektionalität**: Sowohl der Eingang als auch alle Ausgänge sind unidirektional (`adapter::types::unidirectional::AIWS`), d.h. Daten fließen nur vom Socket zu den Plugs.  
- **Keine Ereignissteuerung**: Der Split-Block arbeitet ohne Ereignisse – die Datenweitergabe erfolgt implizit über die Adapter-Verbindungen.  
- **Keine Zustandsmaschine**: Es existiert kein ECC (Execution Control Chart), daher ist der Block zustandslos und benötigt keine Initialisierung.  
- **Typ-Hash**: Ein optionales Attribut `eclipse4diac::core::TypeHash` kann für Identifikations- und Versionierungszwecke gesetzt werden, ist aber im vorliegenden Fall leer.

## Zustandsübersicht

Der Funktionsblock besitzt keine internen Zustände. Er ist rein kombinatorisch und führt keine sequenziellen Abläufe aus.

## Anwendungsszenarien

- **Signalverteilung in Automatisierungssystemen**: Wenn ein Sensor- oder Steuerungssignal (z.B. ein AIWS-konformer Temperatur- oder Druckwert) an mehrere unabhängige Module weitergegeben werden muss.  
- **Redundante Verarbeitung**: Ein Signal wird an identische, parallel arbeitende Algorithmen oder Sicherheitslogiken verteilt.  
- **Test- und Simulationsumgebungen**: Ein einzelnes AIWS-Signal soll auf mehrere Prüf- oder Überwachungsblöcke aufgeteilt werden.  
- **Architekturvereinfachung**: Erspart die manuelle Verkabelung mehrerer Split-Blöcke und reduziert die Komplexität des Applikationsdiagramms.

## Vergleich mit ähnlichen Bausteinen

- **AIWS_SPLIT_n (z.B. AIWS_SPLIT_4)**: Andere Varianten mit einer unterschiedlichen Anzahl von Ausgängen (z.B. 2, 4, 8). Der vorliegende Block spezialisiert sich auf eine Aufteilung in genau neun Stränge.  
- **Manueller Split mit mehreren FB-Instanzen**: Ohne diesen Baustein müsste man das AIWS-Signal durch Hintereinanderschaltung mehrerer 2- oder 3-fach-Split-Blöcke realisieren, was die Übersichtlichkeit verringert.  
- **Datenverteiler auf Basis von Ereignissen**: Bausteine, die über Ereignisse gesteuert werden, benötigen zusätzliche Event-Verdrahtung und sind für reine Datenweiterleitung weniger effizient.

## Fazit

`AIWS_SPLIT_9` ist ein einfacher, aber nützlicher generischer Funktionsblock zur Vervielfachung eines unidirektionalen AIWS-Adapter-Signals auf neun Ausgänge. Er verzichtet auf überflüssige Komplexität, benötigt keine Ereignissteuerung und kann ohne zusätzliche Konfiguration direkt in IEC 61499-Applikationen eingesetzt werden. Dank seiner generischen Natur ist er flexibel an verschiedene Adapter-Typen anpassbar und eignet sich besonders für Signalverteilungen in modularen Automatisierungsarchitekturen.