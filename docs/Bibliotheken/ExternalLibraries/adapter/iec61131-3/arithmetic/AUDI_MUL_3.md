# AUDI_MUL_3


![AUDI_MUL_3](./AUDI_MUL_3.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUDI_MUL_3** ist ein generischer Baustein zur Multiplikation von drei Eingangswerten. Die Werte werden über unidirektionale Adapter vom Typ **AUDI** bereitgestellt und das Ergebnis über einen gleichartigen Adapter ausgegeben. Der Baustein ist für den Einsatz in IEC 61499‑basierten Steuerungssystemen konzipiert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Nicht vorhanden – die gesamte Datenübertragung erfolgt adapterbasiert ohne explizite Ereignissteuerung.

### **Ereignis-Ausgänge**
Nicht vorhanden.

### **Daten-Eingänge**
Nicht vorhanden – die Eingangswerte werden über die **Sockets IN1, IN2 und IN3** als Adapter bereitgestellt.

### **Daten-Ausgänge**
Nicht vorhanden – das Ergebnis wird über den **Plug OUT** als Adapter ausgegeben.

### **Adapter**

| Name | Richtung | Typ | Beschreibung |
|------|----------|-----|--------------|
| **IN1** | Socket (Eingang) | `adapter::types::unidirectional::AUDI` | Erster Multiplikationsfaktor. |
| **IN2** | Socket (Eingang) | `adapter::types::unidirectional::AUDI` | Zweiter Multiplikationsfaktor. |
| **IN3** | Socket (Eingang) | `adapter::types::unidirectional::AUDI` | Dritter Multiplikationsfaktor. |
| **OUT** | Plug (Ausgang) | `adapter::types::unidirectional::AUDI` | Ergebnis der Multiplikation `IN1 * IN2 * IN3`. |

## Funktionsweise
Der FB **AUDI_MUL_3** führt eine arithmetische Multiplikation der drei über die Adapter **IN1, IN2 und IN3** bereitgestellten Werte durch. Das Produkt wird kontinuierlich berechnet und über den Adapter **OUT** zur Verfügung gestellt. Der zugrundeliegende Datentyp **AUDI** ist generisch definiert (über das Attribut `eclipse4diac::core::GenericClassName`) und kann zur Konfigurationszeit durch einen konkreten numerischen Typ (z. B. INT, REAL) ersetzt werden. Eine explizite Triggerung durch Ereignisse ist nicht erforderlich, da die Adapter die Datenübertragung eigenständig abwickeln.

## Technische Besonderheiten
- **Generischer Datentyp**: Der FB ist als generischer Baustein (`GenericClassName = 'GEN_AUDI_MUL'`) ausgelegt. Der verwendete Adaptertyp **AUDI** kann durch einen beliebigen numerischen Datentyp ersetzt werden, solange der gleiche Typ an allen Adaptern verwendet wird.
- **Adapterbasiertes Interface**: Statt diskreter Daten‑ und Ereignisports kommuniziert der FB ausschließlich über unidirektionale Adapter. Dies ermöglicht eine flexible Verkettung mit anderen Bausteinen desselben Adaptertyps.
- **Keine Explizite Zustandslogik**: Der FB benötigt keinen inneren Zustandsautomaten – die Multiplikation erfolgt rein datenflussgesteuert.

## Zustandsübersicht
Der **AUDI_MUL_3** besitzt keinen expliziten Zustandsautomaten. Die Ausgabe **OUT** entspricht stets dem aktuellen Produkt der drei Eingänge. Sobald an allen Sockets gültige Daten anliegen, wird das Ergebnis ohne Verzögerung berechnet.

## Anwendungsszenarien
- **Mehrdimensionale Berechnungen**: Kombination mehrerer physikalischer Größen, die multipliziert werden müssen (z. B. Volumen aus Länge, Breite, Höhe).
- **Skalierung von Signalen**: Multiplikation eines Sensorwerts mit zwei Kalibrierungsfaktoren.
- **Verschachtelte Arithmetik**: Einsatz als Teil einer größeren Berechnungskette, bei der das Produkt dreier Eingänge benötigt wird.

## Vergleich mit ähnlichen Bausteinen
- **AUDI_MUL_2**: Führt die Multiplikation von nur zwei Eingängen durch. Der **AUDI_MUL_3** erweitert diese Funktionalität auf drei Faktoren.
- **AUDI_ADD_3**: Führt eine Addition dreier Werte durch, während der **AUDI_MUL_3** eine Multiplikation realisiert – beide nutzen die gleiche Adapterstruktur.
- **Konventionelle IEC 61499-Bausteine**: Übliche Multifunktionsblöcke verwenden oft separate Daten‑ und Ereignisports. Der adapterbasierte Ansatz vereinfacht die Typisierung und Wiederverwendbarkeit in generischen Frameworks.

## Fazit
Der **AUDI_MUL_3** ist ein kompakter, generischer Funktionsblock zur Multiplikation von drei Werten. Durch die adaptergesteuerte Schnittstelle und die generische Typisierung eignet er sich hervorragend für modulare, wiederverwendbare Steuerungsapplikationen. Die einfache datenflussorientierte Arbeitsweise ohne Zustandsautomaten macht ihn intuitiv einsetzbar und erweiterbar.