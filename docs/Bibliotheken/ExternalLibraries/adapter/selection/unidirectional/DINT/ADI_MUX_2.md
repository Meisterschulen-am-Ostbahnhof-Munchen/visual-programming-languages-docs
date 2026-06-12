# ADI_MUX_2


![ADI_MUX_2](./ADI_MUX_2.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ADI_MUX_2** ist ein generischer Multiplexer für ADI-Adapter (Agricultural Data Interface). Er ermöglicht die Auswahl zwischen zwei ADI-Eingängen (IN1 und IN2) und leitet den gewählten Eingang zum Ausgang OUT weiter. Die Auswahl erfolgt über den Index K, der durch ein Ereignis gesetzt wird.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Setzt den Index K und löst die Multiplexer-Aktion aus. |

### **Ereignis-Ausgänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF  | Event | Bestätigt die erfolgte Indexsetzung und Auswahl. |

### **Daten-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| K    | UINT | Auswahlindex (0 → IN1, 1 → IN2) |

### **Daten-Ausgänge**
Keine direkten Datenausgänge. Die Ausgabe erfolgt über den Adapter **OUT**.

### **Adapter**
| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| Plug (Ausgang) | OUT   | `adapter::types::unidirectional::ADI` | Ausgang: liefert die Daten des gewählten Eingangs. |
| Socket (Eingang) | IN1  | `adapter::types::unidirectional::ADI` | Erster Eingang (K = 0). |
| Socket (Eingang) | IN2  | `adapter::types::unidirectional::ADI` | Zweiter Eingang (K = 1). |

## Funktionsweise
1. Der Baustein wartet auf ein **REQ**-Ereignis.
2. Beim Eintreffen von **REQ** wird der Wert des Daten-Eingangs **K** ausgelesen.
3. Abhängig von **K** wird entweder **IN1** (K = 0) oder **IN2** (K = 1) über den Adapter **OUT** nach außen sichtbar gemacht.
4. Nach erfolgreicher Auswahl wird das Bestätigungsereignis **CNF** gesendet.

Die Auswahl erfolgt rein ereignisgesteuert; jede Änderung von **K** erfordert ein erneutes **REQ**-Ereignis, um wirksam zu werden.

## Technische Besonderheiten
- **Generischer Funktionsblock**: Der FB ist als generischer Baustein (`GEN_ADI_MUX`) deklariert und kann für verschiedene ADI-Datentypen verwendet werden (z. B. durch Anpassung der ADI-Adapterdefinition).
- **Adapterbasierte Schnittstelle**: Die Kommunikation erfolgt ausschließlich über ADI-Adapter (unidirektional). Es werden keine direkten Datenvariablen an den Ausgängen verwendet.
- **Einfache Logik**: Keine interne Zustandsmaschine – die Aktion wird direkt durch das Ereignis ausgelöst.

## Zustandsübersicht
Der FB besitzt keine explizite Zustandsmaschine. Der Arbeitsablauf lässt sich wie folgt beschreiben:
1. **Warten** auf **REQ**.
2. **Verarbeiten**: Einlesen von **K** und Durchschalten des entsprechenden Eingangs.
3. **Bestätigen**: Senden von **CNF**.
4. Rückkehr in den Wartezustand.

## Anwendungsszenarien
- **Sensorumschaltung**: Wahl zwischen zwei ADI-konformen Sensoren (z. B. Temperatur/Druck) in einer landwirtschaftlichen Steuerung.
- **Redundanz**: Umschalten auf einen Ersatz-ADI-Eingang bei Ausfall des primären Signals.
- **Modusauswahl**: Je nach Betriebsmodus (z. B. manuell/automatisch) wird ein anderer Datenstrom verwendet.

## Vergleich mit ähnlichen Bausteinen
- **ADI_MUX_2** ist auf genau zwei Eingänge beschränkt.
- Für mehr Eingänge wären entsprechende Varianten (z. B. ADI_MUX_4, ADI_MUX_8) denkbar, die den Index **K** entsprechend erweitern.
- Im Gegensatz zu einem allgemeinen Multiplexer für Standarddatentypen (z. B. INT, REAL) arbeitet dieser FB ausschließlich mit ADI-Adaptern und ist daher in ADI-basierte Systemarchitekturen integriert.

## Fazit
Der **ADI_MUX_2** ist ein kompakter, ereignisgesteuerter Multiplexer für ADI-Adapter. Er eignet sich hervorragend für Anwendungen, bei denen zwischen zwei ADI-Datenquellen dynamisch umgeschaltet werden muss. Dank seiner generischen Auslegung kann er in unterschiedlichsten ADI-Kontexten eingesetzt werden, ohne dass eine Anpassung der internen Logik erforderlich ist.