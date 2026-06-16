# GET_DATE


![GET_DATE](./GET_DATE.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **GET_DATE** liest einen DATE-Wert aus einer InOut-Variable aus und stellt diesen als gepufferten Ausgang bereit. Bei Anforderung durch ein Ereignis wird der aktuelle Wert der Quelle in einen internen Puffer kopiert und anschließend am Ausgang sowie an der InOut-Variable selbst ausgegeben.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name | Typ | Kommentar | Mit-Variablen |
|------|-----|-----------|----------------|
| REQ | Event | Normale Ausführungsanforderung | IN |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar | Mit-Variablen |
|------|-----|-----------|----------------|
| CNF | Event | Ausführungsbestätigung | OUT, IN |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| IN | DATE | Quellvariable (InOut) |

### **Daten-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| OUT | DATE | Gepufferter Ausgabewert |
| IN | DATE | Quellvariable (InOut) – wird bei CNF ebenfalls ausgegeben |

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Baustein besitzt einen einfachen Ausführungszustand **REQ**:
1. Ein eingehendes Ereignis am Eingang **REQ** löst die Verarbeitung aus.
2. Der interne Algorithmus kopiert den aktuellen Wert der InOut-Variable **IN** in das Ausgangssignal **OUT**.
3. Anschließend wird das Ereignis **CNF** gesendet. Dabei werden sowohl der Wert von **OUT** als auch der (unveränderte) Wert von **IN** an den Ausgang übergeben.

Die Funktionalität entspricht einer einfachen Wertübernahme ohne weitere Verarbeitung oder Zustandsspeicherung über mehrere Aufrufe hinweg.

## Technische Besonderheiten
- Die Verwendung einer **InOut-Variable** ermöglicht den direkten Zugriff auf eine externe Variable, ohne einen separaten Dateneingang zu deklarieren.
- Die Pufferung erfolgt nur während der Ausführung des Algorithmus; bei jedem neuen **REQ** wird der aktuelle Wert von **IN** erneut gelesen.
- Der Baustein ist als **SimpleFB** realisiert und besitzt keine internen Zustandsübergänge – die Verarbeitung ist rein kombinatorisch mit einem einzigen Schritt.

## Zustandsübersicht
Der Funktionsblock besteht aus genau einem Zustand:
- **REQ**: Beim Eintreten wird der Algorithmus ausgeführt, der **OUT** mit **IN** beschreibt, und das Ereignis **CNF** wird gesendet.

Es gibt keine weiteren Zustände oder bedingten Übergänge.

## Anwendungsszenarien
- **Lesen eines globalen Datums**: Wenn eine Systemzeit oder ein Datum aus einer zentralen Variable gelesen und lokal verwendet werden soll.
- **Pufferung für nachfolgende Verarbeitung**: Um einen DATE-Wert zu einem bestimmten Zeitpunkt festzuhalten und an andere Bausteine weiterzugeben.
- **Kaskadierung von InOut-Zugriffen**: In Kombination mit weiteren Bausteinen, die auf die gleiche InOut-Variable zugreifen, um konsistente Daten zu gewährleisten.

## Vergleich mit ähnlichen Bausteinen
- **GET_BOOL**, **GET_INT**, **GET_STRING** etc.: Diese Bausteine arbeiten nach dem gleichen Prinzip, jedoch mit anderen Datentypen. Sie alle nutzen eine InOut-Variable als Quelle und einen gepufferten Ausgang.
- **SET_DATE**: Der Gegenpart – er schreibt einen Wert in eine InOut-Variable anstelle des Lesens.
- Alle diese Bausteine sind einfach aufgebaut und eignen sich für standardisierte Zugriffe auf gemeinsam genutzte Daten.

## Fazit
**GET_DATE** ist ein minimalistischer, aber nützlicher Funktionsblock für den Lesezugriff auf einen DATE-Wert über eine InOut-Variable. Seine einfache Zustandslogik und die direkte Wertkopie machen ihn zuverlässig und leicht verständlich. Er eignet sich besonders für modulare Automatisierungslösungen, bei denen Daten zwischen Bausteinen über eine gemeinsame Variable ausgetauscht werden sollen.