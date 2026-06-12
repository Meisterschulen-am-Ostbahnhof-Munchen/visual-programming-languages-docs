# AIS_SPLIT_6


![AIS_SPLIT_6](./AIS_SPLIT_6.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **AIS_SPLIT_6** dient dazu, ein eingehendes AIS-Signal (Automation Interface Signal) auf sechs separate AIS-Ausgänge zu verteilen. Er fungiert als generischer Splitter, der das ankommende Signal ohne Verzögerung oder Manipulation an alle angeschlossenen Ausgänge weiterleitet.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine Ereigniseingänge vorhanden.

### **Ereignis-Ausgänge**

Keine Ereignisausgänge vorhanden.

### **Daten-Eingänge**

Keine Dateneingänge vorhanden (die Datenübertragung erfolgt ausschließlich über den Adapter).

### **Daten-Ausgänge**

Keine Datenausgänge vorhanden (die Datenübertragung erfolgt ausschließlich über die Adapter).

### **Adapter**

| Typ | Richtung | Name | Beschreibung |
|-----|----------|------|--------------|
| `adapter::types::unidirectional::AIS` | Eingang (Socket) | IN | Eingehendes AIS-Signal, das auf alle Ausgänge verteilt wird. |
| `adapter::types::unidirectional::AIS` | Ausgang (Plug) | OUT1 | Erster Ausgang mit dem gesplitteten AIS-Signal. |
| `adapter::types::unidirectional::AIS` | Ausgang (Plug) | OUT2 | Zweiter Ausgang mit dem gesplitteten AIS-Signal. |
| `adapter::types::unidirectional::AIS` | Ausgang (Plug) | OUT3 | Dritter Ausgang mit dem gesplitteten AIS-Signal. |
| `adapter::types::unidirectional::AIS` | Ausgang (Plug) | OUT4 | Vierter Ausgang mit dem gesplitteten AIS-Signal. |
| `adapter::types::unidirectional::AIS` | Ausgang (Plug) | OUT5 | Fünfter Ausgang mit dem gesplitteten AIS-Signal. |
| `adapter::types::unidirectional::AIS` | Ausgang (Plug) | OUT6 | Sechster Ausgang mit dem gesplitteten AIS-Signal. |

## Funktionsweise

Der Baustein empfängt ein AIS-Signal über den Socket `IN` und leitet es gleichzeitig und identisch an alle sechs Plugs `OUT1` bis `OUT6` weiter. Es findet keine Datenverarbeitung, Filterung oder Zwischenspeicherung statt – die Verteilung erfolgt rein signaltechnisch. Der Baustein arbeitet unidirektional (nur vom Eingang zu den Ausgängen) und stellt somit eine einfache 1:6-Vervielfachung des AIS-Signals dar.

## Technische Besonderheiten

- **Generischer Typ**: Der Baustein ist als generischer Funktionsblock (`GEN_AIS_SPLIT`) ausgeführt, kann also mit verschiedenen AIS-Typen verwendet werden, solange die Adapterdefinition `adapter::types::unidirectional::AIS` übereinstimmt.
- **Unidirektional**: Der Datenaustausch erfolgt nur in eine Richtung – vom Eingang zu den Ausgängen. Rückwirkungen von den Ausgängen auf den Eingang sind nicht vorgesehen.
- **Keine Eigenlogik**: Da weder Ereignisse noch Dateneingänge/-ausgänge existieren, läuft der Baustein rein passiv und benötigt keine Zustandsmaschine oder Algorithmen.
- **Einfache Skalierbarkeit**: Durch die feste Anzahl von sechs Ausgängen ist der Baustein für typische Anwendungen optimiert, bei denen genau sechs parallele AIS-Verbindungen benötigt werden.

## Zustandsübersicht

Der Baustein besitzt keine eigene Zustandsmaschine (ECC). Sein Verhalten ist deterministisch und zeitlos: Ein ankommendes AIS-Signal wird sofort an alle Ausgänge weitergegeben. Es gibt keine internen Zustände oder Schritte.

## Anwendungsszenarien

- **Verteilen von Steuersignalen**: Ein AIS-Signal von einer zentralen Steuerung (z. B. einem übergeordneten Funktionsbaustein) muss an mehrere untergeordnete Komponenten weitergeleitet werden.
- **Monitoring und Parallelbetrieb**: Ein Signal soll gleichzeitig für Regelung, Überwachung und Protokollierung genutzt werden.
- **Testaufbauten**: Einheitliches Testsignal wird auf mehrere simulierte oder reale Module verteilt.
- **Redundante Verkabelung**: Signalverteilung über mehrere Pfade zur Erhöhung der Ausfallsicherheit.

## Vergleich mit ähnlichen Bausteinen

Im 4diac-Framework existieren möglicherweise andere Split-Bausteine, die sich in der Anzahl der Ausgänge oder im Datentyp unterscheiden. `AIS_SPLIT_6` ist speziell auf die AIS-Adapter-Schnittstelle und sechs Ausgänge zugeschnitten. Andere Splitter könnten eventuell über zusätzliche Ereignisse oder Konfigurationsparameter verfügen (z. B. selektives Weiterleiten), während dieser Baustein bewusst einfach und ohne Konfiguration gehalten ist.

## Fazit

Der `AIS_SPLIT_6` ist ein nützlicher und minimalistischer Baustein zur Signalfächerung in AIS-basierten Steuerungssystemen. Er erfüllt zuverlässig die Aufgabe, ein eingehendes Signal auf sechs Ausgänge zu verteilen, und zeichnet sich durch seine Einfachheit, generische Auslegung und klare Trennung der Schnittstellen aus. Dadurch eignet er sich besonders für modulare, transparente Steuerungsarchitekturen.