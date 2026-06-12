# AB_SPLIT_4


![AB_SPLIT_4](./AB_SPLIT_4.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein **AB_SPLIT_4** dient dazu, eine einzelne eingehende unidirektionale Adapterverbindung vom Typ `AB` auf vier parallele ausgehende Adapterverbindungen gleichen Typs zu verteilen. Er ist als generischer Baustein konzipiert und ermöglicht die Aufteilung eines Daten- oder Signalflusses auf mehrere nachgeschaltete Komponenten.

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
| Socket   | `IN` | `adapter::types::unidirectional::AB` | Eingehende unidirektionale Adapterverbindung |
| Plug     | `OUT1` | `adapter::types::unidirectional::AB` | Erste ausgehende Adapterverbindung |
| Plug     | `OUT2` | `adapter::types::unidirectional::AB` | Zweite ausgehende Adapterverbindung |
| Plug     | `OUT3` | `adapter::types::unidirectional::AB` | Dritte ausgehende Adapterverbindung |
| Plug     | `OUT4` | `adapter::types::unidirectional::AB` | Vierte ausgehende Adapterverbindung |

## Funktionsweise

Der Baustein fungiert als passiver Verteiler (Splitter) auf Adapterebene. Sobald am Socket `IN` eine Adapterverbindung des Typs `AB` hergestellt wird, leitet der Baustein die über diese Verbindung ankommenden Daten oder Signale unverändert an alle vier Plugs `OUT1` bis `OUT4` weiter. Die Aufteilung erfolgt ohne Datenmodifikation oder Pufferung. Der Baustein besitzt keine eigenen Ereignisse oder Datenpunkte; die gesamte Kommunikation erfolgt ausschließlich über die Adapterschnittstellen.

## Technische Besonderheiten

- **Generische Auslegung:** Der Baustein ist als generischer FB (`GenericClassName = 'GEN_AB_SPLIT'`) implementiert und kann daher für verschiedene konkrete Ausprägungen des Adaptertyps `AB` verwendet werden.
- **Unidirektionalität:** Die Adapter sind als unidirektional deklariert. Dies bedeutet, dass der Datenfluss nur in eine Richtung (vom Socket zu den Plugs) erfolgt. Rückkanäle sind nicht vorgesehen.
- **Keine aktive Logik:** Der Baustein enthält keinen Algorithmus oder Zustandsautomaten. Er fungiert rein passiv als Verdrahtungshilfe auf der Architekturebene.
- **Einfachheit:** Der Baustein reduziert die Komplexität der Systemverkabelung, indem er eine physische oder logische Aufteilung eines Adaptersignals modelliert.

## Zustandsübersicht

Der Baustein besitzt keinen internen Zustandsautomaten (ECC – Execution Control Chart). Er verhält sich statisch und leitet während der gesamten Laufzeit die an `IN` anliegenden Daten an alle Ausgänge weiter. Es gibt keine Unterbrechungs- oder Initialisierungszustände.

## Anwendungsszenarien

- **Verteilen von Sensorwerten:** Ein Sensor liefert über einen `AB`-Adapter Daten, die parallel an mehrere Steuerungsmodule oder Anzeigeeinheiten weitergegeben werden müssen.
- **Test- und Diagnoseumgebungen:** Ein Datenstrom wird an eine Verarbeitungseinheit und gleichzeitig an eine Logging‑ oder Überwachungskomponente gesendet.
- **Modulare Systeme:** Innerhalb einer größeren Automatisierungsanwendung kann der Baustein verwendet werden, um ein gemeinsames Bussignal auf mehrere nachgeschaltete Funktionsbausteine aufzusplitten.

## Vergleich mit ähnlichen Bausteinen

Ähnliche Splitter-Bausteine existieren für andere Adaptertypen oder für datenbasierte Weiterleitungen. Der `AB_SPLIT_4` zeichnet sich durch seine spezifische Passform für den Adaptertyp `AB` und die unidirektionale Auslegung aus. Im Gegensatz zu Bausteinen mit Ereignis- oder Datenschnittstellen benötigt er keine zusätzliche Taktung oder Synchronisation – die Aufteilung erfolgt implizit durch die Verbindungstopologie.

## Fazit

Der `AB_SPLIT_4` ist ein einfacher, aber nützlicher generischer Funktionsbaustein zur Vervielfachung einer unidirektionalen Adapterverbindung. Er erleichtert die Strukturierung von Steuerungsanwendungen, indem er redundante Verkabelung vermeidet und eine klare Aufteilung von Signalfüssen ermöglicht. Seine generische Implementierung macht ihn flexibel und in verschiedenen Kontexten einsetzbar.