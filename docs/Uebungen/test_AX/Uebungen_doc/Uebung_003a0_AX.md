# Uebung_003a0_AX: DigitalInput_I1/_I2 auf DigitalOutput_Q1/_I2 - mit untyped Subapp




[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/041f4df4-b729-484d-b786-b6dcdf151961)

Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_003a0_AX`. Im Gegensatz zur Verwendung von Typen (wie in `Uebung_003a_AX`) wird hier gezeigt, wie man Logik visuell gruppieren kann, ohne separate Typ-Definitionen anzulegen. Dies geschieht durch sogenannte "Untyped SubApps".

----


## Ziel der Übung

Das Hauptziel dieser Übung ist es, Möglichkeiten zur rein visuellen Strukturierung von Anwendungen aufzuzeigen. Untypisierte Sub-Applikationen dienen als "Container" oder Ordner innerhalb eines Netzwerks, um zusammengehörige Funktionen zu kapseln. Sie helfen, komplexe Diagramme aufzuräumen ("Aufräumen durch Einklappen"), ohne dass man sich Gedanken über Wiederverwendbarkeit oder Schnittstellen-Definitionen machen muss.

-----

## Beschreibung und Komponenten

[cite_start]Die Subapplikation `Uebung_003a0_AX.SUB` enthält zwei eingebettete Sub-Applikationen (`SubApp` und `SubApp_1`), die jeweils einen eigenen Signalpfad beinhalten[cite: 1].

### Untypisierte Sub-Applikationen

Anders als bei typisierten SubApps, die auf einer externen Definition basieren, existiert die Logik dieser Container nur innerhalb dieser spezifischen Instanz.



1.  **Container `SubApp`**:
    *   Beinhaltet die Logik für Kanal 2.
    *   Intern: [cite_start]`DigitalInput_I2` verbunden mit `DigitalOutput_Q2`[cite: 1].

2.  **Container `SubApp_1`**:
    *   Beinhaltet die Logik für Kanal 1.
    *   Intern: [cite_start]`DigitalInput_I1` verbunden mit `DigitalOutput_Q1`[cite: 1].

### Funktionsbausteine (FBs)

Innerhalb der Container werden die bekannten Bausteine verwendet:
  * **`logiBUS_IXA`**: Zum Einlesen der Signale.
  * **`logiBUS_QXA`**: Zum Ausgeben der Signale.

-----

## Funktionsweise

Die Logik ist identisch zur parallelen Steuerung, jedoch ist die Ansicht hierarchisch gegliedert. Der Aufbau in `Uebung_003a0_AX.SUB` zeigt die Verschachtelung:

```xml
<SubAppNetwork>
    <SubApp Name="SubApp">
        <SubAppNetwork>
            <FB Name="DigitalInput_I2" ... />
            <FB Name="DigitalOutput_Q2" ... />
            <AdapterConnections>
                <Connection Source="DigitalInput_I2.IN" Destination="DigitalOutput_Q2.OUT"/>
            </AdapterConnections>
        </SubAppNetwork>
    </SubApp>
    
    <SubApp Name="SubApp_1">
        <SubAppNetwork>
            <FB Name="DigitalInput_I1" ... />
            <FB Name="DigitalOutput_Q1" ... />
            <AdapterConnections>
                <Connection Source="DigitalInput_I1.IN" Destination="DigitalOutput_Q1.OUT"/>
            </AdapterConnections>
        </SubAppNetwork>
    </SubApp>
</SubAppNetwork>
```

[cite_start][cite: 1]

Der funktionale Ablauf:
Die Kapselung hat keinen Einfluss auf die Laufzeit-Ausführung. Die Bausteine verhalten sich exakt so, als wären sie alle auf der obersten Ebene platziert.
1.  `SubApp_1` verarbeitet das Signal von `I1` zu `Q1`.
2.  `SubApp` verarbeitet das Signal von `I2` zu `Q2`.

-----

## Anwendungsbeispiel

Ein typisches Anwendungsbeispiel ist die **Visuelle Gruppierung von Funktionsbereichen**:

In einer großen Anlage könnte man untypisierte SubApps nutzen, um die Logik thematisch zu sortieren, z.B. einen Container "Temperaturregelung", einen "Antriebssteuerung" und einen "Sicherheitsüberwachung". Wenn man die Hauptansicht öffnet, sieht man nur diese drei Blöcke und nicht hunderte von einzelnen Gattern und Verbindungen. Dies erleichtert die Navigation ("Zoom-In"-Effekt), ist aber nicht für die Wiederverwendung gedacht (dafür nutzt man typisierte SubApps).