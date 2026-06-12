# AR_TO_ALR


![AR_TO_ALR](./AR_TO_ALR.svg)

* * * * * * * * * *
## Einleitung

Composite-Funktionsblock zur Konvertierung eines AR-Adapters (REAL) in einen ALR-Adapter (LREAL). Er dient der Anpassung von Datenformaten in IEC‑61499‑2‑Umgebungen und ist unter der Eclipse Public License 2.0 lizenziert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**  

| Name | Beschreibung |
|------|--------------|
| **E1** (von AR_IN) | Ereignis zur Auslösung der Datenübergabe |

### **Ereignis-Ausgänge**  

| Name | Beschreibung |
|------|--------------|
| **E1** (von ALR_OUT) | Ereignis, das nach erfolgreicher Konvertierung ausgegeben wird |

### **Daten-Eingänge**  

| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| **D1** (von AR_IN) | REAL | 32‑Bit Gleitkommazahl |

### **Daten-Ausgänge**  

| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| **D1** (von ALR_OUT) | LREAL | 64‑Bit Gleitkommazahl |

### **Adapter**

- **ALR_OUT** (Plug): Typ `adapter::types::unidirectional::ALR` – LREAL‑Ausgangsadapter  
- **AR_IN** (Socket): Typ `adapter::types::unidirectional::AR` – REAL‑Eingangsadapter  

## Funktionsweise

Der Baustein verbindet die Adapterschnittstellen direkt. Ein eingehendes Ereignis an `AR_IN.E1` wird sofort an `ALR_OUT.E1` weitergeleitet. Gleichzeitig wird der Datenwert `AR_IN.D1` (REAL) nach `ALR_OUT.D1` (LREAL) kopiert, wobei die Laufzeitumgebung eine implizite Typkonvertierung durchführt. Es existiert kein Zustandsautomat; die Funktion ist rein kombinatorisch.

## Technische Besonderheiten

- Composite‑FB ohne eigene Logik (kein ECC)  
- Verwendung unidirektionaler Adapter gemäß IEC 61499‑2  
- Automatische Typumwandlung durch die 4diac‑Laufzeit (z. B. 4diac‑ide)  
- Paket: `adapter::conversion::unidirectional`

## Zustandsübersicht

Keine Zustände vorhanden – der FB besitzt keinen Ausführungs-Zustandsautomaten.

## Anwendungsszenarien

- Anschluss eines REAL‑liefernden Sensors an eine Komponente, die LREAL erwartet  
- Migration bestehender REAL‑Adapter auf LREAL mit höherer Genauigkeit  
- Schnittstellenanpassung in heterogenen Automatisierungssystemen  

## Vergleich mit ähnlichen Bausteinen

Ähnliche Bausteine existieren für andere Typkonvertierungen (z. B. `LREAL_TO_REAL`, `INT_TO_REAL`). Der vorliegende Block ist speziell auf die unidirektionalen Adapter `AR` und `ALR` zugeschnitten und erfordert keine eigene Implementierungslogik.

## Fazit

Der `AR_TO_ALR`‑Baustein ermöglicht eine einfache und effiziente Umwandlung von REAL‑ zu LREAL‑Adapterdaten. Als Composite‑FB realisiert, nutzt er die direkte Verbindung der Adapterschnittstellen und bietet so hohe Performance bei minimaler Latenz.