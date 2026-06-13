# Uebung_007a3_AX: Blinker mit E_CYCLE, E_SWITCH und E_SR




[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/041f4df4-b729-484d-b786-b6dcdf151961)

Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_007a3_AX`. Diese Übung zeigt die "saubere" Lösung für einen schaltbaren Blinker.

----


## Ziel der Übung

Sicherstellen, dass der Blinker immer im Zustand "AUS" stoppt.

-----

## Beschreibung und Komponenten

[cite_start]Die Subapplikation `Uebung_007a3_AX.SUB` verwendet eine komplexere Logik[cite: 1]:

  * **`AX_CYCLE`**: Der Taktgeber (Startet/Stoppt).
  * **`E_SR`**: Ein Speicher ("Blinker ist aktiv").
  * **`AX_SPLIT_2`**: Verteilt das Signal vom Speicher (zur Lampe und zur Rückkopplung).
  * **`AX_AE_MERGE`**: Führt das Taktsignal (`AE_CYCLE.EO` - nur Event) und das Rückkopplungssignal (`E_SR.Q` - Event und BOOL) zusammen. Das Daten-Bit vom `E_SR.Q` bleibt dabei erhalten.
  * **`E_SWITCH`**: Das eigentliche "Herzstück". Es nutzt das gemergte Signal, um das `AX_SR`-Flip-Flop umzuschalten.

Aber das Wichtigste: Der `STOP` Eingang ist **zusätzlich** direkt mit `E_SR.R` verbunden.

-----

## Funktionsweise

1.  **Start/Blinken**: `START` drückt den Taster und startet den `AE_CYCLE`. Wenn `E_SR.Q` aktiv ist, sorgt die Schleife über `E_SWITCH` (durch `AX_AE_MERGE` getriggert) für das Toggeln.
2.  **Stoppen**: Wenn `STOP` gedrückt wird:
    *   Der `AE_CYCLE` stoppt (keine neuen Takte).
    *   Der `E_SR` wird **resettet**. Damit wird der Ausgang `Q` und somit die Lampe `Q1` **zwingend** auf FALSE gesetzt.

-----

## Anwendungsbeispiel

**Professioneller Indikator**: Eine Störungsleuchte in der Industrie muss blinken, wenn ein Fehler vorliegt, und **aus** sein, wenn der Fehler quittiert wurde. Sie darf niemals dauerhaft leuchten (das würde oft "Betriebsbereit" oder etwas anderes bedeuten).