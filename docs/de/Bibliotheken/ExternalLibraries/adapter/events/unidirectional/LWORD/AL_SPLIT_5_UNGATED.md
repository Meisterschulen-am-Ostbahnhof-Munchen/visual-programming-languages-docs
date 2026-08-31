# AL_SPLIT_5_UNGATED

> ℹ️ **UNGATED-Variante:** Dieser Baustein ist die ungegatete Version von [`AL_SPLIT_5`](AL_SPLIT_5.md). Er unterdrückt **keine** unveränderten Wiederholungen – jedes neu berechnete Ergebnis wird bedingungslos weitergegeben, auch ohne Wertänderung. Das ist wichtig für Verbraucher, die eine periodische Kadenz unabhängig von Wertänderung brauchen (z. B. Ableitungs-/Frequenzberechnungen, die sonst nicht gegen Null abklingen). Alle Angaben zu Änderungserkennung/Change-Gating weiter unten auf dieser Seite gelten **nicht** für diesen Baustein.

![AL_SPLIT_5_UNGATED](./AL_SPLIT_5_UNGATED.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AL_SPLIT_5_UNGATED** dient als generischer Splitter für einen unidirektionalen Adapter vom Typ `AL`. Er teilt ein eingehendes Signal (über den `IN`-Socket) auf fünf separate Ausgänge (`OUT1` bis `OUT5`) auf. Der Baustein ist als generisch gekennzeichnet, wodurch der konkrete Adaptertyp beim Einsatz festgelegt werden kann.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine Ereignis-Eingänge vorhanden.

### **Ereignis-Ausgänge**

Keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**

Keine Daten-Eingänge vorhanden.

### **Daten-Ausgänge**

Keine Daten-Ausgänge vorhanden.

### **Adapter**

| Typ      | Richtung | Name | Beschreibung                       |
|----------|----------|------|------------------------------------|
| Socket   | Eingang  | IN   | Unidirektionaler `AL`-Adapter-Eingang |
| Plug     | Ausgang  | OUT1 | Erster Ausgang (unidirektionaler `AL`) |
| Plug     | Ausgang  | OUT2 | Zweiter Ausgang (unidirektionaler `AL`) |
| Plug     | Ausgang  | OUT3 | Dritter Ausgang (unidirektionaler `AL`) |
| Plug     | Ausgang  | OUT4 | Vierter Ausgang (unidirektionaler `AL`) |
| Plug     | Ausgang  | OUT5 | Fünfter Ausgang (unidirektionaler `AL`) |

## Funktionsweise

Der Baustein empfängt über den Socket `IN` ein Signal des Typs `AL` und leitet dieses unverändert an alle fünf Plugs `OUT1` bis `OUT5` weiter. Es findet keine Datenverarbeitung oder Ereignisbehandlung statt; die Aufteilung erfolgt rein auf Adapterebene. Dadurch können mehrere nachgeschaltete Komponenten parallel mit dem gleichen Adaptersignal versorgt werden.

Der Funktionsblock ist als generischer Baustein (`GEN_AL_SPLIT`) ausgelegt. Der konkrete Adaptertyp `AL` kann bei der Instanziierung über ein Attribut festgelegt werden.

## Technische Besonderheiten

- **Keine Ereignisse oder Daten**: Der Baustein besitzt ausschließlich Adapterschnittstellen, keine Ereignis- oder Datenports.
- **Generische Auslegung**: Der Typ des `AL`-Adapters ist parametrierbar (generic class), sodass verschiedene Ausprägungen desselben Adaptertyps verwendet werden können.
- **reine Signalverteilung**: Es handelt sich um eine reine 1:5-Verteilung ohne jegliche Logik, Verzögerung oder Transformation.

## Zustandsübersicht

Der Baustein besitzt keinen internen Zustandsautomaten, da er keine Ereignisse verarbeitet. Er verhält sich statisch und leitet das Eingangssignal permanent an alle Ausgänge weiter.

## Anwendungsszenarien

- **Signalverteilung**: Wenn mehrere Komponenten dasselbe Adaptersignal eines `AL`-Typs benötigen, z. B. um einen Sensorwert an verschiedene Steuerungslogiken zu senden.
- **Test- und Debugging-Umgebungen**: Ein eingehendes Adaptersignal kann an mehrere Monitor- oder Logging-Bausteine gleichzeitig weitergegeben werden.
- **Redundanz**: Das Signal kann an parallele Verarbeitungspfade verteilt werden.

## Vergleich mit ähnlichen Bausteinen

Im 4diac-Ökosystem existieren weitere Splitter-Bausteine, z. B. `SPLIT` für Ereignis- oder Datenflüsse. Der Vorteil von `AL_SPLIT_5_UNGATED` liegt in der ausschließlichen Adapter-Schnittstelle. Während ein `SPLIT`-Baustein Ereignisse oder Daten trennt, arbeitet dieser Baustein direkt auf der Adapterebene und erfordert keine Umsetzung zwischen Ereignissen und Daten. Ähnliche Bausteine mit anderer Anzahl von Ausgängen (z. B. `AL_SPLIT_2`, `AL_SPLIT_3`) sind denkbar, jedoch nicht standardmäßig in dieser generischen Form enthalten.

- **[`AL_SPLIT_5`](AL_SPLIT_5.md)**: Die gegatete Variante – aktualisiert den Ausgang nur bei tatsächlicher Wertänderung.

## Änderungserkennung

Dieser Baustein führt **keine** Änderungserkennung durch. Jedes neu berechnete Ergebnis wird bedingungslos auf den Ausgang geschrieben und das zugehörige Adapter-Event gesendet, unabhängig davon, ob sich der Wert gegenüber dem vorherigen Durchlauf geändert hat.

## Fazit

Der **AL_SPLIT_5_UNGATED** ist ein einfacher, aber nützlicher generischer Funktionsblock zur Vervielfältigung eines unidirektionalen Adaptersignals auf fünf Ausgänge. Aufgrund seiner reinen Adapterschnittstelle und fehlenden Ereignis-/Datenlogik eignet er sich besonders für Anwendungen, die ein Signal ohne Verarbeitung an mehrere Empfänger verteilen müssen. Die generische Auslegung erhöht die Flexibilität bei der Wiederverwendung in verschiedenen Projekten.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
