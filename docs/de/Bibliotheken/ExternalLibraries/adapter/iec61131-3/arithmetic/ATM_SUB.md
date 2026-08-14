# ATM_SUB

![ATM_SUB](./ATM_SUB.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **ATM_SUB** subtrahiert zwei Zeitwerte (Typ TIME) über vollständig adapterbasierte Schnittstellen: `IN2` wird von `IN1` abgezogen, das Ergebnis wird nur bei tatsächlicher Wertänderung auf den Ausgangsadapter geschrieben. Im Gegensatz zu den generischen `ATM_ADD_*`-Bausteinen ist ATM_SUB als handverdrahtetes Composite-FB realisiert, das die Änderungserkennung explizit über eigene Bausteine abbildet.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine – die Auslösung erfolgt ausschließlich über die Adapter-Sockets `IN1`/`IN2`.

### **Ereignis-Ausgänge**

Keine expliziten Ereignisausgänge in der Interface-Liste. Das Ergebnis wird über den Adapter-Ausgang **OUT** bereitgestellt, dessen Ereignis (E1) nur bei tatsächlicher Wertänderung gesendet wird.

### **Daten-Eingänge**

Keine direkten Daten-Eingänge.

### **Daten-Ausgänge**

Keine direkten Daten-Ausgänge. Das Subtraktionsergebnis wird über den Adapter-Ausgang **OUT** als Datenwert (D1) ausgegeben.

### **Adapter**

- **IN1** (Adapter, Typ `adapter::types::unidirectional::ATM`): Minuend.
- **IN2** (Adapter, Typ `adapter::types::unidirectional::ATM`): Subtrahend.
- **OUT** (Adapter, Typ `adapter::types::unidirectional::ATM`): Ergebnis von `IN1 - IN2`.

## Funktionsweise

Ein Ereignis an **IN1.E1** oder **IN2.E1** löst intern den Baustein **F_SUB** (Typ `iec61131::arithmetic::F_SUB`) aus, der `IN1.D1 - IN2.D1` berechnet. Das Ergebnis läuft anschließend über **F_MOVE** (Typ `iec61131::selection::F_MOVE`, mit `DataType="TIME"` fest verdrahtet) auf einen **E_D_FF_ANY**-Baustein (Typ `iec61499::events::E_D_FF_ANY`). Dieser vergleicht den neuen Wert mit dem zuletzt gespeicherten und lässt das Ereignis an **OUT.E1** nur dann durch, wenn sich der Wert tatsächlich geändert hat – der neue Wert wird in jedem Fall an **OUT.D1** übernommen.

## Technische Besonderheiten

- **Explizite Änderungserkennung als Composite-Struktur:** Anders als bei den generischen `GEN_ATM_*`-Bausteinen, die die Änderungserkennung in C++ implementieren, bildet ATM_SUB sie über die Kombination `F_SUB → F_MOVE → E_D_FF_ANY` innerhalb des FBNetworks ab.
- **F_MOVE als Typanker:** Der `F_MOVE`-Baustein trägt das Attribut `DataType="TIME"`, wodurch der generische `ANY`-Datenpfad auf `TIME` festgelegt wird, bevor er dem `E_D_FF_ANY` zugeführt wird.
- **Vollständig adapterbasiert:** Beide Operanden und das Ergebnis sind als `ATM`-Adapter ausgeführt, es gibt keine klassischen Daten-Ein-/Ausgänge.

## Zustandsübersicht

Der Baustein hält implizit den zuletzt ausgegebenen Wert im internen `E_D_FF_ANY`-Speicher:

- **Warten** auf ein Ereignis an IN1.E1 oder IN2.E1
- **Berechnen** von IN1 − IN2 über F_SUB
- **Vergleichen** mit dem gespeicherten Wert in E_D_FF_ANY
- **Ausgeben**: OUT.D1 wird immer aktualisiert, OUT.E1 nur bei tatsächlicher Änderung gesendet

## Anwendungsszenarien

- Berechnung von Restlaufzeiten oder Differenzen zwischen zwei Zeitwerten, z. B. Soll- minus Ist-Zeit.
- Reduktion nachgeschalteter Event-Last, wenn sich das Ergebnis über mehrere Zyklen hinweg nicht ändert.

## Vergleich mit ähnlichen Bausteinen

- **ATM_ADD_2/3/4:** Addieren statt zu subtrahieren; als generische `GEN_ATM_ADD`-Bausteine implementiert (Änderungserkennung in C++, nicht als sichtbares FBNetwork).
- **F_SUB:** Der direkte, adapterfreie Subtraktionsbaustein ohne eigene Änderungserkennung, den ATM_SUB intern verwendet.

## Fazit

`ATM_SUB` liefert eine vollständig adapterbasierte Subtraktion zweier Zeitwerte mit expliziter, im FBNetwork sichtbarer Änderungserkennung. Er eignet sich besonders dort, wo Differenzbildung zwischen Zeitwerten benötigt wird und unnötige Folge-Events bei unverändertem Ergebnis vermieden werden sollen.
