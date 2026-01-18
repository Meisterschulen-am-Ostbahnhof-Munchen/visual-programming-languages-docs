# E_DEMUX

```{index} single: E_DEMUX
```

<img width="1139" height="202" alt="E_DEMUX" src="https://user-images.githubusercontent.com/113907528/204897696-f71c191f-099b-40f9-b861-6e94bb89c3ff.png">

* * * * * * * * * *

## Einleitung
Der `E_DEMUX` (Event Demultiplexer) ist ein Funktionsbaustein nach IEC 61499, der ein einzelnes Eingangereignis (`EI`) an einen von mehreren Ausgängen weiterleitet. Die Auswahl des spezifischen Ausgangs wird durch den Wert einer Eingangsvariable (`K`) bestimmt. Diese Version des Bausteins ist ein 1-zu-4 Demultiplexer.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **EI (Event Input)**: Das Eingangereignis, das verteilt werden soll.
    - **Verbundene Daten**: `K`

### **Ereignis-Ausgänge**
- **EO0**: Wird ausgelöst, wenn `EI` ankommt und `K = 0`.
- **EO1**: Wird ausgelöst, wenn `EI` ankommt und `K = 1`.
- **EO2**: Wird ausgelöst, wenn `EI` ankommt und `K = 2`.
- **EO3**: Wird ausgelöst, wenn `EI` ankommt und `K = 3`.

### **Daten-Eingänge**
- **K**: Der Auswahlindex, der bestimmt, welcher Ausgang ausgelöst wird (Datentyp: `UINT`).

## Funktionsweise
1.  **Ereignisempfang**: Der Baustein wartet auf ein Ereignis am Eingang `EI`.
2.  **Auswahl**: Wenn das `EI`-Ereignis eintrifft, wird der Wert der Datenvariable `K` ausgewertet.
3.  **Weiterleitung**:
    - Ist `K` = 0, wird das Ereignis an `EO0` weitergeleitet.
    - Ist `K` = 1, wird das Ereignis an `EO1` weitergeleitet.
    - Ist `K` = 2, wird das Ereignis an `EO2` weitergeleitet.
    - Ist `K` = 3, wird das Ereignis an `EO3` weitergeleitet.
4.  **Ungültiger Index**: Wenn der Wert von `K` außerhalb des gültigen Bereichs [0, 3] liegt, wird kein Ausgangsereignis ausgelöst, und das `EI`-Ereignis wird verworfen.

Das Eingangsereignis wird somit immer exklusiv an genau einen Ausgang weitergeleitet, sofern der Index `K` gültig ist.

## Technische Besonderheiten
- **1-zu-4 Verteilung**: Dieser Baustein verteilt ein Ereignis auf vier mögliche Ausgänge.
- **Index-gesteuert**: Die Logik basiert auf einem numerischen Index.
- **Deterministisches Verhalten**: Die Weiterleitung ist klar und eindeutig definiert, was für zuverlässige Steuerungen sorgt.

## Anwendungsszenarien
- **Zustandsmaschinen**: Auswahl des nächsten Zustandsübergangs basierend auf einem berechneten Index.
- **Modus-Umschaltung**: Aktivierung unterschiedlicher Anlagenteile je nach gewähltem Betriebsmodus (`K` = Modus-Nummer).
- **Sequenzer/Schrittketten**: Aktivierung des nächsten Schritts in einer Kette.
- **Fehler-Routing**: Weiterleiten eines allgemeinen Fehlerereignisses an einen spezifischen Handler basierend auf einem Fehlercode (`K` = Fehlercode).

## Vergleich mit ähnlichen Bausteinen

| Merkmal        | E_DEMUX (dieser) | E_MUX          | E_SWITCH         |
|----------------|------------------|----------------|------------------|
| Funktionsprinzip| 1:4 Verteilung   | n:1 Zusammenführung | 1:2 Verteilung   |
| Steuerung      | Index `K` [0-3]  | Index `K`      | `BOOL`-Bedingung `G` |
| Ereignisfluss  | Aufteilung       | Zusammenführung| Bedingte Weiche  |

*Hinweis: Es existieren auch andere Varianten wie `E_DEMUX_2` und `E_DEMUX_8` für 2 bzw. 8 Ausgänge.*

## Fazit
Der `E_DEMUX` ist ein fundamentaler Baustein für die Steuerung des Ereignisflusses in IEC 61499-Anwendungen. Er ermöglicht eine klare, indexbasierte Aufteilung von Ereignisströmen und ist damit ein Schlüsselwerkzeug für die Implementierung von Zustandslogiken, Modus-Umschaltungen und Sequenzsteuerungen.
