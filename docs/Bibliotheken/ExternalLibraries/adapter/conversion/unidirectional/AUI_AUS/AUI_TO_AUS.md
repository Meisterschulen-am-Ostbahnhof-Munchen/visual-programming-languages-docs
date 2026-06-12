# AUI_TO_AUS


![AUI_TO_AUS](./AUI_TO_AUS.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AUI_TO_AUS** dient als zusammengesetzter Baustein zur Umwandlung eines AUI-Adapters (Datentyp UINT) in einen AUS-Adapter (Datentyp USINT). Er wird typischerweise eingesetzt, um zwischen unterschiedlichen Adaptertypen in der 4diac-IDE zu vermitteln, wenn eine Größenreduktion des Wertebereichs oder eine Typanpassung erforderlich ist. Der Baustein kapselt die Konvertierungslogik und ermöglicht eine nahtlose Integration in bestehende Ablaufumgebungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine separaten Ereignis-Eingänge. Die Ereignissteuerung erfolgt über die angeschlossenen Adapter.

### **Ereignis-Ausgänge**
Keine separaten Ereignis-Ausgänge. Die Ereignisweitergabe erfolgt über die angeschlossenen Adapter.

### **Daten-Eingänge**
Keine separaten Daten-Eingänge. Die Dateneingabe erfolgt über die angeschlossenen Adapter.

### **Daten-Ausgänge**
Keine separaten Daten-Ausgänge. Die Datenausgabe erfolgt über die angeschlossenen Adapter.

### **Adapter**

| Richtung | Name                                | Typ                              | Beschreibung                              |
|----------|-------------------------------------|----------------------------------|-------------------------------------------|
| Socket   | **AUI_IN**                          | adapter::types::unidirectional::AUI | UINT Eingangsadapter (Quelle)             |
| Plug     | **AUS_OUT**                         | adapter::types::unidirectional::AUS | USINT Ausgangsadapter (Ziel)              |

Der Socket `AUI_IN` nimmt den UINT-Wert (16‑Bit ohne Vorzeichen) sowie das zugehörige Ereignissignal auf. Der Plug `AUS_OUT` gibt den konvertierten USINT-Wert (8‑Bit ohne Vorzeichen) mit dem entsprechenden Ereignis aus.

## Funktionsweise

Der FB arbeitet als einfaches Durchschalteelement mit Typkonvertierung:

1. **Ereignisempfang**: Ein eingehendes Ereignis am Socket `AUI_IN.E1` triggert die Verarbeitung.
2. **Datenübernahme**: Der zugehörige Datenwert `AUI_IN.D1` (Typ UINT) wird ausgelesen.
3. **Konvertierung**: Intern wird die Funktion `F_UINT_TO_USINT` aus der IEC‑61131‑Bibliothek aufgerufen. Diese wandelt den UINT-Wert in einen USINT-Wert um. Bei Überschreitung des USINT-Wertebereichs (0…255) wird der Wert gemäß der zugrunde liegenden Implementierung beschnitten oder entsprechend behandelt (in der Regel auf 255 gekappt).
4. **Ausgabe**: Der konvertierte Wert wird auf `AUS_OUT.D1` (Typ USINT) bereitgestellt, und das Ausgangsereignis `AUS_OUT.E1` wird gesendet.

Die gesamte Kopplung erfolgt über die Ereignis- und Datenverbindungen im FBNetzwerk des Composite‑Bausteins.

## Technische Besonderheiten

- **Bereichseinschränkung**: Die Konvertierung von UINT (0…65535) auf USINT (0…255) führt zwangsläufig zu einem Informationsverlust, sofern der Eingangswert größer als 255 ist. Anwender müssen sicherstellen, dass der Wertebereich des Eingangs den Erwartungen entspricht.
- **Keine Zustandsspeicherung**: Der FB ist zustandslos – jede Verarbeitung erfolgt unabhängig von vorherigen Umwandlungen.
- **Wiederverwendbarkeit**: Der Baustein ist als gekapselte Komponente ausgelegt und kann in verschiedenen Projekten eingesetzt werden, ohne dass die Konvertierungslogik erneut implementiert werden muss.
- **Kompatibilität**: Vorausgesetzt wird die Verfügbarkeit der Bibliothek `iec61131::conversion::F_UINT_TO_USINT`.

## Zustandsübersicht

Der FB verfügt über keine explizite Zustandsmaschine. Der interne Ablauf kann jedoch als zweischrittig beschrieben werden:

- **Bereit (Idle)**: Der FB wartet auf ein eingehendes Ereignis am Socket.
- **Verarbeitung (Convert)**: Nach Ereigniseingang wird die Konvertierung durchgeführt und das Ausgangsereignis ausgelöst. Danach kehrt der FB sofort in den Bereit-Zustand zurück.

Eine detaillierte Zustandsgrafik ist nicht erforderlich, da der FB keine Verzögerungen oder mehrstufigen Schritte aufweist.

## Anwendungsszenarien

- **Sensoranbindung**: Ein Sensor liefert Werte im UINT‑Format, die an eine nachfolgende Logik mit USINT‑Anforderung übergeben werden müssen.
- **Gerätekopplung**: Zwischen zwei Geräten oder Komponenten, die unterschiedliche Adaptertypen verwenden, wird eine nahtlose Kommunikation hergestellt.
- **Datenreduktion**: In Fällen, in denen die höhere Auflösung eines UINT nicht benötigt wird, kann die Konvertierung zu USINT Speicher‑ und Bandbreitenvorteile bringen.
- **Systemmigration**: Bei der Umstellung von älteren auf neuere Adapterprotokolle kann dieser FB als temporäre oder dauerhafte Brücke dienen.

## Vergleich mit ähnlichen Bausteinen

Es existieren andere Konvertierungsbausteine in der 4diac‑Bibliothek, z. B. `F_UINT_TO_USINT`, der direkt einen UINT‑Eingang auf einen USINT‑Ausgang abbildet. Der hier beschriebene **AUI_TO_AUS** unterscheidet sich dadurch, dass er Adapter (AUI und AUS) anstelle von elementaren Dateneingängen verwendet. Dadurch ist er in der Lage, die gesamte Schnittstelle inklusive Ereignissteuerung zu kapseln, was den Einsatz in komplexen, adapterbasierten Architekturen vereinfacht. Ein reiner Funktionsbaustein wie `F_UINT_TO_USINT` benötigt hingegen separate Ereignis‑ und Datenverbindungen.

## Fazit

Der **AUI_TO_AUS** ist ein kompakter und fokussierter Baustein zur Adapter‑Konvertierung von UINT nach USINT. Seine composite‑Struktur erleichtert die Integration in vorhandene 4diac‑Projekte, reduziert den Verdrahtungsaufwand und erhöht die Übersichtlichkeit. Die einfache Funktionsweise und die klare Schnittstelle machen ihn zu einem nützlichen Werkzeug für alle Anwendungen, bei denen eine Typumwandlung auf Adapterebene erforderlich ist.