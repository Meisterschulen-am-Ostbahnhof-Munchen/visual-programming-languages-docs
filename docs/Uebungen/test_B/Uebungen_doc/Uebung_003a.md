# Uebung_003a: DigitalInput_I1/_I2 auf DigitalOutput_Q1/_I2 - mit typed Subapp




[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)

Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_003a`. Hier wird ein fortgeschrittener Ansatz zur Strukturierung von IEC 61499-Anwendungen demonstriert: Die Kapselung von Logik in wiederverwendbare, typisierte Sub-Applikationen ("Typed SubApps").

----


## Ziel der Übung

Das Hauptziel ist die Vermeidung von redundantem Code. Anstatt für jeden Kanal die gleichen Bausteine und Verbindungen manuell zu zeichnen, wird einmalig ein generischer "Kanal-Typ" definiert. Dieser kann dann beliebig oft instanziiert und individuell konfiguriert werden. Dies erhöht die Übersichtlichkeit und reduziert Fehler bei der Programmierung großer Anlagen.

-----

## Beschreibung und Komponenten

[cite_start]Die Subapplikation `Uebung_003a.SUB` verwendet zwei Instanzen eines selbst definierten Sub-App-Typs, um zwei Signalpfade zu realisieren[cite: 1].

### Typisierte Sub-Applikation: `Uebung_003a_sub`

[cite_start]Dieser Baustein kapselt die grundlegende Logik der Signalweiterleitung[cite: 2]. Er besitzt zwei Parameter zur Hardware-Zuordnung:
  * **`Input`**: Bestimmt den physischen Eingang (z.B. `Input_I1`).
  * **`Output`**: Bestimmt den physischen Ausgang (z.B. `Output_Q1`).

Im Inneren des Typs befinden sich ein `logiBUS_IX` und ein `logiBUS_QX` Baustein, die über eine Event- und eine Data-Connection fest miteinander verbunden sind.

### Instanzen in der Hauptanwendung

In `Uebung_003a` werden zwei Instanzen dieses Typs platziert:
  * **`F1`**: [cite_start]Parametriert für den Pfad `I1` zu `Q1`[cite: 1].
  * **`F2`**: [cite_start]Parametriert für den Pfad `I2` zu `Q2`[cite: 1].

-----

## Funktionsweise

Die Komplexität der Einzelverbindungen ist im Inneren der Sub-Applikation verborgen ("Information Hiding"). Die Hauptanwendung definiert lediglich die Zuweisung der physischen Adressen. Der Aufbau in `Uebung_003a.SUB` ist daher extrem kompakt:

```xml
<SubApp Name="F1" Type="Uebungen::Uebung_003a_sub">
    <Parameter Name="Input" Value="Input_I1"/>
    <Parameter Name="Output" Value="Output_Q1"/>
</SubApp>
<SubApp Name="F2" Type="Uebungen::Uebung_003a_sub">
    <Parameter Name="Input" Value="Input_I2"/>
    <Parameter Name="Output" Value="Output_Q2"/>
</SubApp>
```

[cite_start][cite: 1]

Funktional verhält sich die Anwendung exakt wie die flache Struktur in Übung 003. Jede Instanz arbeitet als eigenständiger Block, der auf Ereignisse an seinem zugewiesenen Hardware-Eingang reagiert und den Hardware-Ausgang aktualisiert.

-----

## Anwendungsbeispiel

**Objektorientierte Anlagensteuerung**:
Stellen Sie sich eine Förderbandanlage mit 20 identischen Sektionen vor. Anstatt 20 mal die gleiche Logik zu zeichnen, erstellt man einen Typ "Sektion". In der Hauptanwendung platziert man 20 Instanzen und gibt ihnen nur die Start-Adressen der jeweiligen Hardware-IOs. Muss später die Logik geändert werden (z.B. eine zusätzliche Zeitverzögerung), ändert man dies nur an einer einzigen Stelle (im Typ), und alle 20 Sektionen übernehmen die Änderung sofort.