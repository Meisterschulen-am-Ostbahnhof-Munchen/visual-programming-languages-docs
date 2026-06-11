# AULI_TO_AR


![AULI_TO_AR](./AULI_TO_AR.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AULI_TO_AR** dient als konvertierender Composite-Baustein, der einen **AULI**-Adapter (ULINT) in einen **AR**-Adapter (REAL) umwandelt.  
Er ermöglicht die einfache Integration von Komponenten, die mit unterschiedlichen Datentypen arbeiten, und stellt die Typanpassung über standardisierte Adapter-Schnittstellen bereit.

## Schnittstellenstruktur

Der FB besitzt keine direkten Ereignis- oder Datenein-/ausgänge, sondern kommuniziert ausschließlich über zwei Adapter-Schnittstellen.

### **Ereignis-Eingänge**
- **AULI_IN.E1** (Ereignis vom Socket AULI_IN) – löst die Konvertierung des eingehenden ULINT-Wertes aus.

### **Ereignis-Ausgänge**
- **AR_OUT.E1** (Ereignis zum Plug AR_OUT) – signalisiert, dass der konvertierte REAL-Wert bereitsteht.

### **Daten-Eingänge**
- **AULI_IN.D1** (Daten vom Socket AULI_IN) – der zu konvertierende ULINT-Wert.

### **Daten-Ausgänge**
- **AR_OUT.D1** (Daten zum Plug AR_OUT) – der konvertierte REAL-Wert.

### **Adapter**
| Name   | Richtung | Typ                                              | Beschreibung                  |
|--------|----------|--------------------------------------------------|-------------------------------|
| AULI_IN | Socket   | `adapter::types::unidirectional::AULI` (ULINT) | Eingangswert                 |
| AR_OUT  | Plug     | `adapter::types::unidirectional::AR`    (REAL)  | Ausgangswert (konvertiert)  |

## Funktionsweise
Der FB ist als Composite-Baustein realisiert und enthält eine Instanz des Konvertierungs-FBs `F_ULINT_TO_REAL` aus der IEC‑61131‑Bibliothek.  

Ablauf:
1. Ein Ereignis auf **AULI_IN.E1** triggert die Ausführung des internen Konvertierungsbausteins `Convert`.
2. Der aktuelle ULINT-Wert von **AULI_IN.D1** wird an den Eingang `Convert.IN` übergeben.
3. Der interne FB führt die Umwandlung von `ULINT` nach `REAL` durch und legt das Ergebnis an `Convert.OUT` ab.
4. Nach Abschluss der Konvertierung wird das Ereignis **AR_OUT.E1** ausgelöst, und der konvertierte REAL-Wert steht an **AR_OUT.D1** zur Verfügung.

## Technische Besonderheiten
- **Composite-Struktur** – ermöglicht Wiederverwendung und Kapselung der Konvertierungslogik.
- **Adapter-basiert** – keine direkten Ein-/Ausgänge; die Kommunikation erfolgt über unidirektionale Adapter (Socket/Plug).
- **Verwendung der IEC‑61131-Standardfunktion** `F_ULINT_TO_REAL` – garantiert plattformunabhängige und korrekte Typumwandlung.
- **Ereignisgesteuerte Ausführung** – die Konvertierung wird nur bei Bedarf durch ein Eingangsereignis angestoßen.
- **Lizenz** – Eclipse Public License 2.0 (siehe Quelltext).

## Zustandsübersicht
Der FB besitzt **keine eigene Zustandsmaschine**. Die Konvertierung erfolgt rein funktional und ereignisgesteuert über den internen Baustein. Nach jedem Eingangsereignis wird einmalig umgewandelt und das Ergebnis ausgegeben.

## Anwendungsszenarien
- **Adapter-Brücke** zwischen Komponenten, die ULINT liefern, und solchen, die REAL erwarten.
- **Datenaufbereitung** in Steuerungssystemen, wenn physikalische Größen (z. B. Zählerstände als ULINT) in Gleitkommawerte für Berechnungen umgewandelt werden müssen.
- **Modulare Vernetzung** in IEC‑61499‑Anwendungen, wo Adapter als standardisierte Schnittstellen zwischen Funktionsbausteinen dienen.

## Vergleich mit ähnlichen Bausteinen
- **AULI_TO_LREAL** – analoge Konvertierung zu `LREAL` (Doppelgenauigkeit).  
- **Direkte Konvertierungs-FBs** (z. B. `F_ULINT_TO_REAL`): Diese arbeiten auf Datenebene, erfordern aber manuelle Verdrahtung von Ereignissen und Daten. Der **AULI_TO_AR** kapselt diese Verdrahtung und bietet eine kompakte Adapter-Schnittstelle.  
- **Andere Adapter-Konverter** – es existieren entsprechende Bausteine für andere Typkombinationen (z. B. `LINT_TO_AR`), die ähnlich aufgebaut sind.

## Fazit
Der **AULI_TO_AR** ist ein nützlicher Composite-Baustein zur einfachen und standardisierten Typkonvertierung von ULINT nach REAL über Adapter-Schnittstellen. Dank der ereignisgesteuerten Ausführung und der Nutzung einer IEC‑61131‑Standardfunktion ist er zuverlässig, wiederverwendbar und fügt sich nahtlos in IEC‑61499‑Projekte ein.