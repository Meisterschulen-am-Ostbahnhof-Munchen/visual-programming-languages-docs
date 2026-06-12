# GET_ANY


![GET_ANY](./GET_ANY.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **GET_ANY** liest einen beliebigen Wert (Typ `ANY`) aus einer InOut-Variable und stellt diesen als gepufferten Ausgangswert bereit. Er dient dazu, den aktuellen Wert einer variablen Quelle zu einem bestimmten Zeitpunkt zu erfassen und für nachfolgende Verarbeitungsschritte zwischenzuspeichern.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ | Mit Variablen | Beschreibung |
|------|-----|---------------|--------------|
| REQ | Event | IN | Normaler Ausführungsauftrag; liest den aktuellen Wert von IN. |

### **Ereignis-Ausgänge**
| Name | Typ | Mit Variablen | Beschreibung |
|------|-----|---------------|--------------|
| CNF | Event | IN, OUT | Bestätigung nach erfolgreicher Ausführung; die Werte von IN und OUT sind dann gültig. |

### **Daten-Eingänge**
Der FB besitzt keine separaten Dateneingänge. Die Quelldaten werden über die InOut-Variable bereitgestellt.

### **Daten-Ausgänge**
| Name | Typ | Beschreibung |
|------|-----|--------------|
| OUT | ANY | Gepufferter Ausgangswert. Enthält den zum Zeitpunkt der letzten REQ-Ausführung gelesenen Wert von IN. |

### **Adapter**
Keine.

## Funktionsweise
1. Ein Ereignis an **REQ** löst den internen Algorithmus `REQ` aus.
2. Der Algorithmus führt die Zuweisung `OUT := IN` aus.
   - **IN** ist eine InOut-Variable, die sowohl gelesen als auch beschrieben werden kann – hier wird sie nur als Quelle verwendet.
   - **OUT** erhält den aktuellen Wert von **IN** und speichert ihn zwischen.
3. Nach Abschluss der Zuweisung wird das Ereignis **CNF** gesendet. Zu diesem Zeitpunkt sind sowohl **IN** (unverändert) als auch **OUT** gültig.

## Technische Besonderheiten
- Der FB nutzt eine **InOut-Variable** (`IN`) als Quelle. Dies ermöglicht den direkten Zugriff auf einen anderen Baustein-Ausgang oder eine globale Variable, ohne dass eine separate Verbindung über einen Dateneingang erforderlich ist.
- Der **Typ `ANY`** macht den Baustein generisch; er kann mit beliebigen Datentypen (z. B. INT, REAL, BOOL, STRING) verwendet werden.
- Es existiert nur ein einziger Zustand, daher ist die Ausführung deterministisch und erfolgt in einem Schritt.

## Zustandsübersicht
Der FB ist als **SimpleFB** implementiert mit genau einem Zustand:

| Zustand | Beschreibung |
|---------|--------------|
| REQ | Führt den Algorithmus `REQ` aus und sendet CNF aus. Nach der Aktion kehrt der FB in diesen Zustand zurück (default). |

Es sind keine weiteren Zustände (z. B. Warten, Fehler) definiert.

## Anwendungsszenarien
- **Wertabtastung**: Zu einem bestimmten Zeitpunkt (Ereignis) soll ein aktueller Wert eines Sensors oder einer Berechnung festgehalten werden, z. B. für eine spätere Protokollierung oder Vergleiche.
- **Signalentkopplung**: Wenn ein Ausgang mehrfach gelesen werden muss, ohne dass sich der Wert während der Bearbeitung ändert, puffert GET_ANY den Wert.
- **Typunabhängige Schnittstelle**: Als generischer Zwischenspeicher in Bibliotheken, die mit verschiedenen Datentypen arbeiten.

## Vergleich mit ähnlichen Bausteinen
- **`GET`-Bausteine** (z. B. `GET_INT`): Diese sind typspezifisch und erfordern explizite Datentypen. `GET_ANY` bietet dagegen **Typflexibilität** auf Kosten der Typsicherheit zur Entwurfszeit.
- **`MOVE`-FB**: Ein `MOVE`-Baustein kopiert typischerweise von einem Eingang auf einen Ausgang, verwendet aber keine InOut-Variable. `GET_ANY` hingegen liest direkt aus einer bestehenden Variablen, ohne dass eine separate Eingangsverbindung nötig ist.

## Fazit
`GET_ANY` ist ein einfacher, aber mächtiger Baustein zum **Zwischenspeichern eines beliebigen Werts** aus einer InOut-Quelle. Seine generische Typauslegung und die direkte Anbindung an vorhandene Variablen reduzieren den Verkabelungsaufwand und erhöhen die Flexibilität in der Steuerungslogik. Er eignet sich besonders für Anwendungen, bei denen ein Wert genau zu einem Ereigniszeitpunkt eingefroren werden muss.