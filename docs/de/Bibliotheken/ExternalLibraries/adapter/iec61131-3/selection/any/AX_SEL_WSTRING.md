# AX_SEL_WSTRING




![AX_SEL_WSTRING](./AX_SEL_WSTRING.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AX_SEL_WSTRING` dient der binären Auswahl (Selektion) zwischen zwei Eingängen vom Typ `WSTRING` (Wide String). Die Steuerung, welcher der beiden Eingänge an den Ausgang durchgeschaltet wird, erfolgt über einen gekoppelten Adapter. Dieser Baustein verbindet die klassische Auswahllogik der IEC 61131-3 mit der ereignisgesteuerten Architektur der IEC 61499.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
* **EI0**: Aktualisiert und übernimmt den Wert des Daten-Eingangs `IN0`.
* **EI1**: Aktualisiert und übernimmt den Wert des Daten-Eingangs `IN1`.

### **Ereignis-Ausgänge**
* **CNF**: Bestätigungsereignis (Confirmation). Signalisiert, dass ein neuer ausgewählter Wert am Ausgang `OUT` anliegt.

### **Daten-Eingänge**
* **IN0** (`WSTRING`): Erster auswählbarer String-Eingang (wird selektiert, wenn das Auswahlsignal des Adapters inaktiv bzw. im Standardzustand ist).
* **IN1** (`WSTRING`): Zweiter auswählbarer String-Eingang (wird selektiert, wenn das Auswahlsignal des Adapters aktiv ist).

### **Daten-Ausgänge**
* **OUT** (`WSTRING`): Der aktuell selektierte String-Wert.

### **Adapter**
* **G** (Typ: `adapter::types::unidirectional::AX`): Unidirektionaler Adapter, der als Selektor fungiert. Eine Zustandsänderung an diesem Adapter triggert die Neuberechnung des Ausgangs.

## Funktionsweise
Im Inneren des Funktionsblocks befindet sich ein Netzwerk aus Standard-Auswahlbausteinen (`F_SEL`), Zuweisungsbausteinen (`F_MOVE`) und ereignisgesteuerten D-Flip-Flops (`E_D_FF` und `E_D_FF_ANY`):

1. **Datenhaltung:** Die Eingangsdaten an `IN0` und `IN1` werden bei Eintreffen der jeweiligen Ereignisse `EI0` bzw. `EI1` in internen Speichern zwischengespeichert.
2. **Selektion:** Der Adapter `G` liefert das Auswahlsignal. Sobald sich das Signal am Adapter ändert, wird das Ereignis verarbeitet und der interne Baustein `F_SEL` schaltet den entsprechenden String (`IN0` oder `IN1`) zum Ausgang durch.
3. **Ereignisfilterung:** Das Ausgangsereignis `CNF` wird über ein Wertänderungs-D-Flip-Flop (`E_D_FF_ANY_OUT`) geführt. Dies stellt sicher, dass ein `CNF`-Ereignis primär dann ausgegeben wird, wenn sich das Auswahlsignal `G` ändert oder sich der Wert am Ausgang tatsächlich aktualisiert.

## Technische Besonderheiten
* **Unicode-Unterstützung:** Durch die Verwendung des Datentyps `WSTRING` können im Gegensatz zum Standard-`STRING` auch internationale Zeichensätze und Sonderzeichen problemlos verarbeitet werden.
* **Ressourceneffizienz:** Durch die interne Filterung von Ereignissen werden unnötige Kaskadierungen von Berechnungen im nachfolgenden System minimiert. Ein Ausgangsereignis wird gezielt erzeugt.

## Zustandsübersicht
* **Selektor G = 0 (bzw. inaktiv):** `OUT` entspricht dem Wert von `IN0`.
* **Selektor G = 1 (bzw. aktiv):** `OUT` entspricht dem Wert von `IN1`.
* **Wertänderung an inaktivem Kanal:** Wenn beispielsweise `IN1` aktualisiert wird, während `G` auf `IN0` zeigt, ändert sich der Ausgang `OUT` nicht. Es wird kein `CNF`-Ereignis ausgelöst, bis der Selektor umschaltet.

## Anwendungsszenarien
* **Sprachumschaltung auf HMIs:** Dynamisches Umschalten von Bedien- und Anzeigetexten (z. B. zwischen Deutsch und Englisch) über ein zentrales Steuersignal.
* **Status- und Fehlermeldesysteme:** Auswahl einer spezifischen Textmeldung basierend auf dem Zustand einer Anlage oder eines Sensors.
* **Rezeptursteuerung:** Umschalten von Parametersätzen oder Prozessnamen im Textformat bei Chargenwechseln.

## Vergleich mit ähnlichen Bausteinen
* **Standard `SEL` (IEC 61131-3):** Der klassische `SEL`-Baustein arbeitet rein datenflussorientiert ohne Ereignisschnittstellen. `AX_SEL_WSTRING` erweitert diese Funktionalität für die ereignisbasierte Steuerung in IEC 61499 und nutzt Adapter zur sauberen Strukturierung.
* **`MUX` (Multiplexer):** Während ein Multiplexer die Auswahl aus einer Vielzahl von Kanälen ermöglicht, ist `AX_SEL_WSTRING` auf eine schlanke, binäre Auswahl (Entweder-Oder) spezialisiert.

## Fazit
Der `AX_SEL_WSTRING` ist ein spezialisierter und optimierter Funktionsblock für die ereignisgesteuerte Textauswahl. Durch die Kapselung der internen Speicher- und Selektionslogik vereinfacht er Anwendungsdiagramme in 4diac-ide erheblich und sorgt für ein sauberes Schnittstelldesign mittels Adaptern.