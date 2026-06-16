# ALI_TO_ADI


![ALI_TO_ADI](./ALI_TO_ADI.svg)

* * * * * * * * * *
## Einleitung
Dieser Composite-Funktionsblock dient der Umwandlung eines **ALI**-Adaptertyps (LINT, 64‑Bit‑Integer) in einen **ADI**-Adaptertyp (DINT, 32‑Bit‑Integer). Er ermöglicht die nahtlose Integration von Komponenten, die unterschiedliche Adapter-Formate verwenden, indem er die Datenkonvertierung kapselt und über Ereignissteuerung synchronisiert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine direkten Ereignis-Eingänge vorhanden. Die Steuerung erfolgt über den eingehenden Adapter **ALI_IN**.

### **Ereignis-Ausgänge**
Keine direkten Ereignis-Ausgänge vorhanden. Die Ausgabe wird über den ausgehenden Adapter **ADI_OUT** getaktet.

### **Daten-Eingänge**
Keine direkten Daten-Eingänge vorhanden. Die Eingangsdaten werden über den Adapter **ALI_IN** (vom Typ ALI) bereitgestellt.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge vorhanden. Die umgewandelten Daten werden über den Adapter **ADI_OUT** (vom Typ ADI) ausgegeben.

### **Adapter**

| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| **ALI_IN** | `adapter::types::unidirectional::ALI` | Socket (Eingang) | Liefert den LINT-Wert sowie ein zugehöriges Ereignis (E1). |
| **ADI_OUT** | `adapter::types::unidirectional::ADI` | Plug (Ausgang) | Gibt den konvertierten DINT-Wert sowie ein Bestätigungsereignis (E1) aus. |

## Funktionsweise
Der Baustein enthält im Inneren die Instanz `Convert` vom Typ `iec61131::conversion::F_LINT_TO_DINT`.  
Die Ereignis- und Datenverbindungen sind wie folgt geschaltet:

- Das Ereignis `ALI_IN.E1` triggert die Umwandlung über `Convert.REQ`.
- Der Datenwert `ALI_IN.D1` wird an `Convert.IN` übergeben.
- Nach erfolgreicher Konvertierung signalisiert `Convert.CNF` das Ereignis `ADI_OUT.E1`.
- Der Ergebniswert `Convert.OUT` wird an `ADI_OUT.D1` weitergeleitet.

Somit wird bei jedem Ereignis am Eingangsadapter der LINT-Wert in einen DINT-Wert umgerechnet und synchron über den Ausgangsadapter bereitgestellt.

## Technische Besonderheiten
- **Composite-Baustein**: Der FB kapselt die Konvertierung in einem wiederverwendbaren Adapter-zu-Adapter-Wandler.
- **Datentypumwandlung**: Es findet eine 64‑Bit‑ zu 32‑Bit‑Integer‑Konvertierung statt. Bei Werten außerhalb des DINT-Bereichs (−2³¹ … 2³¹−1) kommt es zu einem Überlauf oder einer Begrenzung (implementierungsabhängig).
- **Ereignissynchronisation**: Die Umwandlung erfolgt streng getaktet durch die Ereigniskette; ein neuer Wert wird nur nach einem vorherigen Ereignis verarbeitet.

## Zustandsübersicht
Der Baustein besitzt keine eigene Zustandsmaschine (ECC). Seine gesamte Logik wird durch den internen Funktionsblock `F_LINT_TO_DINT` realisiert, der als einfacher Umwandlungsbaustein ohne Zustandsverhalten arbeitet.

## Anwendungsszenarien
- Anbindung einer Komponente, die einen 64‑Bit‑Zähler oder Zeitstempel (LINT) liefert, an ein System, das nur 32‑Bit‑DINT‑Adapter unterstützt.
- Migration von Altsystemen mit 32‑Bit‑Arithmetik auf neuere 64‑Bit‑Sensoren, ohne die gesamte Adapterlandschaft zu ändern.
- Zwischenschicht in einer Hierarchie, in der unterschiedliche Integer-Breiten aufeinandertreffen.

## Vergleich mit ähnlichen Bausteinen
Es existieren separate Konvertierungsbausteine wie `F_LINT_TO_DINT` für direkte Datenumwandlungen. Der `ALI_TO_ADI`-Baustein hebt sich dadurch ab, dass er die Konvertierung vollständig in die Adapter-Schnittstelle integriert. Statt mehrerer diskreter Funktionsblöcke und manueller Adapterverkabelung wird die gesamte Logik in einem wiederverwendbaren Composite-Baustein zusammengefasst, der die Ereignis- und Datenströme automatisch behandelt.

## Fazit
Der `ALI_TO_ADI`-Funktionsblock bietet eine saubere, gekapselte Lösung für die Umwandlung von LINT- in DINT‑Adapter. Durch die Verwendung eines Composite-Bausteins reduziert er die Komplexität in der Applikation und sorgt für eine standardisierte, ereignisgesteuerte Konvertierung zwischen unterschiedlichen Integer-Breiten in der IEC 61499‑Umgebung.