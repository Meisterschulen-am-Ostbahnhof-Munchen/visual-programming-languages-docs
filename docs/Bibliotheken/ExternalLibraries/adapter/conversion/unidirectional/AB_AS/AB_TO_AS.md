# AB_TO_AS


![AB_TO_AS](./AB_TO_AS.svg)

* * * * * * * * * *
## Einleitung

Der **AB_TO_AS** ist ein Composite-Funktionsbaustein (FB), der einen unidirektionalen AB-Adapter (BYTE) in einen unidirektionalen AS-Adapter (SINT) umwandelt. Er dient als konvertierende Brücke zwischen zwei verschiedenen Datentypen in einer IEC 61499-basierten Steuerungsanwendung.

## Schnittstellenstruktur

Der FB besitzt keine eigenen Ereignis- oder Datenports auf der obersten Ebene. Die gesamte Kommunikation erfolgt über zwei Adapter-Schnittstellen:

### **Ereignis-Eingänge**

- **E1** (über **AB_IN**, Socket, Typ `adapter::types::unidirectional::AB`)  
  Dieses Ereignis wird vom angeschlossenen Quell-Adapter empfangen und löst die Konvertierung eines BYTE-Wertes in einen SINT-Wert aus.

### **Ereignis-Ausgänge**

- **E1** (über **AS_OUT**, Plug, Typ `adapter::types::unidirectional::AS`)  
  Dieses Ereignis wird nach erfolgreicher Konvertierung an den Ziel-Adapter gesendet, um den neuen SINT-Wert zu signalisieren.

### **Daten-Eingänge**

- **D1** (BYTE, über **AB_IN**-Adapter)  
  Enthält den zu konvertierenden BYTE-Wert. Er wird über das Ereignis **E1** am Eingang abgetastet.

### **Daten-Ausgänge**

- **D1** (SINT, über **AS_OUT**-Adapter)  
  Stellt den konvertierten SINT-Wert bereit. Er wird nach Abschluss der Konvertierung mit dem Ereignis **E1** am Ausgang gültig.

### **Adapter**

| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| **AB_IN** | Socket (Eingang) | `adapter::types::unidirectional::AB` | Nimmt BYTE-Daten und ein Trigger-Ereignis vom Quellsystem entgegen. |
| **AS_OUT** | Plug (Ausgang) | `adapter::types::unidirectional::AS` | Stellt die konvertierten SINT-Daten mit einem Bestätigungsereignis für das Zielsystem bereit. |

## Funktionsweise

Der **AB_TO_AS**-FB enthält intern einen einzelnen Funktionsbaustein des Typs `iec61131::conversion::F_BYTE_TO_SINT`. Dieser Baustein führt die eigentliche Datentypkonvertierung von BYTE auf SINT durch.

1. Ein eingehendes Ereignis **AB_IN.E1** triggert den **F_BYTE_TO_SINT**-Baustein über dessen **REQ**-Eingang.
2. Gleichzeitig wird der Datenwert von **AB_IN.D1** (BYTE) auf den **IN**-Eingang des Konverters gelegt.
3. Nach der Verarbeitung signalisiert der Konverter sein **CNF**-Ereignis, das an den Adapter-Ausgang **AS_OUT.E1** weitergeleitet wird.
4. Der konvertierte SINT-Wert wird vom **OUT**-Ausgang des Konverters auf **AS_OUT.D1** übertragen.

Damit ist eine asynchrone, ereignisgesteuerte Übersetzung eines BYTE-Werts in einen SINT-Wert realisiert.

## Technische Besonderheiten

- **Composite-FB**: Die Logik ist vollständig in der internen FBNetzwerk-Struktur gekapselt. Dies erleichtert Wartung und Wiederverwendung.
- **Lizenz**: Der Baustein wird unter der **Eclipse Public License 2.0** bereitgestellt (SPDX-Lizenzkennung: EPL-2.0).
- **Version**: 1.0, veröffentlicht 2026.
- **Abhängigkeiten**: Der interne Konverterbaustein `F_BYTE_TO_SINT` aus der Bibliothek `iec61131::conversion` wird vorausgesetzt.

## Zustandsübersicht

Der **AB_TO_AS** besitzt keinen eigenen Zustandsautomaten. Die Verarbeitung erfolgt rein datenfluss- und ereignisgesteuert über den eingebetteten **F_BYTE_TO_SINT**-Baustein. Somit gibt es keine expliziten Zustände, lediglich die impliziten Abläufe: *Warten auf Eingabeereignis*, *Konvertierung aktiv* und *Ausgabeereignis gesendet*.

## Anwendungsszenarien

- **Systemintegration**: Verbindung zweier Subsysteme, die unterschiedliche Adapter-Datentypen (BYTE vs. SINT) verwenden.
- **Datenformatumstellung**: Wenn ein bestehender Steuerungsalgorithmus SINT-Werte erwartet, die Quelle aber nur BYTE-Adapter bereitstellt.
- **Protokollanpassung**: In heterogenen Automatisierungsumgebungen, in denen Bausteine verschiedener Hersteller oder Bibliotheken kombiniert werden müssen.

## Vergleich mit ähnlichen Bausteinen

- **F_BYTE_TO_SINT** (direkter FB): Bietet dieselbe Konvertierungslogik, jedoch ohne Adapter-Kapselung. Erfordert manuelle Verkabelung von Ereignis- und Datenleitungen.
- **AB_TO_INT** oder **AB_TO_USINT**: Ähnliche Adapter-Konverter für andere Ziel-Datentypen. Der **AB_TO_AS** ist speziell auf SINT ausgelegt.
- **Eigene Implementierung**: Der Composite-Bauweise erlaubt eine einfache Erweiterung, z. B. durch Hinzufügen von Plausibilitätsprüfungen oder Skalierungen, ohne die Grundfunktion zu verändern.

## Fazit

Der **AB_TO_AS** ist ein spezialisierter, aber einfach aufgebauter Composite-FB, der eine saubere und wiederverwendbare Lösung zur Adapter-basierten Datentypkonvertierung von BYTE zu SINT bietet. Durch die Nutzung eines standardisierten Konverterbausteins und die klare Ereignissteuerung fügt er sich nahtlos in IEC-61499-Netzwerke ein. Seine Lizenzierung unter EPL-2.0 fördert die offene Nutzung und Weiterentwicklung.