# AQ_TO_AB


![AQ_TO_AB](./AQ_TO_AB.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AQ_TO_AB` dient der Konvertierung eines AQ-Adapters (Quarter Byte) in einen AB-Adapter (BYTE). Er ermöglicht die nahtlose Verbindung von Komponenten, die unterschiedliche Adapter-Schnittstellen verwenden, indem er die Signale unverändert durchleitet. Der Baustein ist als reiner „Durchschleif“-FB realisiert, der keine Datenmanipulation vornimmt.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der FB besitzt keine expliziten Ereignis-Eingänge auf oberster Ebene. Die Ereignisübertragung erfolgt über die Adapter-Schnittstellen.

### **Ereignis-Ausgänge**
Der FB besitzt keine expliziten Ereignis-Ausgänge auf oberster Ebene. Die Ereignisübertragung erfolgt über die Adapter-Schnittstellen.

### **Daten-Eingänge**
Der FB besitzt keine expliziten Daten-Eingänge auf oberster Ebene. Die Datenübertragung erfolgt über die Adapter-Schnittstellen.

### **Daten-Ausgänge**
Der FB besitzt keine expliziten Daten-Ausgänge auf oberster Ebene. Die Datenübertragung erfolgt über die Adapter-Schnittstellen.

### **Adapter**
| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AQ` | IN | Eingang (Socket) | AQ-Adapter als Eingangsschnittstelle für Quarter-Byte-Daten |
| `adapter::types::unidirectional::AB` | OUT | Ausgang (Plug) | AB-Adapter als Ausgangsschnittstelle für BYTE-Daten |

## Funktionsweise
Der Baustein verbindet intern die Ereignis- und Datenkanäle des Eingangsadapters `IN` direkt mit den entsprechenden Kanälen des Ausgangsadapters `OUT`. Konkret werden folgende Verbindungen hergestellt:
- Ereignisverbindung: `IN.E1` → `OUT.E1`
- Datenverbindung: `IN.D1` → `OUT.D1`

Somit werden alle ankommenden Ereignisse und Daten des AQ-Adapters unverändert an den AB-Adapter weitergegeben. Der FB selbst führt keine Verarbeitung oder Konvertierung der Nutzdaten durch – er fungiert ausschließlich als Schnittstellenadapter.

## Technische Besonderheiten
- **Unidirektionaler Datenfluss:** Der FB unterstützt nur eine Richtung (AQ → AB).
- **Keine Zustandsänderung:** Da keinerlei Logik oder Speicher vorhanden ist, handelt es sich um einen rein kombinatorischen Baustein.
- **Einfaches Durchschleifen:** Die Implementierung beschränkt sich auf zwei direkte Verbindungen im FBNetwork.
- **Adapter-Konvertierung:** Der FB erlaubt die Integration von AQ-kompatiblen Komponenten in ein System, das AB-Adapter erwartet, ohne dass Anpassungen der angeschlossenen Bausteine nötig sind.

## Zustandsübersicht
Der FB besitzt keinen Zustandsautomaten. Das Verhalten ist deterministisch: Jedes eingehende Ereignis triggert sofort das entsprechende Ausgangsereignis, und jeder eingehende Datenwert wird unverzögert zum Ausgang weitergeleitet.

## Anwendungsszenarien
- **Systemintegration:** Verbindung eines Sensormoduls mit AQ-Schnittstelle an eine Steuerung, die AB-Adapter verwendet.
- **Protokollumsetzung:** Nutzung in Bibliotheken, um unterschiedliche Adaptertypen kompatibel zu machen.
- **Testumgebungen:** Einsatz als einfacher Adapter in Testaufbauten, um Schnittstellen anzupassen.

## Vergleich mit ähnlichen Bausteinen
- **AB_TO_AQ:** Führt die umgekehrte Konvertierung (AB → AQ) durch.
- **AQ_TO_BYTE_EXT:** Ein hypothetischer FB, der zusätzlich Datenkonvertierungen (z. B. Skalierung, Formatierung) vornimmt, während `AQ_TO_AB` ausschließlich die Schnittstelle wechselt.
- **Generische Adapter-Wrapper:** Andere Plattformen bieten oft generische Konvertierungsbausteine, die jedoch komplexer konfiguriert werden müssen. `AQ_TO_AB` ist spezialisiert und dadurch sehr leichtgewichtig.

## Fazit
Der Funktionsblock `AQ_TO_AB` bietet eine schlanke und effiziente Lösung zur Adapterkonvertierung von AQ auf AB. Durch seine einfache Durchschleif-Struktur ist er zuverlässig, ressourcenschonend und ideal für Situationen, in denen lediglich die Schnittstellenform geändert werden muss, ohne die Signale zu beeinflussen. Er eignet sich besonders für modulare Systeme mit unterschiedlichen Adapterstandards.