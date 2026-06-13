# Uebung_006a4_AX: SR und T-Flip-Flop mit 3x IE




[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/041f4df4-b729-484d-b786-b6dcdf151961)

Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_006a4_AX`. Sie ist eine Optimierung von `Uebung_006a3_AX` durch Verwendung eines vorgefertigten Bausteins.

----


## Ziel der Übung

Nutzung von Bibliotheken ("Don't reinvent the wheel").

-----

## Beschreibung und Komponenten

[cite_start]Die Subapplikation `Uebung_006a4_AX.SUB` ersetzt das komplexe Netzwerk aus Gatter und SubApp der vorherigen Übung durch den Baustein `LinksRechts_AX`[cite: 1].

### Funktionsbausteine (FBs)




![Uebung_006a4_AX_network](./Uebung_006a4_AX_network.svg)

  * **`LinksRechts`**: Typ `logiBUS::utils::sequence::verteiler::LinksRechts_AX`. Dieser Baustein kapselt die komplette Logik für die Richtungssteuerung und Verriegelung.
  * **`AX_T_FF_SR`**: Liefert weiterhin das "Ein/Aus" Signal an den Eingang `EIN` des Verteilers.

-----

## Funktionsweise

Die Logik ist gekapselt. Der Baustein `LinksRechts_AX` kümmert sich intern darum, das Eingangssignal abwechselnd auf den Ausgang `Links` und `Rechts` zu leiten.

-----

## Vorteil

Der Code ist wesentlich aufgeräumter, lesbarer und weniger fehleranfällig.