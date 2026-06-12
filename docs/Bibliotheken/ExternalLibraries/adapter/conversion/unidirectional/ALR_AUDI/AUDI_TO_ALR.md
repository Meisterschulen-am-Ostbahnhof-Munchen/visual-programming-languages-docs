# AUDI_TO_ALR


![AUDI_TO_ALR](./AUDI_TO_ALR.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AUDI_TO_ALR** ist ein Composite-Baustein, der einen unidirektionalen Adapter vom Typ **AUDI** (Datentyp `UDINT`) in einen Adapter vom Typ **ALR** (Datentyp `LREAL`) umwandelt. Er dient als einfaches Bindeglied zwischen zwei unterschiedlichen Adapter-Schnittstellen und ermöglicht so die Integration von Komponenten, die auf unterschiedlichen Datenformaten basieren.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Kommentar |
|------|-----------|
| `AUDI_IN.E1` | Ereignis-Eingang des AUDI-Adapters (durchgeschliffen zum ALR-Ausgang) |

### **Ereignis-Ausgänge**

| Name | Kommentar |
|------|-----------|
| `ALR_OUT.E1` | Ereignis-Ausgang des ALR-Adapters (übernommen vom AUDI-Eingang) |

### **Daten-Eingänge**

| Name | Datentyp | Kommentar |
|------|----------|-----------|
| `AUDI_IN.D1` | `UDINT` | Daten-Eingang des AUDI-Adapters (wird direkt als LREAL weitergegeben) |

### **Daten-Ausgänge**

| Name | Datentyp | Kommentar |
|------|----------|-----------|
| `ALR_OUT.D1` | `LREAL` | Daten-Ausgang des ALR-Adapters (Wert vom AUDI-Eingang, typkonvertiert) |

### **Adapter**

| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| Socket (Eingang) | `AUDI_IN` | `adapter::types::unidirectional::AUDI` | Nimmt die UDINT-Daten und das zugehörige Ereignis entgegen |
| Plug (Ausgang) | `ALR_OUT` | `adapter::types::unidirectional::ALR` | Stellt die konvertierten LREAL-Daten und das Ereignis bereit |

## Funktionsweise

Der Funktionsblock leitet das eingehende Ereignis `E1` vom Socket `AUDI_IN` direkt an den Plug `ALR_OUT` weiter. Gleichzeitig wird der Datenwert `D1` (Typ `UDINT`) unverändert auf den Ausgangsdatenkanal `D1` (Typ `LREAL`) übertragen. Die tatsächliche Typkonvertierung von `UDINT` nach `LREAL` erfolgt innerhalb der verwendeten Adapter-Schnittstellen; der Composite-Baustein selbst führt keine arithmetische oder logische Umformung durch, sondern fungiert als reine Verdrahtungshilfe.

## Technische Besonderheiten

- **Reine Adapter-Durchleitung:** Der Baustein enthält keinerlei eigene Logik oder Zustandsautomaten – er verbindet lediglich die gleichnamigen Kanäle der beiden Adapter.
- **Unidirektionale Kommunikation:** Sowohl der AUDI- als auch der ALR-Adapter unterstützen nur eine Datenflussrichtung, was den Einsatz in einfachen Sensor-/Aktor-Schnittstellen oder bei der Kopplung unterschiedlicher Protokolle erleichtert.
- **Keine Typkonvertierung im Baustein:** Die Wandlung von `UDINT` auf `LREAL` wird von der Infrastruktur der Adapter übernommen. Der Entwickler muss sicherstellen, dass die verwendeten Adapter-Implementierungen die nötige Konvertierung bereitstellen.

## Zustandsübersicht

Als Composite-Baustein besitzt `AUDI_TO_ALR` keinen eigenen Zustandsautomaten. Sein Verhalten ist rein kombinatorisch: Ein eingehendes Ereignis wird sofort – ohne Verzögerung oder Bedingung – an den Ausgang weitergegeben.

## Anwendungsszenarien

- **Integration von UDINT-basierten Sensoren** (z.B. Drehgeber mit 32‑Bit‑Zählern) in ein LREAL‑verarbeitendes Regelungssystem.
- **Adapterbrücke** zwischen verschiedenen Bibliotheken oder Komponenten, die auf unterschiedlichen Datentypen basieren, aber einheitliche Adapter-Schnittstellen verwenden.
- **Prototypenentwicklung** und schnelle Verkabelung von Adaptern, ohne eine separate Konvertierungslogik erstellen zu müssen.

## Vergleich mit ähnlichen Bausteinen

Im 4diac‑Ökosystem existieren einfache Konvertierungsbausteine wie `INT_TO_REAL` oder `UDINT_TO_LREAL`, die meist als Basic‑ oder Service‑FBs realisiert sind. Der vorliegende Composite‑FB unterscheidet sich dadurch, dass er nicht den Datenwert selbst konvertiert, sondern zwei komplette Adapter miteinander verbindet. Er ist daher spezifisch für Umgebungen, die auf Adapter‑Schnittstellen angewiesen sind, und nicht für reine Datenfluss‑Konvertierung gedacht.

## Fazit

`AUDI_TO_ALR` ist ein minimaler, aber nützlicher Composite‑Baustein, um zwei unidirektionale Adapter mit unterschiedlichen Datentypen zu koppeln. Er reduziert den Verdrahtungsaufwand und macht die Typanpassung explizit sichtbar. Der Baustein sollte immer dann eingesetzt werden, wenn eine saubere Trennung zwischen Adapter‑Typen und eine einfache Durchleitung von Ereignis und Daten gewünscht ist.