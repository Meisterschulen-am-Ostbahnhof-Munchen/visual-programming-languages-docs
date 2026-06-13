# Uebung_008_AX: Blinker mit E_CYCLE, E_SWITCH und E_SR




[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/041f4df4-b729-484d-b786-b6dcdf151961)

Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_008_AX`.

----


## Ziel der Übung

Implementierung eines dauerhaft laufenden Blinkers als Basis-Baustein.

-----

## Beschreibung und Komponenten

## Beschreibung und Komponenten

Die Subapplikation `Uebung_008_AX.SUB` ist eine Variante, die den `AX_AE_MERGE` Baustein nutzt, um die Ereignisse korrekt zusammenzuführen.

Der `AE_CYCLE` läuft dauerhaft (oder wird einmalig initialisiert). Der `AX_AE_MERGE` führt das Taktsignal (`AE_CYCLE.EO`) mit dem Rückkopplungssignal (`AX_SR.Q`) zusammen. Die Logik mit `E_SWITCH` und `AX_SR` sorgt für das Toggeln. Da keine externen Eingriffe vorgesehen sind, blinkt dieser Ausgang permanent, solange die Steuerung läuft.

-----

## Anwendungsbeispiel

**Lebenszeichen (Heartbeat)**: Eine LED, die auf der Platine oder am Schaltschrank blinkt, um anzuzeigen: "Die CPU lebt noch und das Programm läuft".