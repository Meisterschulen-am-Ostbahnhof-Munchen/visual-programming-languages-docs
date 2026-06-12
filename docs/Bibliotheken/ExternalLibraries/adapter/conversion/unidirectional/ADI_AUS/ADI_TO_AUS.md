# ADI_TO_AUS


![ADI_TO_AUS](./ADI_TO_AUS.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock ADI_TO_AUS dient als Adapter-Konverter von einem DINT-Adapter (ADI) zu einem USINT-Adapter (AUS). Er wandelt einen DINT-Wert in einen USINT-Wert um und ermöglicht die nahtlose Integration von Komponenten mit unterschiedlichen Datentypen in der 4diac-IDE.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **E1** (über ADI_IN): Das Ereignis löst die Konvertierung aus.

### **Ereignis-Ausgänge**
- **E1** (über AUS_OUT): Signalisiert den Abschluss der Konvertierung und die Bereitstellung des Ausgangswerts.

### **Daten-Eingänge**
- **D1** (über ADI_IN): DINT-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **D1** (über AUS_OUT): USINT-Wert, das Ergebnis der Konvertierung.

### **Adapter**
- **ADI_IN**: Socket (Eingang) vom Typ `adapter::types::unidirectional::ADI`. Stellt DINT-Daten und Ereignisse bereit.
- **AUS_OUT**: Plug (Ausgang) vom Typ `adapter::types::unidirectional::AUS`. Empfängt USINT-Daten und Ereignisse zur weiteren Verarbeitung.

## Funktionsweise
Der Baustein ist als Composite FB realisiert. Bei einem Ereignis am Ereigniseingang E1 (über ADI_IN) wird der zugehörige DINT-Wert von Daten-Eingang D1 ausgelesen und dem internen Konvertierungsbaustein `F_DINT_TO_USINT` übergeben. Dieser wandelt den Wert nach IEC 61131-Standard um (z. B. durch Begrenzung auf den USINT-Bereich 0 – 255 oder Typumwandlung). Das Ergebnis wird über den Daten-Ausgang D1 ausgegeben und ein Ereignis am Ausgang E1 (über AUS_OUT) signalisiert die Verfügbarkeit des neuen Werts.

## Technische Besonderheiten
- Der FB verwendet einen IEC 61131-konformen Konvertierungsbaustein für die Typumwandlung von DINT zu USINT.
- Es handelt sich um einen Composite FB (verschachtelter Baustein), der die Logik in einem Netzwerk aus einem einzelnen Convert-FB abbildet.
- Die Kommunikation erfolgt ausschließlich über Adapter-Schnittstellen, was eine modulare Kapselung ermöglicht.
- Bei der Konvertierung können Werte außerhalb des USINT-Bereichs (0 – 255) abgeschnitten oder auf den maximalen bzw. minimalen Wert begrenzt werden (abhängig vom verwendeten Konvertierungsbaustein).

## Zustandsübersicht
Da der Baustein keinen eigenen Zustandsautomaten besitzt, ist sein Verhalten rein ereignisgesteuert: Auf jedes ankommende Ereignis reagiert er mit einer sofortigen Konvertierung und Ausgabe. Es gibt keine internen Zustände oder Verzögerungen.

## Anwendungsszenarien
- Anbindung eines Sensors, der DINT-Werte liefert, an eine Steuerung, die USINT erwartet.
- Integration von Adapter-basierten Komponenten mit unterschiedlichen Datentypen in einer 4diac-Applikation.
- Migration von bestehenden Systemen, bei denen Datenformate angepasst werden müssen.

## Vergleich mit ähnlichen Bausteinen
- Ein direkter Konvertierungsbaustein wie `F_DINT_TO_USINT` führt dieselbe Umwandlung durch, arbeitet jedoch auf Standard-Ein-/Ausgängen. Der ADI_TO_AUS kapselt die Logik in Adapter-Schnittstellen und ist daher speziell für Adapter-basierte Kommunikationswege ausgelegt.
- Der Baustein unterscheidet sich von anderen Adapter-Konvertern durch die spezifische Typkombination DINT↔USINT.

## Fazit
Der ADI_TO_AUS ist ein praktischer Hilfsbaustein für die nahtlose Integration von DINT- und USINT-Adaptern in der 4diac-IDE. Seine einfache, ereignisgesteuerte Funktionsweise und die Kapselung als Composite FB machen ihn flexibel einsetzbar und gut wartbar. Er eignet sich besonders für Projekte, die eine klare Trennung zwischen Adapter-Schnittstellen und Konvertierungslogik erfordern.