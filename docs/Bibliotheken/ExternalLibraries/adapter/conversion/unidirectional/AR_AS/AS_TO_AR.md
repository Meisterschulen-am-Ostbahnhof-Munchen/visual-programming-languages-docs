# AS_TO_AR


![AS_TO_AR](./AS_TO_AR.svg)

* * * * * * * * * *

## Einleitung  
Der Funktionsblock `AS_TO_AR` ist ein Composite-Baustein, der einen unidirektionalen Adapter vom Typ **AS** (SINT) auf einen Adapter vom Typ **AR** (REAL) umsetzt. Er wird eingesetzt, um eine logische Verbindung zwischen Komponenten herzustellen, die auf unterschiedlichen Datentypen basieren – speziell von einem vorzeichenbehafteten 8‑Bit‑Integer (SINT) zu einer Gleitkommazahl (REAL).

## Schnittstellenstruktur

### **Ereignis-Eingänge**  
Der Baustein besitzt keine eigenständigen Ereignis-Eingänge. Ereignisse werden ausschließlich über den integrierten Adapter **AS_IN** empfangen.  
- **AS_IN.E1** – Ereignis vom angeschlossenen SINT‑Adapter.

### **Ereignis-Ausgänge**  
Ereignisse werden über den integrierten Adapter **AR_OUT** weitergegeben.  
- **AR_OUT.E1** – Ereignis zum angeschlossenen REAL‑Adapter.

### **Daten-Eingänge**  
Daten werden ausschließlich über den Adapter **AS_IN** bereitgestellt.  
- **AS_IN.D1** – Datenwert vom Typ **SINT** (vorzeichenbehafteter 8‑Bit‑Integer).

### **Daten-Ausgänge**  
Daten werden ausschließlich über den Adapter **AR_OUT** ausgegeben.  
- **AR_OUT.D1** – Datenwert vom Typ **REAL** (Gleitkommazahl).

### **Adapter**  
| Typ | Name | Richtung | Kommentar |
|-----|------|----------|-----------|
| `adapter::types::unidirectional::AS` | **AS_IN** | Socket | Eingangsadapter für SINT‑Daten |
| `adapter::types::unidirectional::AR` | **AR_OUT** | Plug | Ausgangsadapter für REAL‑Daten |

## Funktionsweise  
Der `AS_TO_AR`‑Baustein verhält sich als reine Typkonvertierungs‑Durchleitung. Im enthaltenen Funktionsnetzwerk werden das Ereignis `AS_IN.E1` direkt mit `AR_OUT.E1` und der Datenwert `AS_IN.D1` direkt mit `AR_OUT.D1` verbunden. Die eigentliche Umwandlung von **SINT** in **REAL** erfolgt implizit durch die Adapter‑Definitionen des jeweiligen Typs. Der Baustein selbst führt keine zusätzliche Logik oder Berechnung aus.

## Technische Besonderheiten  
- **Composite‑Baustein**: Die Konvertierung wird allein durch die Verschaltung von Adaptern im Funktionsnetzwerk realisiert. Eine eigene Zustandsmaschine (ECC) ist nicht vorhanden.  
- **Paket‑Zugehörigkeit**: Der Baustein ist im Paket `adapter::conversion::unidirectional` eingeordnet.  
- **Keine Datenhaltung**: Alle Werte werden instantan weitergeleitet; der Baustein besitzt kein internes Gedächtnis.  
- **Implizite Typumwandlung**: Die Konvertierung von Ganzzahl (SINT) in Gleitkommazahl (REAL) findet in der Peripherie der Adapter‑Typen statt.  

## Zustandsübersicht  
Der `AS_TO_AR`‑Baustein besitzt keinen Zustandsautomaten (ECC). Das Verhalten ist rein kombinatorisch und beschränkt sich auf die direkte Weiterleitung von Ereignissen und Daten.

## Anwendungsszenarien  
- Anbindung eines Sensors, der seine Messwerte als SINT‑Adapter bereitstellt, an eine Verarbeitungskomponente, die REAL‑Adapter erwartet.  
- Übergang zwischen unterschiedlichen '4diac'‑Adaptertypen in heterogenen Steuerungsprojekten.  
- Vorbereitung von Werten für mathematische Operatoren oder Visualisierungskomponenten, die REAL‑Eingänge benötigen.

## Vergleich mit ähnlichen Bausteinen  
- **AR_TO_AS** – Führt die umgekehrte Konvertierung von REAL nach SINT durch.  
- **Allgemeine Typkonverter** (z. B. `INT_TO_REAL`) arbeiten auf Ebene einzelner Datenports, während `AS_TO_AR` ganze Adapterschnittstellen umsetzt.  
- Der Baustein bietet keine einstellbaren Parameter (z. B. Rundungsmodi); eine spezifischere Konvertierung müsste über separate Funktionsbausteine realisiert werden.

## Fazit  
`AS_TO_AR` ist ein einfacher, aber nützlicher Composite‑Baustein zur Adapter‑Typkonvertierung von SINT auf REAL. Er ermöglicht die verlustfreie Integration von Komponenten mit unterschiedlichen Datentypen in durchgängigen Steuerungsabläufen und zeichnet sich durch geringe Komplexität und direkte Durchleitung aus.