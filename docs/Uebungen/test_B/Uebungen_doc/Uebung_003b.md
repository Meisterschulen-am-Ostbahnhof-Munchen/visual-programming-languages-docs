# Uebung_003b: DigitalInput_I1-2-3-4 auf DigitalOutput_Q1-2-3-4




[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)

Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_003b`. Diese Übung erweitert das Konzept der modularen Steuerung aus `Uebung_003a` auf insgesamt vier unabhängige Kanäle.

----


## Ziel der Übung

Das Hauptziel ist die Demonstration der Skalierbarkeit durch Typisierung. Es wird gezeigt, wie einfach eine bestehende Logik vervielfältigt werden kann, indem ein bereits definierter Sub-App-Typ mehrfach instanziiert wird. Dies unterstreicht den Effizienzvorteil der IEC 61499 bei der Verwaltung vieler gleichartiger Hardware-Schnittstellen.

-----

## Beschreibung und Komponenten

[cite_start]Die Subapplikation `Uebung_003b.SUB` verwendet vier Instanzen des Typs `Uebung_003b_sub` (identisch zu `Uebung_003a_sub`), um vier I/O-Paare zu verknüpfen[cite: 1].

### Typisierte Sub-Applikation: `Uebung_003b_sub`

[cite_start]Dieser Baustein kapselt die 1:1 Weiterleitung von einem digitalen Eingang (`IX`) zu einem digitalen Ausgang (`QX`)[cite: 2]. Er stellt zwei Parameter für die Konfiguration bereit:
  * **`Input`**: Auswahl des physischen Eingangs (z.B. `Input_I1` bis `Input_I4`).
  * **`Output`**: Auswahl des physischen Ausgangs (z.B. `Output_Q1` bis `Output_Q4`).

### Instanzen in der Hauptanwendung

In `Uebung_003b` werden vier Instanzen (`F1` bis `F4`) genutzt:
  * **`F1`**: `I1` ➡️ `Q1`
  * **`F2`**: `I2` ➡️ `Q2`
  * **`F3`**: `I3` ➡️ `Q3`
  * **`F4`**: `I4` ➡️ `Q4`

-----

## Funktionsweise

Die Logik ist vollständig in den Sub-Applikationen gekapselt. Die Hauptanwendung dient nur noch als Konfigurations-Ebene. Der Aufbau in `Uebung_003b.SUB` zeigt die Zuweisung der Parameter:

```xml
<SubApp Name="F1" Type="Uebungen::Uebung_003b_sub">
    <Parameter Name="Input" Value="Input_I1"/>
    <Parameter Name="Output" Value="Output_Q1"/>
</SubApp>
<!-- ... Instanzen F2 und F3 ... -->
<SubApp Name="F4" Type="Uebungen::Uebung_003b_sub">
    <Parameter Name="Input" Value="Input_I4"/>
    <Parameter Name="Output" Value="Output_Q4"/>
</SubApp>
```

[cite_start][cite: 1]

Jeder Kanal arbeitet völlig autark. Wenn an Eingang `I3` eine Änderung erkannt wird, reagiert ausschließlich die Instanz `F3` und schaltet den Ausgang `Q3`. Die anderen Kanäle bleiben davon unberührt.

-----

## Anwendungsbeispiel

**Modularer Schaltschrankbau**:
Stellen Sie sich ein IO-Modul mit 8 oder 16 Kanälen vor. Anstatt für jeden Kanal einzeln Verbindungen zu ziehen, nutzt man die typisierte Sub-Applikation als "Kanal-Treiber". Die Software-Struktur spiegelt so exakt den modularen Aufbau der Hardware wider, was die Fehlersuche und Dokumentation massiv vereinfacht.