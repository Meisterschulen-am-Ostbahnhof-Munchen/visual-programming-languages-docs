# AR_TO_AUS


![AR_TO_AUS](./AR_TO_AUS.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock AR_TO_AUS ist ein Composite-Baustein zur Umwandlung eines REAL-Wertes in einen USINT-Wert über eine unidirektionale Adapterschnittstelle. Er kapselt den Konvertierungsprozess und stellt eine einheitliche Verbindung zwischen einem REAL-Adaptersocket und einem USINT-Adapterplug bereit. Der FB ist für den Einsatz in Automatisierungssystemen konzipiert, die eine Datentypanpassung erfordern.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **AR_IN.E1** (über Socket `AR_IN`): Ereignis zum Starten der Konvertierung des anliegenden REAL-Wertes.

### **Ereignis-Ausgänge**
- **AUS_OUT.E1** (über Plug `AUS_OUT`): Ereignis, das nach erfolgreicher Konvertierung und Ausgabe des USINT-Wertes ausgelöst wird.

### **Daten-Eingänge**
- **AR_IN.D1** (über Socket `AR_IN`, Typ: REAL): Eingangswert, der in USINT konvertiert werden soll.

### **Daten-Ausgänge**
- **AUS_OUT.D1** (über Plug `AUS_OUT`, Typ: USINT): Konvertierter Ausgangswert.

### **Adapter**
- **Socket AR_IN** (Typ: `adapter::types::unidirectional::AR`): Unidirektionaler REAL-Eingangsadapter.
- **Plug AUS_OUT** (Typ: `adapter::types::unidirectional::AUS`): Unidirektionaler USINT-Ausgangsadapter.

## Funktionsweise

Der FB AR_TO_AUS arbeitet als reiner Datenkonverter ohne eigene Zustandslogik. Intern wird der vordefinierte Baustein `F_REAL_TO_USINT` aus der IEC-61131-Standardbibliothek verwendet.

Ablauf:
1. Ein eingehendes Ereignis an `AR_IN.E1` triggert die Verarbeitung.
2. Der aktuelle Wert von `AR_IN.D1` (REAL) wird an den Eingang `IN` des internen Konverters übergeben.
3. Nach Abschluss der Konvertierung wird der Ergebniswert (USINT) an `AUS_OUT.D1` weitergeleitet.
4. Gleichzeitig wird das Ereignis `AUS_OUT.E1` ausgelöst, um nachgeschaltete Bausteine zu aktivieren.

Der gesamte Daten- und Ereignisfluss ist unidirektional vom Eingangs- zum Ausgangsadapter.

## Technische Besonderheiten

- Der FB ist als Composite implementiert und verwendet den Baustein `iec61131::conversion::F_REAL_TO_USINT` aus der Bibliothek `adapter::conversion::unidirectional`.
- Es findet keine Wertebereichsprüfung statt; die Konvertierung folgt den Regeln der IEC 61131 (REAL → USINT: Nachkommastellen werden abgeschnitten, Werte außerhalb des Bereichs 0…255 können zu undefiniertem Verhalten führen).
- Der FB besitzt keine eigene Zustandsmaschine und arbeitet ereignisgesteuert.
- Der Einsatz von Adaptern ermöglicht eine lose Kopplung der Schnittstellen und erleichtert die Wiederverwendung in verschiedenen Projektkontexten.

## Zustandsübersicht

Der FB AR_TO_AUS besitzt keinen eigenen Zustandsautomaten. Das Laufzeitverhalten wird vollständig durch den internen Funktionsbaustein `F_REAL_TO_USINT` bestimmt, der standardmäßig zustandslos arbeitet. Die Ereignissteuerung erfolgt direkt von `AR_IN.E1` zu `AUS_OUT.E1` ohne Zwischenzustände.

## Anwendungsszenarien

- **Sensor-Aktor-Kopplung**: Ein REAL-Wert (z. B. von einem analogen Sensor) muss als USINT an einen binären Aktor (z. B. Motorsteuerung mit 8‑Bit‑Wert) weitergegeben werden.
- **Schnittstellenanpassung**: Wenn ein Adapter vom Typ `AR` (REAL) mit einem Adapter vom Typ `AUS` (USINT) verbunden werden muss.
- **Datenvorverarbeitung**: Vor der Übergabe an Systeme, die nur USINT-Werte akzeptieren (z. B. Diagnose- oder Visualisierungskomponenten).

## Vergleich mit ähnlichen Bausteinen

- **AR_TO_INT** / **AR_TO_BYTE**: Analoger Aufbau für die Konvertierung in andere Datentypen (INT, BYTE). Der vorliegende FB beschränkt sich auf die Wandlung von REAL in USINT.
- **Direkte Konverter-FBs** (z. B. `F_REAL_TO_USINT`): Diese bieten keine Adapterschnittstellen, sondern erfordern eine direkte Verdrahtung. AR_TO_AUS kapselt diesen Konverter und stellt eine ad-hoc nutzbare Adapterverbindung bereit.
- **Bidirektionale Konverter**: Im Gegensatz zu diesen arbeitet AR_TO_AUS strikt unidirektional, was die Klarheit des Datenflusses erhöht.

## Fazit

Der Funktionsblock AR_TO_AUS bietet eine einfache, modulare Lösung zur Konvertierung eines REAL-Adapters in einen USINT-Adapter. Durch die Verwendung eines standardisierten Konvertierungsbausteins und die Kapselung als Composite-FB kann er leicht in bestehende 4diac-Projekte integriert werden. Er eignet sich besonders für Szenarien, in denen eine klare Trennung von Schnittstellen und eine unidirektionale Datenübertragung erforderlich sind.