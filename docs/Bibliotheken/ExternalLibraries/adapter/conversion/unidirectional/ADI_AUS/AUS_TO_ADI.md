# AUS_TO_ADI


![AUS_TO_ADI](./AUS_TO_ADI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein AUS_TO_ADI ist ein zusammengesetzter (Composite) Funktionsbaustein, der eine unidirektionale Adapter-Konvertierung von `AUS` (Daten vom Typ `USINT`) nach `ADI` (Daten vom Typ `DINT`) realisiert. Er kapselt einen IEC 61131‑Konvertierungsbaustein und ermöglicht so eine saubere Trennung von Adaptertypen in der 4diac-IDE.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine separaten Ereignis-Eingänge vorhanden. Die Ereignissteuerung erfolgt über den Socket‑Adapter `AUS_IN` (siehe Abschnitt **Adapter**).

### **Ereignis-Ausgänge**
Keine separaten Ereignis-Ausgänge vorhanden. Die Ereignisweiterleitung erfolgt über den Plug‑Adapter `ADI_OUT` (siehe Abschnitt **Adapter**).

### **Daten-Eingänge**
Keine separaten Daten-Eingänge vorhanden. Die Daten werden über den Socket‑Adapter `AUS_IN` bereitgestellt.

### **Daten-Ausgänge**
Keine separaten Daten-Ausgänge vorhanden. Die konvertierten Daten werden über den Plug‑Adapter `ADI_OUT` ausgegeben.

### **Adapter**

| Name | Richtung | Typ | Beschreibung |
|------|----------|-----|--------------|
| `AUS_IN` | Socket (Eingang) | `adapter::types::unidirectional::AUS` | Unidirektionaler Adapter‑Eingang, der einen `USINT`‑Wert (und ein zugehöriges Ereignis) bereitstellt. |
| `ADI_OUT` | Plug (Ausgang) | `adapter::types::unidirectional::ADI` | Unidirektionaler Adapter‑Ausgang, der den konvertierten `DINT`‑Wert (und ein zugehöriges Ereignis) ausgibt. |

## Funktionsweise
Der Baustein arbeitet ereignisgesteuert:
1. Ein eingehendes Ereignis am Socket `AUS_IN.E1` triggert den internen Konvertierungsbaustein `Convert` (Typ `F_USINT_TO_DINT`).
2. Der Konvertierungsbaustein liest den Datenwert `AUS_IN.D1` (`USINT`) und wandelt ihn in einen `DINT`‑Wert um.
3. Nach Abschluss der Konvertierung wird ein Ereignis am Ausgang `Convert.CNF` erzeugt.
4. Dieses Ereignis wird auf den Plug‑Adapter `ADI_OUT.E1` weitergeleitet, und der konvertierte Wert wird über `ADI_OUT.D1` ausgegeben.

Die gesamte Logik ist als Datenfluss im enthaltenen FBNetzwerk abgebildet – es wird keine Zustandsmaschinenlogik innerhalb des Composite‑Bausteins verwendet.

## Technische Besonderheiten
- Der Baustein verwendet den IEC 61131‑Baustein `F_USINT_TO_DINT` (Typkonvertierung vorzeichenloser 8‑Bit zu vorzeichenbehaftetem 32‑Bit Integer).
- Es handelt sich um einen reinen **Composite‑Baustein** – das Verhalten wird vollständig durch das interne FBNetzwerk definiert.
- Die Adapter sind **unidirektional** ausgelegt: Daten fließen nur vom Socket zum Plug.
- Durch die Kapselung der Konvertierung in einen eigenen Baustein können unterschiedliche Adaptertypen zusammengeschaltet werden, ohne dass die umgebende Applikation die Typen konvertieren muss.

## Zustandsübersicht
Der Baustein besitzt keine eigene Zustandsmaschine. Das Verhalten wird direkt durch den inneren Konvertierungsbaustein und die Ereignisverbindungen gesteuert. Eine Fehlerbehandlung (z. B. Bereichsüberschreitung bei der Konvertierung) ist nicht explizit implementiert und müsste entweder im aufrufenden Kontext oder durch Erweiterung des Bausteins ergänzt werden.

## Anwendungsszenarien
- **Adapter‑Brücke**: Austausch von Daten zwischen Komponenten, die unterschiedliche Adaptertypen verwenden (z. B. Sensoren mit `USINT`‑Werten und Steuerungen, die `DINT`‑Werte erwarten).
- **Datenintegration**: Einbindung von Bausteinen aus IEC 61131‑Bibliotheken in eine 4diac‑Anwendung, die auf Adaptern basiert.
- **Typanpassung**: Schnelle Umwandlung von Datentypen in der Adapter‑Ebene, ohne die Logik der angeschlossenen Bausteine ändern zu müssen.

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu einem direkten Einsatz des Konvertierungsbausteins `F_USINT_TO_DINT` bietet `AUS_TO_ADI` eine **adapter‑orientierte Schnittstelle**. Dadurch wird die Konvertierung vollständig transparent für den Anwender, der nur mit den Adaptern arbeitet.
- Ähnliche Adapter‑Konvertierungen könnten für andere Datentypen existieren (z. B. `BOOL_TO_ADI`, `INT_TO_ADI`). Der vorliegende Baustein ist speziell für die Umwandlung von `USINT` nach `DINT` ausgelegt.

## Fazit
Der Composite‑Baustein `AUS_TO_ADI` bietet eine einfache und saubere Möglichkeit, einen `AUS`-Adapter (USINT‑basiert) in einen `ADI`-Adapter (DINT‑basiert) zu konvertieren. Durch die interne Nutzung des IEC 61131‑Konvertierungsbausteins ist die Umsetzung standardkonform und wiederverwendbar. Der Baustein eignet sich besonders für modulare Anwendungen, bei denen unterschiedliche Adaptertypen harmonisiert werden müssen.