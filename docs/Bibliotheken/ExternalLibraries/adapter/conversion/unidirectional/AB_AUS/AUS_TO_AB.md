# AUS_TO_AB


![AUS_TO_AB](./AUS_TO_AB.svg)

* * * * * * * * * *

## Einleitung
Der **AUS_TO_AB** ist ein Composite-Funktionsblock zur Konvertierung eines unidirektionalen **AUS-Adapters** (USINT-Datentyp) in einen **AB-Adapter** (BYTE-Datentyp). Er dient als Brücke zwischen unterschiedlichen Adapter-Schnittstellen in Automatisierungssystemen und ermöglicht die nahtlose Integration von Komponenten, die auf verschiedenen Datentypen basieren. Der Baustein nutzt intern den Standardkonvertierungsblock *F_USINT_TO_BYTE* aus der IEC 61131-Bibliothek.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Der Baustein besitzt keine eigenen Ereignis-Eingangsports. Ereignisse werden über den **AUS_IN**-Adapter (Socket) empfangen:
- **AUS_IN.E1** – Auslöser für die Datenkonvertierung und Weitergabe an den Ausgang.

### **Ereignis-Ausgänge**
Ereignisse werden über den **AB_OUT**-Adapter (Plug) ausgegeben:
- **AB_OUT.E1** – Bestätigung, dass der konvertierte Wert am Ausgang anliegt.

### **Daten-Eingänge**
Daten werden über den **AUS_IN**-Adapter bereitgestellt:
- **AUS_IN.D1** (USINT) – Der zu konvertierende 8‑Bit‑vorzeichenlose Integerwert.

### **Daten-Ausgänge**
Daten werden über den **AB_OUT**-Adapter weitergegeben:
- **AB_OUT.D1** (BYTE) – Der konvertierte Byte‑Wert.

### **Adapter**

| Name      | Typ                                    | Richtung | Beschreibung |
|-----------|----------------------------------------|----------|--------------|
| **AUS_IN** | `adapter::types::unidirectional::AUS` | Socket   | Eingangsadapter für USINT‑Daten und Ereignisse. |
| **AB_OUT** | `adapter::types::unidirectional::AB`  | Plug     | Ausgangsadapter für BYTE‑Daten und Ereignisse. |

## Funktionsweise
Der **AUS_TO_AB** ist als reines Composite‑FB ohne eigene Logik realisiert. Er verbindet den AUS_IN‑ und AB_OUT‑Adapter über den internen Baustein **F_USINT_TO_BYTE**:

1. Ein eingehendes Ereignis auf **AUS_IN.E1** triggert den Konvertierungsbaustein **Convert** (`F_USINT_TO_BYTE`) über dessen **REQ**‑Eingang.
2. Gleichzeitig wird der Datenwert von **AUS_IN.D1** an den **Convert.IN**-Eingang übergeben.
3. Nach erfolgter Konvertierung (USINT → BYTE) bestätigt **Convert** mit einem Ereignis auf **CNF**.
4. Dieses Ereignis wird direkt an **AB_OUT.E1** weitergeleitet.
5. Der konvertierte Byte‑Wert von **Convert.OUT** wird an **AB_OUT.D1** übergeben.

Damit ist eine synchronisierte, ereignisgesteuerte Datenweitergabe gewährleistet.

## Technische Besonderheiten
- **Composite‑FB**: Enthält keine eigene Zustandsmaschine; die gesamte Logik wird durch den internen FB `F_USINT_TO_BYTE` abgebildet.
- **Unidirektionale Adapter**: Sowohl der eingehende als auch der ausgehende Adapter sind unidirektional – die Datenflüsse erfolgen ausschließlich in eine Richtung.
- **Standardkonformität**: Der Baustein basiert auf IEC 61499‑2 und nutzt die IEC 61131‑Konvertierungsfunktion `F_USINT_TO_BYTE`. Dadurch ist er in kompatiblen Laufzeitumgebungen (z. B. 4diac‑FORTE) sofort einsetzbar.
- **Lizenz**: Veröffentlicht unter der Eclipse Public License 2.0 (EPL‑2.0). Copyright (c) 2026 HR Agrartechnik GmbH.

## Zustandsübersicht
Da es sich um einen Composite‑FB ohne eigene ECC (Execution Control Chart) handelt, besteht kein expliziter Zustandsautomat. Das Verhalten ist rein ereignisgesteuert und wird durch die interne Verschaltung der Einzelfunktionsblöcke bestimmt. Nach dem Start liegt jederzeit eine Bereitschaft vor – ein eingehendes Ereignis wird direkt verarbeitet.

## Anwendungsszenarien
- **Systemintegration** in der Landtechnik oder anderen Automatisierungsumgebungen, in denen ein **AUS-Adapter** (USINT) an einen **AB-Adapter** (BYTE) angebunden werden muss.
- **Nachrüstung älterer Komponenten**, die einen BYTE‑Ausgang liefern, mit modernen USINT‑basierten Sensoren oder Aktoren.
- **Prototyping und Testaufbauten**, bei denen schnell zwischen verschiedenen Adaptertypen gewechselt werden soll.
- **Datenaufbereitung** in Kommunikationsknoten, die unterschiedliche Adapterprotokolle vereinheitlichen.

## Vergleich mit ähnlichen Bausteinen
- **F_USINT_TO_BYTE** – direkter Funktionsblock für die reine Datentypkonvertierung, jedoch ohne Adapter‑Einbindung. **AUS_TO_AB** fügt die Adapter‑ und Ereignislogik hinzu.
- **BYTE_TO_USINT** – inverse Umwandlung (BYTE → USINT), falls die umgekehrte Adapterrichtung benötigt wird (nicht im Lieferumfang dieses Bausteins).
- **Generische Adapter‑Konverter** – komplexere Blöcke, die mehrere Datentypen gleichzeitig umsetzen. **AUS_TO_AB** ist auf den spezifischen Anwendungsfall optimiert und daher schlanker.

## Fazit
Der **AUS_TO_AB** ist ein nützlicher und leichter Baustein zur Umwandlung eines **AUS-Adapters (USINT)** in einen **AB-Adapter (BYTE)**. Seine Composite‑Struktur minimiert Implementierungsaufwand, während die Verwendung eines standardisierten Konvertierungsblocks die Zuverlässigkeit sichert. Der Baustein eignet sich besonders für die schnelle Integration heterogener Adapter‑Schnittstellen in IEC 61499‑basierten Steuerungssystemen.