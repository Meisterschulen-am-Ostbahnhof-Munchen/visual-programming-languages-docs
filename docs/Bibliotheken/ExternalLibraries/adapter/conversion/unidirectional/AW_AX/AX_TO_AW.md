# AX_TO_AW

Kein Bild verfügbar.


![AX_TO_AW](./AX_TO_AW.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AX_TO_AW` ist ein zusammengesetzter Baustein (Composite FB) zur Konvertierung eines unidirektionalen BOOL-Adapters (Typ `AX`) in einen unidirektionalen WORD-Adapter (Typ `AW`). Er dient als Schnittstellenwandler, der ein ankommendes Ereignis und einen BOOL-Datenwert direkt an den Ausgangsadapter weiterleitet, wobei der BOOL-Wert implizit in ein WORD umgewandelt wird.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der Baustein besitzt keine separaten Ereignis-Eingänge. Das Ereignis wird über den Socket-Adapter `AX_IN` (Typ `AX`) bereitgestellt (internes Ereignis `E1`).

### **Ereignis-Ausgänge**
Der Baustein besitzt keine separaten Ereignis-Ausgänge. Das Ereignis wird über den Plug-Adapter `AW_OUT` (Typ `AW`) ausgegeben (internes Ereignis `E1`).

### **Daten-Eingänge**
Der Baustein besitzt keine separaten Daten-Eingänge. Die Eingangsdaten (BOOL) werden über den Socket-Adapter `AX_IN` (Datenpunkt `D1`, Typ `BOOL`) bereitgestellt.

### **Daten-Ausgänge**
Der Baustein besitzt keine separaten Daten-Ausgänge. Die Ausgangsdaten (WORD) werden über den Plug-Adapter `AW_OUT` (Datenpunkt `D1`, Typ `WORD`) ausgegeben.

### **Adapter**

| Richtung | Bezeichnung | Typ | Kommentar |
|----------|-------------|-----|-----------|
| **Socket** | `AX_IN` | `adapter::types::unidirectional::AX` | BOOL-Adapter-Eingang (bestehend aus Ereignis `E1` und Daten `D1:BOOL`) |
| **Plug** | `AW_OUT` | `adapter::types::unidirectional::AW` | WORD-Adapter-Ausgang (bestehend aus Ereignis `E1` und Daten `D1:WORD`) |

## Funktionsweise
Der Baustein leitet das vom Socket `AX_IN` empfangene Ereignis (`E1`) direkt an den Plug `AW_OUT` (`E1`) weiter. Gleichzeitig wird der eingehende BOOL-Wert (`AX_IN.D1`) ohne weitere Verarbeitung an den WORD-Ausgang (`AW_OUT.D1`) übergeben. Dabei findet eine implizite Typkonvertierung von `BOOL` nach `WORD` statt (übliche Abbildung: `FALSE` → 0, `TRUE` → 1). Es findet keine Logik, Verzögerung oder Zustandsänderung statt – der FB fungiert als reine Durchreiche.

## Technische Besonderheiten
- **Composite FB:** Der Baustein besitzt keinen eigenen Zustandsautomaten (ECC), sondern besteht ausschließlich aus einer Verdrahtung der enthaltenen Adapter-Schnittstellen.
- **Typkonvertierung:** Die Konvertierung von `BOOL` nach `WORD` erfolgt automatisch durch die Datenverbindung zwischen den Adaptern. Es ist keine explizite Konvertierungslogik implementiert.
- **Performance:** Durch die direkte Kopplung werden keine zusätzlichen Verarbeitungsschritte eingeführt, was eine minimale Latenz gewährleistet.
- **Wiederverwendbarkeit:** Der Baustein kann in Projekten eingesetzt werden, die Adapter unterschiedlicher Typen verbinden müssen, ohne dass eine separate Konvertierungslogik erforderlich ist.

## Zustandsübersicht
Da es sich um einen Composite FB ohne eigenen ECC handelt, existieren keine expliziten Zustände. Der Baustein verhält sich wie eine reine Signalweiterleitung und besitzt kein eigenes Verhaltensmodell.

## Anwendungsszenarien
- **Anbindung eines BOOL-basierten Sensors** an ein Steuerungssystem, das WORD-Schnittstellen erwartet (z. B. digitale Eingänge als Bitmasken).
- **Adapterschicht** in Bibliotheken, in denen Komponenten mit unterschiedlichen Adapter-Typen zusammengeführt werden müssen, ohne die Quellbausteine zu verändern.
- **Prototypische Entwicklung** zur schnellen Integration von BOOL- und WORD-Adaptern vor einer späteren Optimierung.

## Vergleich mit ähnlichen Bausteinen
- **AW_TO_AX (theoretisch):** Wäre die inverse Konvertierung von WORD zu BOOL – würde eine Reduktion des Wertebereichs erfordern (z. B. nur Bit 0 wird ausgewertet).
- **TYPCONV-Bausteine:** In der Regel bieten IEC-61499-Bibliotheken explizite Typkonverter (z. B. `BOOL_TO_WORD`), die jedoch als normale Funktionsblöcke mit Ereignis- und Dateneingängen arbeiten und nicht als Adapter-Konverter. 
- **Direkte Adapter-Kopplung:** Ohne `AX_TO_AW` müssten die Adapter-Typen identisch sein oder eine separate Konvertierung in der Netzwerkebene erfolgen.

## Fazit
Der Funktionsblock `AX_TO_AW` ist ein einfacher, aber nützlicher Konverter, der die Kopplung zwischen BOOL- und WORD-Adaptern ermöglicht. Dank der direkten Durchschleifung von Ereignis und Daten bei minimalem Overhead eignet er sich hervorragend für Schnittstellenanpassungen in verteilten Automatisierungssystemen. Seine Composite-Struktur macht ihn transparent, leicht verständlich und einfach in bestehende Projekte integrierbar.