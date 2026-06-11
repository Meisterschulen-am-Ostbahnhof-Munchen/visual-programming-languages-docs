# ALR_TO_AL


![ALR_TO_AL](./ALR_TO_AL.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ALR_TO_AL** ist ein Composite-Baustein (zusammengesetzter Baustein) gemäß IEC 61499-2. Er dient der Umwandlung eines **ALR-Adapters** (LREAL-Datentyp) in einen **AL-Adapter** (LWORD-Datentyp). Implementiert wird die Konvertierung über den internen Baustein `F_LREAL_TO_LWORD` aus der IEC 61131-3-Bibliothek.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Der Funktionsblock besitzt **keine eigenständigen Ereignis-Eingänge**. Ereignisse werden über den **Socket-Adapter** `ALR_IN` bereitgestellt:

| Adapter | Ereignis / Signal | Beschreibung |
|---------|-------------------|--------------|
| ALR_IN  | E1                | Trigger-Ereignis zur Auslösung der Konvertierung |

### **Ereignis-Ausgänge**
Der Funktionsblock besitzt **keine eigenständigen Ereignis-Ausgänge**. Ereignisse werden über den **Plug-Adapter** `AL_OUT` ausgegeben:

| Adapter | Ereignis / Signal | Beschreibung |
|---------|-------------------|--------------|
| AL_OUT  | E1                | Bestätigungsereignis nach abgeschlossener Konvertierung |

### **Daten-Eingänge**
Auch hier gibt es **keine direkten Dateneingänge**. Die Daten werden über den Socket-Adapter `ALR_IN` hereingeführt:

| Adapter | Daten / Signal | Datentyp | Beschreibung |
|---------|----------------|----------|--------------|
| ALR_IN  | D1             | LREAL    | Eingangswert im LREAL-Format |

### **Daten-Ausgänge**
Keine direkten Datenausgänge. Die Ausgabedaten erfolgen über den Plug-Adapter `AL_OUT`:

| Adapter | Daten / Signal | Datentyp | Beschreibung |
|---------|----------------|----------|--------------|
| AL_OUT  | D1             | LWORD    | Konvertierter Ausgangswert im LWORD-Format |

### **Adapter**
Der Baustein wird über zwei Adapter mit der Umgebung verbunden:

- **Socket** `ALR_IN`: Vom Typ `adapter::types::unidirectional::ALR` – bereitgestellt von einer vorhergehenden Komponente.
- **Plug** `AL_OUT`: Vom Typ `adapter::types::unidirectional::AL` – wird einer nachfolgenden Komponente angeboten.

Die Adapter übertragen sowohl Ereignisse als auch Daten über ihre jeweiligen Ports (E1, D1).

## Funktionsweise
Bei Eintreffen eines Ereignisses **E1** am Socket `ALR_IN` wird der interne Baustein `F_LREAL_TO_LWORD` (Typ `iec61131::conversion::F_LREAL_TO_LWORD`) über seinen Ereigniseingang `REQ` aktiviert. Gleichzeitig wird der Datenwert `D1` des Adapter-Sockets an den Dateneingang `IN` des Konvertierungsbausteins übergeben. Nach erfolgreicher Umwandlung gibt der interne Baustein ein Bestätigungsereignis an seinem Ausgang `CNF` aus. Dieses Ereignis wird an den Ereigniseingang `E1` des Plug-Adapters `AL_OUT` weitergeleitet. Der konvertierte Wert (LWORD) wird über die Datenverbindung `Convert.OUT` → `AL_OUT.D1` an den Adapter-Plug übergeben.

Die Konvertierung selbst entspricht der IEC 61131-3-Funktion `LREAL_TO_LWORD`, die den bitweisen Aufbau eines LREAL-Wertes in einen LWORD-Wert abbildet (z. B. zur Übertragung von Gleitkommazahlen als Rohdaten).

## Technische Besonderheiten
- **Composite-Baustein**: Die Funktionalität wird durch eine interne Netzwerkschaltung realisiert, die den Baustein `F_LREAL_TO_LWORD` verwendet.
- **Paketierung**: Der Baustein ist im Paket `adapter::conversion::unidirectional` abgelegt, was auf seine Verwendung in unidirektionalen Adapterketten hinweist.
- **Import**: `iec61131::conversion::F_LREAL_TO_LWORD` muss im Projekt verfügbar sein.
- **Copyright**: Der Baustein wurde für die HR Agrartechnik GmbH entwickelt und steht unter der Eclipse Public License 2.0 (EPL-2.0).

## Zustandsübersicht
Da es sich um einen **Composite-FB** ohne eigene Zustandsmaschine handelt, ergibt sich das Verhalten aus dem des internen Funktionsblocks `F_LREAL_TO_LWORD`. Dieser führt eine reine, stateless-Konvertierung durch: Ein Ereignis löst die Berechnung aus, das Ergebnis wird sofort bereitgestellt. Der Baustein hat keinen internen Zustand, der über mehrere Aufrufe hinweg erhalten bleibt.

## Anwendungsszenarien
- **Datenformat-Anpassung**: Wenn ein Systemteil Daten im ALR-Format (LREAL über Adapter) liefert, aber eine nachfolgende Komponente nur AL-Schnittstellen (LWORD über Adapter) versteht.
- **Kommunikation zwischen unterschiedlichen Steuerungsebenen**: Z. B. Übergabe von physikalischen Messwerten aus einer SPS (LREAL) an ein übergeordnetes Leitsystem, das LWORD als Rohdatenformat erwartet.
- **Test- und Simulationsaufbauten**: Erzeugung definierter LWORD-Werte aus LREAL-Quellen, ohne die eigentliche Adapterlogik zu ändern.

## Vergleich mit ähnlichen Bausteinen
- **AL_TO_ALR**: Führt die entgegengesetzte Konvertierung (LWORD → LREAL) durch.
- **Direkte Konvertierungsfunktionen**: Die IEC 61131-3 bietet `LREAL_TO_LWORD` und `LWORD_TO_LREAL` als elementare Bausteine – `ALR_TO_AL` kapselt diese in einen Adapter-konformen Composite-Baustein, sodass er direkt in Adapterketten eingesetzt werden kann.

## Fazit
Der Funktionsblock **ALR_TO_AL** ist ein spezialisierter Konvertierungsbaustein für die Umwandlung eines LREAL-Adapters in einen LWORD-Adapter. Seine Composite-Struktur ermöglicht eine saubere Integration in bestehende Adapter-basierte Architekturen, ohne dass der Anwender die zugrundeliegende Konvertierungsfunktion manuell verschalten muss. Die eindeutige Ereignissteuerung und die Verwendung standardisierter Datentypen machen ihn zu einer robusten Lösung für die Anpassung von Datenformaten in IEC 61499-Steuerungssystemen.