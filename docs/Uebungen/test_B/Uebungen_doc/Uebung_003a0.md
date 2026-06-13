# Uebung_003a0: DigitalInput_I1/_I2 auf DigitalOutput_Q1/_I2 - mit untyped Subapp




[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)

Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_003a0`. Im Gegensatz zur Verwendung von Typen (wie in `Uebung_003a`) wird hier gezeigt, wie man Logik visuell gruppieren kann, ohne separate Typ-Definitionen in der Bibliothek anzulegen. Dies geschieht durch sogenannte "Untyped SubApps".

----


## Ziel der Übung

Das Hauptziel dieser Übung ist es, Möglichkeiten zur rein visuellen Strukturierung von Anwendungen aufzuzeigen. Untypisierte Sub-Applikationen dienen als "Container" oder Ordner innerhalb eines Netzwerks, um zusammengehörige Funktionen zu kapseln. Sie helfen, komplexe Diagramme aufzuräumen ("Aufräumen durch Einklappen"), ohne dass man sich Gedanken über Wiederverwendbarkeit oder Schnittstellen-Definitionen machen muss.

-----

## Beschreibung und Komponenten

[cite_start]Die Subapplikation `Uebung_003a0.SUB` enthält zwei eingebettete Sub-Applikationen (`SubApp` und `SubApp_1`), die jeweils einen eigenen Signalpfad beinhalten[cite: 1].

### Untypisierte Sub-Applikationen

Anders als bei typisierten SubApps, die auf einer externen Definition basieren, existiert die Logik dieser Container nur innerhalb dieser spezifischen Instanz. Sie haben keine externen Ein- oder Ausgänge im Interface (in diesem Beispiel), sondern greifen direkt auf die Hardware zu.

1.  **Container `SubApp`**:
    *   Beinhaltet die Logik für Kanal 2.
    *   Intern: [cite_start]`DigitalInput_I2` verbunden mit `DigitalOutput_Q2`[cite: 1].

2.  **Container `SubApp_1`**:
    *   Beinhaltet die Logik für Kanal 1.
    *   Intern: [cite_start]`DigitalInput_I1` verbunden mit `DigitalOutput_Q1`[cite: 1].

### Funktionsbausteine (FBs)

Innerhalb der Container werden die bekannten Standard-Bausteine verwendet:
  * **`logiBUS_IX`**: Zum ereignisbasierten Einlesen der Signale.
  * **`logiBUS_QX`**: Zum ereignisbasierten Ausgeben der Signale.

-----

## Funktionsweise

Die Logik ist identisch zur parallelen Steuerung, jedoch ist die Ansicht hierarchisch gegliedert. Der Aufbau in `Uebung_003a0.SUB` zeigt die Verschachtelung:

```xml
<SubAppNetwork>
    <SubApp Name="SubApp">
        <SubAppNetwork>
            <FB Name="DigitalInput_I2" ... />
            <FB Name="DigitalOutput_Q2" ... />
            <EventConnections> ... </EventConnections>
            <DataConnections> ... </DataConnections>
        </SubAppNetwork>
    </SubApp>
    
    <SubApp Name="SubApp_1">
        <SubAppNetwork>
            <FB Name="DigitalInput_I1" ... />
            <FB Name="DigitalOutput_Q1" ... />
            <EventConnections> ... </EventConnections>
            <DataConnections> ... </DataConnections>
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

**Visuelle Gruppierung von Funktionsbereichen**:
In einer großen Anlage könnte man untypisierte SubApps nutzen, um die Logik thematisch zu sortieren, z.B. einen Container "Temperaturregelung", einen "Antriebssteuerung" und einen "Sicherheitsüberwachung". Wenn man die Hauptansicht öffnet, sieht man nur diese drei Blöcke und nicht hunderte von einzelnen Gattern und Verbindungen. Dies erleichtert die Navigation ("Zoom-In"-Effekt), ist aber nicht für die Wiederverwendung über mehrere Projekte hinweg gedacht (dafür nutzt man typisierte SubApps).