# WSTRING_AIWS_AX_SEL_AIWS


![WSTRING_AIWS_AX_SEL_AIWS](./WSTRING_AIWS_AX_SEL_AIWS.svg)

**********

## Einleitung

Der Funktionsbaustein `WSTRING_AIWS_AX_SEL_AIWS` ist ein zusammengesetzter Funktionsbaustein (Composite Function Block) für IEC 61499-Systeme. Seine Hauptaufgabe ist die binäre Auswahl (Multiplexing) zwischen zwei Zeichenketten-Eingängen (WSTRING). Er ermöglicht es, basierend auf einem logischen Auswahlsignal, entweder eine direkt anliegende Zeichenkette oder ein über einen Adapter empfangenes Signal an einen Ausgangs-Adapter weiterzuleiten.

Dank der Verwendung von Adaptern lässt sich dieser Baustein nahtlos in moderne, serviceorientierte Steuerungsarchitekturen innerhalb der 4diac-IDE integrieren.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung | Gekoppelte Daten |
| :--- | :--- | :--- |
| `EI0` | Triggert die Übernahme und Verarbeitung des Daten-Eingangs `IN0`. | `IN0` |

### **Ereignis-Ausgänge**

*Es gibt keine direkten Ereignis-Ausgänge auf Bausteinebene. Die Ereignisweiterleitung erfolgt gekoppelt über den Ausgangs-Adapter `OUT`.*

### **Daten-Eingänge**

| Datenpunkt | Datentyp | Beschreibung |
| :--- | :--- | :--- |
| `IN0` | `WSTRING` | Direkt anliegender, auswählbarer Zeichenketten-Eingang. |

### **Daten-Ausgänge**

*Es gibt keine direkten Daten-Ausgänge auf Bausteinebene. Die Datenweiterleitung erfolgt über den Ausgangs-Adapter `OUT`.*

### **Adapter**

| Adaptername | Typ | Richtung (Plug/Socket) | Beschreibung |
| :--- | :--- | :--- | :--- |
| `OUT` | `adapter::types::unidirectional::AIWS` | Plug (Stecker) | Der ausgewählte Ausgang (Zeichenkette und Event-Ausgang). |
| `IN1` | `adapter::types::unidirectional::AIWS` | Socket (Buchse) | Der zweite auswählbare Eingang (als Adapter). |
| `G` | `adapter::types::unidirectional::AX` | Socket (Buchse) | Der Selektor-Eingang. Steuert, welches Signal durchgeschaltet wird. |

## Funktionsweise

Das interne Netzwerk des Funktionsbausteins verbindet die Ereignis- und Datenströme der Adapter mit klassischen IEC 61131-Wahl- und Kopierfunktionen (`F_SEL`, `F_MOVE`).

1. **Eingangskanal 0 (`IN0`):** Ein Event an `EI0` puffert den Wert von `IN0` über das Flip-Flop `E_D_FF_ANY_IN0` und schreibt ihn über `F_MOVE_IN0` in das Selektionsglied `F_SEL` (Eingang `IN0`).
2. **Eingangskanal 1 (`IN1`):** Ein eingehendes Event am Adapter `IN1.E1` puffert die Daten `IN1.D1` über das Flip-Flop `E_D_FF_ANY_IN1` und schreibt sie über `F_MOVE_IN1` in das Selektionsglied `F_SEL` (Eingang `IN1`).
3. **Auswahlsignal (`G`):** Ein Event am Selektor-Adapter `G.E1` übernimmt den Zustand von `G.D1` (Boolean) über das Flip-Flop `E_D_FF_G` und legt diesen an den Steuereingang `G` von `F_SEL` an.
4. **Auswahlprozess (`F_SEL`):**
   * Ist das Auswahlsignal `G` **FALSE**, wird der Wert von `IN0` an den Ausgang weitergegeben.
   * Ist das Auswahlsignal `G` **TRUE**, wird der Wert von `IN1` an den Ausgang weitergegeben.
5. **Ausgabe (`OUT`):** Jede Änderung oder Aktivierung an den Eingängen führt zu einer Aktualisierung am Selektionsglied. Das Ergebnis wird mittels `F_MOVE_OUT` kopiert, über `E_D_FF_ANY_OUT` stabilisiert und als Event `OUT.E1` mit den Daten `OUT.D1` am Ausgangs-Adapter bereitgestellt.

```
                  +-------------------------+
                  |  WSTRING_AIWS_AX_SEL_AIWS|
                  |                         |
      [IN0] ----->|---\                     |
   (WSTRING)      |    \   +-----------+    |
                  |     -->|   F_SEL   |    |
   [IN1.D1] ----->|------->|           |    |
    (AIWS)        |        |           |--->|-----> [OUT.D1]
                  |     -->|           |    |       (AIWS)
    [G.D1] ------>|----/   +-----------+    |
     (AX)         |                         |
                  +-------------------------+
```

## Technische Besonderheiten

* **Datentypkonsistenz:** Der Baustein ist intern fest für den Datentyp `WSTRING` (Wide Character String) parametriert. Dies erlaubt auch die Verarbeitung von Unicode-Zeichenketten.
* **Ereignisgesteuertes Latch-Verhalten:** Durch die Verwendung von Event-D-Flip-Flops (`E_D_FF_ANY` und `E_D_FF`) wird sichergestellt, dass die Daten nur dann aktualisiert werden, wenn ein entsprechendes Triggereingangsereignis eintrifft. Dies verhindert unkontrollierte Datenänderungen ("Race Conditions").
* **Unidirektionale Adapter:** Die verwendeten Schnittstellenadapter (`AIWS` und `AX`) arbeiten rein unidirektional, was den Datenfluss übersichtlich und deterministisch hält.

## Zustandsübersicht

Da es sich um einen Composite-Funktionsbaustein (CFB) ohne eine eigene interne Execution Control Chart (ECC) handelt, wird sein Verhalten direkt durch das Zusammenspiel der internen Komponenten bestimmt:

* **Inaktiv / Ruhezustand:** Es liegen keine Events an den Eingängen an. Die Ausgänge halten ihre letzten stabilen Werte.
* **Aktualisierung Eingang 0:** `EI0` triggert -> `IN0` wird neu eingelesen -> `F_SEL` berechnet neu -> Falls `G` = `FALSE`, wird der Ausgang aktualisiert und `OUT.E1` gefeuert.
* **Aktualisierung Eingang 1:** `IN1.E1` triggert -> `IN1.D1` wird neu eingelesen -> `F_SEL` berechnet neu -> Falls `G` = `TRUE`, wird der Ausgang aktualisiert und `OUT.E1` gefeuert.
* **Umschaltung:** `G.E1` triggert -> Selektorzustand ändert sich -> `F_SEL` schaltet den entsprechenden Pfad durch -> Der Ausgang wird mit dem neuen ausgewählten Wert aktualisiert und `OUT.E1` gefeuert.

## Anwendungsszenarien

* **Dynamische Text- und Sprachumschaltung:** Umschalten von Bedienoberflächen-Texten oder Systemmeldungen zwischen einem Standardwert (`IN0`) und einer dynamisch empfangenen Textressource (`IN1`).
* **Fehler- und Statusmeldungs-Auswahl:** Selektion einer spezifischen Statusmeldung bei anstehendem Alarm (gesteuert durch das Auswahlsignal `G`).
* **Signal-Multiplexing in Adapter-Strukturen:** Integration in modularisierte Anlagensteuerungen, bei denen Datenströme mittels Adaptern gebündelt und flexibel geroutet werden sollen.

## Vergleich mit ähnlichen Bausteinen

* **Standard `F_SEL` (IEC 61131-3):** Das klassische `F_SEL` arbeitet rein datengetrieben und besitzt keine integrierte Event-Steuerung oder Adapterkompatibilität. `WSTRING_AIWS_AX_SEL_AIWS` erweitert diese Funktionalität um die in IEC 61499 benötigte Event-Schnittstelle und verpackt die Signale in standardisierte Adapter.
* **Typunspezifische Selektoren:** Im Vergleich zu generischen Selektionsbausteinen ist dieser Baustein durch die feste Verdrahtung von `WSTRING`-Typen und spezifischen Adaptern (`AIWS`, `AX`) typsicher und sofort einsatzbereit, ohne dass Datentyp-Zuordnungen vorgenommen werden müssen.

## Fazit

Der `WSTRING_AIWS_AX_SEL_AIWS`-Funktionsbaustein bietet eine robuste und gebrauchsfertige Lösung zur signal- und eventgesteuerten Auswahl von Weitzeichen-Strings. Durch die Kapselung komplexer Flip-Flop- und Konvertierungslogiken vereinfacht er das Design von übersichtlichen und wartbaren Steuerungsanwendungen in der 4diac-IDE.