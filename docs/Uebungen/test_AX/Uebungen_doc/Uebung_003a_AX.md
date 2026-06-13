# Uebung_003a_AX: DigitalInput_I1/_I2 auf DigitalOutput_Q1/_I2 - mit typed Subapp




[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/041f4df4-b729-484d-b786-b6dcdf151961)

Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_003a_AX`. Die Übung demonstriert einen fortgeschrittenen Ansatz zur Strukturierung von IEC 61499-Anwendungen: die Verwendung von typisierten Sub-Applikationen ("Typed SubApps") zur Kapselung und Wiederverwendung von Logik.

----


## Ziel der Übung

Das Hauptziel ist es zu zeigen, wie redundanter Code vermieden werden kann. Anstatt identische Strukturen (z.B. die Verbindung eines Eingangs mit einem Ausgang) mehrfach zu zeichnen, wird einmalig ein generischer Baustein definiert. Dieser kann dann beliebig oft instanziiert und konfiguriert werden. Dies erhöht die Übersichtlichkeit und Wartbarkeit von großen Projekten erheblich.

-----

## Beschreibung und Komponenten

[cite_start]Die Subapplikation `Uebung_003a_AX.SUB` verwendet zwei Instanzen eines selbst definierten Sub-Typs, um zwei Signalpfade zu realisieren[cite: 1].

### Typisierte Sub-Applikation: `Uebung_003a_AX_sub`

[cite_start]Dieser Baustein kapselt die grundlegende Logik: "Lies einen Eingang und schreibe auf einen Ausgang"[cite: 2]. Er verfügt über Schnittstellen zur Parametrierung:


  * **`Input`**: Bestimmt, welcher physische Eingang gelesen werden soll (z.B. `Input_I1`).
  * **`Output`**: Bestimmt, welcher physische Ausgang geschaltet werden soll (z.B. `Output_Q1`).

Intern enthält dieser Sub-Typ:
  * Einen `logiBUS_IXA` Baustein zum Lesen des Eingangs.
  * Einen `logiBUS_QXA` Baustein zum Schreiben des Ausgangs.
  * Eine Adapter-Verbindung, die beide direkt verknüpft.

### Instanzen in der Hauptanwendung

In `Uebung_003a_AX` werden zwei Instanzen dieses Typs erzeugt:
  * **`F1`**: [cite_start]Konfiguriert für `Input_I1` auf `Output_Q1`[cite: 1].
  * **`F2`**: [cite_start]Konfiguriert für `Input_I2` auf `Output_Q2`[cite: 1].

-----

## Funktionsweise

Die Logik ist im Inneren der Sub-Applikation versteckt ("Information Hiding"). Die Hauptanwendung definiert nur noch die Verschaltung der Parameter. Der Aufbau in `Uebung_003a_AX.SUB` ist daher extrem kompakt:

```xml
<SubApp Name="F1" Type="Uebungen::Uebung_003a_AX_sub">
    <Parameter Name="Input" Value="Input_I1"/>
    <Parameter Name="Output" Value="Output_Q1"/>
</SubApp>
<SubApp Name="F2" Type="Uebungen::Uebung_003a_AX_sub">
    <Parameter Name="Input" Value="Input_I2"/>
    <Parameter Name="Output" Value="Output_Q2"/>
</SubApp>
```

[cite_start][cite: 1]

Der funktionale Ablauf entspricht exakt dem der `Uebung_003_AX` (parallele Steuerung), jedoch ist die Implementierung modularer. Jede Instanz (`F1`, `F2`) arbeitet als eigenständiger, isolierter Block, der seine interne Adapter-Logik ausführt.

-----

## Anwendungsbeispiel

Ein perfektes Anwendungsbeispiel ist die **Objektorientierte Anlagensteuerung**:

Stellen Sie sich eine Förderbandanlage mit 50 identischen Förderbändern vor. Jedes Band hat einen Motor (Ausgang) und eine Lichtschranke (Eingang). Anstatt 50 mal die gleichen Bausteine und Verbindungen zu zeichnen, erstellt man einmal einen Typ "Förderband-Modul". In der Hauptanwendung platziert man dann einfach 50 Instanzen dieses Moduls und weist ihnen nur noch die physikalischen Adressen zu. Ändert sich später die Logik (z.B. soll der Motor verzögert stoppen), muss man dies nur an einer Stelle (im Typ) ändern, und alle 50 Bänder werden automatisch aktualisiert.