# hsv2rgb

```{index} single: hsv2rgb
```

<img width="1412" height="272" alt="image" src="https://github.com/user-attachments/assets/d564035b-fcbb-4237-a4be-75da3e2fd29d" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `hsv2rgb` ist ein Hilfsbaustein zur Farbraumkonvertierung. Er wandelt eine im HSV-Farbmodell (Hue, Saturation, Value) definierte Farbe in die entsprechenden Werte des RGB-Farbmodells (Red, Green, Blue) um. Dies ist besonders nützlich für Anwendungen, die Farben auf Basis ihrer wahrnehmungsbezogenen Eigenschaften (Farbton, Sättigung, Helligkeit) steuern müssen, während die Ausgabegeräte (wie LEDs oder Displays) RGB-Werte erwarten.

![hsv2rgb](hsv2rgb.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **REQ (Service Request):** Löst die Konvertierungsberechnung aus. Bei diesem Ereignis werden die aktuellen Werte an den Daten-Eingängen `hue`, `saturation` und `value` übernommen.

### **Ereignis-Ausgänge**
*   **CNF (Confirmation of Requested Service):** Wird ausgelöst, sobald die Konvertierung abgeschlossen ist. Dieses Ereignis liefert die berechneten RGB-Werte an den Daten-Ausgängen `r`, `g` und `b`.

### **Daten-Eingänge**
*   **hue (UDINT):** Der Farbton (Hue) im HSV-Modell. Der Wertebereich ist nicht im Baustein vordefiniert, typischerweise wird jedoch ein Bereich von 0-360° oder 0-65535 verwendet.
*   **saturation (UDINT):** Die Sättigung (Saturation) im HSV-Modell. Typischer Wertebereich: 0-100% oder 0-255.
*   **value (UDINT):** Die Helligkeit (Value) im HSV-Modell. Typischer Wertebereich: 0-100% oder 0-255.

### **Daten-Ausgänge**
*   **r (UDINT):** Der berechnete Rot-Anteil (Red) im RGB-Modell.
*   **g (UDINT):** Der berechnete Grün-Anteil (Green) im RGB-Modell.
*   **b (UDINT):** Der berechnete Blau-Anteil (Blue) im RGB-Modell.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Baustein arbeitet ereignisgesteuert. Bei Eintreffen des `REQ`-Ereignisses startet der interne Algorithmus. Er nimmt die an den Daten-Eingängen anliegenden HSV-Werte entgegen und berechnet daraus die entsprechenden RGB-Werte gemäß dem standardisierten HSV-zu-RGB-Konvertierungsalgorithmus. Nach Abschluss der Berechnung werden die Ergebnisse an den Daten-Ausgängen `r`, `g` und `b` ausgegeben und das `CNF`-Ereignis signalisiert, dass die neuen Werte gültig und abrufbereit sind.

## Technische Besonderheiten
*   **Datentyp:** Alle Eingangs- und Ausgangsdaten sind vom Typ `UDINT` (unsigned double integer, 32-bit). Dies ermöglicht eine hohe Auflösung und Genauigkeit bei der Farbdarstellung.
*   **Wertebereich:** Der Baustein selbst definiert keine Skalierung oder Begrenzung der Wertebereiche für HSV oder RGB. Die Interpretation der Zahlenwerte (z.B. 0-360 für Hue, 0-255 für RGB) liegt in der Verantwortung der anbindenden Applikation. Der Konvertierungsalgorithmus muss entsprechend auf den erwarteten Eingabebereich ausgelegt sein.
*   **Deterministisches Verhalten:** Die Ausführung ist deterministisch und liefert für identische Eingabewerte stets die gleichen RGB-Ausgabewerte.

## Zustandsübersicht
Der Funktionsblock besitzt einen einfachen, zustandslosen Ablauf:
1.  **Warte-Zustand:** Der Baustein wartet auf das `REQ`-Ereignis.
2.  **Berechnungs-Zustand:** Bei `REQ` werden die Eingabedaten gelesen und die Konvertierung durchgeführt. Dieser Zustand ist transient.
3.  **Ausgabe-Zustand:** Die Ergebnisse werden an die Ausgänge geschrieben und das `CNF`-Ereignis wird generiert. Der Baustein kehrt unmittelbar danach in den Warte-Zustand zurück.

## Anwendungsszenarien
*   **Farbsteuerung von RGB-LEDs:** Benutzerfreundliche Farbauswahl über HSV-Parameter (z.B. via Drehgeber oder Touch-Oberfläche) mit anschließender Umrechnung für die LED-Ansteuerung.
*   **Visualisierungs-Systeme:** Konvertierung von in HSV definierten Alarm- oder Statusfarben für die Darstellung auf RGB-Monitoren oder -Panels.
*   **Industrielle Beleuchtung:** Dynamische Lichtsteuerung in Produktions- oder Logistikumgebungen, bei der Farbübergänge intuitiv über Helligkeit und Sättigung definiert werden.

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu universellen Rechenbausteinen (wie `MUL`, `ADD`) oder Skalierern ist `hsv2rgb` ein anwendungsspezifischer Baustein, der einen komplexen, nicht-linearen Algorithmus kapselt. Er erspart dem Anwender die aufwändige und fehleranfällige Implementierung der Konvertierung in Structured Text oder anderen Sprachen. Ein direkter Gegenpart `rgb2hsv` für die umgekehrte Konvertierung wäre ein ähnlich spezialisierter Baustein.

## Fazit
Der `hsv2rgb`-Funktionsblock ist ein nützliches und spezialisiertes Werkzeug für alle 4diac-Anwendungen, die mit Farbmanipulation zu tun haben. Durch die Kapselung des Konvertierungsalgorithmus in einen standardisierten IEC 61499-Baustein vereinfacht er die Programmierung erheblich, fördert die Wiederverwendbarkeit und erhöht die Zuverlässigkeit der Software. Seine Verwendung ist dort empfehlenswert, wo eine intuitive, auf menschlicher Farbwahrnehmung basierende Steuerung auf eine geräteorientierte RGB-Ausgabe trifft.