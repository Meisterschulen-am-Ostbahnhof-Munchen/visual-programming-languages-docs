# AIS_MUX_3


![AIS_MUX_3](./AIS_MUX_3.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **AIS_MUX_3** ist ein generischer Multiplexer für AIS-Daten. Er wählt anhand eines Index `K` einen von drei AIS-Eingangsadaptern (`IN1`, `IN2`, `IN3`) aus und verbindet dessen Signale mit dem Ausgangsadapter `OUT`. Ein Ereignis `REQ` löst die Auswahl aus und wird nach erfolgreicher Umschaltung mit `CNF` quittiert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Ereignis | Beschreibung |
|----------|--------------|
| REQ      | Startet die Multiplex-Operation: Der Wert von `K` bestimmt, welcher Eingang auf den Ausgang geschaltet wird. |

### **Ereignis-Ausgänge**
| Ereignis | Beschreibung |
|----------|--------------|
| CNF      | Quittiert die erfolgreiche Auswahl des Eingangs entsprechend `K`. |

### **Daten-Eingänge**
| Name | Typ  | Beschreibung |
|------|------|--------------|
| K    | UINT | Index für die Auswahl des Eingangs (0 = IN1, 1 = IN2, 2 = IN3). |

### **Daten-Ausgänge**
Keine direkten Datenausgänge vorhanden. Die Ausgangsdaten werden über den Adapter `OUT` bereitgestellt.

### **Adapter**
| Name | Typ                                    | Beschreibung |
|------|----------------------------------------|--------------|
| OUT  | adapter::types::unidirectional::AIS    | Ausgangsadapter, der den gewählten Eingang widerspiegelt. |
| IN1  | adapter::types::unidirectional::AIS    | Erster Eingangsadapter (Index 0). |
| IN2  | adapter::types::unidirectional::AIS    | Zweiter Eingangsadapter (Index 1). |
| IN3  | adapter::types::unidirectional::AIS    | Dritter Eingangsadapter (Index 2). |

## Funktionsweise
1. Der Baustein erwartet an den Eingangsadaptern `IN1`, `IN2` und `IN3` drei verschiedene AIS-Datenquellen.
2. Ein eingehendes Ereignis an `REQ` überträgt den aktuellen Wert des Daten-Eingangs `K` zur internen Logik.
3. Abhängig von `K` (gültige Werte: 0, 1, 2) wird der entsprechende Eingangsadapter auf den Ausgangsadapter `OUT` durchgeschaltet.
4. Nach erfolgter Umschaltung wird das Ereignis `CNF` gesendet, um die Verarbeitung zu bestätigen.

Hinweis: Bei ungültigen Werten von `K` (z. B. größer 2) kann das Verhalten je nach Implementierung variieren; üblich ist die Rückgabe des letzten gültigen Zustands oder ein undefinierter Zustand.

## Technische Besonderheiten
- **Generischer Typ**: Der FB verwendet das Attribute `eclipse4diac::core::GenericClassName = 'GEN_AIS_MUX'`, was darauf hinweist, dass er als generischer Baustein in der 4diac-IDE angelegt wurde und für beliebige AIS-Adapter mit derselben Schnittstelle eingesetzt werden kann.
- **Keine eigene Zustandsmaschine**: Der FB besitzt keine explizite ECC (Execution Control Chart) in der XML-Definition; die Multiplex-Funktionalität wird vermutlich durch die zugrundeliegende Adapter-Architektur oder durch eine einfache Ereignis-Weitergabe realisiert.
- **Adapterbasierte Kommunikation**: Sowohl Eingänge als auch Ausgang sind als Adapter vom Typ `adapter::types::unidirectional::AIS` definiert. Dies ermöglicht eine lose Kopplung und flexible Wiederverwendung in AIS-basierten Datenströmen.

## Zustandsübersicht
Der FB weist keine dokumentierte Zustandsautomaten-Steuerung auf. Aus der Schnittstellenbeschreibung lässt sich lediglich ein grundlegender Ablauf herleiten:

1. **IDLE**: Warten auf ein `REQ`-Ereignis.
2. **MUX**: Verarbeitung des Index `K` und Durchschalten des entsprechenden Eingangs auf den Ausgang – ohne Zwischenzustände.
3. nach Abschluss wird **CNF** ausgegeben und der Baustein kehrt in den **IDLE**-Zustand zurück.

## Anwendungsszenarien
- **Landwirtschaftliche Sensorik**: Auswahl eines von drei AIS-kompatiblen Sensoren (z. B. Bodenfeuchte, Temperatur, GPS) für eine einheitliche Weiterverarbeitung.
- **Datenquellenumschaltung**: In einer Steuerung, die je nach Betriebsart oder Zeitplan auf verschiedene AIS-Datenquellen zurückgreift.
- **Redundanz und Test**: Wechsel zwischen mehreren AIS-Signalquellen zur Validierung oder Fehlererkennung.

## Vergleich mit ähnlichen Bausteinen
| Baustein | Anzahl Eingänge | Besonderheit |
|----------|-----------------|--------------|
| AIS_MUX_2 | 2 | Einfacher Zweikanal-Multiplexer für AIS-Adapter. |
| AIS_MUX_3 | 3 | Erweiterung auf drei Kanäle; ideal für Systeme mit drei Datenquellen. |
| AIS_MUX_4 | 4 | Höhere Kanalzahl, aber weniger spezifisch für 3‑Kanalszenarien. |

Im Vergleich zu einem allgemeinen MUX-FB (z. B. MUX aus IEC‑61499‑Standardbibliotheken) verwendet AIS_MUX_3 ausschließlich AIS-Adapter, was eine klare Datenstruktur und Typsicherheit innerhalb eines AIS-basierten Frameworks bietet.

## Fazit
Der Funktionsbaustein **AIS_MUX_3** ermöglicht eine einfache und effiziente Umschaltung zwischen drei AIS-Datenquellen. Dank der generischen Definition und der Adapter-Schnittstelle ist er flexibel in AIS-Anwendungen der Agrartechnik sowie in anderen Industrien einsetzbar. Die klare Ereignissteuerung und die begrenzte Komplexität machen ihn zu einem robusten Baustein für Multiplex-Aufgaben.