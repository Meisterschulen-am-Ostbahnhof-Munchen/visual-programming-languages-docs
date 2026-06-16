# AI_TO_AR


![AI_TO_AR](./AI_TO_AR.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AI_TO_AR** ist ein Composite-Baustein, der eine Schnittstellenumsetzung von einem **AI**‑Adapter (Integer-Typ) auf einen **AR**‑Adapter (Real-Typ) ermöglicht. Er dient als reine Durchleitungs- und Anpassungseinheit zwischen verschiedenen Adapterprotokollen in einem industriellen Steuerungssystem.

## Schnittstellenstruktur
Da **AI_TO_AR** keine eigenständigen Ereignis- oder Datenschnittstellen besitzt, erfolgt die gesamte Kommunikation ausschließlich über die angeschlossenen Adapter.

### **Ereignis-Eingänge**
– nicht vorhanden –  
Die Ereignissteuerung erfolgt über den eingehenden Adapter **AI_IN**.

### **Ereignis-Ausgänge**
– nicht vorhanden –  
Die Ereignisweiterleitung erfolgt über den ausgehenden Adapter **AR_OUT**.

### **Daten-Eingänge**
– nicht vorhanden –  
Die Daten werden über den **AI_IN**‑Adapter als Integer-Wert bereitgestellt.

### **Daten-Ausgänge**
– nicht vorhanden –  
Die Daten werden über den **AR_OUT**‑Adapter als Real-Wert ausgegeben.

### **Adapter**

| Name   | Typ                                          | Richtung | Beschreibung          |
|--------|----------------------------------------------|----------|-----------------------|
| AI_IN  | `adapter::types::unidirectional::AI`        | Socket   | Integer‑Adapter (Eingang) |
| AR_OUT | `adapter::types::unidirectional::AR`        | Plug     | Real‑Adapter (Ausgang)    |

## Funktionsweise
Im FBNetzwerk des Composite-Bausteins sind die Ereignis- und Datenleitungen der beiden Adapter direkt miteinander verbunden:
- Das Ereignis **E1** des AI_IN‑Adapters wird auf das Ereignis **E1** des AR_OUT‑Adapters geleitet.
- Der Datenwert **D1** (Typ INT) des AI_IN‑Adapters wird auf den Datenwert **D1** (Typ REAL) des AR_OUT‑Adapters übertragen.

Der Baustein führt selbst keine explizite Typkonvertierung durch; die Anpassung von Integer auf Real erfolgt entweder implizit durch die Laufzeitumgebung oder muss durch den angeschlossenen Kontext sichergestellt werden. Somit fungiert der Block als reine Durchschleife für Ereignisse und Daten zwischen den beiden Adapterschnittstellen.

## Technische Besonderheiten
- Der Baustein enthält keinen eigenen Event‑oder Data‑Interface; seine gesamte Kommunikation läuft über die Adapter.
- Es ist kein interner Zustandsautomat (ECC) vorhanden – der Block arbeitet rein ereignisgesteuert durch die Verbindungen.
- Durch die Verwendung von Adaptern wird eine lose Kopplung zwischen den Ein‑ und Ausgängen erreicht, was die Wiederverwendbarkeit und Austauschbarkeit der Schnittstellen erhöht.

## Zustandsübersicht
Der Baustein besitzt keinen Zustandsautomaten. Die Verarbeitung erfolgt direkt ohne Verzögerung oder Zustandsabhängigkeit.

## Anwendungsszenarien
- **Adapter-Konvertierung**: Einsatz in Anlagen, in denen ein Integer‑basiertes Sensorsignal (AI) an eine Komponente übergeben werden muss, die ein Real‑Signal (AR) erwartet.
- **Schnittstellenanpassung**: Nutzung in modularen Steuerungslösungen, um zwischen verschiedenen Adaptertypen zu vermitteln, ohne die eigentliche Datenverarbeitung zu beeinflussen.
- **Prototypen und Tests**: Schnelles Zusammenstecken von unterschiedlichen Adapter‑Komponenten während der Entwicklungsphase.

## Vergleich mit ähnlichen Bausteinen

| Baustein  | Funktion                                        | Besonderheit                          |
|-----------|-------------------------------------------------|---------------------------------------|
| AI_TO_AR  | Durchleitung von INT nach REAL über Adapter     | Keine eigene Logik, reine Adaptervermittlung |
| REAL_TO_INT | Konvertierung von REAL nach INT (i.d.R. mit Rundung) | Enhält oft einen eigenen Algorithmus |
| ADAPTER_COUPLER | Allgemeine Adapterkopplung ohne Typanpassung   | Erfordert identische Datentypen       |

Im Gegensatz zu dedizierten Konvertern nimmt **AI_TO_AR** keine aktive Wertumwandlung vor, sondern verlässt sich auf die Kompatibilität der angeschlossenen Adapter.

## Fazit
**AI_TO_AR** ist ein einfacher, aber effektiver Composite-Baustein zur Verbindung zweier unterschiedlicher Adapterschnittstellen (INT nach REAL). Er eignet sich besonders für die systemübergreifende Signalweitergabe in IEC 61499‑basierten Steuerungen, bei denen die Logik der Typumsetzung außerhalb des Blocks liegt. Seine klare Struktur macht ihn zu einem nützlichen Werkzeug für modulare und flexible Automatisierungslösungen.