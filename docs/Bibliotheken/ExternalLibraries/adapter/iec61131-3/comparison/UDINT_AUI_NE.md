# UDINT_AUI_NE


![UDINT_AUI_NE](./UDINT_AUI_NE.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein **UDINT_AUI_NE** realisiert den Vergleich zweier Werte auf Ungleichheit („not equal“). Er ist als standardisierte Vergleichsfunktion nach IEC 61131-3 klassifiziert und nutzt Adapter-Schnittstellen für den zweiten Eingang und das Ergebnis. Der Baustein ist asynchron ereignisgesteuert: Ein anliegendes Ereignis am Eingang **REQ** löst den Vergleich aus, das Ergebnis wird über den Ausgangsadapter ausgegeben.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ   | Kommentar         |
|------|-------|-------------------|
| REQ  | Event | Service Request   |

- **REQ**: Startet den Vergleich. Der Eingang **IN1** wird mit dem Wert von **IN2** verglichen. Der Baustein erwartet, dass vor dem Auslösen des Ereignisses der entsprechende Datenwert an **IN1** und der zweite Wert über den Adapter **IN2** anliegen.

### **Ereignis-Ausgänge**

Der Baustein besitzt keine eigenständigen Ereignis-Ausgänge. Das Ergebnis wird über den Adapter **OUT** signalisiert (siehe Abschnitt **Adapter**).

### **Daten-Eingänge**

| Name | Typ              | Kommentar                |
|------|------------------|--------------------------|
| IN1  | ANY_ELEMENTARY   | Eingangswert 1           |

- **IN1**: Erster zu vergleichender Wert. Der Datentyp ist generisch (`ANY_ELEMENTARY`), sodass elementare Typen wie BOOL, INT, REAL, UDINT usw. verwendet werden können.

### **Daten-Ausgänge**

Der Baustein besitzt keine eigenständigen Daten-Ausgänge. Das Vergleichsergebnis wird über den Adapter **OUT** ausgegeben.

### **Adapter**

| Richtung | Name | Typ der Adapter-Schnittstelle                   | Kommentar                     |
|----------|------|------------------------------------------------|-------------------------------|
| Socket   | IN2  | `adapter::types::unidirectional::AUI`          | Eingangswert 2                |
| Plug     | OUT  | `adapter::types::unidirectional::AX`           | value 1 != value2 = true      |

- **IN2** (Socket): Empfängt den zweiten Vergleichswert über einen unidirektionalen Adapter vom Typ `AUI`. Der angeschlossene Adapter muss einen elementaren Wert bereitstellen.
- **OUT** (Plug): Gibt das boolesche Ergebnis des Vergleichs aus. Der Adapter vom Typ `AX` signalisiert `true`, wenn `IN1 != Wert von IN2`, andernfalls `false`.

## Funktionsweise

Der Baustein arbeitet intern mit dem vordefinierten Funktionsbaustein **F_NE** (aus der Bibliothek `iec61131::comparison`). Der Ablauf ist:

1. Ein Ereignis am Eingang **REQ** aktiviert den Vergleich. Gleichzeitig muss der Wert an **IN1** anliegen.
2. Über den Socket **IN2** wird der zweite Wert bereitgestellt. Der interne FB **F_NE** erhält ein Ereignis von **IN2.E1** sowie von **REQ** (beide Event-Quellen sind auf **F_NE.REQ** verschaltet).
3. **F_NE** vergleicht die beiden Datenwerte (**IN1** und **IN2.D1**) und liefert das Ergebnis an seinem Ausgang **OUT** (boolesch).
4. Das Ausgangsereignis **F_NE.CNF** wird an den Plug **OUT.E1** weitergeleitet. Die Ausgangsdaten (**OUT.D1**) enthalten das Vergleichsergebnis.

Somit wird nach jedem **REQ**-Ereignis (oder einem Ereignis von **IN2**) das Ergebnis am Adapter **OUT** aktualisiert.

## Technische Besonderheiten

- **Generische Datentypen:** Der Eingang **IN1** ist als `ANY_ELEMENTARY` deklariert, sodass der Baustein mit allen elementaren Datentypen kompatibel ist. Der zweite Eingang wird über den Adapter **IN2** bereitgestellt – auch dieser muss demselben elementaren Typ entsprechen.
- **Adapter-Schnittstellen:** Der Baustein verwendet ausschließlich Adapter für die zweite Eingangsgröße und die Ausgabe. Dies ermöglicht eine modulare, typsichere Verbindung in der 4diac-IDE.
- **Asynchrone Ereignissteuerung:** Der Vergleich wird durch Ereignisse angestoßen. Das Ergebnis wird ereignisgesteuert über den Adapter ausgegeben – es liegt kein kontinuierlicher Datenausgang vor.
- **Interne Standard-Implementierung:** Der Baustein nutzt den IEC-61131-3-konformen Vergleichsbaustein **F_NE**, was die Korrektheit und Standardkonformität gewährleistet.

## Zustandsübersicht

Der Baustein besitzt keinen expliziten Zustandsautomaten. Sein Verhalten kann wie folgt beschrieben werden:

- **Ruhezustand:** Es liegt kein Ereignis an **REQ** oder **IN2** an.
- **Vergleich aktiv:** Sobald ein Ereignis an **REQ** empfangen wird, startet der interne FB **F_NE** den Vergleich. Das Ergebnis wird nach einer kurzen Verarbeitungszeit am Ausgangsadapter **OUT** ausgegeben.
- **Ergebnis bereit:** Der Ausgang **OUT** liefert `true` oder `false` und wird durch das Ereignis **OUT.E1** quittiert.

Der Baustein ist ready für den nächsten Vergleich, sobald das Ergebnis ausgegeben wurde.

## Anwendungsszenarien

- **Ungleichheitsprüfung in Steuerungsabläufen:** Überwachung, ob zwei Messwerte (z. B. Temperatur, Druck) voneinander abweichen.
- **Zustandsvergleich:** Prüfen, ob ein Sollwert von einem Istwert abweicht, um Schalt- oder Alarmfunktionen auszulösen.
- **Datenvalidierung:** Vergleich von Eingangsdaten aus verschiedenen Quellen auf Unterschiedlichkeit.

## Vergleich mit ähnlichen Bausteinen

- **F_E (Equal) / UDINT_AUI_EQ:** Führt einen Gleichheitsvergleich durch. Der Unterschied liegt im invertierten Ergebnis.
- **F_LT, F_GT:** Führen Kleiner- bzw. Größer-Vergleiche durch, die jedoch andere logische Ergebnisse liefern.
- **Eigene Implementierung ohne Adapter:** Vergleichsbausteine ohne Adapter verwenden direkte Dateneingänge; der **UDINT_AUI_NE** ist speziell für den Einsatz in adapterbasierten Architekturen konzipiert.

## Fazit

Der Funktionsbaustein **UDINT_AUI_NE** ist ein standardkonformer, ereignisgesteuerter Ungleichheitsvergleich für elementare Datentypen. Seine Besonderheit liegt in der Verwendung von Adapter-Schnittstellen für den zweiten Eingang und das Ergebnis, was eine flexible und typsichere Einbindung in modulare 4diac- Netzwerke ermöglicht. Er eignet sich ideal für Anwendungen, bei denen auf Ungleichheit zweier Werte reagiert werden muss.