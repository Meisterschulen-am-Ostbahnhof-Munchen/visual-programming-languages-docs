# ADI_TO_AD


![ADI_TO_AD](./ADI_TO_AD.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ADI_TO_AD** ist ein Composite-Baustein (zusammengesetzter FB), der eine Schnittstellenkonvertierung von einem **ADI**-Adapter (DINT-basiert) zu einem **AD**-Adapter (DWORD-basiert) realisiert. Er fungiert als unidirektionaler Wandler und ermöglicht die nahtlose Integration von Komponenten mit unterschiedlichen Datenadapter-Typen in der 4diac-IDE.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Der FB besitzt keine eigenständigen Ereignis-Eingänge auf Ebene der Schnittstelle. Die Ereignissteuerung erfolgt ausschließlich über den angeschlossenen **Socket-Adapter ADI_IN**:
- **ADI_IN.E1** – Ereignis, das die Datenkonvertierung anstößt.

### **Ereignis-Ausgänge**
Auch auf dieser Ebene gibt es keine separaten Ereignis-Ausgänge. Der Ausgang wird über den **Plug-Adapter AD_OUT** bereitgestellt:
- **AD_OUT.E1** – Ereignis, das nach erfolgreicher Konvertierung ausgelöst wird.

### **Daten-Eingänge**
- **ADI_IN.D1** – Eingabe des zu konvertierenden DINT-Werts (Quelladapter).

### **Daten-Ausgänge**
- **AD_OUT.D1** – Ausgabe des konvertierten DWORD-Werts (Zieladapter).

### **Adapter**
- **ADI_IN** (Socket) – vom Typ `adapter::types::unidirectional::ADI` (DINT-Daten).
- **AD_OUT** (Plug) – vom Typ `adapter::types::unidirectional::AD` (DWORD-Daten).

Beide Adapter sind unidirektional ausgelegt (je ein Ereignis- und ein Datenkanal).

## Funktionsweise
Der FB enthält einen internen Baustein `F_DINT_TO_DWORD` aus der IEC 61131-Bibliothek, der die eigentliche Typumwandlung vornimmt. Die Ablaufsteuerung ist wie folgt:
1. Ein eingehendes Ereignis am **ADI_IN.E1** triggert den **Convert.REQ**-Eingang des internen Konverters.
2. Der Konverter wandelt den über **ADI_IN.D1** anliegenden DINT-Wert in einen DWORD-Wert um.
3. Nach Abschluss der Konvertierung signalisiert **Convert.CNF** den erfolgreichen Abschluss und feuert das Ereignis am **AD_OUT.E1**, gleichzeitig wird der konvertierte Wert an **AD_OUT.D1** ausgegeben.

Damit wird eine transparente, ereignisgesteuerte Konvertierung zwischen den Adaptertypen realisiert.

## Technische Besonderheiten
- **Typkonvertierung**: Die eigentliche Umwandlung erfolgt über den standardisierten IEC 61131-Baustein `F_DINT_TO_DWORD`, der eine bitidentische Übertragung des Integer-Werts in den DWORD-Raum sicherstellt (keine logische Interpretation, nur Typanpassung).
- **Unidirektionalität**: Der FB ist strikt unidirektional aufgebaut und erwartet genau einen Eingangs- und einen Ausgangsadapter. Eine Rückwärtskonvertierung ist nicht vorgesehen.
- **Paketstruktur**: Der FB ist im Paket `adapter::conversion::unidirectional` organisiert und importiert die entsprechende IEC-Bibliothek.

## Zustandsübersicht
Als Composite-Baustein besitzt **ADI_TO_AD** keine eigenen expliziten Zustände. Sein Verhalten wird vollständig durch den inneren Konverter bestimmt:
- **Idle**: Wartet auf ein Ereignis am ADI_IN.
- **Umwandlung aktiv**: Wenn `Convert.REQ` gesetzt ist.
- **Abschluss**: Nach `Convert.CNF` wird das Ergebnis am Ausgang bereitgestellt.

## Anwendungsszenarien
- **Schnittstellenanpassung**: Wenn eine Komponente einen DINT-Adapter bereitstellt, aber ein nachgeschaltetes Modul einen DWORD-Adapter erwartet (z. B. bei der Integration von Steuerungen mit unterschiedlichen Datenbreiten).
- **Systemmodernisierung**: Alte DINT-basierte Sensoren oder Aktoren (über ADI) sollen mit neuen DWORD-fähigen Bussystemen (über AD) verbunden werden.
- **Prototypische Entwicklung**: Schnelles Umschalten zwischen Adaptervarianten ohne Änderung der Applikationslogik.

## Vergleich mit ähnlichen Bausteinen
- **Direkte Konverter-FBs**: Im Gegensatz zu reinen Typkonvertern (wie `F_DINT_TO_DWORD`) arbeitet **ADI_TO_AD** auf Adapterebene und integriert die Ereignissteuerung sowie die Schnittstellenanpassung in einem Baustein.
- **Bidirektionale Adapter**: Es existieren auch Bausteine, die eine Konvertierung in beide Richtungen anbieten (z. B. ADI_TO_AD und AD_TO_ADI kombiniert). Der vorliegende FB ist auf die eine Richtung spezialisiert und daher schlanker.
- **Manuelle Verkabelung**: Ohne diesen FB müsste man die Adapter intern manuell verschalten und die Ereignissignale separat führen – der Composite-Baustein kapselt diese Komplexität.

## Fazit
Der **ADI_TO_AD**-Funktionsblock ist ein nützlicher und übersichtlicher Composite-Baustein zur einfachen Anpassung zwischen DINT- und DWORD-basierten Adaptern. Er reduziert den manuellen Verschaltungsaufwand, nutzt bewährte IEC-Konvertierungslogik und fügt sich nahtlos in unidirektionale Datenflüsse ein. Ideal für Entwickler, die schnell und sauber zwischen Adaptertypen wechseln müssen, ohne tief in die interne Signalverarbeitung eingreifen zu wollen.