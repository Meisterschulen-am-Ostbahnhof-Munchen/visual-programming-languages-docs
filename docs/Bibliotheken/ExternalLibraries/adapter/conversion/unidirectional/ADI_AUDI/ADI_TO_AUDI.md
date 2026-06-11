# ADI_TO_AUDI


![ADI_TO_AUDI](./ADI_TO_AUDI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock ADI_TO_AUDI dient der Konvertierung eines Adapters vom Typ ADI (DINT) in einen Adapter vom Typ AUDI (UDINT). Es handelt sich um einen zusammengesetzten Baustein (Composite FB), der einen internen Konvertierungsbaustein verwendet, um die Datentypen von signed 32-bit Integer (DINT) nach unsigned 32-bit Integer (UDINT) zu wandeln. Der Baustein ermöglicht die nahtlose Integration von Komponenten, die unterschiedliche Adaptertypen verwenden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der Baustein besitzt keine direkten Ereignis-Eingänge. Ereignisse werden über den eingehenden Adapter **ADI_IN** bereitgestellt. Der Adapter ADI definiert einen Ereignis-Ausgang E1, der mit dem Ereignis-Eingang REQ des internen Konvertierungsbausteins verbunden ist.

| Bezeichnung | Datentyp | Beschreibung |
|-------------|----------|--------------|
| (über ADI_IN.E1) | EVENT | Auslöser für die Konvertierung |

### **Ereignis-Ausgänge**

Der Baustein besitzt keine direkten Ereignis-Ausgänge. Ereignisse werden über den ausgehenden Adapter **AUDI_OUT** weitergegeben. Der interne Konvertierungsbaustein signalisiert die Fertigstellung über CNF, das mit dem Ereignis-Eingang E1 des Adapters AUDI verbunden ist.

| Bezeichnung | Datentyp | Beschreibung |
|-------------|----------|--------------|
| (über AUDI_OUT.E1) | EVENT | Bestätigung der abgeschlossenen Konvertierung |

### **Daten-Eingänge**

Der Baustein besitzt keine direkten Daten-Eingänge. Der zu konvertierende DINT-Wert wird über den eingehenden Adapter **ADI_IN** (Ausgang D1) bereitgestellt.

| Bezeichnung | Datentyp | Beschreibung |
|-------------|----------|--------------|
| (über ADI_IN.D1) | DINT | Der als DINT vorliegende Wert, der in UDINT konvertiert werden soll |

### **Daten-Ausgänge**

Der Baustein besitzt keine direkten Daten-Ausgänge. Der konvertierte UDINT-Wert wird über den ausgehenden Adapter **AUDI_OUT** (Eingang D1) ausgegeben.

| Bezeichnung | Datentyp | Beschreibung |
|-------------|----------|--------------|
| (über AUDI_OUT.D1) | UDINT | Das Ergebnis der Konvertierung als UDINT |

### **Adapter**

Der Baustein stellt zwei Adapter-Schnittstellen bereit:

| Name | Richtung | Typ | Beschreibung |
|------|----------|-----|--------------|
| ADI_IN | Socket | adi (unidirectional) | Eingangsadapter – liefert DINT-Daten und ein Ereignis zur Auslösung |
| AUDI_OUT | Plug | audi (unidirectional) | Ausgangsadapter – gibt konvertierte UDINT-Daten und ein Bestätigungsereignis aus |

Die Adapter sind unidirektional, d.h. sie übertragen Daten und Ereignisse nur in eine Richtung.

## Funktionsweise

Der Funktionsblock arbeitet als reine Hülle (Composite) und enthält einen einzelnen internen Baustein vom Typ `iec61131::conversion::F_DINT_TO_UDINT`. Sobald am Eingangsadapter ADI_IN ein Ereignis an E1 eintrifft, wird der interne Baustein über seinen REQ-Eingang getriggert. Dieser liest den an ADI_IN.D1 anliegenden DINT-Wert, konvertiert ihn in einen UDINT-Wert und legt das Ergebnis an seinem Ausgang OUT an. Gleichzeitig erzeugt er ein Bestätigungsereignis an CNF, das über den Ausgangsadapter AUDI_OUT.E1 weitergeleitet wird. Der konvertierte Wert steht dann am AUDI_OUT.D1 zur Verfügung.

## Technische Besonderheiten

- Der Baustein ist als Composite FB realisiert und enthält selbst keine eigene Logik. Die gesamte Funktionalität wird durch den internen Konvertierungsbaustein bereitgestellt.
- Die Adapter sind vom Typ "unidirectional", d.h. die Daten- und Ereignisflüsse sind gerichtet.
- Der Baustein ist Teil der Adapter-Konvertierungsbibliothek und erleichtert die Anbindung von Komponenten mit unterschiedlichen Adapter-Datentypen.
- Die Datentypkonvertierung von DINT nach UDINT erfolgt typisiert; ein Überlauf bei negativen Werten ist zu beachten (z. B. wird -1 zu 4294967295).

## Zustandsübersicht

Der Funktionsblock besitzt keine eigene Zustandsmaschine. Sein Verhalten ergibt sich ausschließlich aus dem Zusammenspiel des internen Bausteins `F_DINT_TO_UDINT` und der Ereignisverbindungen. Der interne Baustein hat eine einfache Zustandslogik: Im Ruhezustand wartet er auf ein REQ-Ereignis, führt dann die Konvertierung aus und sendet CNF. Es gibt keine weiteren Zustände.

## Anwendungsszenarien

- **Adapterwechsel**: Wenn in einer Anwendung ein DINT-basierter Adapter (ADI) durch einen UDINT-basierten Adapter (AUDI) ersetzt werden muss, ohne die umgebende Logik zu ändern.
- **Systemintegration**: Verbindung von Komponenten, die unterschiedliche Integer-Typen verwenden (z. B. ein Sensor liefert DINT, ein Aktor erwartet UDINT).
- **Protokollanpassung**: In heterogenen Steuerungssystemen, wo Adaptertypen nicht direkt kompatibel sind.

## Vergleich mit ähnlichen Bausteinen

- **ADI_TO_AUDI** (dieser Baustein): Konvertiert DINT-Adapter zu UDINT-Adapter.
- **AUDI_TO_ADI**: Ein hypothetischer Gegenstück, das UDINT in DINT wandeln würde (existiert nicht in der gegebenen XML, aber denkbar).
- **Direkte Konvertierung mit F_DINT_TO_UDINT**: Statt den Adapter zu verwenden, könnte man den Konvertierungsbaustein direkt einsetzen, müsste dann aber die Adapterstruktur manuell nachbilden. Der ADI_TO_AUDI kapselt diese Anpassung und bietet eine saubere Schnittstelle.

## Fazit

Der Funktionsblock ADI_TO_AUDI stellt eine einfache und effektive Lösung zur Konvertierung von DINT- auf UDINT-Adapter dar. Als Composite FB nutzt er einen bewährten Standard-Konvertierungsbaustein und bietet über seine Adapter eine klare, unidirektionale Schnittstelle. Er eignet sich besonders für die Systemintegration und Adapteranpassung in IEC 61499-basierten Automatisierungslösungen.