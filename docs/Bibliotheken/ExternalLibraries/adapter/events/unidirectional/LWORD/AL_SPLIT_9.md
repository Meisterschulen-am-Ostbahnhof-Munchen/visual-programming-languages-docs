# AL_SPLIT_9


![AL_SPLIT_9](./AL_SPLIT_9.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AL_SPLIT_9** ist ein generischer Baustein, der einen eingehenden Adapter vom Typ `AL` auf neun gleichartige ausgehende Adapter aufteilt. Er wird verwendet, um ein Signal oder einen Datenfluss, der über einen einzigen Adapter ankommt, an mehrere nachfolgende Komponenten zu verteilen. Der Baustein ist als generischer Typ (`GEN_AL_SPLIT`) definiert und muss vor der Verwendung an den konkreten Adaptertyp gebunden werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der Baustein besitzt keine Ereignis-Eingänge. Die Datenweitergabe erfolgt ausschließlich über Adapterverbindungen.

### **Ereignis-Ausgänge**

Es sind keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**

Keine separaten Dateneingänge – die eigentlichen Daten werden über den eingehenden Adapter übertragen.

### **Daten-Ausgänge**

Keine separaten Datenausgänge – die Ausgangsdaten werden über die neun ausgehenden Adapter bereitgestellt.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| **Socket** (Eingang) | `IN` | `adapter::types::unidirectional::AL` | Ein eingehender Adapter, der das zu verteilende Signal oder die Daten liefert. |
| **Plug** (Ausgang) | `OUT1` … `OUT9` | `adapter::types::unidirectional::AL` | Neun ausgehende Adapter, die jeweils eine Kopie des Eingangssignals ausgeben. |

## Funktionsweise

Der Baustein agiert als passiver Verteiler. Sobald der eingehende Adapter `IN` mit einem Signal oder Datenpaket belegt wird, leitet der Baustein dieses an alle neun Ausgangsadapter (`OUT1` … `OUT9`) weiter. Die Weiterleitung erfolgt ohne Pufferung oder Verzögerung – es handelt sich um eine reine 1:9‑Aufteilung.

Da der Baustein generisch ist, muss ihm vor der Nutzung ein konkreter `AL`‑Adaptertyp zugewiesen werden. Dies geschieht in der Entwicklungsumgebung durch die Angabe des spezifischen Adaptertyps, der die eigentlichen Datenfelder und Ereignisse definiert.

## Technische Besonderheiten

- **Generischer Baustein:** Der FB ist als `GEN_AL_SPLIT` deklariert und erfordert eine Bindung an einen konkreten `AL`‑Adaptertyp (z. B. `SimpleData_AL`). Die Bindung wird durch das Attribut `eclipse4diac::core::GenericClassName` gesteuert.
- **Typensicherheit:** Alle neun Ausgänge verwenden denselben Adaptertyp wie der Eingang. Dadurch wird sichergestellt, dass die Datenstruktur identisch bleibt.
- **Zustandslos:** Der Baustein besitzt keine internen Zustände oder Speicher – die Verteilung erfolgt instantan bei jedem neuen Datendurchlauf.
- **Keine Ereignissteuerung:** Da keine Ereigniseingänge definiert sind, wird die Verteilung allein durch die Datenänderung am Eingangsadapter ausgelöst.

## Zustandsübersicht

Der Baustein verfügt über keinen internen Zustandsautomaten. Er arbeitet zustandslos und rein datenflussgetrieben.

## Anwendungsszenarien

- **Signalverteilung:** Ein Sensorwert (z. B. Temperatur, Druck) soll gleichzeitig an mehrere Auswerteeinheiten oder Steuerungen gesendet werden.
- **Datenreplikation:** Ein Steuerbefehl soll parallel an mehrere Aktoren verteilt werden.
- **Modulare Architekturen:** Aufteilung eines Datenstroms in einer Pipeline, um verschiedene Verarbeitungszweige zu speisen.

## Vergleich mit ähnlichen Bausteinen

- **AL_SPLIT_2, AL_SPLIT_4:** Bausteine mit analoger Funktionalität, die das Eingangssignal auf 2 bzw. 4 Ausgänge verteilen. `AL_SPLIT_9` deckt eine größere Anzahl von Ausgängen ab, was insbesondere in komplexen Verteilstrukturen nützlich ist.
- **Einfache Kopplung (z. B. direkte Verbindung):** Ohne Split-Baustein müsste der Absender mehrere Adapterverbindungen selbst bereitstellen. Der Split-Baustein kapselt diese Logik und vereinfacht die Gesamtarchitektur.

## Fazit

Der `AL_SPLIT_9` ist ein einfacher, aber leistungsfähiger generischer Verteilerbaustein für Adapterschnittstellen vom Typ `AL`. Er ermöglicht eine saubere, wartbare Aufteilung eines Datenflusses auf neun unabhängige Pfade. Dank seiner generischen Natur und der Zustandslosigkeit eignet er sich hervorragend für modulare und skalierbare Automatisierungslösungen.