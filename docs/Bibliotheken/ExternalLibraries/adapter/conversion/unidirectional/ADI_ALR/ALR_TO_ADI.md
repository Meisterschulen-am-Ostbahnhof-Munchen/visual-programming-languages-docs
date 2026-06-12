# ALR_TO_ADI


![ALR_TO_ADI](./ALR_TO_ADI.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock **ALR_TO_ADI** ist ein Composite-Baustein, der eine Konvertierung zwischen zwei unterschiedlichen Adapter-Typen ermöglicht. Er übersetzt einen **ALR-Adapter** (der Daten vom Typ LREAL liefert) in einen **ADI-Adapter** (der Daten vom Typ DINT bereitstellt). Eingesetzt wird er in Umgebungen, die auf dem IEC 61499-Standard basieren, um die Kommunikation zwischen Komponenten mit unterschiedlichen Datentyp-Schnittstellen zu vereinheitlichen.

## Schnittstellenstruktur
Der Baustein besitzt keine eigenständigen Ereignis- oder Daten-Ein-/Ausgänge auf der obersten Ebene. Die gesamte Kommunikation erfolgt über die beiden Adapter-Schnittstellen.

### **Ereignis-Eingänge**
Der FB hat keine direkten Ereignis-Eingänge. Ereignisse werden über den **ALR_IN**-Socket empfangen.

### **Ereignis-Ausgänge**
Der FB hat keine direkten Ereignis-Ausgänge. Ereignisse werden über den **ADI_OUT**-Plug gesendet.

### **Daten-Eingänge**
Der FB hat keine direkten Daten-Eingänge. Daten werden über den **ALR_IN**-Socket empfangen.

### **Daten-Ausgänge**
Der FB hat keine direkten Daten-Ausgänge. Daten werden über den **ADI_OUT**-Plug gesendet.

### **Adapter**
| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| ALR_IN | Socket | adapter::types::unidirectional::ALR | Liefert ein Ereignis (E1) und einen Datenwert (D1) vom Typ LREAL. |
| ADI_OUT | Plug | adapter::types::unidirectional::ADI | Erwartet ein Ereignis (E1) und gibt einen Datenwert (D1) vom Typ DINT aus. |

## Funktionsweise
Der Baustein ist als Composite realisiert und enthält intern einen einzelnen Konvertierungs-FB: `iec61131::conversion::F_LREAL_TO_DINT`. Die Verschaltung erfolgt wie folgt:

1. **Ereignisweiterleitung**: Ein am Socket **ALR_IN** eintreffendes Ereignis (E1) wird direkt an den `REQ`-Eingang des Konvertierungs-FBs weitergegeben.
2. **Datenübergabe**: Der Datenwert **D1** des **ALR_IN**-Adapters wird an den `IN`-Eingang des Konvertierungs-FBs übergeben.
3. **Konvertierung**: Der FB `F_LREAL_TO_DINT` wandelt den LREAL-Wert in einen DINT-Wert um.
4. **Rückmeldung**: Das Bestätigungsereignis (CNF) des Konvertierungs-FBs löst das Ereignis **E1** am Plug **ADI_OUT** aus.
5. **Datenausgabe**: Der konvertierte DINT-Wert vom Ausgang `OUT` des Konvertierungs-FBs wird an den Datenausgang **D1** des **ADI_OUT**-Adapters übergeben.

Somit entsteht eine synchronisierte, ereignisgesteuerte Umwandlung: Jeder Eingangsimpuls erzeugt einen Ausgangsimpuls mit dem konvertierten Datenwert.

## Technische Besonderheiten
- **Composite-Baustein**: Die Implementierung nutzt einen internen Standard-FB aus der IEC 61131-Bibliothek, was Wartbarkeit und Wiederverwendung fördert.
- **Unidirektionalität**: Die Adapter sind als unidirektional deklariert, d.h. die Daten fließen nur in eine Richtung (ALR → ADI).
- **Paketstruktur**: Der Baustein ist im Paket `adapter::conversion::unidirectional` organisiert, was eine klare Einordnung in eine Bibliothek ermöglicht.
- **Keine Zustandsspeicherung**: Die Konvertierung erfolgt rein kombinatorisch mit ereignisgesteuerter Triggerung – es wird kein interner Zustand gehalten.

## Zustandsübersicht
Da der FB kein eigenes Zustandsdiagramm besitzt, beschränkt sich die Zustandslogik auf die des internen Konvertierungs-FBs. Im Wesentlichen gibt es zwei Phasen:

- **Warten**: Der FB wartet auf ein Ereignis am ALR_IN-Socket.
- **Konvertieren**: Nach Empfang des Ereignisses wird die Konvertierung durchgeführt und das Ergebnis am ADI_OUT-Socket ausgegeben.

Es gibt keine Verzögerungen oder Fehlerbehandlung – die Konvertierung erfolgt sofort und erzeugt stets einen gültigen DINT-Wert (bei Überlauf oder ungültigen Werten verhält sich der Konvertierungs-FB gemäß IEC 61131).

## Anwendungsszenarien
- **Systemintegration**: Ein Systemteil liefert Daten als LREAL (z.B. Gleitkomma-Messwerte), ein anderer benötigt ganzzahlige DINT-Werte (z.B. für Zählregister oder Indexberechnungen).
- **Adapter-Anpassung**: Wenn eine Komponente nur ALR-Adapter unterstützt, aber eine andere Komponente ADI-Adapter erwartet, kann dieser FB als Vermittler dienen.
- **Protokollumsetzung**: In eigenständigen Subsystemen, die über Adapter verbunden sind, ermöglicht der Baustein eine saubere Typanpassung ohne Änderung der ursprünglichen Adapterdefintion.

## Vergleich mit ähnlichen Bausteinen
- **F_LREAL_TO_DINT (direkter FB)**: Dieser FB erledigt die reine Konvertierung, benötigt aber eigene Ereignis- und Datenschnittstellen und keine Adapter. `ALR_TO_ADI` kapselt diesen FB, um ihn kompatibel zu Adapter-basierten Verbindungen zu machen.
- **ALR_TO_DINT (hypothetisch)**: Ein direkter Baustein mit eigener Ein-/Ausgangsschnittstelle (Ereignis + Daten) würde keine Adapter verwenden. Der vorliegende FB ist speziell für die Verwendung in einem Adapter-Framework konzipiert.
- **Umgekehrte Konvertierung (ADI_TO_ALR)**: Analog dazu existiert vermutlich ein Baustein für die Gegenrichtung (DINT → LREAL), der ebenfalls auf demselben Konvertierungsprinzip aufbaut.

## Fazit
Der Composite-FB `ALR_TO_ADI` bietet eine elegante Lösung, um zwischen Adapter-Typen mit unterschiedlichen Datentypen zu vermitteln. Durch die Wiederverwendung eines standardisierten Konvertierungsbausteins bleibt die Implementierung schlank und zuverlässig. Der FB eignet sich besonders für modulare, adapterbasierte Systeme, in denen Typkonflikte zwischen Komponenten aufgelöst werden müssen.