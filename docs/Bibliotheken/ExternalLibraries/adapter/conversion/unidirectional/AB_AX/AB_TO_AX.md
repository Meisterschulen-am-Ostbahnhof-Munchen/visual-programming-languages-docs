# AB_TO_AX


![AB_TO_AX](./AB_TO_AX.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AB_TO_AX** ist ein zusammengesetzter Baustein (Composite FB) zur Umwandlung eines BYTE-Signals (über den AB-Adapter) in ein BOOL-Signal (über den AX-Adapter). Er dient als Konverter zwischen zwei unterschiedlichen Adaptertypen der unidirektionalen Adapterfamilie.

## Schnittstellenstruktur
### **Adapter (Eingang)**
- **AB_IN** (Typ: `adapter::types::unidirectional::AB`):  
  Nimmt einen BYTE-Wert sowie ein zugehöriges Ereignis entgegen. Der Adapter stellt die Daten über die internen Kanäle D1 (BYTE) und E1 (Ereignis) bereit.

### **Adapter (Ausgang)**
- **AX_OUT** (Typ: `adapter::types::unidirectional::AX`):  
  Gibt einen BOOL-Wert sowie ein auslösendes Ereignis aus. Der Adapter liefert das Ergebnis über D1 (BOOL) und E1 (Ereignis).

## Funktionsweise
Der Baustein verwendet intern einen `F_NE`-Vergleichsbaustein (ungleich). Das eingehende BYTE-Signal (AB_IN.D1) wird mit dem konstanten Wert `BYTE#0` verglichen.  
- Wenn der BYTE-Wert ungleich 0 ist, liefert der Vergleich `TRUE`.  
- Wenn der BYTE-Wert gleich 0 ist, liefert der Vergleich `FALSE`.  

Der Ablauf wird durch das Ereignis `AB_IN.E1` gestartet. Dieses triggert den `F_NE`-Baustein. Nach Abschluss des Vergleichs wird das Ereignis `AX_OUT.E1` ausgelöst und das Ergebnis (BOOL) über `AX_OUT.D1` ausgegeben.

## Technische Besonderheiten
- Der Baustein ist als Composite realisiert, d.h. seine Funktionalität ergibt sich aus der Verschaltung von Standard-FBs (hier `F_NE`).
- Er ist für die Verwendung in der 4diac-IDE mit der Spezifikation IEC 61499-2 ausgelegt.
- Die Adapter `AB` und `AX` sind unidirektional, sodass die Daten- und Ereignisflüsse klar getrennt sind.
- Der interne Vergleich erfolgt binär: Jeder von Null verschiedene BYTE-Wert wird als `TRUE` interpretiert.

## Zustandsübersicht
Der Baustein besitzt keine eigene Zustandsmaschine. Die gesamte Verarbeitung erfolgt ereignisgesteuert über die internen Verbindungen. Der `F_NE`-Baustein arbeitet deterministisch ohne Zwischenzustände.

## Anwendungsszenarien
- **Signalkonvertierung**: Ein digitaler Sensor liefert einen Byte-Wert (z.B. Zählerstand oder Status). AB_TO_AX wandelt diesen in ein boolsches Signal um, das z.B. eine Alarmierung auslöst, sobald der Wert ungleich Null ist.
- **Adapterbrücke**: In einer Steuerungskomponente wird ein AB-Adapter verwendet, die nachgeschaltete Logik erwartet jedoch einen AX-Adapter. Der Baustein fungiert als einfacher Übersetzer.
- **Schwellwertersetzung**: Ersetzt einen expliziten Vergleichsbaustein durch einen kompakten Adapter-Konverter.

## Vergleich mit ähnlichen Bausteinen
Andere Konverterbausteine wie `BOOL_TO_BYTE` oder `BYTE_TO_BOOL` existieren als einfache Datenumwandler, arbeiten jedoch meist auf Datenebene ohne Adapter. AB_TO_AX integriert die Adapterschnittstelle und ermöglicht so eine nahtlose Einbindung in adapterbasierte Architekturen. Im Gegensatz zu einem allgemeinen Vergleichsbaustein (`F_NE`) kapselt dieser FB die spezifische Konvertierungslogik und bietet eine aufgeräumte Schnittstelle.

## Fazit
Der **AB_TO_AX**-Baustein bietet eine saubere und einfache Methode, um ein BYTE-Signal aus einem AB-Adapter in ein BOOL-Signal für einen AX-Adapter zu wandeln. Durch die Nutzung des Standardvergleichs `Ungleich Null` ist er besonders für binäre Schwellwertentscheidungen geeignet und vereinfacht die Wiederverwendung in adapterorientierten Steuerungsprojekten.