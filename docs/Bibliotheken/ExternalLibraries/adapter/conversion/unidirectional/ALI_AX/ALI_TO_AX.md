# ALI_TO_AX


![ALI_TO_AX](./ALI_TO_AX.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **ALI_TO_AX** ist ein zusammengesetzter (Composite) Baustein, der einen Adapter vom Typ **ALI** (enthält einen LINT-Wert) in einen Adapter vom Typ **AX** (enthält einen BOOL-Wert) umwandelt.  
Die Konvertierung erfolgt nach der Regel: Ein LINT-Wert ungleich 0 wird als BOOL-Wert **TRUE** interpretiert, ein Wert gleich 0 als **FALSE**.  
Der Baustein dient als bidirektionale Brücke zwischen Adaptern, die auf unterschiedlichen Datentypen basieren.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **ALI_IN.E1** – Eingangsereignis vom ALI-Adapter. Lösen die Verarbeitung aus.

### **Ereignis-Ausgänge**

- **AX_OUT.E1** – Ausgangsereignis zum AX-Adapter. Wird nach erfolgreicher Verarbeitung gesendet.

### **Daten-Eingänge**

(Keine direkten Daten-Eingänge. Die Daten werden über den ALI-Adapter bereitgestellt:)

- **ALI_IN.D1** – LINT-Eingangswert über den Adapter.

### **Daten-Ausgänge**

(Keine direkten Daten-Ausgänge. Die Daten werden über den AX-Adapter ausgegeben:)

- **AX_OUT.D1** – BOOL-Ausgangswert über den Adapter.

### **Adapter**

| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| **ALI_IN** | Socket (Eingang) | `adapter::types::unidirectional::ALI` | Eingangsadapter mit einem LINT-Wert. |
| **AX_OUT** | Plug (Ausgang) | `adapter::types::unidirectional::AX` | Ausgangsadapter mit einem BOOL-Wert. |

## Funktionsweise

Der Baustein verwendet intern den Vergleichsbaustein **F_NE** („Not Equal“) aus der IEC 61131-Bibliothek. Der Ablauf ist:

1. Über den Socket `ALI_IN` wird ein LINT-Wert empfangen.
2. Das Ereignis `ALI_IN.E1` triggert den Baustein `F_NE` über dessen `REQ`-Eingang.
3. Im `F_NE` wird der Eingangswert (`IN1`) mit dem konstanten Wert `LINT#0` (`IN2`) verglichen.
4. Das Ergebnis `OUT` ist ein BOOL:  
   - **TRUE**, wenn `IN1 ≠ 0`  
   - **FALSE**, wenn `IN1 = 0`
5. Nach Abschluss des Vergleichs sendet `F_NE` ein `CNF`-Ereignis, das den Ausgangsadapter `AX_OUT` über dessen `E1` triggert.
6. Gleichzeitig wird der BOOL-Wert auf `AX_OUT.D1` ausgegeben.

Somit wird ein beliebiger LINT-Wert (auch negative Zahlen) in ein binäres Signal umgesetzt.

## Technische Besonderheiten

- **Reine Logik-Konvertierung**: Es findet keine Skalierung oder Schwellwertbildung statt. Jeder von Null verschiedene Wert wird als `TRUE` interpretiert.
- **Nutzung von Composite-FB**: Der Baustein kapselt die Adapter-Konvertierung in einer wiederverwendbaren Einheit und erlaubt einfaches Einbinden in größere Netzwerke.
- **Ereignisgesteuert**: Die Verarbeitung erfolgt nur bei einem eingehenden Ereignis (`ALI_IN.E1`). Der Ausgang wird nur nach einer erfolgreichen Verarbeitung aktualisiert.
- **Lizenz**: Der Baustein steht unter der **Eclipse Public License 2.0** (EPL-2.0).

## Zustandsübersicht

Da es sich um einen Composite-Baustein ohne eigene Zustandsmaschine handelt, ergibt sich die Zustandslogik aus der internen Verkettung:

1. **Warten auf Ereignis**: Der Baustein ist inaktiv, bis `ALI_IN.E1` eintrifft.
2. **Vergleich läuft**: Nach Empfang des Ereignisses wird der `F_NE`-Baustein ausgeführt.
3. **Ergebnis ausgeben**: Nach Abschluss des Vergleichs wird das Ergebnis auf `AX_OUT.D1` gesetzt und `AX_OUT.E1` ausgelöst.

Es gibt keine Schleifen, zeitlichen Verzögerungen oder Fehlerzustände – die Funktion ist deterministisch und fehlerfrei.

## Anwendungsszenarien

- **Signalkonvertierung in Steuerungssystemen**: Wenn ein LINT-basiertes Protokoll (z. B. Zählerstände, Encoder) in eine einfache binäre Information (z. B. „Aktiv“, „Präsenz“) umgewandelt werden muss.
- **Adapter-Brücken**: Einsatz in Systemen, die heterogene Adaptertypen verwenden, um die Kommunikation zwischen Komponenten mit unterschiedlichen Datentypen zu ermöglichen.
- **Testumgebungen**: Schnelle Umwandlung von numerischen Werten in boolesche Signale für Debugging oder Simulation.

## Vergleich mit ähnlichen Bausteinen

- **Direkter Compare-Baustein**: Statt `F_NE` könnte auch ein `F_EQ` (equal) mit anschließender Negation verwendet werden – funktional identisch.
- **Schwellwert-Bausteine (z. B. Greater_than)**: Würden einen expliziten Schwellwert erfordern; `ALI_TO_AX` entscheidet hart nach Null.
- **Typkonvertierungen (z. B. LINT_TO_BOOL)**: Einige Bibliotheken bieten primitive Konverter – diese arbeiten jedoch meist nicht auf Adapter-Ebene. `ALI_TO_AX` ist speziell für die Adapter‑Schnittstellen zugeschnitten.

## Fazit

Der Baustein **ALI_TO_AX** bietet eine einfache und zuverlässige Methode, um einen LINT-Adapterwert in einen BOOL-Adapterwert zu übersetzen.  
Dank des klaren Logikaufbaus und der ereignisgesteuerten Architektur ist er sowohl für den Produktiveinsatz als auch für schnelle Prototypen geeignet.  
Die Verwendung des Composite-Konzepts fördert die Modularität und Wiederverwendbarkeit in IEC 61499-basierten Steuerungsanwendungen.