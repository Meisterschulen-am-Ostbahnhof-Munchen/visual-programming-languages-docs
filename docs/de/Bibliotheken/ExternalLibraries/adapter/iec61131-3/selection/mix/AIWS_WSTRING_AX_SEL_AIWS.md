# AIWS_WSTRING_AX_SEL_AIWS


![AIWS_WSTRING_AX_SEL_AIWS](./AIWS_WSTRING_AX_SEL_AIWS.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AIWS_WSTRING_AX_SEL_AIWS` ist ein zusammengesetzter Funktionsbaustein (Composite Function Block) für die 4diac-IDE. Er dient der binären Auswahl (Selektion) zwischen zwei `WSTRING`-Eingangssignalen auf Basis eines Selektions-Signals (`G`). 

Dieser Baustein verbindet klassische IEC 61499 Ereignisse und Datenvariablen mit modernen, unidirektionalen Adaptern. Er ermöglicht eine saubere, ereignisgesteuerte Signalumschaltung direkt im Steuerungsnetzwerk.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*   **EI1**: Aktualisiert und übernimmt den Wert am Dateneingang `IN1`.

### **Ereignis-Ausgänge**

*   *Keine direkten Ereignis-Ausgänge vorhanden. Die Ereignisausgabe erfolgt gekapselt über den Ausgangsadapter `OUT`.*

### **Daten-Eingänge**

*   **IN1** (`WSTRING`): Frei wählbarer Dateneingang, der bei einem Ereignis an `EI1` eingelesen wird.

### **Daten-Ausgänge**

*   *Keine direkten Daten-Ausgänge vorhanden. Die Datenweitergabe erfolgt gekapselt über den Ausgangsadapter `OUT`.*

### **Adapter**

*   **OUT** (Plug, Typ: `adapter::types::unidirectional::AIWS`): Der ausgewählte Ausgang als unidirektionaler Adapter. Über diesen werden der selektierte `WSTRING`-Wert (`D1`) und das dazugehörige Aktualisierungsereignis (`E1`) ausgegeben.
*   **IN0** (Socket, Typ: `adapter::types::unidirectional::AIWS`): Der standardmäßig ausgewählte Eingang (unidirektionaler Adapter), der den alternativen `WSTRING`-Wert bereitstellt.
*   **G** (Socket, Typ: `adapter::types::unidirectional::AX`): Der Selektor-Eingang (unidirektionaler Adapter), der bestimmt, welcher der beiden Eingänge durchgeschaltet wird.

---

## Funktionsweise

Das interne Netzwerk (`FBNetwork`) des Bausteins regelt die Synchronisation und die logische Auswahl der Signale:

1.  **Pufferung & Synchronisation:**
    Die Eingangswerte von `IN0` (über den Adapter), `IN1` (über den lokalen Dateneingang) und der Selektor `G` werden bei Eintreffen eines entsprechenden Ereignisses in internen Speicherbausteinen (`E_D_FF_ANY` bzw. `E_D_FF`) zwischengespeichert. Dies stellt sicher, dass Daten und Ereignisse synchron verarbeitet werden.
2.  **Wertübernahme:**
    Die gepufferten Daten werden über Konvertierungs- und Zuweisungsglieder (`F_MOVE_IN0` und `F_MOVE_IN1`) an den zentralen Auswahlbaustein übergeben.
3.  **Auswahl-Logik (`F_SEL`):**
    Ein Standard-Auswahlbaustein (`iec61131::selection::F_SEL`) führt die Selektion durch:
    *   Ist der Zustand des Selektors `G` gleich `FALSE`, wird der Wert von **IN0** an den Ausgang weitergegeben.
    *   Ist der Zustand des Selektors `G` gleich `TRUE`, wird der Wert von **IN1** ausgewählt.
4.  **Ausgabe:**
    Der ausgewählte `WSTRING`-Wert wird über einen Ausgangspuffer (`E_D_FF_ANY_OUT`) an den Ausgangsadapter `OUT` übergeben. Gleichzeitig wird das Ausgangsereignis `OUT.E1` getriggert, um nachfolgende Programmteile über die Änderung zu informieren.

```
       +-------------+
IN0 -->|             |
       |    F_SEL    |--> OUT (Wenn G = FALSE -> IN0)
IN1 -->|             |--> OUT (Wenn G = TRUE  -> IN1)
       +-------------+
              ^
              |
        G (Selector)
```

---

## Technische Besonderheiten

*   **Mischbetrieb:** Der Baustein kombiniert geschickt klassische IEC 61499 Daten- und Ereigniselemente (für `IN1` / `EI1`) mit modernen Adapterstrukturen (`IN0`, `G`, `OUT`).
*   **Datenkonsistenz:** Durch den Einsatz von internen D-Flipflops (`E_D_FF_ANY`) wird sichergestellt, dass nur konsistente und stabile Datenzustände an den Ausgang weitergeleitet werden und keine "Race Conditions" entstehen.

## Zustandsübersicht

Da es sich um einen zusammengesetzten Funktionsbaustein (Composite FB) handelt, besitzt dieser keine eigene Execution Control Chart (ECC). Das Verhalten ist rein daten- und ereignisgesteuert und hängt von den Zuständen der internen Signal-Verbindungen ab.

## Anwendungsszenarien

*   **Dynamische Textumschaltung:** Umschalten von Statusmeldungen, Rezeptnamen oder Fehlermeldungen im `WSTRING`-Format auf einem HMI oder Display.
*   **Default-Wert-Übersteuerung:** Bereitstellung eines Standardpfades oder Standardwerts über den Adapter `IN0`, welcher bei Bedarf (z. B. im Einrichtbetrieb oder bei Benutzerinteraktion) durch das Signal an `IN1` überschrieben werden kann.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zum elementaren Standard-Auswahlbaustein `F_SEL` aus der IEC 61131-3 Bibliothek bietet der `AIWS_WSTRING_AX_SEL_AIWS` eine direkte Integration in adapterbasierte Architekturen. Entwickler müssen Ereignisse und Daten nicht manuell über Hilfsbausteine entkoppeln oder zusammenführen, da dieser Baustein die Kapselung und Synchronisation intern und vollautomatisch übernimmt.

## Fazit

Der `AIWS_WSTRING_AX_SEL_AIWS` ist ein robuster und sofort einsatzbereiter Hilfsbaustein für die strukturierte Applikationsentwicklung in 4diac. Er eignet sich hervorragend für modulare Architekturen, in denen Zeichenketten flexibel und ereignisgesteuert umgeschaltet werden müssen.