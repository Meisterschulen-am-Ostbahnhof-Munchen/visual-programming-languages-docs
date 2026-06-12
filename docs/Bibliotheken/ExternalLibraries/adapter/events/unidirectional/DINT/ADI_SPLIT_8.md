# ADI_SPLIT_8


![ADI_SPLIT_8](./ADI_SPLIT_8.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `ADI_SPLIT_8` dient dazu, einen einzelnen unidirektionalen ADI-Adapter (Application Data Interface) auf acht baugleiche Ausgangs-Adapter aufzuteilen. Er ist als generischer Baustein realisiert, der durch die Angabe eines `GenericClassName`-Attributs an verschiedene ADI-Kontexte angepasst werden kann. Der FB vereinfacht die Signaldistribution in Steuerungsanwendungen, indem er einen eingehenden Adapter-Pfad ohne Datenverlust auf mehrere Empfänger verteilt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Es sind keine Ereignis-Eingänge vorhanden. Die Datenweitergabe erfolgt kontinuierlich und ereignislos durch direkte Adapterverbindung.

### **Ereignis-Ausgänge**

Es sind keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**

Es sind keine Daten-Eingänge im herkömmlichen Sinne definiert. Die Informationsübertragung erfolgt ausschließlich über die Adapterschnittstellen.

### **Daten-Ausgänge**

Es sind keine Daten-Ausgänge vorhanden.

### **Adapter**

| Richtung | Name  | Typ              | Beschreibung                                    |
|----------|-------|------------------|-------------------------------------------------|
| Socket   | IN    | ADI (unidirektional) | Eingangsschnittstelle, die auf acht Ausgänge verteilt wird. |
| Plug     | OUT1  | ADI (unidirektional) | Erster ausgehender Adapter (identisch zu IN).   |
| Plug     | OUT2  | ADI (unidirektional) | Zweiter ausgehender Adapter.                    |
| Plug     | OUT3  | ADI (unidirektional) | Dritter ausgehender Adapter.                    |
| Plug     | OUT4  | ADI (unidirektional) | Vierter ausgehender Adapter.                    |
| Plug     | OUT5  | ADI (unidirektional) | Fünfter ausgehender Adapter.                    |
| Plug     | OUT6  | ADI (unidirektional) | Sechster ausgehender Adapter.                   |
| Plug     | OUT7  | ADI (unidirektional) | Siebter ausgehender Adapter.                    |
| Plug     | OUT8  | ADI (unidirektional) | Achter ausgehender Adapter.                     |

## Funktionsweise

Der FB leitet den über den Socket `IN` ankommenden ADI-Adapter unverändert auf alle acht `OUT`-Plugs weiter. Jeder Ausgang stellt eine eigenständige, aber inhaltlich identische Kopie des eingehenden Adapters dar. Die Verteilung erfolgt direkt – es findet keine Pufferung, Verzögerung oder Transformation statt. Änderungen am `IN`-Adapter werden sofort an alle `OUT`-Adapter propagiert. Der Baustein arbeitet rein kombinatorisch und benötigt keine Taktung oder Initialisierung.

## Technische Besonderheiten

- **Generischer Typ**: Durch das Attribut `eclipse4diac::core::GenericClassName` kann der FB auf verschiedene konkrete ADI-Implementierungen parametrisiert werden. Standardmäßig ist der Klassenname auf `'GEN_ADI_SPLIT'` gesetzt.
- **Keine Zustandshaltung**: Der FB besitzt kein internes Gedächtnis und keine Zustandsautomaten; er agiert als einfacher Signalverteiler.
- **Unidirektionalität**: Alle Adapter sind unidirektional ausgelegt – die Daten fließen nur vom Socket zu den Plugs. Eine Rückkopplung ist nicht vorgesehen.
- **Keine Ereignissteuerung**: Die Verteilung geschieht ohne Ereignisse, was die Laufzeitdeterministik erhöht.

## Zustandsübersicht

Der `ADI_SPLIT_8` FB besitzt keine internen Zustände oder einen ECC (Execution Control Chart). Er verhält sich statisch und führt zu jeder Zeit die gleiche Funktion aus. Eine Zustandsübersicht entfällt daher.

## Anwendungsszenarien

- **Signalbroadcasting**: Verteilen eines Messwert- oder Steuerungssignals (z. B. Temperatur, Drehzahl) an mehrere parallele Regelkreise.
- **Adapter-Multiplexing**: Bereitstellung eines zentralen ADI-Pfades für mehrere Subsysteme, die denselben Datenstrom benötigen.
- **Test- und Simulationsumgebungen**: Einspeisen eines simulierten Signals auf mehrere Empfänger-Blöcke gleichzeitig.
- **Modulare Automatisierungsarchitekturen**: Aufbau redundanter oder paralleler Verarbeitungspfade durch einfache Duplikation von Adapterverbindungen.

## Vergleich mit ähnlichen Bausteinen

- **SPLIT (Daten-Ereignis-Variante)**: Klassische Split-Bausteine (z. B. `E_SPLIT`) verteilen Ereignisse oder Datenwerte, nicht jedoch ganze Adapter-Pfade. `ADI_SPLIT_8` arbeitet auf einer höheren Abstraktionsebene (Adapterebene).
- **FORK-FBs**: Einige IEC 61499 Implementierungen bieten Fork-Bausteine für Adapter, die jedoch oft ereignisgesteuert sind. Dieser FB hier zeichnet sich durch den Verzicht auf Ereignisse und die feste Anzahl von acht Ausgängen aus.
- **Manuelle Verdrahtung**: Ohne diesen FB müsste jede Zielverbindung einzeln über Koppeladapter oder manuelle Verzweigungen realisiert werden – aufwändiger und fehleranfälliger.

## Fazit

`ADI_SPLIT_8` ist ein leistungsfähiger, generischer Split-Baustein für unidirektionale ADI-Adapter in IEC 61499 Anwendungen. Er reduziert den Verdrahtungsaufwand erheblich, erhöht die Übersichtlichkeit und ermöglicht die einfache Vervielfachung eines Adapterpfades. Durch die generische Parametrierung und den ereignislosen Betrieb eignet er sich besonders für datengetriebene Automatisierungssysteme, die eine zuverlässige und latenzarme Signalverteilung erfordern.