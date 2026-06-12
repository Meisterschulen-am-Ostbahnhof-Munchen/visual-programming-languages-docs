# AS_TO_ALR


![AS_TO_ALR](./AS_TO_ALR.svg)

*Kein Bild verfügbar.*

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AS_TO_ALR** ist ein zusammengesetzter Baustein (Composite FB), der einen **AS-Adapter** (Datentyp SINT) in einen **ALR-Adapter** (Datentyp LREAL) umwandelt. Er dient als einfache Schnittstellen‑Konvertierung zwischen diesen beiden unidirektionalen Adaptertypen und ist im Paket `adapter::conversion::unidirectional` abgelegt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name  | Kommentar                          |
|-------|------------------------------------|
| E1    | Ereignis vom AS-Adapter (Socket AS_IN) |

### **Ereignis-Ausgänge**

| Name  | Kommentar                            |
|-------|--------------------------------------|
| E1    | Ereignis zum ALR-Adapter (Plug ALR_OUT) |

### **Daten-Eingänge**

| Name | Datentyp | Kommentar                       |
|------|----------|---------------------------------|
| D1   | SINT     | Datenwert vom AS-Adapter (Socket AS_IN) |

### **Daten-Ausgänge**

| Name | Datentyp | Kommentar                         |
|------|----------|-----------------------------------|
| D1   | LREAL    | Datenwert zum ALR-Adapter (Plug ALR_OUT) |

### **Adapter**

| Richtung | Name   | Typ                                   | Kommentar                  |
|----------|--------|---------------------------------------|----------------------------|
| Socket   | AS_IN  | `adapter::types::unidirectional::AS`  | Eingangs‑Adapter (SINT)    |
| Plug     | ALR_OUT| `adapter::types::unidirectional::ALR` | Ausgangs‑Adapter (LREAL)   |

## Funktionsweise

Der **AS_TO_ALR**-Baustein leitet die eingehenden Ereignisse und Datenwerte direkt und ohne weitere Verarbeitung an die Ausgangsseite weiter.  
- Das Ereignis **E1** am Socket `AS_IN` wird unverzögert an den Plug `ALR_OUT` übergeben.  
- Der Datenwert **D1** vom Typ SINT wird an den Ausgang gleichen Namens weitergeleitet. Die Umwandlung von SINT nach LREAL erfolgt implizit durch die Laufzeitumgebung – der Funktionsblock selbst führt keine arithmetische Operation aus.

Der Baustein besitzt keine eigene Zustandsmaschine (ECC) und keine internen Algorithmen; seine gesamte Funktionalität wird durch die enthaltenen Verbindungen realisiert.

## Technische Besonderheiten

- **Komposit‑Struktur**: Der FB besteht ausschließlich aus einem internen Netzwerk (FBNetwork) mit direkten Ereignis‑ und Datenverbindungen zwischen den Adaptern.
- **Implicite Typkonvertierung**: Die Datenkonvertierung von SINT nach LREAL wird von der IEC‑61499‑Laufzeitumgebung sichergestellt. Eine explizite Typanpassung ist nicht erforderlich.
- **Paketierung**: Der Baustein ist im Paket `adapter::conversion::unidirectional` organisiert und bietet eine saubere Trennung zwischen Adapter‑ und Konverterlogik.

## Zustandsübersicht

Der **AS_TO_ALR**-Baustein besitzt keine eigene Zustandsmaschine (kein ECC‑Diagramm). Sein Verhalten ist rein durch die direkte Verschaltung der Ein‑ und Ausgänge definiert. Ein definierter Start‑ oder Endzustand existiert nicht.

## Anwendungsszenarien

- **Sensor‑Anbindung**: Ein Sensor liefert Daten im SINT‑Format (z. B. ein 8‑Bit‑Zähler), die über einen AS‑Adapter in eine Umgebung mit LREAL‑Schnittstelle (z. B. Analog‑Adapter) eingebunden werden sollen.
- **Protokoll‑Konvertierung**: In heterogenen Automatisierungssystemen, in denen unterschiedliche Komponenten Adapter verschiedener Typen erwarten, dient **AS_TO_ALR** als einfacher Umsetzer.
- **Schnittstellen‑Migration**: Bei der Umstellung von SINT‑ auf LREAL‑basierte Adapter kann dieser Baustein als temporäre Brücke verwendet werden.

## Vergleich mit ähnlichen Bausteinen

- **AS_TO_AR**: Wandelt einen AS‑Adapter (SINT) in einen AR‑Adapter (REAL) um – ähnliche Struktur, jedoch mit kleinerem Wertebereich (REAL statt LREAL).
- **ALR_TO_AS**: Die inverse Konvertierung (LREAL → SINT), die ggf. eine explizite Bereichsprüfung oder Rundung erfordert.
- **AS_TO_ALR** zeichnet sich durch den größeren Wertebereich des Ausgangs (LREAL) aus, was eine verlustfreie Übertragung von SINT‑Werten ermöglicht.

## Fazit

Der **AS_TO_ALR** ist ein minimaler, aber nützlicher Konverterbaustein für die einfache Ankopplung von AS‑Adaptern an ALR‑Adapter. Seine Composite‑Architektur und die implizite Typkonvertierung machen ihn leicht verständlich und effizient in der Anwendung.