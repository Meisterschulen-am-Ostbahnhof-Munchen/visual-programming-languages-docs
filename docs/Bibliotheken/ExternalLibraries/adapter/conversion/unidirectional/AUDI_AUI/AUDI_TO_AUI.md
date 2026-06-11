# AUDI_TO_AUI


![AUDI_TO_AUI](./AUDI_TO_AUI.svg)

*Kein Bild vorhanden.*

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AUDI_TO_AUI` ist ein Composite‑Baustein, der einen AUDI‑Adapter (Datentyp UDINT) in einen AUI‑Adapter (Datentyp UINT) umwandelt. Er dient als einfache Schnittstellenanpassung zwischen Komponenten, die unterschiedliche ganzzahlige Datentypen für ihre unidirektionalen Adapter verwenden. Der Baustein kapselt die Konvertierung und ermöglicht eine nahtlose Integration in IEC 61499‑Netzwerke.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der FB besitzt keinen direkten Ereignis-Eingang auf der oberen Ebene. Ereignisse werden über den Socket `AUDI_IN` empfangen:
- **E1** – Auslöser für die Konvertierung eines neuen Datenwerts.

### **Ereignis-Ausgänge**
Der FB besitzt keinen direkten Ereignis-Ausgang auf der oberen Ebene. Ereignisse werden über den Plug `AUI_OUT` gesendet:
- **E1** – Bestätigung, dass der konvertierte Wert am Ausgang anliegt.

### **Daten-Eingänge**
Der FB besitzt keinen direkten Daten-Eingang auf der oberen Ebene. Daten werden über den Socket `AUDI_IN` empfangen:
- **D1** (`UDINT`) – Der umzuwandelnde Eingangswert.

### **Daten-Ausgänge**
Der FB besitzt keinen direkten Daten-Ausgang auf der oberen Ebene. Daten werden über den Plug `AUI_OUT` ausgegeben:
- **D1** (`UINT`) – Der konvertierte Ausgangswert.

### **Adapter**
- **Socket `AUDI_IN`** – Unidirektionaler Eingangsadapter vom Typ `adapter::types::unidirectional::AUDI`. Er liefert ein Ereignis `E1` und einen Datenwert `D1` (Typ `UDINT`).
- **Plug `AUI_OUT`** – Unidirektionaler Ausgangsadapter vom Typ `adapter::types::unidirectional::AUI`. Er erwartet ein Ereignis `E1` und gibt einen Datenwert `D1` (Typ `UINT`) aus.

## Funktionsweise
Der Baustein ist als Composite realisiert und enthält intern den Funktionsblock `iec61131::conversion::F_UDINT_TO_UINT`. Die Ablaufsteuerung erfolgt ereignisgesteuert:

1. Ein Ereignis am Socket `AUDI_IN.E1` triggert den Eingang `REQ` des internen Konvertierungsbausteins.
2. Gleichzeitig wird der Datenwert `AUDI_IN.D1` an den Eingang `IN` des Konverters übergeben.
3. Der Konverter führt die Wandlung von `UDINT` nach `UINT` durch.
4. Nach Abschluss sendet der Konverter ein Ereignis an seinem Ausgang `CNF`, welches auf den Plug `AUI_OUT.E1` weitergeleitet wird.
5. Der konvertierte Wert am Ausgang `OUT` des Konverters wird auf den Datenausgang `AUI_OUT.D1` gelegt.

Die gesamte Konvertierung erfolgt innerhalb eines einzigen Ereignisdurchlaufs (synchron).

## Technische Besonderheiten
- **Composite‑Architektur:** Der FB ist als Composite entworfen, d. h. seine Funktionalität wird vollständig durch das interne Netzwerk bestimmt. Dies erleichtert die Wiederverwendung und Anpassung.
- **Standard‑Konvertierungsbaustein:** Die eigentliche Typumwandlung verwendet den IEC 61131‑Baustein `F_UDINT_TO_UINT`, der eine plattformunabhängige und getestete Implementierung bereitstellt.
- **Lizenz:** Der Baustein steht unter der Eclipse Public License 2.0 (EPL‑2.0).
- **Version:** 1.0, erstellt am 17.02.2026.

## Zustandsübersicht
Der FB besitzt keine eigenen Zustände. Da das Composite‑Netzwerk nur aus einem einzigen funktionalen Baustein besteht, der seinerseits zustandslos arbeitet, verhält sich `AUDI_TO_AUI` ebenfalls zustandslos. Jeder Ereignisimpuls führt sofort zu einer einmaligen Konvertierung.

## Anwendungsszenarien
- **Anbindung von Sensoren/Aktoren:** Ein Sensor liefert Werte als `UDINT` über einen AUDI‑Adapter, während die nachfolgende Verarbeitungskette `UINT` über AUI erwartet.
- **Systemintegration:** In heterogenen Automatisierungssystemen treten häufig unterschiedliche Datentypen auf. Der Baustein dient als Adapter, um Komponenten verschiedener Hersteller oder Bibliotheken zu verbinden.
- **Prototypenentwicklung:** Einfache und schnelle Anpassung von Schnittstellen ohne manuelle Konvertierungslogik.

## Vergleich mit ähnlichen Bausteinen
- **`AUDI_TO_XXX`‑Bausteine:** Es existieren analoge Bausteine für andere Zieltypen (z. B. `AUDI_TO_DINT`, `AUDI_TO_SINT`). `AUDI_TO_AUI` ist spezifisch für die Umwandlung nach `UINT`.
- **Direkte Adapter‑Kopplung:** Ohne Konvertierungsbaustein müsste die Typumwandlung in der Applikation selbst oder durch einen generischen Funktionsbaustein erfolgen. `AUDI_TO_AUI` bietet eine gekapselte, wiederverwendbare Lösung.

## Fazit
Der `AUDI_TO_AUI`‑Funktionsblock stellt eine kompakte und zuverlässige Möglichkeit dar, zwischen zwei unidirektionalen Adaptern mit unterschiedlichen Datentypen zu vermitteln. Durch die Composite‑Struktur und die Nutzung eines standardisierten Konvertierungsbausteins ist er wartungsarm und einfach in bestehende IEC 61499‑Projekte integrierbar.