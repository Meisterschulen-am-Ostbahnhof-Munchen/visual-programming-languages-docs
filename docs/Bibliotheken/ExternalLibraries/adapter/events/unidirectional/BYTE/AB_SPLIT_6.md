# AB_SPLIT_6


![AB_SPLIT_6](./AB_SPLIT_6.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **AB_SPLIT_6** ist ein generischer Adapter-Splitter. Er dient dazu, einen eingehenden unidirektionalen Adapterdatenstrom (Typ `AB`) gleichzeitig auf sechs separate Ausgänge zu verteilen. Dadurch können die Daten eines einzelnen Adapters mehreren nachgeschalteten Bausteinen ohne Datenverlust zur Verfügung gestellt werden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der Baustein besitzt keine Ereignis-Eingänge. Die Datenweitergabe erfolgt ausschließlich über die Adapterschnittstelle.

### **Ereignis-Ausgänge**
Es sind keine Ereignis-Ausgänge vorhanden. Die Ausgaben erfolgen rein über die Adapter.

### **Daten-Eingänge**
Der Baustein verfügt über keine separaten Daten-Eingänge. Die eigentlichen Nutzdaten werden über den Adaptereingang `IN` transportiert.

### **Daten-Ausgänge**
Es existieren keine expliziten Daten-Ausgänge. Die aufgeteilten Daten werden über die Adapterausgänge `OUT1` bis `OUT6` bereitgestellt.

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AB` | `IN` | Socket | Eingangsadapter, der die zu verteilenden Daten liefert. |
| `adapter::types::unidirectional::AB` | `OUT1` | Plug | Erster Ausgangsadapter – erhält eine Kopie der Eingangsdaten. |
| `adapter::types::unidirectional::AB` | `OUT2` | Plug | Zweiter Ausgangsadapter. |
| `adapter::types::unidirectional::AB` | `OUT3` | Plug | Dritter Ausgangsadapter. |
| `adapter::types::unidirectional::AB` | `OUT4` | Plug | Vierter Ausgangsadapter. |
| `adapter::types::unidirectional::AB` | `OUT5` | Plug | Fünfter Ausgangsadapter. |
| `adapter::types::unidirectional::AB` | `OUT6` | Plug | Sechster Ausgangsadapter. |

## Funktionsweise
Der Baustein liest die vom Adapter `IN` ankommenden Daten ein und gibt diese identisch an alle sechs Ausgangsadapter `OUT1` bis `OUT6` weiter. Es handelt sich um eine reine 1:6-Verteilung ohne Pufferung oder Datenverarbeitung. Sobald am Eingang Daten anliegen, werden diese sofort und gleichzeitig auf alle Ausgänge übertragen. Die Anzahl der Ausgänge ist fest auf sechs festgelegt.

## Technische Besonderheiten
- **Generischer Baustein**: Der FB ist als generischer Typ (`GEN_AB_SPLIT`) realisiert und kann im 4diac-IDE-Framework mehrfach verwendet werden.
- **Unidirektionale Schnittstelle**: Alle Adapter sind vom Typ `unidirectional::AB`, was bedeutet, dass der Datenfluss nur in eine Richtung (vom Eingang zu den Ausgängen) erfolgt.
- **Keine Zustandsabhängigkeit**: Da weder Ereignisse noch Triggermechanismen existieren, arbeitet der Baustein kontinuierlich und ohne inneren Zustand.
- **Lizenz**: Der Baustein steht unter der Eclipse Public License 2.0 (EPL-2.0).

## Zustandsübersicht
Der Baustein besitzt keinen internen Automaten oder diskrete Zustände. Die Funktionsweise ist rein durchlaufend – es gibt keine Initialisierung, keine Fehlerzustände und keine zeitlichen Abhängigkeiten.

## Anwendungsszenarien
- **Datenverteilung in Steuerungsanwendungen**: Wenn ein Sensor oder eine Datenquelle (z. B. ein IO‑Link‑Master über einen `AB`-Adapter) ihre Messwerte mehreren parallel arbeitenden Funktionsbausteinen zur Verfügung stellen muss.
- **Redundante Verarbeitung**: Ein Eingangssignal wird gleichzeitig an mehrere unabhängige Berechnungs- oder Überwachungslogiken weitergeleitet.
- **Prototyping**: Einfaches Duplizieren eines Adapter-Signals während der Entwicklungsphase, ohne dass eigene Splitter-Logik geschrieben werden muss.

## Vergleich mit ähnlichen Bausteinen
- **AB_SPLIT_2 / AB_SPLIT_4**: Analog aufgebaut, aber mit zwei bzw. vier Ausgängen. Der vorliegende Baustein bietet die maximale Anzahl von sechs Ausgängen.
- **Generische Splits mit Ereignissen**: Manche Splitter arbeiten ereignisgesteuert (z. B. `E_SPLIT`), erfordern dann aber zusätzliche Trigger. Der `AB_SPLIT_6` arbeitet dagegen kontinuierlich und ereignislos über die Adapterschnittstelle.
- **Daten‑Splitter (z. B. `F_SPLIT`)**: Diese teilen einzelne Datenwerte (z. B. ein Array) auf, während der `AB_SPLIT_6` den gesamten Adapter-Datenstrom unverändert kopiert.

## Fazit
Der `AB_SPLIT_6` ist ein einfacher, aber nützlicher generischer Funktionsbaustein zur Vervielfachung eines unidirektionalen Adaptersignals auf bis zu sechs Ausgänge. Er ist leicht verständlich, benötigt keine Konfiguration und eignet sich hervorragend für die schnelle Verteilung von Adapterdaten in industriellen Steuerungsanwendungen.