# BYTE_AQ_AX_SEL_AQ


![BYTE_AQ_AX_SEL_AQ](./BYTE_AQ_AX_SEL_AQ.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein `BYTE_AQ_AX_SEL_AQ` ist ein zusammengesetzter Funktionsbaustein (Composite Function Block - CFB) für die ereignisgesteuerte, binäre Auswahl (Multiplexing) von Daten des Typs `BYTE`. Der Baustein kombiniert die klassische Auswahllogik (äquivalent zu `SEL` aus der IEC 61131-3) mit den Vorteilen der ereignisorientierten Ausführung der IEC 61499.

Er ermöglicht es, flexibel zwischen einem direkt angebundenen Byte-Eingang und einem über einen Adapter eingespeisten Byte-Eingang zu wählen. Das Auswahlsignal sowie das Ausgangssignal werden ebenfalls über standardisierte Adapter übertragen, was eine hochmodulare und übersichtliche Strukturierung im Steuerungsnetzwerk erlaubt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **EI0**: Triggert das Einlesen und Übernehmen des direkt angebundenen Daten-Eingangs `IN0`.

### **Ereignis-Ausgänge**
*   *Keine direkten Ereignis-Ausgänge.* (Die Ereignisausgabe erfolgt gekoppelt über den Ausgangs-Adapter `OUT`).

### **Daten-Eingänge**
*   **IN0** (BYTE): Direkt angebundener Daten-Eingang, dessen Wert bei einem Ereignis an `EI0` erfasst wird.

### **Daten-Ausgänge**
*   *Keine direkten Daten-Ausgänge.* (Die Datenbeschreibung erfolgt gekoppelt über den Ausgangs-Adapter `OUT`).

### **Adapter**
*   **OUT** (Plug / Stecker, Typ: `adapter::types::unidirectional::AQ`): Der ausgewählte Ausgang des Bausteins. Gibt das selektierte Byte-Signal zusammen mit dem zugehörigen Aktualisierungsereignis aus.
*   **IN1** (Socket / Buchse, Typ: `adapter::types::unidirectional::AQ`): Adapter-basierter Daten-Eingang für das zweite auswählbare Byte-Signal inklusive dessen Aktualisierungsereignis.
*   **G** (Socket / Buchse, Typ: `adapter::types::unidirectional::AX`): Adapter-basierter Selektor-Eingang (Boolean). Bestimmt, welcher der beiden Eingänge auf den Ausgang durchgeschaltet wird.

---

## Funktionsweise
Im internen Netzwerk des Bausteins werden die eingehenden Daten und Ereignisse synchronisiert und verarbeitet:

1.  **Datenerfassung und Pufferung:**
    *   Der Wert von `IN0` wird bei Auftreten des Ereignisses `EI0` im internen Flip-Flop `E_D_FF_ANY_IN0` zwischengespeichert.
    *   Der Wert des Adapters `IN1` (Daten `D1`) wird bei Auftreten des Adapter-Ereignisses `IN1.E1` im Flip-Flop `E_D_FF_ANY_IN1` zwischengespeichert.
    *   Das Auswahlsignal des Adapters `G` (Daten `D1`) wird bei Auftreten des Adapter-Ereignisses `G.E1` im Flip-Flop `E_D_FF` zwischengespeichert.

2.  **Auswahllogik (Selection):**
    *   Sobald sich einer der Eingänge oder der Selektor ändert, wird über die internen Move-Bausteine (`F_MOVE_IN0`, `F_MOVE_IN1`) der Auswahlbaustein `F_SEL` aufgerufen.
    *   Der Baustein `F_SEL` arbeitet nach folgendem Prinzip:
        *   Ist das Selektionssignal **`G` = FALSE**, wird der Wert von **`IN0`** an den Ausgang weitergegeben.
        *   Ist das Selektionssignal **`G` = TRUE**, wird der Wert von **`IN1`** an den Ausgang weitergegeben.

3.  **Ausgangssteuerung:**
    *   Das Ergebnis der Auswahl wird über `F_MOVE_OUT` an das Ausgangs-Flip-Flop `E_D_FF_ANY_OUT` übergeben.
    *   Dies triggert das Ereignis `OUT.E1` des Ausgangs-Adapters und aktualisiert gleichzeitig den Datenwert `OUT.D1`.

```
                  +-----------------------------------+
                  |        BYTE_AQ_AX_SEL_AQ          |
                  |                                   |
   [EI0] -------->| EI0                               |
   (BYTE) IN0 --->| IN0                               |
                  |                                   |
 [AQ-Socket] ---->| IN1                           OUT |======> [AQ-Plug]
                  |                                   |       (Selected Output)
 [AX-Socket] ---->| G                                 |
                  +-----------------------------------+
```

---

## Technische Besonderheiten
*   **Sichere Datenkonsistenz:** Durch den Einsatz von flankengetriggerten D-Flip-Flops (`E_D_FF` und `E_D_FF_ANY`) im internen Netzwerk wird sichergestellt, dass Datenwerte nur bei Vorliegen des entsprechenden Ereignisses übernommen werden. Dies verhindert "Race Conditions" (Wettlaufeffekte) zwischen asynchronen Eingangssignalen.
*   **Mischbetrieb:** Der Baustein ermöglicht eine elegante Brücke zwischen klassischer, pin-basierter Verdrahtung (`IN0`/`EI0`) und moderner, adapter-basierter Signalübertragung.

---

## Zustandsübersicht
Da es sich um einen zusammengesetzten Funktionsbaustein (Composite FB) ohne eigene Execution Control Chart (ECC) handelt, wird das Verhalten vollständig durch das Zusammenspiel der internen Bausteine bestimmt:

*   **Bereitschaft (Idle):** Baustein wartet auf Ereignisse an `EI0`, `IN1.E1` oder `G.E1`.
*   **Datenaktualisierung:** Bei Eintreffen eines Ereignisses wird der jeweilige Pfad aktualisiert, die Selektion neu berechnet und unmittelbar am Adapter `OUT` bereitgestellt.

---

## Anwendungsszenarien
*   **Umschaltung zwischen Sollwerten:** Ein System benötigt standardmäßig einen fest definierten Parameter (übergeben an `IN0` als statischer Wert). Unter bestimmten Betriebsbedingungen soll jedoch auf einen dynamisch berechneten Sollwert von einem anderen Softwaremodul (übergeben via Adapter `IN1`) umgeschaltet werden.
*   **Betriebsartenwahl:** Auswahl von Byte-basierten Steuerwörtern oder Zustands-IDs in Abhängigkeit einer übergeordneten Automatik-/Hand-Umschaltung (gesteuert durch den Selektor-Adapter `G`).
*   **Modulare Signalbündelung:** Reduzierung des Verdrahtungsaufwands in komplexen 4diac-Anwendungen durch die Nutzung von unidirektionalen Adaptern zur Signalweiterleitung.

---

## Vergleich mit ähnlichen Bausteinen
*   **Standard-Auswahlbaustein `F_SEL`:** Der klassische `F_SEL` besitzt keine integrierte Ereignissteuerung und keine Adapter-Schnittstellen. Er reagiert rein datenflussorientiert. `BYTE_AQ_AX_SEL_AQ` erweitert diese Funktionalität um ereignisgesteuerte Speicherung und die direkte Kopplung an Adapter-Kanäle.
*   **Einfache Selektoren ohne Adapter:** Erfordern das manuelle Herausführen und Verschalten aller Ereignisleitungen. Dieser Baustein kapselt diese Logik und sorgt für ein aufgeräumtes Anwendungsdiagramm in der 4diac IDE.

---

## Fazit
Der `BYTE_AQ_AX_SEL_AQ` ist ein äußerst nützlicher Hilfsbaustein für modulare Steuerungsarchitekturen. Er verbindet die Robustheit der ereignisbasierten Verarbeitung mit der Flexibilität von Adaptern und eignet sich hervorragend für Umschalt- und Multiplexing-Aufgaben von Byte-Daten in verteilten Systemen.