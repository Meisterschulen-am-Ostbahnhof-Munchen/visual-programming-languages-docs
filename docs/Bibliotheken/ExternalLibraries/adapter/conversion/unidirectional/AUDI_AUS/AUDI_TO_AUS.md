# AUDI_TO_AUS


![AUDI_TO_AUS](./AUDI_TO_AUS.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **AUDI_TO_AUS** dient als Komposit-Baustein zur Umwandlung eines UDINT-Wertes (über den AUDI-Adapter) in einen USINT-Wert (über den AUS-Adapter). Er kapselt die Konvertierung und erlaubt eine einfache Anbindung von Komponenten, die unterschiedliche Datentypen erwarten.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **AUDI_IN.E1** (Ereignis vom AUDI-Adapter) – initiiert die Konvertierung des anliegenden Datenwertes.

### **Ereignis-Ausgänge**
- **AUS_OUT.E1** (Ereignis zum AUS-Adapter) – signalisiert den Abschluss der Konvertierung und die Bereitstellung des Ergebnisses.

### **Daten-Eingänge**
- **AUDI_IN.D1** (UDINT aus dem AUDI-Adapter) – der zu konvertierende 32‑Bit‑Wert.

### **Daten-Ausgänge**
- **AUS_OUT.D1** (USINT zum AUS-Adapter) – der konvertierte 8‑Bit‑Wert.

### **Adapter**
- **AUDI_IN** (Socket) – Adapter vom Typ `adapter::types::unidirectional::AUDI` (UDINT‑Quelle).
- **AUS_OUT** (Plug) – Adapter vom Typ `adapter::types::unidirectional::AUS` (USINT‑Senke).

## Funktionsweise
Der Baustein ist als reines „Durchreichen“ implementiert. Im FBNetzwerk wird der eingehende Ereignisimpuls (`AUDI_IN.E1`) direkt an den internen Konvertierungsbaustein `F_UDINT_TO_USINT` weitergeleitet. Gleichzeitig wird der Datenwert `AUDI_IN.D1` an den Eingang `IN` des Konverters übergeben. Nach erfolgter Umwandlung sendet der Konverter das Bestätigungsereignis (`CNF`) an den Ausgangs-Adapter (`AUS_OUT.E1`) und das Ergebnis (`OUT`) an den Datenausgang (`AUS_OUT.D1`). Es findet keine Zwischenspeicherung oder weitere Logik statt.

## Technische Besonderheiten
- Verwendet den Standard-Konvertierungsbaustein `iec61131::conversion::F_UDINT_TO_USINT` aus der IEC‑61131‑Bibliothek.
- Reine Ereignis- und Datenweiterleitung – keine eigene Zustandsmaschine erforderlich.
- Die Konvertierung ist verlustbehaftet: Ein UDINT (32‑Bit) wird auf einen USINT (8‑Bit) abgebildet, d.h. höherwertige Bits gehen verloren (Werte > 255 werden abgeschnitten oder nach Herstellerdefinition behandelt).

## Zustandsübersicht
Der Composite‑Baustein besitzt keine eigenen Zustände; er ist vollständig ereignisgetrieben. Der interne Konverter `F_UDINT_TO_USINT` arbeitet nach dem Standard‑Protokoll (REQ/CNF). Es existieren keine zusätzlichen Sperren oder Verzögerungen.

## Anwendungsszenarien
- Anbindung eines UDINT‑basierten Sensors an einen Aktor, der nur einen USINT‑Wert akzeptiert.
- Umwandlung von Adressen oder Zählwerten, wenn nur der niederwertige Teil benötigt wird.
- Schnittstellenanpassung in einer gemischten IEC‑61499 Umgebung, in der verschiedene Datentypen verwendet werden.

## Vergleich mit ähnlichen Bausteinen
- **AUDI_TO_AUDI** oder **AUS_TO_AUS**: Würden keine Konvertierung durchführen, sondern nur eine reine Weiterleitung.
- **F_UDINT_TO_USINT** (direkt): Dieser Baustein führt die gleiche Konvertierung durch, bietet aber keine Adapter‑Schnittstelle. `AUDI_TO_AUS` kapselt die Adapter‑Typen und vereinfacht die Netzwerkstruktur.
- Bei Bedarf einer Bereichsüberprüfung oder Fehlerbehandlung müsste ein eigener Baustein erstellt werden; dieser Baustein führt keine Plausibilitätsprüfung durch.

## Fazit
`AUDI_TO_AUS` ist ein einfacher, aber nützlicher Strip‑Down‑Baustein für die unidirektionale UDINT‑zu‑USINT‑Konvertierung über Adapter. Er reduziert die Komplexität im FBNetzwerk, indem er die Adapter‑Kopplung und die Konvertierungslogik in einem Block vereint. Aufgrund der fehlenden Fehlerbehandlung ist er nur für Anwendungen geeignet, bei denen Werte > 255 nicht vorkommen oder deren Verlust toleriert werden kann.