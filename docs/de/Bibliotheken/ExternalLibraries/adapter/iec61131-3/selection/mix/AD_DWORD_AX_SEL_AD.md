# AD_DWORD_AX_SEL_AD

```text
                     +-----------------------------+
                     |     AD_DWORD_AX_SEL_AD      |
                     |                             |
         [AX] G ====>| S                         P |====> OUT [AD]
       [AD] IN0 ====>| S                           |
                     |                             |
     (Event) EI1 --->| EI1                         |
    (DWORD) IN1 ---->| IN1                         |
                     +-----------------------------+

![AD_DWORD_AX_SEL_AD](./AD_DWORD_AX_SEL_AD.svg)

                    * S = Socket / P = Plug
```

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AD_DWORD_AX_SEL_AD` ist ein zusammengesetzter Funktionsbaustein (Composite Function Block) für IEC 61499-Systeme. Er dient der binären Auswahl (Selektion) von `DWORD`-Werten. Der Baustein ermöglicht es, ereignisgesteuert zwischen einem über einen Adapter eingespeisten Wert (`IN0`) und einem direkt am Block anliegenden Datenwert (`IN1`) umzuschalten. Das Auswahlsignal sowie der ausgewählte Ausgangswert werden ebenfalls über standardisierte Adapter übertragen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*   **EI1**: Löst die Aktualisierung und Übernahme des direkt anliegenden Daten-Eingangs `IN1` aus.

### **Ereignis-Ausgänge**

*   *Keine direkten Ereignis-Ausgänge.* (Die Ereignisausgabe erfolgt gekapselt über den Adapter-Plug `OUT`).

### **Daten-Eingänge**

*   **IN1** (DWORD): Direkt anliegende, wählbare Eingangsvariable.

### **Daten-Ausgänge**

*   *Keine direkten Daten-Ausgänge.* (Die Datenausgabe erfolgt gekapselt über den Adapter-Plug `OUT`).

### **Adapter**

*   **OUT** (Plug, Typ: `adapter::types::unidirectional::AD`): Gibt den ausgewählten `DWORD`-Wert (`D1`) und das dazugehörige Aktualisierungsereignis (`E1`) aus.
*   **IN0** (Socket, Typ: `adapter::types::unidirectional::AD`): Erster wählbarer Eingangswert (DWORD), der über einen unidirektionalen Adapter geliefert wird.
*   **G** (Socket, Typ: `adapter::types::unidirectional::AX`): Selektor-Eingang. Steuert über ein boolesches Signal, welcher der beiden Eingänge (`IN0` oder `IN1`) auf den Ausgang `OUT` geschaltet wird.

---

## Funktionsweise

Der Baustein arbeitet intern mit einer Kombination aus Flip-Flops (`E_D_FF_ANY` und `E_D_FF`) zur Zustandsspeicherung und dem standardmäßigen Selektionsbaustein `F_SEL`.

1.  **Wertspeicherung**: Sobald ein Ereignis an `IN0.E1`, `G.E1` oder dem direkten Eingang `EI1` eintrifft, speichern die internen Flip-Flops die aktuellen Datenwerte von `IN0.D1`, `G.D1` bzw. `IN1` ab.
2.  **Umschaltung (Selektion)**:
    *   Ist das Selektionssignal des Adapters `G` (Wert `G.D1`) **`FALSE`**, wird der Wert von **`IN0`** (über den internen Baustein `F_MOVE_IN0`) an den Selektor weitergegeben.
    *   Ist das Selektionssignal des Adapters `G` (Wert `G.D1`) **`TRUE`**, wird der Wert von **`IN1`** (über den internen Baustein `F_MOVE_IN1`) ausgewählt.
3.  **Ausgabe**: Der ausgewählte Wert wird an den Ausgangsadapter `OUT` übergeben, und das Ereignis `OUT.E1` signalisiert die erfolgreiche Aktualisierung des Ausgangs.

---

## Technische Besonderheiten

*   **Asynchrone Verarbeitung**: Durch die internen Daten-Flip-Flops werden Signalzustände so lange zwischengespeichert, bis eine logische Auswertung stattfindet. Dadurch ist eine zuverlässige Verarbeitung auch bei zeitlich versetzten Ereignissen gewährleistet.
*   **Hybrid-Schnittstelle**: Der Baustein verbindet die klassische event-/datenbasierte IEC 61499-Modellierung (Eingang `IN1` / `EI1`) mit der moderneren, adapterbasierten Modellierung (`IN0`, `G`, `OUT`). Dies erleichtert die Integration in bestehende, gemischte Architekturen.

---

## Zustandsübersicht

Die folgende Tabelle zeigt das Verhalten des Ausgangs in Abhängigkeit vom Selektionssignal `G`:

| Zustand des Selektors (`G.D1`) | Ausgewählter Eingang | Ausgangswert (`OUT.D1`) | Triggerndes Ereignis |
| :--- | :--- | :--- | :--- |
| `FALSE` | `IN0` | Wert von `IN0.D1` | `IN0.E1` oder `G.E1` |
| `TRUE` | `IN1` | Wert von `IN1` | `EI1` oder `G.E1` |

---

## Anwendungsszenarien

*   **Hand-/Automatik-Umschaltung**: Auswahl zwischen einem manuell vorgegebenen DWORD-Wert (z.B. über ein HMI an `IN1`) und einem automatischen Wert aus der Prozesssteuerung (über Adapter `IN0`).
*   **Rezeptur- und Parametersteuerung**: Dynamisches Umschalten von Konfigurations- oder Schwellwerten im DWORD-Format während des laufenden Betriebs.
*   **Modulare Signalroutung**: Reduzierung des Verdrahtungsaufwands in komplexen Steuerungsanwendungen durch die Kapselung von Daten- und Eventleitungen in Adaptern.

---

## Vergleich mit ähnlichen Bausteinen

*   **`F_SEL` (IEC 61131-3)**: Der Standard-Selektionsbaustein besitzt keine Ereignissteuerung und keine Adapter-Unterstützung. `AD_DWORD_AX_SEL_AD` erweitert diese Grundfunktionalität um Event-Handling und Kapselung durch Adapter.
*   **Standard-Multiplexer**: Erfordern oft eine Vielzahl einzelner Event- und Datenleitungen für jeden Kanal. Dieser Baustein reduziert das "Spaghetti-Design" im 4diac-Applikationsfenster durch die Verwendung von standardisierten Adapterschnittstellen.

---

## Fazit

Der `AD_DWORD_AX_SEL_AD` ist ein robuster und flexibler Hilfsbaustein für die strukturierte Signalverarbeitung. Er eignet sich hervorragend für Applikationen, bei denen Übersichtlichkeit und die konsequente Nutzung von Adaptern zur Reduzierung der Verbindungskomplexität im Vordergrund stehen.