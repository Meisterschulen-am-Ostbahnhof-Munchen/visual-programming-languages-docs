# ASR_SPLIT_8


![ASR_SPLIT_8](./ASR_SPLIT_8.svg)

*(Bild des Funktionsblocks hier einfügen)*

* * * * * * * * * *
## Einleitung

Der Funktionsblock `ASR_SPLIT_8` dient dazu, ein einzelnes eingehendes **ASR**-Adapter-Signal unverändert auf acht identische Ausgänge zu verteilen. Er wird als generischer Baustein definiert und eignet sich besonders für Anwendungen, in denen ein Sensorsignal oder Steuersignal mehrfach benötigt wird – beispielsweise in der landwirtschaftlichen Automatisierungstechnik.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine Ereignis-Eingänge vorhanden. Der Funktionsblock arbeitet rein adapterbasiert ohne ereignisgesteuerte Ausführung.

### **Ereignis-Ausgänge**

Keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**

Keine Daten-Eingänge vorhanden. Alle Signalübertragungen erfolgen über die **Adapter**-Schnittstellen.

### **Daten-Ausgänge**

Keine Daten-Ausgänge vorhanden.

### **Adapter**

| Richtung | Name  | Typ                           | Beschreibung                                                      |
|----------|-------|-------------------------------|-------------------------------------------------------------------|
| Socket   | IN    | `adapter::types::unidirectional::ASR` | Eingehendes ASR-Signal, das auf alle Ausgänge verteilt wird. |
| Plug     | OUT1  | `adapter::types::unidirectional::ASR` | Erster Ausgang mit dem Signal von IN.                             |
| Plug     | OUT2  | `adapter::types::unidirectional::ASR` | Zweiter Ausgang mit dem Signal von IN.                            |
| Plug     | OUT3  | `adapter::types::unidirectional::ASR` | Dritter Ausgang mit dem Signal von IN.                            |
| Plug     | OUT4  | `adapter::types::unidirectional::ASR` | Vierter Ausgang mit dem Signal von IN.                            |
| Plug     | OUT5  | `adapter::types::unidirectional::ASR` | Fünfter Ausgang mit dem Signal von IN.                            |
| Plug     | OUT6  | `adapter::types::unidirectional::ASR` | Sechster Ausgang mit dem Signal von IN.                           |
| Plug     | OUT7  | `adapter::types::unidirectional::ASR` | Siebter Ausgang mit dem Signal von IN.                            |
| Plug     | OUT8  | `adapter::types::unidirectional::ASR` | Achter Ausgang mit dem Signal von IN.                             |

## Funktionsweise

Der `ASR_SPLIT_8`-Block stellt eine **1-zu-8-Signalverteilung** für den ASR-Adaptertyp dar. Das am Socket `IN` anliegende ASR-Signal wird ohne Verzögerung oder Zustandsänderung an alle acht Plug-Ausgänge (`OUT1`...`OUT8`) weitergeleitet. Es findet keine Signalaufbereitung, Filterung oder logische Verknüpfung statt – der Block arbeitet rein passiv und ohne eigenes Verhalten.

Da der Adaptertyp `ASR` als unidirectional definiert ist, fließen die Daten nur vom Socket zu den Plugs. Änderungen am Eingangssignal wirken sich unmittelbar auf alle Ausgänge aus.

## Technische Besonderheiten

- **Generische Typparametrisierung**: Der FB besitzt die Attribute `eclipse4diac::core::GenericClassName` (Wert `'GEN_ASR_SPLIT'`) und `eclipse4diac::core::TypeHash`, welche die Verwendung eines generischen ASR-Datentyps ermöglichen. Dadurch kann der Baustein für verschiedene ASR-Untertypen wiederverwendet werden.
- **Keine Ereignissteuerung**: Der Baustein enthält keine Ereignisein- oder -ausgänge; die Signalweitergabe erfolgt ausschließlich über die Adapter-Schnittstellen. Dies vereinfacht die Einbindung in statische Datenflüsse.
- **Kein internes Verhalten**: Es existiert keine Zustandsmaschine oder Algorithmus – die Funktionalität beschränkt sich auf die reine Verdrahtungslogik der 4diac-IDE.

## Zustandsübersicht

Der `ASR_SPLIT_8` besitzt **keine internen Zustände**. Die Ausgabe ist zu jedem Zeitpunkt eine direkte Funktion des Eingangssignals. Der Block verhält sich wie eine passive Verdrahtung (steriler Splitter) ohne Speicher- oder Verzögerungseffekte.

## Anwendungsszenarien

- **Verteilung eines Sensorsignals** (z. B. Drehzahl, Druck oder Position) an mehrere parallele Regelkreise oder Anzeigeeinheiten.
- **Aufteilung eines Steuerbefehls** auf mehrere Aktoren in einer landwirtschaftlichen Maschine, wie z. B. die gleichzeitige Ansteuerung mehrerer Ventile oder Antriebe.
- **Monitoring und Logging**: Ein Signal kann über einen Ausgang an eine Steuerung und über einen zweiten Ausgang an ein Diagnosesystem weitergeleitet werden.

## Vergleich mit ähnlichen Bausteinen

| Baustein               | Ausgänge | Besonderheit                                   |
|------------------------|----------|------------------------------------------------|
| `ASR_SPLIT_8`          | 8        | Bietet die maximal mögliche Anzahl an ASR-Kopien in einem Block. |
| `ASR_SPLIT_4`          | 4        | Kompaktere Alternative für kleinere Verteilungen. |
| `ASR_SPLIT_2`          | 2        | Minimaler Splitter für Punkt-zu-Punkt-Weitergabe. |

Die **8er-Version** ist die umfangreichste und erlaubt den Anschluss vieler Verbraucher ohne zusätzliche Kaskadierung. Gegenüber einer Kaskade mehrerer 2er- oder 4er-Splitter reduziert `ASR_SPLIT_8` die Anzahl der benötigten Blöcke und vereinfacht das Engineering.

## Fazit

Der `ASR_SPLIT_8` ist ein einfacher, aber effizienter Baustein, um ein ASR-Signal auf acht unabhängige Pfade zu verteilen. Durch seine generische Auslegung und das Fehlen von Zuständen und Ereignissen ist er robust, ressourcenschonend und ideal für unidirektionale Datenweiterleitungen in landwirtschaftlichen und industriellen Automatisierungssystemen geeignet. Er ergänzt die Familie der ASR-Splitter und deckt den Bedarf an einer hohen Anzahl paralleler Ausgänge ab.