# AR_TO_AX

![AR_TO_AX](./AR_TO_AX.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock AR_TO_AX wandelt einen REAL-Wert, der über einen AR-Adapter empfangen wird, in einen BOOL-Wert um und gibt diesen über einen AX-Adapter aus. Die Umwandlung erfolgt durch einen Vergleich des REAL-Werts mit 0,0. Ist der Wert ungleich Null, wird TRUE ausgegeben, ansonsten FALSE. Der Baustein dient als Brücke zwischen analogen und digitalen Adapterschnittstellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine direkten Ereignis-Eingänge auf FB-Ebene. Der Ereignis-Eingang ist im AR-Adapter (`AR_IN.E1`) enthalten.

### **Ereignis-Ausgänge**
Keine direkten Ereignis-Ausgänge auf FB-Ebene. Der Ereignis-Ausgang ist im AX-Adapter (`AX_OUT.E1`) enthalten.

### **Daten-Eingänge**
Keine direkten Daten-Eingänge auf FB-Ebene. Der Daten-Eingang ist im AR-Adapter (`AR_IN.D1`) enthalten.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge auf FB-Ebene. Der Daten-Ausgang ist im AX-Adapter (`AX_OUT.D1`) enthalten.

### **Adapter**
- **AR_IN** (Socket) – Adapter vom Typ `adapter::types::unidirectional::AR`. Nimmt einen REAL-Wert sowie ein Ereignis zum Start der Verarbeitung entgegen.
- **AX_OUT** (Plug) – Adapter vom Typ `adapter::types::unidirectional::AX`. Stellt den BOOL-Ergebniswert sowie ein Ereignis zur Bestätigung der Verarbeitung bereit.

## Funktionsweise

Der Baustein verarbeitet eingehende REAL-Werte folgendermaßen:

1. Ein Ereignis an `AR_IN.E1` triggert den internen Vergleichsbaustein `F_NE` (ungleich).
2. Der über `AR_IN.D1` anliegende REAL-Wert wird mit dem konstanten Wert 0,0 verglichen.
3. Das Ergebnis des Vergleichs (BOOL) wird über `F_NE.OUT` an `AX_OUT.D1` weitergeleitet.
4. Ein Ereignis am Ausgang `F_NE.CNF` wird an `AX_OUT.E1` gesendet, um die Verfügbarkeit des BOOL-Werts zu signalisieren.

Der interne Baustein `F_NE` ist ein IEC 61131-3-konformer Vergleichsbaustein und gibt TRUE aus, wenn der Eingang `IN1` ungleich `IN2` (hier 0,0) ist.

## Technische Besonderheiten
- Verwendet einen Composite-FB-Ansatz, bei dem die Logik aus einem einzigen Vergleichsbaustein und Adapterverbindungen besteht.
- Alle Ein- und Ausgänge sind über standardisierte unidirektionale Adapter (`AR`, `AX`) realisiert, was eine modulare und austauschbare Schnittstellendefinition ermöglicht.
- Der Vergleichswert (0,0) ist fest im FB eingestellt und kann nicht zur Laufzeit geändert werden.
- Die Ausführung erfolgt ereignisgesteuert: Nur bei einem Ereignis an `AR_IN.E1` wird eine Umwandlung durchgeführt.

## Zustandsübersicht
Da der FB als Composition (Netzwerk aus Basisbausteinen) implementiert ist, besitzt er keine eigene Zustandsmaschine. Die Funktion wird durch die sequenzielle Verarbeitung der Ereignis- und Datenflüsse im internen Netzwerk bestimmt:

- **Wartezustand**: Kein Ereignis an `AR_IN.E1`. Der Ausgangswert bleibt unverändert.
- **Verarbeitungszustand**: Ein Ereignis an `AR_IN.E1` löst den Vergleich aus und erzeugt ein Ereignis an `AX_OUT.E1`, sobald der BOOL-Wert bereitsteht.

## Anwendungsszenarien
- **Schwellwertschalter**: Ein analoger Sensor (z.B. Drucksensor) liefert REAL-Werte. Der FB gibt TRUE aus, sobald der Wert von 0,0 abweicht (z.B. bei Überschreitung eines Schwellwerts, wenn der Nullpunkt kalibriert ist).
- **Digitalisierung von Analogsignalen**: Zur Anbindung analoger Adapter an digitale Logik in der Steuerungstechnik.
- **Einfache Plausibilitätsprüfung**: Prüfen, ob ein REAL-Wert ungleich Null (z.B. gültiger Messwert) vorliegt.

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu einem generischen `AR_TO_BOOL`-Baustein, der direkte Daten ohne Adapter verwendet, ist AR_TO_AX speziell für die Verwendung mit Adapterschnittstellen ausgelegt. Ein Vergleichsbaustein mit einstellbarem Schwellwert (z.B. `F_GT`, `F_LT`) würde mehr Flexibilität bieten, aber auch zusätzlichen Konfigurationsaufwand erfordern. Der vorliegende Baustein bietet eine einfache, feste Umwandlung: ungleich Null → TRUE.

## Fazit
Der AR_TO_AX-Funktionsblock bietet eine kompakte Lösung zur Umwandlung eines REAL-Adapter-Werts in einen BOOL-Adapter-Wert mittels Nullvergleich. Durch die Verwendung von Adaptern und einem standardisierten Vergleichsbaustein ist er einfach in bestehende 4diac-Projekte integrierbar und eignet sich gut für schnelle, unidirektionale Signalkonvertierungen.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
