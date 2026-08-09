# AW_WORD_AX_SEL_AW


![AW_WORD_AX_SEL_AW](./AW_WORD_AX_SEL_AW.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AW_WORD_AX_SEL_AW` ist ein zusammengesetzter Funktionsbaustein (Composite Function Block) für die IEC 61499, der eine binäre Auswahl (Selektion) zwischen zwei Datenquellen des Typs `WORD` realisiert. Die Auswahl erfolgt ereignisgesteuert über einen Selektor. Der Baustein nutzt eine Mischung aus klassischen Schnittstellen (Ereignis-/Dateneingänge) und modernen, unidirektionalen Adaptern zur flexiblen und modularen Signalverarbeitung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*   **EI1**: Löst die Übernahme und Verarbeitung des direkt anliegenden Datenwerts `IN1` aus.

### **Ereignis-Ausgänge**

*   *Keine direkten Ereignis-Ausgänge.* Die Ereignisausgabe erfolgt gekapselt über den Ausgangs-Adapter `OUT`.

### **Daten-Eingänge**

*   **IN1** (WORD): Auswählbare Eingangsvariable, die direkt am Baustein anliegt.

### **Daten-Ausgänge**

*   *Keine direkten Daten-Ausgänge.* Die Datenübergabe erfolgt gekapselt über den Ausgangs-Adapter `OUT`.

### **Adapter**

*   **OUT** (Plug, Typ: `adapter::types::unidirectional::AW`): Der Ausgangs-Adapter, der das ausgewählte `WORD`-Signal sowie das zugehörige Aktualisierungsereignis ausgibt.
*   **IN0** (Socket, Typ: `adapter::types::unidirectional::AW`): Der erste auswählbare Eingang, der als Adapter gekoppelt ist.
*   **G** (Socket, Typ: `adapter::types::unidirectional::AX`): Der Selektor-Eingang (Adapter), welcher steuert, welcher der beiden Eingänge (`IN0` oder `IN1`) auf den Ausgang geschaltet wird.

## Funktionsweise

Intern basiert der Funktionsbaustein auf einem Netzwerk aus standardisierten Hilfsbausteinen (wie Flip-Flops und Selektoren):

1.  **Ereignis- und Datenspeicherung**:
    *   Trifft ein Ereignis am Adapter `G` (Selektor) oder `IN0` (Eingang 0) bzw. am direkten Ereigniseingang `EI1` ein, puffern die internen D-Flip-Flops (`E_D_FF` bzw. `E_D_FF_ANY`) den aktuellen Zustand des jeweiligen Datenkanals.
2.  **Wertübertragung**:
    *   Die gepufferten Werte von `IN0` und `IN1` werden über Konvertierungsbausteine (`F_MOVE`) an den eigentlichen Auswahlkern (`F_SEL`) übergeben.
3.  **Auswahllogik (F_SEL)**:
    *   Der Baustein `F_SEL` wertet den Zustand des Selektors `G` aus:
        *   Ist `G` **FALSE** (0), wird der Wert von `IN0` selektiert.
        *   Ist `G` **TRUE** (1), wird der Wert von `IN1` selektiert.
4.  **Ausgabe**:
    *   Das Ergebnis der Auswahl wird über ein weiteres Flip-Flop (`E_D_FF_ANY_OUT`) an den Ausgangs-Adapter `OUT` übergeben, wodurch gleichzeitig der Datenwert (`D1`) aktualisiert und das Ausgangsereignis (`E1`) getriggert wird.

## Technische Besonderheiten

*   **Hybrid-Architektur**: Die Kombination aus klassischer Daten-/Ereignis-Schnittstelle (`IN1`/`EI1`) und Adapter-Schnittstellen (`IN0`, `G`, `OUT`) ermöglicht eine hohe Flexibilität bei der Integration in bestehende Systeme.
*   **Asynchroner Schutz**: Durch die Verwendung von internen D-Flip-Flops wird sichergestellt, dass Datenänderungen nur bei tatsächlichen Ereignissen übernommen werden. Dies verhindert Dateninkonsistenzen (Race Conditions).
*   **Kapselung**: Durch die Verwendung unidirektionaler Adapter wird die Anzahl der sichtbaren Verbindungslinien im übergeordneten System- oder Applikationsdiagramm drastisch reduziert.

## Zustandsübersicht

| Zustand Selektor (`G.D1`) | Ausgewählter Eingang | Signal am Ausgang (`OUT.D1`) |
| :--- | :--- | :--- |
| **FALSE** | `IN0` (über Adapter) | Wert von `IN0.D1` |
| **TRUE** | `IN1` (direkter Eingang) | Wert von `IN1` |

## Anwendungsszenarien

*   **Umschaltung zwischen Automatik- und Handbetrieb**: `IN0` liefert den automatischen Sollwert über ein Bussystem (Adapter), während `IN1` einen manuellen Vorgabewert aus einer lokalen Visualisierung darstellt. Der Selektor `G` schaltet zwischen den Betriebsmodi um.
*   **Signal-Routing**: Dynamische Weiterleitung von Sensordaten (im `WORD`-Format) in modular aufgebauten verfahrenstechnischen Anlagen.
*   **Redundante Messwertauswahl**: Schnelles Umschalten auf einen Ersatzwert (`IN1`), falls der Hauptsensor (`IN0`) eine Störung meldet.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zum Standard-Funktionsbaustein `F_SEL` aus der IEC 61131-3 Bibliothek bietet der `AW_WORD_AX_SEL_AW` eine direkte Integration in die ereignisgesteuerte Welt von IEC 61499. Während der klassische `F_SEL` zyklisch aufgerufen werden muss und keine eigene Ereignisbehandlung besitzt, arbeitet dieser Baustein rein ereignisbasiert und minimiert so die Prozessorlast. Zudem spart die Adapterstruktur im Vergleich zu herkömmlichen 4diac-Selektoren erheblichen Verdrahtungsaufwand.

## Fazit

Der `AW_WORD_AX_SEL_AW` ist ein spezialisierter und optimierter Baustein für die moderne, ereignisgesteuerte Steuerungssoftware. Durch die clevere Kombination von Adaptern und Standard-Auswahllogik eignet er sich hervorragend für saubere, modulare und effiziente Applikationsdesigns in der 4diac IDE.